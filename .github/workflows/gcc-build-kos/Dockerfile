FROM kos/gcc-build-deps:latest


SHELL ["/bin/bash", "-c"]

COPY .github/workflows/gcc-build-kos/config.mk ${KOS_BASE}/utils/dc-chain/config.mk

RUN cd $KOS_BASE/utils/dc-chain \
    && ./download.sh \
    && ./unpack.sh \
    && make patch


RUN cd $KOS_BASE/utils/dc-chain \
    && make all -j8



