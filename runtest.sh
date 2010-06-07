#!/bin/bash

if [[ $# -ne 2 ]]
then
  echo "Error - parameters missing\nSyntax: $0 test_group test_name\nExample: $0 samples hello\n"
  exit 1
fi

BSP=pc386
TARGET=i386-rtems4.10
EXTENSION=

PWD=`pwd`

$R/rtems-testing/sim-scripts/pc386 -i b-${BSP}${EXTENSION}/${TARGET}/c/${BSP}/testsuites/${1}/${2}/${2}.exe

