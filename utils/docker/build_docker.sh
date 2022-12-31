#!/bin/bash

KOS_ROOT=/opt/toolchains/dc/kos

function build_container {
    config_file=$1
    base_tag=$2
    target=$3

    set -e
    docker build \
        -f $KOS_ROOT/utils/docker/Dockerfile \
        --build-arg BUILD_THREADS=$(nproc) \
        --build-arg CONFIG_FILE=$config_file \
        -t $base_tag-$target \
        --target $target \
        $KOS_ROOT
    set +e
}

# config file
# config.mk.stable.sample
# config.mk.stable.sample

# targets:
# toolchain
# kos
# kos-ports

build_container $1 $2

# BUILD_EXAMPLES="source /opt/toolchains/dc/kos/environ.sh && cd /opt/toolchains/dc/kos/examples && make all"
# docker run --rm -it $CONTAINER_TAG-kos-ports /bin/bash -c "$BUILD_EXAMPLES"