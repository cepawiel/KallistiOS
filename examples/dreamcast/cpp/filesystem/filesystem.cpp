/* KallistiOS ##version##

   filesystem.cpp
   Copyright (C) 2023 Colton Pawielski
*/

#include <vector>
#include <iostream>
#include <cstdint>
#include <malloc.h>
#include <filesystem>

#include <kos/init.h>

KOS_INIT_FLAGS(INIT_MALLOCSTATS);

void printLine(std::string name, int depth) {
    auto pad = [depth]() {
        for(int i = 0; i < depth; i++) {
            printf("  ");
        }
    };

    if (depth == 0) {
        printf("%s\n", name.c_str());
    } else {
        printf("├──%s\n", name.c_str());        
    }
}

void printDirectory(std::filesystem::path dirPath, int depth = 0) {
    printf("\n\nprinting: %s depth %d\n", dirPath.c_str(), depth);
    
    std::error_code ec;
    ec.clear();
    auto status = std::filesystem::status(dirPath, ec);
    printf("ec: %d\n", ec.value());
    printf("ec: %s\n", ec.message().c_str());
    auto type = status.type();
    switch (type) {
        case std::filesystem::file_type::none:
            printf("none\n");
            break;
        case std::filesystem::file_type::not_found:
            printf("not_found\n");
            break;
        case std::filesystem::file_type::regular:
            printf("regular\n");
            break;
        case std::filesystem::file_type::directory:
            printf("directory\n");
            break;
        case std::filesystem::file_type::symlink:
            printf("symlink\n");
            break;
        case std::filesystem::file_type::block:
            printf("block\n");
            break;
        case std::filesystem::file_type::character:
            printf("character\n");
            break;
        case std::filesystem::file_type::fifo:
            printf("fifo\n");
            break;
        case std::filesystem::file_type::socket:
            printf("socket\n");
            break;
        case std::filesystem::file_type::unknown:
            printf("unknown\n");
            break;
        default:
            printf("default %d\n", type);
            break;

    }

    if (!std::filesystem::exists(dirPath)) {
        printf("dirPath does not exist\n");
        return;
    }

    for (auto e : std::filesystem::directory_iterator(dirPath)) {
        printf("e: %08X\n", &e);
        auto t = e.status().type();
        printf("Type: %d\n", t);
        printLine(dirPath, depth);
        if(e.is_directory()) {
            printf("Is Dir: ");
            // printDirectory(e.path(), depth + 1);
        } else if(e.is_block_file()) {
            printf("Is Block: ");
        } else if(e.is_character_file()) {
            printf("Is Char: ");
        } else if(e.is_fifo()) {
            printf("Is FIFO: ");
        } else if(e.is_socket()) {
            printf("Is Socket: ");
        } else if(e.is_symlink()) {
            printf("Is Symlink: ");
        } else if(e.is_regular_file()) {
            printf("Is Regular: ");
        } else {
            printf("Unknown: ");
        }
        const char * path = e.path().c_str();
        printf("[%08X]%s\n", path, path);
    }
}

int main(int argc, char **argv) {
    fclose(stdout);
    stdout = stderr;
    // for (auto &p: std::filesystem::recursive_directory_iterator("/")){
    //     printf("%s\n", p.path().c_str());
    // }

    printDirectory("/");
    printf("Done!\n");
    return 0;
}
