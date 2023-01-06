# Dockerfile

This directory contain a `Dockerfile` which demonstrate you how to build a
Docker image containing the minimal toolchains used for **Sega Dreamcast**
development.

The Docker image foundation is based on [Alpine Linux](https://alpinelinux.org/).

Built toolchains are:
* A `sh-elf` toolchain, targeting the main CPU, which will be located in 
  `/opt/toolchains/dc/sh-elf`;
* An `arm-eabi` toolchain, targeting the audio chip, which will be located in
  `/opt/toolchains/dc/arm-eabi` ;
* The regular toolchain used for compiling various tools.

These images may be used to compile [KallistiOS](https://en.wikipedia.org/wiki/KallistiOS),
the open source **Sega Dreamcast** development library.

The container can be built with the following command:
```
cd <root_kos_repo_path>
docker build \
  -f utils/docker/Dockerfile \
  --build-arg CONFIG_FILE="config.mk.testing.sample" \
  -t example-local-kos-image \
  --target kos-ports \
  .
```
The target parameter supports [toolchain, kos, kos-ports] stages. Additionally 
KOS and Ports can be built with NAOMI support by setting the KOS_SUBARCH build-arg 
to "naomi".

The container can then be run:
```
docker run --rm -it example-local-kos-image "kos-cc --version"
```

Of course, the Docker image produced here can be used for CI/CD pipelines!

Don't hesitate to have multiple `config.mk` files; this may be useful for
building customized toolchains (e.g. a `testing` Docker image with `gcc-9.3.0`
and a `stable` one with `gcc-4.7.4`...).
