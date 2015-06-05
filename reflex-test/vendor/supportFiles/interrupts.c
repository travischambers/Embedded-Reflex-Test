// Set of independent routines to setup all of the interrupts supported by the hardware
// as configured.

#include <stdio.h>
#include "interrupts.h"
#include "xscugic.h"                  // Includes for the interrupt controller.
#include "xscutimer.h"                // Includes for the private timer of the ARM.
#include "xsysmon.h"                  // Includes for the system monitor (contains the XADC).
#include "../../src/leds.h"           // Easy LED access functions can be found here.
#include "globalTimer.h" // global timer routines aid in measuring time.
//#include "intervalTimer.h"


// The sysmon runs off the bus-clock when accessed via the AXI_XADC IP.
// This default will allow nearly a 26 Mhz clock which is the maximum frequency to achieve 1 megasamples
// because a single conversion requires 26 clock cycles.

// Set this constant to determine the period between interrupts.
// The private timer clock is 1/2 the processor frequency, default processor freq.
// for ZYBO is 650 MHz. The default is set for timer interrupts to occur at 100 kHz rate.
#define ZYBO_BUS_CLOCK (XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ / 2)
#define PRIVATE_TIMER_PRESCALER_DEFAULT 0
#define PRIVATE_TIMER_LOAD_VALUE_DEFAULT 3249  // Provides a 10 us interrupt period.
#define PRIVATE_TIMER_TICKS_PER_HEART_BEAT PRIVATE_TIMER_TICKS_PER_SECOND / 8
#define PRIVATE_TIMER_TICKS_PER_ADC_SAMPLE 1

// ****************** These #defines enable/disable certain functionality ********************************

#define HEARTBEAT_TOGGLES_PER_SECOND 8     // How many times the LED LD4 heartbeat toggle off and on per second.
#define INTERRUPTS_ENABLE_ADC_DATA_CAPTURE  // Comment out to disable ADC sample capture to queue.

// ****************** end of #define enable/disable section **********************************************

// ******************* Place the various handles and instance pointers here. *****************************
static XScuGic_Config *GicConfig;    // The configuration parameters of the controller.
static XScuGic InterruptController;  // Pointer to the Xilinx-provided interrupt controller routine.
static XScuTimer_Config *ConfigPtr;  // Pointer to the ARM private timer.
static XScuTimer TimerInstance;      // The timer instance (allows access to timer registers).
static XSysMon_Config *xSysMonConfig;// Handle to the SysMon.
static XSysMon xSysMonInst;          // Instance of the system monitor (to access AXI_XADC registers).

// *********************************** Globals Start ****************************************
volatile int interrupts_isrFlagGlobal = 0;
// *********************************** Globals End   ****************************************

// The sysmon (XADC) runs off the bus-clock when accessed via the AXI_XADC IP (as is done here).
// This default will allow nearly a 26 Mhz clock which is the maximum frequency to achieve 1 megasamples
// because a single conversion requires 26 clock cycles.
#define XADC_CLOCK_DIVIDER 4  // 100 MHz bus clock divided by 4 is 25 MHz.

// Assumes that you are connected to auxiliary port 14: pins JA1 (P) and JA7 (N) on the ZYBO board.
#define XADC_AUX_CHANNEL_14 XSM_CH_AUX_MAX-1

// *********************** Place globals (to this file) and their accessors here *************************

u32 heartBeatTimer = 0;                                           // Used to blink an LED while the program is running.
u32 isrInvocationCount = 0;                                       // Keep track of number of times ISR is called.

u32 privateTimerPrescaler = PRIVATE_TIMER_PRESCALER_DEFAULT;      // Keep track of the private-timer prescaler value
u32 privateTimerLoadValue = PRIVATE_TIMER_LOAD_VALUE_DEFAULT;     // Keep track of the private-timer load value.
// For convenience, compute the number of ticks per second based upon the above values.
u32 privateTimerTicksPerSecond = ZYBO_BUS_CLOCK /((privateTimerPrescaler+1) * (privateTimerLoadValue+1));
// Compute the number of ticks per heart-beat toggle.
u32 privateTimerTicksPerHeartbeat = ZYBO_BUS_CLOCK /((privateTimerPrescaler+1) * (privateTimerLoadValue+1));

