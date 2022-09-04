FROM ubuntu:22.10

LABEL org.opencontainers.image.source https://github.com/${{ github.repository }}

COPY . /opt/toolchains/dc/kos/

SHELL ["/bin/bash", "-c"]

RUN apt update \
    && apt upgrade -y \
    && apt install -y --no-install-recommends \
        binutils pkg-config gawk patch bzip2 tar xz-utils unzip \
        libgmp-dev libmpfr-dev libmpc-dev gettext libelf-dev \
        texinfo bison flex sed build-essential diffutils \
        git curl wget python subversion openssl ca-certificates \
        libjpeg-dev libpng-dev \
        cmake make \
    && apt clean \
    && rm -rf /var/lib/apt/lists/*
