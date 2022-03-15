#!/bin/bash
echo "Compiling to MIPS..."
cat $2 | ./bin/compiler 2> "$4.stderr.txt" 1> $4