// User can set the load value on the private timer.
// Also updates ticks per heart beat so that the LD4 heart-beat toggle rate remains constant.
void interrupts_setPrivateTimerLoadValue(u32 loadValue) {
  XScuTimer_LoadTimer(&TimerInstance, loadValue);
  privateTimerLoadValue = loadValue;
  // Formula derived from the ARM documentation on the private timer (4.1.1)
  privateTimerTicksPerHeartbeat = (ZYBO_BUS_CLOCK /((privateTimerPrescaler+1) * (privateTimerLoadValue+1))) / HEARTBEAT_TOGGLES_PER_SECOND;
}

// User can set the prescaler on the private timer.
// Also updates ticks per heart beat so that the LD4 heart-beat toggle rate remains constant.
void interrupts_setPrivateTimerPrescalerValue(u32 prescalerValue) {
  XScuTimer_LoadTimer(&TimerInstance, prescalerValue);
  privateTimerPrescaler = prescalerValue;
  // Formula derived from the ARM documentation on the private timer (4.1.1)
  privateTimerTicksPerHeartbeat = (ZYBO_BUS_CLOCK /((privateTimerPrescaler+1) * (privateTimerLoadValue+1))) / HEARTBEAT_TOGGLES_PER_SECOND;
}

u32 interrupts_isrInvocationCount() {return isrInvocationCount;}  // Functional accessor for isrInvocationCount.
// Accessor to retrieve the number of times the ISR was invoked (same as count of timer ticks).
u32 interrupts_getPrivateTimerTicksPerSecond() {return ZYBO_BUS_CLOCK /((privateTimerPrescaler+1) * (privateTimerLoadValue+1));}
u32 totalXadcSampleCount = 0;
u32 interrupts_getTotalXadcSampleCount() {return totalXadcSampleCount;}

// Keeps track of the total number of ADC conversions.
u32 totalEocCount;
u32 interrupts_getTotalEocCount() {return totalEocCount;}

// If ADC capture is enabled, put the samples into this queue.
// queue.h must also be present.
#ifdef QUEUE_H_
  #ifdef INTERRUPTS_ENABLE_ADC_DATA_CAPTURE
    #define ADC_DATA_QUEUE_SIZE 100
    queue_t *adcDataQueue1;
  #endif
#endif
bool adcDataCaptureFlag = false;   // ADC capture is disabled by default.

// **********************End globals and accessors section. *************************

// Reads the private counter on the Arm core.
u32 interrupts_getPrivateTimerCounterValue(void) {
  return XScuTimer_GetCounterValue(&TimerInstance);
}

// This will keep track of the number of EOC conversion interrupts have been detected.
static int eocCount = 0;
// True if EOC interrupts have been enabled.
bool eocCountInterruptFlag = false;
// Accessor.
int interrupts_getEocCount() {
  if (!eocCountInterruptFlag){
    printf("getEocCount(): eoc interrupt has not been enabled.\n\r");
  }
  return eocCount;
}

#ifdef QUEUE_H_
// ADC queue accessor.
queue_t *getAdcDataQueue1() {
  return adcDataQueue1;
}
#endif


// Enable EOC interrupt in the SysMon.
int interrupts_enableSysMonEocInts() {
  XSysMon_IntrEnable(&xSysMonInst, XSM_IPIXR_EOC_MASK);
  eocCountInterruptFlag = true;
  return 0;
}

// Disable EOC interrupt in the SysMon.
int interrupts_disableSysMonEocInts() {
  XSysMon_IntrDisable(&xSysMonInst, XSM_IPIXR_EOC_MASK);
  eocCountInterruptFlag = false;
  return 0;
}

// Count timer ticks to know when to get a sample from the XADC.
volatile int sampleTimerTicks = PRIVATE_TIMER_TICKS_PER_ADC_SAMPLE;
int ledValue = 0;

//int adcCaptureArrayIndex=0;                // Use to store ADC values to an array.
#define ADC_VALUE_CAPTURE_ARRAY_SIZE 2000        // Size of capture array.
int adcValues[ADC_VALUE_CAPTURE_ARRAY_SIZE];      // sysmon ISR stores values in here.

// Used to detect if the GIC has been properly initialized before use.
static bool initGicFlag = false;


// Assumes that you are connected to auxiliary port 14.
#define XADC_AUX_CHANNEL_14 XSM_CH_AUX_MAX-1

