#
# Dockerfile for KallistiOS Toolchain
#

FROM alpine:latest as build-deps
LABEL maintainer="KallistiOS cadcdev-kallistios@lists.sourceforge.net"

# Installing prerequisites
RUN apk --update add --no-cache \
	build-base \
	patch \
	bash \
	texinfo \
	libjpeg-turbo-dev \
	gmp-dev \
	mpfr-dev \
	mpc1-dev \
	libpng-dev \
	curl \
	wget \
	git \
	python3 \
	subversion \
	elfutils-dev \
	&& rm -rf /var/cache/apk/*

FROM build-deps as build-toolchain

# name of toolchain config file located in utils/dc-chain
# passed as arg to docker build command
ARG CONFIG_FILE

# Copy Necessary Data into Container
# By only copying the necessary files to build the toolchain docker
# can cache the toolchain layer as long as none of the files in these directories
# are changed. Doing so would trigger rebuilding the toolchain.
# TODO: More specifically copy includes to avoid rebuilds
COPY include /opt/toolchains/dc/kos/include
COPY kernel/arch/dreamcast/include/arch /opt/toolchains/dc/kos/kernel/arch/dreamcast/include/arch
COPY kernel/arch/dreamcast/include/dc /opt/toolchains/dc/kos/kernel/arch/dreamcast/include/dc
COPY utils/dc-chain /opt/toolchains/dc/kos/utils/dc-chain

# Build Sega Dreamcast toolchains
# We copy the specified config to the required config.mk location.
# Also overwrite the default -j2 with the max avalable cores using nproc. 
RUN cd /opt/toolchains/dc/kos/utils/dc-chain \
	&& cp ${CONFIG_FILE} config.mk \
	&& sed -i "s/makejobs=-j2/makejobs=-j$(nproc)/g" config.mk \
	&& echo "Downloading Sources" \
	&& ./download.sh \
	&& echo "Unpacking Sources" \
	&& ./unpack.sh \
	&& echo "Building Toolchain" \
	&& make \
	&& echo "Building GDB" \
	&& make gdb

# Copy Toolchain out of build container into toolchain container.
# This allows the removal of all the remaints of the toolchain build in
# the previous container only keeping the compiled toolchains.
FROM build-deps as toolchain
COPY --from=build-toolchain /opt/toolchains/dc/arm-eabi /opt/toolchains/dc/arm-eabi
COPY --from=build-toolchain /opt/toolchains/dc/sh-elf /opt/toolchains/dc/sh-elf

# build kos and related tools
FROM toolchain as kos

# copy entire KOS folder into container
# TODO: copy only folders necessary for build. 
#		Example: Changes to doc/ will trigger a rebuild
COPY . /opt/toolchains/dc/kos

# setup environ.sh file using default
RUN cd /opt/toolchains/dc/kos \
	&& cp doc/environ.sh.sample environ.sh \
	# create link so environ.sh is sourced for interactive shells
	# example: docker run --rm -it $TAG /bin/bash
	&& ln -s /opt/toolchains/dc/kos/environ.sh /etc/profile.d/kos.sh

# pristine (default) is for dreamcast
# naomi can be specified as a build_arg
# overwriting this at runtime could cause issues
ARG KOS_SUBARCH="pristine"
ENV KOS_SUBARCH=${KOS_SUBARCH}

# set BASH_ENV so it works for non interactive as well
# example: docker run --rm $TAG "make"
ENV BASH_ENV="/opt/toolchains/dc/kos/environ.sh"

# Set Shell to Bash so environ.sh will be sourced in every
# following run command
SHELL ["/bin/bash", "-c"]

# set entry point to bash so arg to docker run can be 
# run as a command.
ENTRYPOINT ["/bin/bash", "-c"]

# if run with no parameters just start bash
CMD ["bash"]

# build KOS
RUN cd /opt/toolchains/dc/kos && make

# TODO: Build KOS Debug Lib

FROM kos as kos-ports

RUN git clone --recursive https://github.com/KallistiOS/kos-ports /opt/toolchains/dc/kos-ports \
	&& source /opt/toolchains/dc/kos/environ.sh \
	&& cd /opt/toolchains/dc/kos-ports \
	&& sh utils/build-all.sh
