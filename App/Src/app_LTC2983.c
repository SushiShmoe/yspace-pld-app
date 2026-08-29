/*
 * app_LTC2983.c
 *
 *  Created on: Feb 17, 2026
 *      Author: vrnak
 */

#include "app_LTC2983.h"
#include "main.h"
#include "LTC2983.h"
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "task.h"
#include "ltc/ltc_defines.h"
#include "LTC2983_config.h"


/*
 *
 * PRIVATE DEFINES
 *
 */

// Default measurement frequency
#define MEASUREMENT_FREQUENCY_DEFAULT 1000

// Flag defines
#define MEASUREMENT_START_FLAG 	0x01
#define MEASUREMENT_HW_FLAG 	0x02
#define MEASUREMENT_DONE_FLAG 	0x04
#define CONFIG_DONE_FLAG 		0x08

// Max loop iterations while waiting for response from LTC2983
#define MAX_CONFIG_ITERATIONS 100

// Max wait time for measurement
#define MEASUREMENT_TIMEOUT_MS 2000




/*
 *
 * EXTERN IMPORTS
 *
 */


/* Driver handles */
extern LTC2983Handle_t ltc1Handle;
extern LTC2983HandleRegistry_t handleRegistry;

osThreadId_t LTCTaskHandle;
static osMutexId_t resultsMutex;

typedef struct {
	volatile LTC2983_AppMeasurementMode mode;
    LTC2983_AppMeasureReady resultStatus;
    uint8_t targetChannel;
    uint32_t continuous_frequency;
    LTC2983_AppTaskState_t appTaskState;
    LTC2983_AppErrorState_t appErrorState;
    bool configDone;
    LTC2983ConvResult_t results[TEMP_RSLT_COUNT];
} LTC2983_App_t;

LTC2983_App_t appHandle = {
		.mode = STOP_MODE,
		.resultStatus = RESULT_NOT_READY,
		.targetChannel = 4,
		.continuous_frequency = MEASUREMENT_FREQUENCY_DEFAULT,

		.appTaskState = LTC2983_APPSTATE_NONE,

		.appErrorState = LTC2983_APPERROR_NONE,

		.configDone = false,

		.results = {{0}},
};



/*
 *
 * PRIVATE FUNCTIONS
 *
 */


/* Function to handle waiting for config */
static void _LTC2983_AppConfigWait(){
	uint8_t waitIteration = 0;
	while (ltc1Handle.State->Status != LTC2983_DRIVER_STATUS_NONE \
			&& ltc1Handle.State->Status != LTC2983_DRIVER_STATUS_COMPLETE \
			&& ltc1Handle.State->Status != LTC2983_DRIVER_STATUS_ERROR \
			&& waitIteration < MAX_CONFIG_ITERATIONS
			){

	    osThreadFlagsWait(CONFIG_DONE_FLAG, osFlagsWaitAny, 10);
	    waitIteration++;
	}

	if (ltc1Handle.State->Status == LTC2983_DRIVER_STATUS_ERROR || waitIteration == MAX_CONFIG_ITERATIONS - 1){
		appHandle.appTaskState = LTC2983_APPSTATE_ERROR;
		appHandle.appErrorState = LTC2983_APPERROR_CONFIG;
	}
}

/* A state machine to handle callbacks */
static void _LTC2983_AppTaskState(LTC2983Handle_t* const ltcHandle){
	(void)ltcHandle;

	switch (appHandle.appTaskState){
		case LTC2983_APPSTATE_STARTUP:
		case LTC2983_APPSTATE_WRITE_GLOBAL_CONFIG:
		case LTC2983_APPSTATE_READ_GLOBAL_CONFIG:
		case LTC2983_APPSTATE_WRITE_MUX_CONFIG:
		case LTC2983_APPSTATE_READ_MUX_CONFIG:
		case LTC2983_APPSTATE_WRITE_MEAS_MULTIMASK_CONFIG:
		case LTC2983_APPSTATE_READ_MEAS_MULTIMASK_CONFIG:
		case LTC2983_APPSTATE_WRITE_CHANNEL_CONFIG:
		case LTC2983_APPSTATE_READ_CHANNEL_CONFIG:{
			osThreadFlagsSet(LTCTaskHandle, CONFIG_DONE_FLAG);
		} break;
		case LTC2983_APPSTATE_MEASUREMENT_WAIT:{
			osThreadFlagsSet(LTCTaskHandle, MEASUREMENT_HW_FLAG);
		} break;
		case LTC2983_APPSTATE_MEASUREMENT_READ:{
			osThreadFlagsSet(LTCTaskHandle, MEASUREMENT_DONE_FLAG);
		} break;
        default:
            break;
	}
}