// Default xSysMon ISR just clears the interrupt.
// Watch out, the code currently indiscriminately clears out all interrupts from the XADC.
void sysMonIsr(void *CallBackRef) {
  u32 intrStatusValue;
  XSysMon *xSysMonPtr = (XSysMon *)CallBackRef;
  // Get the interrupt status from the device and check the value.
  intrStatusValue = XSysMon_IntrGetStatus(xSysMonPtr);
  if (intrStatusValue & XSM_SR_EOC_MASK)  // inc eocCount if the EOC status bit is set.
    totalEocCount++;
  XSysMon_IntrClear(xSysMonPtr, intrStatusValue);  // Clear out ALL XADC interrupt.
}

// ******************************* Start Timer ISR *********************************
void timerIsr(void* callBackRef){
#ifdef INTERVALTIMER_H_  // Enable interval timing when this is defined.
    intervalTimer_start(0);
#endif

    isrInvocationCount++;  // Just keep track of the count for now.
    interrupts_isrFlagGlobal = 1;
    // Put the code that you want executed on a timer interrupt below here.

//  This will capture ADC samples into the queue if defined.
#ifdef INTERRUPTS_ENABLE_ADC_DATA_CAPTURE
  sampleTimerTicks--;
  if (sampleTimerTicks == 0) {
    totalXadcSampleCount++;
#ifdef QUEUE_H_
      queue_overwritePush(adcDataQueue1, XSysMon_GetAdcData(&xSysMonInst, XADC_AUX_CHANNEL_14) >> 4);
#endif
    sampleTimerTicks = PRIVATE_TIMER_TICKS_PER_ADC_SAMPLE;
  }
#endif

#ifdef INTERVALTIMER_H_   // Enable interval timing when this is defined.
  intervalTimer_stop(0);
#endif

  XScuTimer_ClearInterruptStatus(&TimerInstance);
}

// ****************************** End Timer ISR *************************************

// Xilinx calls the Axi XADC module the SysMon (System Monitor).
// This sets up the XADC to continuously sample on aux. channel 14 in single channel mode, unipolar.
int initSysMonInterrupts() {
  int status;
  xSysMonConfig = XSysMon_LookupConfig(XPAR_AXI_XADC_0_DEVICE_ID);
  status = XSysMon_CfgInitialize(&xSysMonInst, xSysMonConfig, xSysMonConfig->BaseAddress);
  if (status != XST_SUCCESS) {
	printf("XSysMon initialize failed!!!\n\r");
    return XST_FAILURE;
  }
  status = XSysMon_SelfTest(&xSysMonInst);
  if (status != XST_SUCCESS) {
	printf("XSysMon self-test failed!!!\n\r");
    return XST_FAILURE;
  }
  XSysMon_SetAdcClkDivisor(&xSysMonInst, XADC_CLOCK_DIVIDER);
//  int adcClkDivisor = XSysMon_GetAdcClkDivisor(&xSysMonInst);
//  printf("Default ADC clock divisor: %d.\n\r", adcClkDivisor);
  XSysMon_SetSequencerMode(&xSysMonInst, XSM_SEQ_MODE_SINGCHAN); // Single-channel mode (channel 14).
  status =  XSysMon_SetSingleChParams(&xSysMonInst, XADC_AUX_CHANNEL_14,
						              FALSE, FALSE, FALSE);
  if(status != XST_SUCCESS) {
	printf("XSysMon set single channel parameters failed!!!\n\r");
    return XST_FAILURE;
  }
 // XSysMon_SetAvg(&xSysMonInst, XSM_AVG_16_SAMPLES); //Don't use, reduces conversion rate by 16.
  XSysMon_SetAlarmEnables(&xSysMonInst, 0x0);  // Disable all alarms.
//  // Set alarm threshold registers for VCCINT to min and max so alarm does not occur.
//  XSysMon_SetAlarmThreshold(&xSysMonInst, XSM_ATR_VCCINT_UPPER, 0xFFFF);
//  XSysMon_SetAlarmThreshold(&xSysMonInst, XSM_ATR_VCCINT_LOWER, 0x0);
//  // Connect the xSysMon ISR to the GIC ISR.
  status = XScuGic_Connect(&InterruptController,
		                    XPAR_FABRIC_AXI_XADC_0_IP2INTC_IRPT_INTR,
		                   (Xil_ExceptionHandler) sysMonIsr,
		                   (void *) &xSysMonInst);
  if (status != XST_SUCCESS) {
	print("XScuGic_Connect failed (sysmon).\n\r");
	return status;
  }
  // Clear out any pending interrupts in the interrupt status register.
  int intrStatus = XSysMon_IntrGetStatus(&xSysMonInst);
  XSysMon_IntrClear(&xSysMonInst, intrStatus);
  // Enable the sysmon interrupt on the GIC (does nothing to the sysmon).
  XScuGic_Enable(&InterruptController, XPAR_FABRIC_AXI_XADC_0_IP2INTC_IRPT_INTR);
  return XST_SUCCESS;
}

