/*
Cubesat Space Protocol - A small network-layer protocol designed for Cubesats
Copyright (C) 2012 Gomspace ApS (http://www.gomspace.com)
Copyright (C) 2012 AAUSAT3 Project (http://aausat3.space.aau.dk) 

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <csp/arch/csp_clock.h>
#include <csp/csp_debug.h>
#include <time.h>

__attribute__((weak)) void csp_clock_get_time(csp_timestamp_t * time) {
		DateTime_t datetime;

	    if (RTC_GetTimeAndDate(&datetime) != HAL_OK) {
	        time->tv_sec = 0;
	        time->tv_nsec = 0;
	        return;
	    }

	    struct tm t;
	    t.tm_sec  = datetime.sTime.Seconds;
	    t.tm_min  = datetime.sTime.Minutes;
	    t.tm_hour = datetime.sTime.Hours;
	    t.tm_mday = datetime.sDate.Date;
	    t.tm_mon  = datetime.sDate.Month - 1;  // struct tm months: 0–11
	    t.tm_year = datetime.sDate.Year+100; // HAL gives years since 2000, struct tm since 1900

	    // Convert to seconds since epoch (UNIX time)
	    time_t unix_time = mktime(&t);
	    time->tv_sec = unix_time;
	    time->tv_nsec = 0;
}

__attribute__((weak)) int csp_clock_set_time(const csp_timestamp_t * time) {
		DateTime_t datetime;
	    time_t unix_time = (time_t)time->tv_sec;

	    struct tm *t = localtime(&unix_time);

	    datetime.sTime.Hours   = t->tm_hour;
	    datetime.sTime.Minutes = t->tm_min;
	    datetime.sTime.Seconds = t->tm_sec;

	    datetime.sDate.Date  = t->tm_mday;
	    datetime.sDate.Month = t->tm_mon + 1;
	    datetime.sDate.Year = t->tm_year - 100; // convert back to 2000-based year

	    uint32_t y = t->tm_year - 100;
	    uint32_t m = t->tm_mon;
	    uint32_t d = t->tm_mday;
	    if (m < 3) { m += 12; y--; }
	    datetime.sDate.WeekDay = ((d + 2*m + 3*(m+1)/5 + y + y/4 - y/100 + y/400 + 1) % 7) + 1;

	    HAL_StatusTypeDef status = RTC_SetTimeAndDate(&datetime);
	    return (status == HAL_OK) ? CSP_ERR_NONE : CSP_ERR_NOTSUP;

}
