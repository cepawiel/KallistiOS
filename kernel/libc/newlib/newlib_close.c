/* KallistiOS ##version##

   newlib_close.c
   Copyright (C)2004 Dan Potter

*/

// #include <sys/reent.h>
#include <kos/fs.h>

int close_r(struct _reent * reent, int f) {
    (void)reent;
    return fs_close(f);
}

int close(int f) {
    return fs_close(f);
}