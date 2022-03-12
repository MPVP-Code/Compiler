#!/bin/bash

echo "========================================"
echo " Cleaning the temporaries and outputs"
make clean
echo " Force building parser"
make codegentest -B
if [[ "$?" -ne 0 ]]; then
    echo "Build failed.";
fi

echo "========================================"
echo " Running codegen tests"

./test_codegen/bin/codegen_main
