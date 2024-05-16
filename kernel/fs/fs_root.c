/* KallistiOS ##version##

   kernel/arch/dreamcast/fs/fs_root.c
   Copyright (C) 2023 Colton Pawielski

   Based on fs_dlsocket.c and related files
   Copyright (C) 2007, 2008, 2012, 2013, 2015 Lawrence Sebald
   Copyright (C) 2003 Megan Potter

*/


#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <stdio.h>

#include <kos/mutex.h>
#include <kos/fs.h>

static mutex_t mutex;
static int root_readdir_count = 0;

static void *root_open(struct vfs_handler *vfs, const char *fn, int mode) {
    int locked;
    (void)vfs;
    root_readdir_count = 0;
    printf("Opening root: %08X\n", fn);
    // for(int i = 0; i < strlen(fn); i++)
    //     printf("%02X\n", fn[i]);

    if (strlen(fn) == 0 || strcmp(fn, "/") == 0) {
        printf("Opening root Dir\n");
        return (void *) 0xDEAD5000;
    }

    return (void *) NULL;
}

static int root_close(void *hnd) {
    int fd = (int) hnd, locked;
    printf("Close root!: %d\n", fd);

    return 0;
}

static dirent_t root_readdir_dirent;
static dirent_t *root_readdir(void *hnd) {
    nmmgr_handler_t *nmhnd;
    nmmgr_list_t    *nmhead;
    int         cnt;

    printf("root_readdir: %08X\n", hnd);

    nmhead = nmmgr_get_list();

    cnt = (int) root_readdir_count;

    LIST_FOREACH(nmhnd, nmhead, list_ent) {
        if(nmhnd->type != NMMGR_TYPE_VFS)
            continue;

        if(!(cnt--))
            break;
    }

    if(nmhnd == NULL) {
        return NULL;
    }

    root_readdir_dirent.attr = O_DIR;
    root_readdir_dirent.size = 0;

    strcpy(root_readdir_dirent.name, nmhnd->pathname);

    printf("name: %s\n", root_readdir_dirent.name);

    root_readdir_count++;
    return &root_readdir_dirent;
}

static int root_stat(vfs_handler_t *vfs, const char *fn, struct stat *rv,
                     int flag) {
    (void)vfs;
    (void)fn;
    (void)rv;
    (void)flag;

    memset(rv, 0, sizeof(struct stat));

    rv->st_dev = (dev_t)('v' | ('f' << 8) | ('s' << 16));

    printf("root_stat: %s\n", fn);

    rv->st_mode = S_IFDIR | S_IRUSR | S_IRGRP | S_IROTH;
    rv->st_size = 0;
    rv->st_blksize = 1;
    rv->st_nlink = 5;
    return 0;
}


static int root_fcntl(void *h, int cmd, va_list ap) {
    int rv = -1;
    printf("FCNTL root: %X\t%08X\n", h, cmd);
    (void)h;
    (void)ap;
    switch(cmd) {
        case F_SETFD:
            printf("F_SETFD\n");
            rv = 0;
            break;
        case F_GETFL:
            rv = O_RDONLY | O_NONBLOCK;
            break;
        default:
            errno = EINVAL;
    }

    return rv;
}

static int root_rewinddir(void *h) {
    int rv = -1;
    printf("Rewind Dir root!\n");

    return rv;
}

/* VFS handler */
vfs_handler_t root_vfs_handler = {
    /* Name handler */
    {
        "/",      /* name */
        0,      /* tbfi */
        0x00010000, /* Version 1.0 */
        0,      /* flags */
        NMMGR_TYPE_VFS,
        NMMGR_LIST_INIT
    },

    0, NULL,    /* no cache, privdata */

    root_open,
    root_close,
    NULL,               /* root_read */
    NULL,               /* root_write */
    NULL,               /* root_seek */
    NULL,               /* root_tell */
    NULL,               /* root_total */
    root_readdir,
    NULL,               /* ioctl */
    NULL,               /* root_rename */
    NULL,               /* root_unlink */
    NULL,               /* mmap */
    NULL,               /* complete */
    root_stat,
    NULL,               /* mkdir */
    NULL,               /* rmdir */
    root_fcntl,
    NULL,               /* poll */
    NULL,               /* link */
    NULL,               /* symlink */
    NULL,               /* seek64 */
    NULL,               /* tell64 */
    NULL,               /* total64 */
    NULL,               /* readlink */
    root_rewinddir,     /* rewinddir */
    NULL                /* fstat */
};


int fs_root_init(void) {
    printf("fs_root_init();\n");
    mutex_init(&mutex, MUTEX_TYPE_NORMAL);
    nmmgr_handler_add(&root_vfs_handler.nmmgr);
    return 0;
}

void fs_root_shutdown(void) {
    printf("fs_root_shutdown();\n");
    mutex_destroy(&mutex);
    return nmmgr_handler_remove(&root_vfs_handler.nmmgr);
}