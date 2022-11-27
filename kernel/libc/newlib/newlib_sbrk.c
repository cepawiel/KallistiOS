/* KallistiOS ##version##

   newlib_sbrk.c
   Copyright (C)2004 Dan Potter

*/

// #include <sys/reent.h>
#include <arch/arch.h>

// checkout incr type, seems suspicious
char * sbrk(ptrdiff_t incr) {
    return (char *)mm_sbrk((unsigned long)incr);
}