/* A function to fire start up */
static void _LTC2983_StartUpCycle(){
	appHandle.appTaskState = LTC2983_APPSTATE_STARTUP;

	LTC2983_StartUp(&ltc1Handle);

	uint8_t waitIteration = 0;
	while (ltc1Handle.State->Status != LTC2983_DRIVER_STATUS_NONE && waitIteration < MAX_CONFIG_ITERATIONS) {
		osThreadFlagsWait(CONFIG_DONE_FLAG, osFlagsWaitAny, 10);

		if (!ltc1Handle.State->StartupDone) {
			LTC2983_StartUp(&ltc1Handle);
		}

		osDelay(10);
		waitIteration++;
	}

	if (ltc1Handle.State->Status == LTC2983_DRIVER_STATUS_ERROR || waitIteration == MAX_CONFIG_ITERATIONS){
		appHandle.appTaskState = LTC2983_APPSTATE_ERROR;
		appHandle.appErrorState = LTC2983_APPERROR_STARTUP;
	}

	osThreadFlagsClear(CONFIG_DONE_FLAG);
}

#define RUN_CONFIG_SETUP(state, config_func) \
    do { \
        appHandle.appTaskState = (state); \
        config_func(&ltc1Handle); \
        _LTC2983_AppConfigWait(); \
        if (appHandle.appTaskState == LTC2983_APPSTATE_ERROR) return; \
    } while(0)

static void _LTC2983_SetupSequence(void) {
    LTC2983_AppMeasurementMode last_mode = LTC2983_AppGetMode();
    appHandle.mode = STARTUP_MODE;

    _LTC2983_StartUpCycle();
    if (appHandle.appTaskState == LTC2983_APPSTATE_ERROR) {
        return;
    }

    RUN_CONFIG_SETUP(LTC2983_APPSTATE_WRITE_GLOBAL_CONFIG, LTC2983_WriteGlobalConfigReg);
    RUN_CONFIG_SETUP(LTC2983_APPSTATE_READ_GLOBAL_CONFIG, LTC2983_ReadGlobalConfigReg);
    RUN_CONFIG_SETUP(LTC2983_APPSTATE_WRITE_MUX_CONFIG, LTC2983_WriteMuxConfigDelay);
    RUN_CONFIG_SETUP(LTC2983_APPSTATE_WRITE_MEAS_MULTIMASK_CONFIG, LTC2983_WriteMeasMultiChannelsMask);
    RUN_CONFIG_SETUP(LTC2983_APPSTATE_WRITE_CHANNEL_CONFIG, LTC2983_WriteChannelsAssignmentData);
    RUN_CONFIG_SETUP(LTC2983_APPSTATE_READ_CHANNEL_CONFIG, LTC2983_ReadChannelsAssignmentData);

	appHandle.mode = last_mode;
	appHandle.configDone = true;
	osThreadFlagsClear(MEASUREMENT_START_FLAG | MEASUREMENT_HW_FLAG | MEASUREMENT_DONE_FLAG | CONFIG_DONE_FLAG);
}

static void _LTC2983_WriteResults(){
	osMutexAcquire(resultsMutex, osWaitForever);

    for(uint8_t i = 0; i < TEMP_RSLT_COUNT; i++) {
        appHandle.results[i] = ltc1Handle.Results->Results[i];
    }

	appHandle.resultStatus = RESULT_READY;
	osMutexRelease(resultsMutex);
}


