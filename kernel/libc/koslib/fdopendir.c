/* KallistiOS ##version##

   newlib_fdopendir.c
   Copyright (C)2023 Colton Pawielski

*/

#include <dirent.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <kos/fs.h>
#include <stdio.h>

DIR *
fdopendir(int fd)
{
    printf("fdopendir %X\n", fd);
	// if (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
	// 	return (NULL);

    // DIR * ret = calloc(sizeof(DIR), 1);

    // char buffer[256] = {};
    
    // close(fd);

    // printf("buffer: %s\n", buffer);

    // int a = fs_open(buffer, O_DIR | O_RDONLY);
    // printf("a: %X\n", a);



    DIR * newd = calloc(0, sizeof(DIR));

    if(!newd) {
        printf("failed to alloc mem for fdopendir\n");
        errno = ENOMEM;
        return NULL;
    }

    newd->fd = fd;
    // newd->d_ent.d_ino = 0;
    // newd->d_ent.d_off = 0;
    // newd->d_ent.d_reclen = 0;
    newd->d_ent.d_type = DT_DIR;
    // sprintf(newd->d_ent.d_name, "/");
    // int len = sprintf(&ret->d_ent.d_name, "%s", "");
    // printf("fdopendir return: %08X\n", newd);
    return newd;
    
    // return (_opendir_common(fd));
    // printf("fdopendir\n");

    
    // file_t fd = fs_open("/", O_DIR);
    // printf("fd: %X\n", fd);



    // ret->fd = 1;
    // sprintf(ret->d_ent.d_name, "/");
    // ret->d_ent.d_type = 4;
    // ret->d_ent.d_reclen = 2;
    // ret->d_ent.d_type = 0;
    // printf("fdopendir return: %08X\n", ret);
    // return ret;

}