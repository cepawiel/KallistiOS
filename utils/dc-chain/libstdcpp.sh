#!/bin/bash

set -x
set -e

TC_ROOT=/opt/toolchains/dc_lto/kos/utils/dc-chain

cd $TC_ROOT/build-gcc-sh-elf-13.2.0-pass2/sh-elf/libstdc++-v3
rm config.cache
make clean

$TC_ROOT/gcc-13.2.0/libstdc++-v3/configure \
    --srcdir=../../../gcc-13.2.0/libstdc++-v3 \
    --cache-file=./config.cache \
    --enable-multilib \
    --enable-cxx-flags='-g3 -O0 -fno-inline' \
    --with-cross-host=x86_64-pc-linux-gnu \
    --prefix=/opt/toolchains/dc_lto/sh-elf \
    --with-newlib \
    --disable-libssp \
    --enable-threads=kos \
    --enable-checking=release \
    --with-multilib-list=m4-single-only \
    --with-endian=little \
    --with-cpu=m4-single-only \
    --enable-languages=c,c++,lto,objc,obj-c++ \
    --program-transform-name=sh-elf- \
    --disable-option-checking \
    --with-target-subdir=sh-elf \
    --build=x86_64-pc-linux-gnu \
    --host=sh-elf \
    --target=sh-elf

make CXXFLAGS='-g3 -fno-inline -O0' -j26 
make CXXFLAGS='-g3 -fno-inline -O0' install