/* KallistiOS ##version##

   newlib_times.c
   Copyright (C) 2004 Dan Potter
   Copyright (C) 2022 Lawrence Sebald

*/

#include <errno.h>
#include <sys/reent.h>
#include <sys/times.h>
#include <arch/timer.h>

int _times_r(struct _reent * re, struct tms * tmsbuf) {
    (void)re;

    if(tmsbuf) {
        /* Conveniently, CLOCKS_PER_SEC is 1000, so we can just use the
           millisecond timer. */
        tmsbuf->tms_utime = (clock_t)timer_ms_gettime64();
        tmsbuf->tms_stime = 0;
        tmsbuf->tms_cutime = 0;
        tmsbuf->tms_cstime = 0;

        return (int)tmsbuf->tms_utime;
    }

    re->_errno = EFAULT;
    return -1;
}
