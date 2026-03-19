/*
 * LTC2983_config.h
 *
 *  Created on: Feb 17, 2026
 *      Author: vrnak
 */

#ifndef INC_LTC2983_CONFIG_H_
#define INC_LTC2983_CONFIG_H_

#include "LTC2983.h"
#include "ltc/ltc_defines.h"


void app_init_LTC2983(void);

/* A public function to set a measurement mode */
void LTC2983_AppSetMode(LTC2983_AppMeasurementMode command);
/* A public function to get a measurement mode */
LTC2983_AppMeasurementMode LTC2983_AppGetMode(void);
/* A public function to get a state */
LTC2983_AppMeasurementMode LTC2983_AppGetState(void);
/* A public function to get a error code */
LTC2983_AppMeasurementMode LTC2983_AppGetError(void);
/* A public function to set frequency of continuous measurement */
void LTC2983_AppSetFrequency(uint32_t frequency);
/* A public function to get frequency of continuous measurement */
uint32_t LTC2983_AppGetFrequency(void);
/* A public function to get the state of a measurement */
uint8_t LTC2983_AppIsResultReady(void);
/* A public function to get the newest results */
uint8_t LTC2983_AppGetResults(LTC2983ConvResult_t * results);

#endif /* INC_LTC2983_CONFIG_H_ */
