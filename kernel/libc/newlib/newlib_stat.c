/* KallistiOS ##version##

   newlib_stat.c
   Copyright (C) 2004 Megan Potter
   Copyright (C) 2011, 2013 Lawrence Sebald

*/

#include <unistd.h>
#include <sys/stat.h>
#include <sys/reent.h>
#include <kos/fs.h>
#include <errno.h>
#include <fcntl.h>

static int stat_int(const char *path, struct stat *buf, int flag) {
    int err = errno, rv;
    file_t fp;
    mode_t md;

    dbgio_printf("newlib_stat: %08X\n", path);
    
    dbgio_printf("newlib_stat: %s\t%08X\n", path, flag);
    for(int i =0 ; i < 4; i++) {
        dbgio_printf("[%02X] ", path[i]);
    }
    dbgio_printf("\n");

    if (path[0] == 0) {
        printf("path is empty\n");
        errno = ENOENT;
        return -1;
    }

    /* Try to use the native stat function first... */
    if(!(rv = fs_stat(path, buf, flag)) || errno != ENOSYS)
        return rv;

    dbgio_printf("FS does not support stat, faking\n");
    /* If this filesystem doesn't implement stat, then fake it to get a few
       important pieces... */
    errno = err;
    fp = fs_open(path, O_RDONLY);
    md = S_IFREG;

    /* If we couldn't get it as a file, try as a directory */
    if(fp == FILEHND_INVALID) {
        fp = fs_open(path, O_RDONLY | O_DIR);
        md = S_IFDIR;
    }

    /* If we still don't have it, then we're not going to get it. */
    if(fp == FILEHND_INVALID) {
        errno = ENOENT;
        return -1;
    }

    /* This really doesn't convey all that much information, but it should help
       with at least some uses of stat. */
    buf->st_mode = md;
    buf->st_size = (off_t)fs_total(fp);

    /* Clean up after ourselves. */
    fs_close(fp);

    return 0;
}

int _stat_r(struct _reent *reent, const char *path, struct stat *buf) {
    (void)reent;
    return stat_int(path, buf, 0);
}

int lstat(const char *path, struct stat *buf) {
    return stat_int(path, buf, AT_SYMLINK_NOFOLLOW);
}
