#!/bin/sh

BSP=pc386
TARGET=i386-rtems4.10 
EXTENSION=

cd b-${BSP}${EXTENSION}
if [[ $# -eq 0 ]]
then
  rm * -rf
  #../rtems/configure --target=${TARGET} --disable-posix --disable-itron --disable-networking --disable-multiprocessing --enable-rtemsbsp=${BSP}
  #../rtems/configure --target=${TARGET} --disable-networking --enable-rtemsbsp=${BSP} --disable-posix
  #../rtems/configure --target=${TARGET} --disable-networking --enable-rtemsbsp=${BSP} --enable-tests=samples
  #../rtems/configure --target=${TARGET} --disable-networking --enable-rtemsbsp=${BSP} --enable-tests

  ## Build for QEMU
  ../rtems/configure --target=${TARGET} --disable-networking \
    --enable-rtemsbsp=${BSP} --enable-tests=samples \
    USE_COM1_AS_CONSOLE=1 BSP_PRESS_KEY_FOR_RESET=0
fi

time make -j 4 2> make.error

echo ""

${TARGET}-objdump -d ${TARGET}/c/${BSP}/testsuites/samples/hello/hello.exe > hello.disasm

${TARGET}-objdump -d ${TARGET}/c/${BSP}/testsuites/samples/ticker/ticker.exe > ticker.disasm

