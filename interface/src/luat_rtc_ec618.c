/*
 * Copyright (c) 2022 OpenLuat & AirM2M
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "luat_base.h"
#include "luat_rtc.h"
#include "common_api.h"
#include "time.h"
#include "osasys.h"
#include "mw_aon_info.h"

int luat_rtc_set(struct tm *tblock){
    uint32_t Timer1 = (((tblock->tm_year)<<16)&0xfff0000) | (((tblock->tm_mon)<<8)&0xff00) | ((tblock->tm_mday)&0xff);
    uint32_t Timer2 = ((tblock->tm_hour<<24)&0xff000000) | ((tblock->tm_min<<16)&0xff0000) | ((tblock->tm_sec<<8)&0xff00) | ((0)&0xff);
    uint32_t ret = OsaTimerSync(0, SET_LOCAL_TIME, Timer1, Timer2);
    if (ret == 0){
        mwAonSetUtcTimeSyncFlag(1);
    }
    return 0;
}

int luat_rtc_get(struct tm *tblock){
    utc_timer_value_t *timeUtc = OsaSystemTimeReadUtc();
    if(timeUtc != NULL){
        gmtime_ec((time_t *)&timeUtc->UTCsecs,tblock);
        tblock->tm_year += 1900;
        return 0;
    }
    return -1;
}

#ifdef __LUATOS__

int luat_rtc_timer_start(int id, struct tm *tblock){
    return -1;
}

int luat_rtc_timer_stop(int id){
    return -1;
}

#endif


