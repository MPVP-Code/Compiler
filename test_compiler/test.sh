#!/bin/bash

echo "========================================"
echo " Testing compiler"
echo "========================================"

echo "========================================"
echo " Cleaning the temporaries and outputs"
make clean
echo " Force building bin/c_compiler"
make bin/c_compiler -B
if [[ "$?" -ne 0 ]]; then
    echo "Build failed.";
fi


echo "Compiling C to MIPS32"
./bin/c_compiler -S test_compiler/test_RETURN.c -o test_compiler/test_RETURN.s
#mips-linux-gnu-gcc -O3 -S -mfp32 -march=mips32 test_compiler/test_RETURN.c -o test_compiler/test_RETURN.s
#echo "Building MIPS32 binary"
mips-linux-gnu-gcc -mfp32 -static -march=mips32 -o test_compiler/test_RETURN.o -c test_compiler/test_RETURN.s
mips-linux-gnu-gcc -mfp32 -static -march=mips32 -o test_compiler/test_RETURN test_compiler/test_RETURN.o test_compiler/test_RETURN_driver.c

echo "Simulating"
set +e
qemu-mips test_compiler/test_RETURN
RESULT=${?}
set -e

if [[ $RESULT == 0 ]]; then
  echo "PASSED";
else
  echo "FAILED";
fi