/* Generic function to make a measurement */
static void _LTC2983_MeasurementSequence(LTC2983Channel_t channel){
	appHandle.appTaskState = LTC2983_APPSTATE_MEASUREMENT_WAIT;
	LTC2983_Convert(&ltc1Handle, channel);

	uint32_t flags = osThreadFlagsWait(MEASUREMENT_HW_FLAG, osFlagsWaitAny, MEASUREMENT_TIMEOUT_MS);

	if (ltc1Handle.State->Status == LTC2983_DRIVER_STATUS_ERROR){
		appHandle.appTaskState = LTC2983_APPSTATE_ERROR;
		appHandle.appErrorState = LTC2983_APPERROR_CONVERT;
		return;
	}

	if (flags == osFlagsErrorTimeout) {
		appHandle.appTaskState = LTC2983_APPSTATE_ERROR;
		appHandle.appErrorState = LTC2983_APPERROR_CONVERT_TIMEOUT;
		return;
	}

	appHandle.appTaskState = LTC2983_APPSTATE_MEASUREMENT_READ;
	LTC2983_ReadTemperatureResults(&ltc1Handle, channel);

	flags = osThreadFlagsWait(MEASUREMENT_DONE_FLAG, osFlagsWaitAny, MEASUREMENT_TIMEOUT_MS);

	if (flags == osFlagsErrorTimeout) {
		appHandle.appTaskState = LTC2983_APPSTATE_ERROR;
		appHandle.appErrorState = LTC2983_APPERROR_READ_TIMEOUT;
		return;
	}

	if (ltc1Handle.State->Status == LTC2983_DRIVER_STATUS_ERROR){
		appHandle.appTaskState = LTC2983_APPSTATE_ERROR;
		appHandle.appErrorState = LTC2983_APPERROR_READ;
		return;
	}

	_LTC2983_WriteResults();
}



/*
 *
 * PUBLIC FUNCTIONS
 *
 */

/* A public function to set a measurement mode */
void LTC2983_StartSingleMeasurement(LTC2983Channel_t channel);
void LTC2983_StartContinuousMeasurement(LTC2983Channel_t channel);
void LTC2983_StopMeasurement();

void LTC2983_AppSetMode(LTC2983_AppMeasurementMode mode){
	switch (mode){
	  case SINGLE_MODE:{
		  LTC2983_StartSingleMeasurement(0);
	  } break;
	  case CONTINUOUS_MODE:{
		  LTC2983_StartContinuousMeasurement(0);
	  } break;
	  case STOP_MODE:{
		  if (LTC2983_AppGetMode() != STOP_MODE){
			  LTC2983_StopMeasurement();
		  }
	  } break;
      case STARTUP_MODE:
          break;
	}
}

/* A public function to get a measurement mode */
LTC2983_AppMeasurementMode LTC2983_AppGetMode(void) {
	return appHandle.mode;
}

/* A public function to get a state */
LTC2983_AppTaskState_t LTC2983_AppGetState(void) {
	return appHandle.appTaskState;
}

/* A public function to get a error code */
LTC2983_AppErrorState_t LTC2983_AppGetError(void) {
	return appHandle.appErrorState;
}

/* A public function to set frequency of continuous measurement */
void LTC2983_AppSetFrequency(uint32_t frequency) {
	appHandle.continuous_frequency = frequency;
}

/* A public function to get frequency of continuous measurement */
uint32_t LTC2983_AppGetFrequency(void) {
	return appHandle.continuous_frequency;
}

/* A public function to get the state of a measurement */
uint8_t LTC2983_AppIsResultReady(void) {
    return (appHandle.resultStatus == RESULT_READY) ? 1 : 0;
}

/* A public function to get the newest results */
uint8_t LTC2983_AppGetResults(LTC2983ConvResult_t *results) {
	if (!LTC2983_AppIsResultReady()){
		return 0;
	}

    osMutexAcquire(resultsMutex, osWaitForever);

    for(uint8_t i = 0; i < TEMP_RSLT_COUNT; i++) {
        results[i] = appHandle.results[i];
    }
    appHandle.resultStatus = RESULT_NOT_READY;
    osMutexRelease(resultsMutex);

    return 1;
}

static void _LTC2983_Manager(void);

void LTC2983_Setup(void *argument) {
    LTC2983_Init(&ltc1Handle);
    LTC2983_RegisterLTC2983HandleRegistry(&handleRegistry);
    LTC2983_RegisterTaskDoneCallback(&ltc1Handle, _LTC2983_AppTaskState);
    _LTC2983_SetupSequence();
    _LTC2983_Manager();
}

