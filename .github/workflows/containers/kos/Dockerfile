ARG PRE_NAME=local_dev

FROM ${PRE_NAME}/sh-gcc-patched-kos:latest

# setup env variables

# default to stock dreamcast
# TODO: Support building for Naomi and Modded DC
ENV KOS_ARCH=dreamcast
ENV KOS_SUBARCH=pristine
ENV KOS_PORTS=${KOS_BASE}/../kos-ports

# Make utility
ENV KOS_MAKE=make

# Load utility
# ENV KOS_LOADER=dc-tool -x

# Genromfs utility
ENV KOS_GENROMFS=${KOS_BASE}/utils/genromfs/genromfs

# Compiler prefixes
ENV KOS_CC_BASE=${KOS_BASE}/../sh-elf
ENV KOS_CC_PREFIX=sh-elf
ENV DC_ARM_BASE=${KOS_BASE}/../arm-eabi
ENV DC_ARM_PREFIX=arm-eabi

# Setup Path
ENV PATH="${PATH}:${KOS_CC_BASE}/bin:/opt/toolchains/dc/bin:${KOS_BASE}/utils/gnu_wrappers"

ENV KOS_CFLAGS="-O2 -fomit-frame-pointer -ml -m4-single-only -ffunction-sections -fdata-sections"
ENV KOS_AFLAGS="-little"

# Arch Kernel Folder
ENV KOS_ARCH_DIR=${KOS_BASE}/kernel/arch/${KOS_ARCH}

# Linker
ENV KOS_LD_FLAGS="${KOS_LDFLAGS} -ml -m4-single-only -Wl,-Ttext=0x8c010000 -Wl,--gc-sections"
ENV KOS_LD_SCRIPT="-T${KOS_BASE}/utils/ldscripts/shlelf.xc"

# DC ARM Sound Compiler
ENV DC_ARM_CC="${DC_ARM_BASE}/bin/${DC_ARM_PREFIX}-gcc"
ENV DC_ARM_AS="${DC_ARM_BASE}/bin/${DC_ARM_PREFIX}-as"
ENV DC_ARM_AR="${DC_ARM_BASE}/bin/${DC_ARM_PREFIX}-ar"
ENV DC_ARM_OBJCOPY="${DC_ARM_BASE}/bin/${DC_ARM_PREFIX}-objcopy"
ENV DC_ARM_LD="${DC_ARM_BASE}/bin/${DC_ARM_PREFIX}-ld"
ENV DC_ARM_CFLAGS="-mcpu=arm7di -Wall -O2 -fno-strict-aliasing -Wl,--fix-v4bx -Wa,--fix-v4bx"
ENV DC_ARM_AFLAGS="-mcpu=arm7di --fix-v4bx"
ENV DC_ARM_MAKE="make"
ENV DC_ARM_START="${KOS_ARCH_DIR}/sound/arm/crt0.s"
ENV DC_ARM_LDFLAGS="${DC_ARM_LDFLAGS} -Wl,-Ttext=0x00000000,-N -nostartfiles -nostdlib -e reset"
ENV DC_ARM_LIB_PATHS=""
ENV DC_ARM_LIBS="-Wl,--start-group -lgcc -Wl,--end-group"	

# KOS Include Paths
ENV KOS_INC_PATHS="${KOS_INC_PATHS} -I${KOS_BASE}/include \
-I${KOS_BASE}/kernel/arch/${KOS_ARCH}/include -I${KOS_BASE}/addons/include \
-I${KOS_PORTS}/include"

# KOS libs
ENV KOS_LIB_PATHS="-L${KOS_BASE}/lib/${KOS_ARCH} -L${KOS_BASE}/addons/lib/${KOS_ARCH} -L${KOS_PORTS}/lib"
ENV KOS_LIBS="-Wl,--start-group -lkallisti -lc -lgcc -Wl,--end-group"

# Compiler paths
ENV KOS_CC="${KOS_CC_BASE}/bin/${KOS_CC_PREFIX}-gcc"
ENV KOS_CCPLUS="${KOS_CC_BASE}/bin/${KOS_CC_PREFIX}-g++"
ENV KOS_AS="${KOS_CC_BASE}/bin/${KOS_CC_PREFIX}-as"
ENV KOS_AR="${KOS_CC_BASE}/bin/${KOS_CC_PREFIX}-ar"
ENV KOS_OBJCOPY="${KOS_CC_BASE}/bin/${KOS_CC_PREFIX}-objcopy"
ENV KOS_LD="${KOS_CC_BASE}/bin/${KOS_CC_PREFIX}-ld"
ENV KOS_RANLIB="${KOS_CC_BASE}/bin/${KOS_CC_PREFIX}-ranlib"
ENV KOS_STRIP="${KOS_CC_BASE}/bin/${KOS_CC_PREFIX}-strip"
ENV KOS_CFLAGS="${KOS_CFLAGS} ${KOS_INC_PATHS} -D_arch_${KOS_ARCH} -D_arch_sub_${KOS_SUBARCH} -Wall -g -fno-builtin"
ENV KOS_CPPFLAGS="${KOS_CPPFLAGS} ${KOS_INC_PATHS_CPP} -fno-operator-names -fno-rtti -fno-exceptions"

ENV KOS_CSTD="-std=c99"
ENV KOS_CPPSTD="-std=gnu++98"

ENV KOS_GCCVER="`kos-cc -dumpversion`"

ENV KOS_LDFLAGS="${KOS_LDFLAGS} ${KOS_LD_SCRIPT} -nodefaultlibs ${KOS_LIB_PATHS}"
ENV KOS_START=""

WORKDIR ${KOS_BASE}

# COPY .github/workflows/containers/kos/environ.sh ${KOS_BASE}/environ.sh

# Build KOS
# RUN source ./environ.sh && make
RUN make

# kos-ports/scripts/validate_dis.py tries to call "python"
RUN apt-get update && apt-get install -y python-is-python3

RUN git clone --recursive https://github.com/kallistiOS/kos-ports ${KOS_PORTS} && \
    sh ${KOS_PORTS}/utils/build-all.sh