// Sets up the timer for periodic interrupts.
int initTimerInterrupts() {
  int status;  // General Xilinx status reporting.
  // Get a handle to the timer.
  ConfigPtr = XScuTimer_LookupConfig(XPAR_XSCUTIMER_0_DEVICE_ID);
  // Init the timer via the handle.
  status = XScuTimer_CfgInitialize(&TimerInstance,
		                           ConfigPtr,
		                           ConfigPtr->BaseAddr);
  if (status != XST_SUCCESS){
	print("XScuTimer_CfgInitialize failed.\n\r");
    return XST_FAILURE;
  }
  status = XScuTimer_SelfTest(&TimerInstance);
  if (status != XST_SUCCESS){
    print("XscuTimer_SelfTest failed.\n\r");
    return status;
  }
  // Connect the timer ISR to the GIC ISR.
  status = XScuGic_Connect(&InterruptController,
		                   XPAR_SCUTIMER_INTR,
		                   (Xil_ExceptionHandler) timerIsr,
		                   (void *) &TimerInstance);
  if (status != XST_SUCCESS) {
	print("XScuGic_Connect failed (timer).\n\r");
	return status;
  }
  // Enable the timer interrupt on the GIC (does nothing to the timer).
  XScuGic_Enable(&InterruptController, XPAR_SCUTIMER_INTR);
  // Enable auto reload mode.
  XScuTimer_EnableAutoReload(&TimerInstance);
  // Load the timer counter preload register.
  // Subtract 1 from the tick count to account for the extra cycle for the counter
  // to transition to zero to generate the interrupt. Page 4-2 of ARM Cortex A9 Mpcore r4p1
//  int loadValue = PRIVATE_TIMER_LOAD_VALUE;
//  int prescalar = XScuTimer_GetPrescaler(&TimerInstance);
//  printf("interrupt.c - load value: %d\n\r", loadValue);
//  printf("interrupt.c - prescalar value: %d\n\r", prescalar);
  XScuTimer_SetPrescaler(&TimerInstance, PRIVATE_TIMER_PRESCALER_DEFAULT);
  XScuTimer_LoadTimer(&TimerInstance, PRIVATE_TIMER_LOAD_VALUE_DEFAULT);
//  prescalar = XScuTimer_GetPrescaler(&TimerInstance);
//  printf("interrupt.c - prescalar value: %d\n\r", prescalar);
//  print("setupTimerInterrupts exited successfully.\n\r");
  return XST_SUCCESS;
}

// Inits all interrupts, which means:
// 1. Sets up the interrupt routine for ARM (GIC ISR) and does all necessary initialization.
// 2. Initializes all supported interrupts and connects their ISRs to the GIC ISR.
// 3. Enables the interrupts at the GIC, but not at the device itself.
// 4. Pretty much does everything but it does not enable the ARM interrupts or any of the device global interrupts.
// if printFailedStatusFlag is true, it prints out diagnostic messages if something goes awry.
int interrupts_initAll(bool printFailedStatusFlag) {
  int status;  // General Xilinx status.
  // Lookup the GIC device and get its handle.
  GicConfig = XScuGic_LookupConfig(XPAR_SCUGIC_SINGLE_DEVICE_ID);
  if (!GicConfig) {
	if (printFailedStatusFlag)
  	  print("XScuGic_LookupConfig failed.\n\r");
	return 1;
  }
  // Init the GIC interrupt controller via its handle.
  status = XScuGic_CfgInitialize(&InterruptController, GicConfig, GicConfig->CpuBaseAddress);
  if (status != XST_SUCCESS) {
	if (printFailedStatusFlag)
	  print("XScuGic_CfgInitialize failed.\n\r");
	return 1;
  }
  Xil_ExceptionInit();  // Initialize the interrupt system.
  // Connect the GIC interrupt handler (provided by Xilinx) to the GIC interrupt.
  // You will connect timerIsr, sysMonIsr, etc., to this interrupt hander.
  Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT,
							   (Xil_ExceptionHandler) XScuGic_InterruptHandler,
							   &InterruptController);
    print("setupGICInterruptController exited successfully.\n\r");

  u8 adcPriority;
  u8 timerPriority;
  u8 adcTrigger;
  u8 timerTrigger;
  XScuGic_GetPriorityTriggerType(&InterruptController, XPAR_SCUTIMER_INTR,
   					&timerPriority, &timerTrigger);
