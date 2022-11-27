/* KallistiOS ##version##

   newlib_exit.c
   Copyright (C)2004 Dan Potter

*/

#include <arch/arch.h>

void exit(int code) {
    arch_exit(code);
}
