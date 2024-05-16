
#include <kos/fs.h>
#include <assert.h>
#include <stdio.h>
#include <fcntl.h>

// int openat(int dirfd, const char *name, int flags, int mode)
// {
//     // printf("openat!!!\n");
//     printf("openat: %d\t%s\n", dirfd, name);
//     // printf("name: %s\n", name);
//     // printf("flags: %08X\n", flags);
//     // printf("mode: %08X\n", mode);

//     int kos_flags = 0;
//     if( flags & 0x200000) { // O_DIRECTORY
//         kos_flags |= O_DIR;
//     }
//     // printf("kos_flags: %08X\n", kos_flags);
//     // handle direct disk access hit flag

//     return fs_openat(dirfd, name, kos_flags, mode);
// }




int openat(int dirfd, const char *name, int flags, int mode) {
    printf("fs_openat fd:%08X flags: %08X name: %s\n", dirfd, flags, name);
    // printf("fs_openat name: %08X\n", name);
    printf("mode: %X\n", mode);
    char buffer[256] = {};

    if (name[0] == "/") {
        sprintf(buffer, "%s", name);
    } else if (dirfd == -2) { // AT_FDCWD
        sprintf(buffer, "%s/%s", fs_getwd(), name);
        if (buffer[0] == '/' && buffer[1] == '/') {
            buffer[1] = '\0';
        }
    } else {
        // pathname is relative to the  directory at dirfd
        sprintf(buffer, "%s", name);
    }
    
    return open(buffer, flags);
}