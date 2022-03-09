#!/bin/bash

echo "Compiling C to MIPS32"
mips-linux-gnu-gcc -O3 -S -mfp32 -march=mips32 test_ADD0.c -o test_ADD0.s
echo "Building MIPS32 binary"
mips-linux-gnu-gcc -mfp32 -static -march=mips32 -o test_ADD0.o -c test_ADD0.s
mips-linux-gnu-gcc -mfp32 -static -march=mips32 -o test_ADD0 test_ADD0.o test_ADD0_driver.c

echo "Simulating"
set +e
qemu-mips test_ADD0
RESULT=${?}
set -e

if [[ $RESULT == 0 ]]; then
  echo "PASSED";
else
  echo "FAILED";
fi