//   printf("timer priority: %x\n\r", timerPriority);
//   printf("timer trigger: %x\n\r", timerTrigger);

   XScuGic_GetPriorityTriggerType(&InterruptController, XPAR_FABRIC_AXI_XADC_0_IP2INTC_IRPT_INTR,
  					&adcPriority, &adcTrigger);
//  printf("xadc priority: %x\n\r", adcPriority);
//  printf("xadc trigger: %x\n\r", adcTrigger);

   // Try setting the XADC to a higher priority than the timer (less is higher priority).
   adcPriority = timerPriority - 10;
//   adcTrigger = 3;  // Changing to rising edge doesn't work - the EOC interrupt count drops way down.
   XScuGic_SetPriorityTriggerType(&InterruptController, XPAR_FABRIC_AXI_XADC_0_IP2INTC_IRPT_INTR,
     					adcPriority, adcTrigger);
   // Verify that the setting changed.
   XScuGic_GetPriorityTriggerType(&InterruptController, XPAR_FABRIC_AXI_XADC_0_IP2INTC_IRPT_INTR,
   					&adcPriority, &adcTrigger);
//   printf("updated xadc priority: %x\n\r", adcPriority);
//   printf("updated xadc trigger: %x\n\r", adcTrigger);

  // init the timer interrupts.
  initTimerInterrupts();
  // Init the SysMon interrupts (XADC).
  initSysMonInterrupts();
  initGicFlag = true;

  // Enable capture of ADC values in queue if queue.h has been included.
#ifdef QUEUE_H_
// Enables capture of ADC value to queue.
  queue_init(adcDataQueue1, ADC_DATA_QUEUE_SIZE);
#endif

  return 0;
}

// This enables overall ARM interrupts.
// Checks the init flag to make sure that the user has init'd the GIC.
int interrupts_enableArmInts() {
  if (initGicFlag) {
    Xil_ExceptionEnable();
    return 0;
  } else {
    printf("Error: Must call initGIC before enableArmInterrupts()\n\r.");
    return 1;
  }
}

// This disables overall ARM interrupts.
// Checks the init flag to make sure that the user has init'd the GIC.
int interrupts_disableArmInts() {
  if (initGicFlag) {
    Xil_ExceptionDisable();
    return 0;
  } else {
    printf("Error: Must call initGIC before disableArmInterrupts()\n\r.");
    return 1;
  }
}

int interrupts_enableTimerGlobalInts() {
  XScuTimer_EnableInterrupt(&TimerInstance);
  return 0;
}
int interrupts_disableTimerGlobalInts(){
  XScuTimer_DisableInterrupt(&TimerInstance);
  return 0;
}

// Call this to change the timer load value from the default.
int setTimerInterval(int loadValue) {
  XScuTimer_LoadTimer(&TimerInstance, loadValue);
  return 0;
}

int interrupts_startArmPrivateTimer() {
  XScuTimer_Start(&TimerInstance);
  return 0;
}

int interrupts_stopArmPrivateTimer() {
  XScuTimer_Stop(&TimerInstance);
  return 0;
}

// Default is to enable EOC (end of conversion) interrupts.
int interrupts_enableSysMonGlobalInts(){
  XSysMon_IntrGlobalEnable(&xSysMonInst);
  return 0;
}

int disableSysMonGlobalInterrupts(){
  XSysMon_IntrGlobalDisable(&xSysMonInst);
  return 0;
}





