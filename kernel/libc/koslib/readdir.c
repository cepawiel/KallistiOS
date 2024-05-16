/* KallistiOS ##version##

   readdir.c
   Copyright (C)2004 Megan Potter

*/

#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <kos/fs.h>

struct dirent * readdir(DIR * dir) {
    dirent_t * d;

    if(!dir) {
        errno = EBADF;
        return NULL;
    }

    printf("readdir: %08X\n", dir);

    d = fs_readdir(dir->fd);

    if(!d)
        return NULL;

    dir->d_ent.d_ino = 0;
    dir->d_ent.d_off = 0;
    dir->d_ent.d_reclen = 0;

    dir->d_ent.d_type = d->type;
    // dir->d_ent.d_type = DT_DIR;

    // if(d->size < 0)
    //     dir->d_ent.d_type = DT_DIR;
    // else
    //     dir->d_ent.d_type = DT_REG;

    strncpy(dir->d_ent.d_name, d->name, sizeof(dir->d_ent.d_name));

    printf("readdir name: %s\n", dir->d_ent.d_name);

    return &dir->d_ent;
}
