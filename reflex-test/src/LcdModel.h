#ifndef LCDMODEL_H_
#define LCDMODEL_H_

#include "ReflexTestData.h"

/**
 * Initialization function for the LCD Model.
 */
void LcdModel_Init(void);

/**
 * Called by the Conductor to get the current state from ReflexTestData
 * @return  returns the current state
 */
ReflexTest_st LcdModel_GetCurrentState(void);

/**
 * Gets the average response time for the player's last round.
 * @return The average response time for the player's last round.
 */
double LcdModel_GetAverageResponseTime();

/**
 * Gets the minimum response time for the player's last round.
 * @return The minimum response time for the player's last round.
 */
double LcdModel_GetMinResponseTime();

/**
 * Gets the maximum response time for the player's last round.
 * @return The maximum response time for the player's last round.
 */
double LcdModel_GetMaxResponseTime();

/**
 * The 10 highest scores since the board has been turned on.
 * @return A pointer to the array containing 10 highest scores.
 */
double* LcdModel_GetHighScores();

#endif /* LCDMODEL_H_ */
