#!/bin/bash

for i in ../compiler_tests/*/*.c; do
  if ! [[ $i =~ .+_driver.c$ ]]; then
      BASE=$(basename $i .c)
      DIR=$(dirname $i)
      NAME_WITHOUT_EXT="$DIR/$BASE"
  fi
done