/* KallistiOS ##version##

   newlib_gettimeofday.c
   Copyright (C)2002,2004 Dan Potter

*/

#include <assert.h>
#include <sys/time.h>
#include <time.h>
#include <arch/timer.h>
#include <arch/rtc.h>

/* This is kind of approximate and works only with "localtime" */
int gettimeofday(struct timeval *__restrict tv, void *__restrict tz) {
    uint32  m, s;

    (void)tz;

    assert(tv != NULL);

    timer_ms_gettime(&s, &m);
    tv->tv_sec = rtc_boot_time() + s;
    tv->tv_usec = m * 1000;

    return 0;
}