/* Function to start a single measurements. */
void LTC2983_StartSingleMeasurement(LTC2983Channel_t channel){
    taskENTER_CRITICAL();

	appHandle.resultStatus = RESULT_NOT_READY;

	appHandle.targetChannel = channel;

	appHandle.mode = SINGLE_MODE;

	taskEXIT_CRITICAL();

	osThreadFlagsSet(LTCTaskHandle, MEASUREMENT_START_FLAG);
}

/* A function to start continuous measurement. */
void LTC2983_StartContinuousMeasurement(LTC2983Channel_t channel){
    taskENTER_CRITICAL();

	appHandle.resultStatus = RESULT_NOT_READY;

	appHandle.targetChannel = channel;

	appHandle.mode = CONTINUOUS_MODE;

	taskEXIT_CRITICAL();

	osThreadFlagsSet(LTCTaskHandle, MEASUREMENT_START_FLAG);
}

/* A function to stop continuous measurement. */
void LTC2983_StopMeasurement(){
    taskENTER_CRITICAL();
	appHandle.mode = STOP_MODE;

	osThreadFlagsSet(LTCTaskHandle, MEASUREMENT_START_FLAG);
	taskEXIT_CRITICAL();
}

/* A function to stop continuous measurement. */
void LTC2983_ChangeRsenseValue(float rsenseVal){
    taskENTER_CRITICAL();
	appHandle.mode = STOP_MODE;

	osThreadFlagsSet(LTCTaskHandle, MEASUREMENT_START_FLAG);

	if (rsenseVal == 0){
		rsenseVal = DEFAULT_RSENSE_VALUE;
	}

	ltc1Handle.ChannelConfigs->Configs[0].Data = LTC2983_SENSOR_TYPE__SENSE_RESISTOR | (uint32_t)(rsenseVal * 1024);

	taskEXIT_CRITICAL();
}

/* Main function to handle the LTC2983 thread. */
static void _LTC2983_Manager(){
	while (1){
		switch (appHandle.mode){
			case STOP_MODE: {
				LTC2983_Sleep(&ltc1Handle);
				appHandle.configDone = false;

				osThreadFlagsClear(MEASUREMENT_START_FLAG | MEASUREMENT_HW_FLAG | MEASUREMENT_DONE_FLAG | CONFIG_DONE_FLAG);
				osThreadFlagsWait(MEASUREMENT_START_FLAG, osFlagsWaitAny, osWaitForever);

				appHandle.resultStatus = RESULT_NOT_READY;
				_LTC2983_SetupSequence();
			} break;
			case CONTINUOUS_MODE:{
				if (appHandle.configDone && appHandle.appTaskState != LTC2983_APPSTATE_ERROR){
					_LTC2983_MeasurementSequence(appHandle.targetChannel);

					if (appHandle.appTaskState == LTC2983_APPSTATE_ERROR){
						appHandle.mode = STOP_MODE;
					}

					osThreadFlagsWait(MEASUREMENT_START_FLAG, osFlagsWaitAny, appHandle.continuous_frequency);
				}
				else{
					appHandle.mode = STOP_MODE;
				}
			} break;
			case SINGLE_MODE:{
				if (appHandle.configDone && appHandle.appTaskState != LTC2983_APPSTATE_ERROR){
					appHandle.resultStatus = RESULT_NOT_READY;
					_LTC2983_MeasurementSequence(appHandle.targetChannel);

					appHandle.mode = STOP_MODE;
				}
			} break;
            case STARTUP_MODE:
                break;
		}
	}
}



/*
 *
 * APP FUNCTIONS
 *
 */

osThreadId_t LTCTaskHandle;
const osThreadAttr_t LTCTask_attributes = {
    .name = "LTC2983Task",
    .priority = (osPriority_t)osPriorityNormal,
    .stack_size = 1024 * 4
};

void app_init_LTC2983(void) {
    if (resultsMutex == NULL) {
        resultsMutex = osMutexNew(NULL);
    }

    LTCTaskHandle = osThreadNew(LTC2983_Setup, NULL, &LTCTask_attributes);

    if (resultsMutex == NULL) {
        appHandle.appTaskState = LTC2983_APPSTATE_ERROR;
        appHandle.appErrorState = LTC2983_APPERROR_MUTEX;
    }
}