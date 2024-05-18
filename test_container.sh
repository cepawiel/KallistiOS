#!/bin/bash


set -e
set -x

docker build \
    --target toolchain \
    -t kos_test \
    -f containers/Dockerfile \
    .


