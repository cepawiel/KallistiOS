# syntax = edrevo/dockerfile-plus

INCLUDE+ ./.github/workflows/gcc-build-deps/Dockerfile

SHELL ["/bin/bash", "-c"]

COPY .github/workflows/gcc-build-kos/config.mk ${KOS_BASE}/utils/dc-chain/config.mk

RUN cd $KOS_BASE/utils/dc-chain \
    && ./download.sh \
    && ./unpack.sh \
    && make patch \
    && make all -j8



