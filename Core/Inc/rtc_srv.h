/*
 * rtc_srv.h
 *
 *  Created on: Aug 29, 2025
 *      Author: veverka
 */

#ifndef INC_RTC_SRV_H_
#define INC_RTC_SRV_H_

#include "main.h"

typedef struct
{
    RTC_TimeTypeDef sTime;
    RTC_DateTypeDef sDate;
} DateTime_t;

typedef enum
{
  RTC_LSI = 0,
  RTC_LSE,
  RTC_HSI,
  RTC_HSE
} RTC_Source;

HAL_StatusTypeDef RTC_Init();
HAL_StatusTypeDef RTC_SetTimeAndDate(DateTime_t *datetime);
HAL_StatusTypeDef RTC_GetTimeAndDate(DateTime_t *datetime);

#endif /* INC_RTC_SRV_H_ */
