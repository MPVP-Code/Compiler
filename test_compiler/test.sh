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

CHECKED=0;
PASSED=0;

echo "========================================"
echo " Testing the compiler"

for filename in compiler_tests/*/*.c; do
  if ! [[ $filename == *_driver.c ]]; then
    ((CHECKED++))
    echo "Testing $filename"
    DIR="$(dirname "$filename")"
    BASE=$(basename $filename .c)
    TEST="$DIR/$BASE"

    set +e
    echo "  Compiling C to MIPS32"
    timeout 5 ./bin/c_compiler -S "$TEST.c" -o "$TEST.s" > /dev/null 2> "$TEST.errorlog"

    echo "  Building MIPS32 binary"
    mips-linux-gnu-gcc -mfp32 -static -march=mips32 -o "$TEST.o" -c "$TEST.s" > /dev/null 2>&1
    mips-linux-gnu-gcc -mfp32 -static -march=mips32 -o "$TEST" "$TEST.o" "${TEST}_driver.c" > /dev/null 2>&1
    RESULT=${?}
    set -e

    if [[ $RESULT == 0 ]]; then
      echo "  Simulating"
      set +e
      timeout 5 qemu-mips "$TEST"
      RESULT=${?}
      set -e

      if [[ $RESULT == 0 ]]; then
        PASSED=$((PASSED+1))
        echo "  PASSED";
      else
        echo "  FAILED";
      fi
    else
      echo "  Compilation error.";
    fi
  fi
done

echo "$PASSED out of $CHECKED tests."