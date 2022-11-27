/* KallistiOS ##version##

   newlib_env_lock.c
   Copyright (C)2004 Dan Potter

*/

// These calls can be nested.
// #include <sys/reent.h>
// #include <sys/lock.h>

// static _LOCK_T lock = __LOCK_INIT_RECURSIVE;

// void __env_lock(struct _reent * r) {
//     (void)r;
//     __newlib_lock_acquire_recursive(&lock);
// }

// void __env_unlock(struct _reent * r) {
//     (void)r;
//     __newlib_lock_release_recursive(&lock);
// }


