FROM ubuntu:22.10

COPY . /opt/toolchains/dc/kos/

SHELL ["/bin/bash", "-c"]

RUN apt-get update \
    && apt-get upgrade -y \
    && apt-get install -y --no-install-recommends \
        binutils pkg-config gawk patch bzip2 tar xz-utils unzip \
        libgmp-dev libmpfr-dev libmpc-dev gettext libelf-dev \
        texinfo bison flex sed build-essential diffutils \
        git curl wget python3 subversion openssl ca-certificates \
        libjpeg-dev libpng-dev \
        cmake make \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*
