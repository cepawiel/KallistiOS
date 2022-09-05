# syntax = edrevo/dockerfile-plus

INCLUDE+ ./.github/workflows/containers/gcc-build-deps/Dockerfile

SHELL ["/bin/bash", "-c"]

COPY .github/workflows/containers/gcc-build-kos/config.mk ${KOS_BASE}/utils/dc-chain/config.mk

WORKDIR ${KOS_BASE}/utils/dc-chain

RUN ./download.sh
RUN ./unpack.sh
RUN make patch
RUN make all

# RUN cd ${KOS_BASE}/utils/dc-chain \
#     && ./download.sh \
#     && ./unpack.sh \
#     && make patch \
#     && make all -j$(nproc)



