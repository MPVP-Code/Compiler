#!/bin/bash

echo "========================================"
echo " Testing compiler"
echo "========================================"

echo "========================================"
echo " Cleaning the temporaries and outputs"
./test_complier/clean.sh
make clean --always-make
echo " Force building bin/c_compiler"
make bin/c_compiler -B
if [[ "$?" -ne 0 ]]; then
    echo "Build failed.";
fi

ASSEMBLY_FILE=$1;
BASE=$(basename "$ASSEMBLY_FILE" .s)
NAME_WITHOUT_EXT="test_compiler/assembly_test/$BASE"

echo "========================================"
echo " Testing the assembly: $NAME_WITHOUT_EXT"
echo "  Building MIPS32 binary"
mips-linux-gnu-gcc -mfp32 -static -march=mips32 -o "$NAME_WITHOUT_EXT.o" -c "$NAME_WITHOUT_EXT.s" 2>&1
mips-linux-gnu-gcc -mfp32 -static -march=mips32 -o "$NAME_WITHOUT_EXT" "$NAME_WITHOUT_EXT.o" "${NAME_WITHOUT_EXT}_driver.c" 2>&1
RESULT=${?}
set -e

if [[ $RESULT == 0 ]]; then
  echo "  Simulating"
  set +e
  qemu-mips "$NAME_WITHOUT_EXT"
  RESULT=${?}
  set -e

  if [[ $RESULT == 0 ]]; then
    echo "  PASSED";
  else
    echo "  FAILED";
  fi
else
  echo "  Build error.";
fi