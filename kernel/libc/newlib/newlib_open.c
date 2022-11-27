/* KallistiOS ##version##

   newlib_open.c
   Copyright (C)2004 Dan Potter

*/

// #include <kos/fs.h>
#include <assert.h>
#include <stdio.h>

extern int fs_open(const char *, int);

int open(const char * f, int flags, ...) {
    // (void)mode;
    return fs_open(f, flags);
}
