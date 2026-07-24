/*
 * rtc_srv.c
 *
 *  Created on: Aug 29, 2025
 *      Author: veverka
 */

#include "rtc_srv.h"

extern RTC_HandleTypeDef hrtc;

// TODO: Init correct clock source
HAL_StatusTypeDef RTC_Init()
{
    /** Configure RTC */
    hrtc.Instance = RTC;
    hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
    hrtc.Init.AsynchPrediv = 127;   // LSE typical
    hrtc.Init.SynchPrediv = 248;    // LSE typical
    hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
    hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
    hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
    //hrtc.Init.BinMode = RTC_BINARY_NONE;

    /*if (HAL_RTC_Init(&hrtc) != HAL_OK)
    {
        Error_Handler();
    }*/

    return HAL_RTC_Init(&hrtc);
}

HAL_StatusTypeDef RTC_SetTimeAndDate(DateTime_t *datetime)
{
    RTC_TimeTypeDef sTime = datetime->sTime;
    RTC_DateTypeDef sDate = datetime->sDate;

    HAL_StatusTypeDef retval = HAL_OK;

    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;

    if ((retval = HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN)) != HAL_OK)
    {
        //Error_Handler();
    	return retval;
    }

    if ((retval = HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN)) != HAL_OK)
    {
        //Error_Handler();
    	return retval;
    }

    return retval;
}

HAL_StatusTypeDef RTC_GetTimeAndDate(DateTime_t *datetime)
{
    HAL_StatusTypeDef retval = HAL_OK;

    if ((retval = HAL_RTC_GetTime(&hrtc, &datetime->sTime, RTC_FORMAT_BIN))) {
        return retval;
    }
    retval = HAL_RTC_GetDate(&hrtc, &datetime->sDate, RTC_FORMAT_BIN);  // Must be called after GetTime

    return retval;
}
