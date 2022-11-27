/* KallistiOS ##version##

   lock_common.c
   Copyright (C)2004 Dan Potter
   Copyright (C)2022 Colton Pawielski

*/



#include <assert.h>
#include <arch/irq.h>
#include <arch/spinlock.h>
#include <sys/lock.h>

struct __lock {
    void *owner;
    int nest;
    volatile int lock;
};


#ifndef __SINGLE_THREAD__

struct __lock __lock___sinit_recursive_mutex;
struct __lock __lock___sfp_recursive_mutex;
struct __lock __lock___atexit_recursive_mutex;
struct __lock __lock___at_quick_exit_mutex;
struct __lock __lock___malloc_recursive_mutex;
struct __lock __lock___env_recursive_mutex;
struct __lock __lock___tz_mutex;
struct __lock __lock___dd_hash_mutex;
struct __lock __lock___arc4random_mutex;

void __retarget_lock_init (_LOCK_T *lock)
{
    spinlock_init(lock);
}

void __retarget_lock_init_recursive(_LOCK_T *lock)
{
    (*lock)->owner = NULL;
    (*lock)->nest = 0;
    spinlock_init(&(*lock)->lock);
}

void __retarget_lock_close(_LOCK_T lock) {}

void __retarget_lock_close_recursive(_LOCK_T lock) {}

void __retarget_lock_acquire (_LOCK_T lock)
{
    spinlock_lock(&lock->lock);
}

void __retarget_lock_acquire_recursive (_LOCK_T lock)
{
    int old;
    int iscur;

    // Check to see if we already own it. If so, everything is clear
    // to incr nest. Otherwise, we can safely go on to do a normal
    // spinlock wait.
    old = irq_disable();
    iscur = lock->owner == thd_current;
    irq_restore(old);

    if(iscur) {
        lock->nest++;
        return;
    }

    // It doesn't belong to us. Wait for it to come free.
    spinlock_lock(&lock->lock);

    // We own it now, so it's safe to init the rest of this.
    lock->owner = thd_current;
    lock->nest = 1;
}

int __retarget_lock_try_acquire(_LOCK_T lock)
{
    assert_msg(0, "We don't support try_acquire");
    return 1;
}

int __retarget_lock_try_acquire_recursive(_LOCK_T lock)
{
    assert_msg(0, "We don't support try_acquire");
    return 1;
}

void __retarget_lock_release (_LOCK_T lock)
{
    spinlock_unlock(&lock->lock);
}

void __retarget_lock_release_recursive (_LOCK_T lock)
{
    // Check to see how much we own it.
    if(lock->nest == 1) {
        lock->owner = NULL;
        lock->nest = -1;
        spinlock_unlock(&lock->lock);
    }
    else {
        lock->nest--;
    }
}

#endif // __SINGLE_THREAD__