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


/* App taskState to control the flow */
typedef enum {
    LTC2983_APPSTATE_NONE,
    LTC2983_APPSTATE_ERROR,
    LTC2983_APPSTATE_STARTUP,
    LTC2983_APPSTATE_WRITE_GLOBAL_CONFIG,
    LTC2983_APPSTATE_READ_GLOBAL_CONFIG,
    LTC2983_APPSTATE_WRITE_MUX_CONFIG,
    LTC2983_APPSTATE_READ_MUX_CONFIG,
    LTC2983_APPSTATE_WRITE_MEAS_MULTIMASK_CONFIG,
    LTC2983_APPSTATE_READ_MEAS_MULTIMASK_CONFIG,
    LTC2983_APPSTATE_WRITE_CHANNEL_CONFIG,
    LTC2983_APPSTATE_READ_CHANNEL_CONFIG,
    LTC2983_APPSTATE_MEASUREMENT_WAIT,
    LTC2983_APPSTATE_MEASUREMENT_READ,
} LTC2983_AppTaskState_t;


/* --- PUBLIC FUNCTIONS --- */

void app_init_LTC2983(void);

/* A public function to set a measurement mode */
void LTC2983_AppSetMode(LTC2983_AppMeasurementMode mode, int channel);

/* A public function to get a measurement mode */
LTC2983_AppMeasurementMode LTC2983_AppGetMode(void);

/* A public function to get the current state machine state */
LTC2983_AppTaskState_t LTC2983_AppGetState(void);

/* A public function to get an error code */
LTC2983_AppErrorState_t LTC2983_AppGetError(void);

/* A public function to set frequency of continuous measurement */
void LTC2983_AppSetFrequency(uint32_t frequency);

/* A public function to get frequency of continuous measurement */
uint32_t LTC2983_AppGetFrequency(void);

/* A public function to get the state of a measurement */
uint8_t LTC2983_AppIsResultReady(void);

/* A public function to get the newest results */
uint8_t LTC2983_AppGetResults(LTC2983ConvResult_t *results);

void LTC2983_ChangeRsenseValue(float rsenseVal);

/* A function to change a config of a channel. */
int LTC2983_ChangeChnlCfg(uint8_t chnl, uint8_t rst, uint32_t data);

#endif /* INC_LTC2983_CONFIG_H_ */
