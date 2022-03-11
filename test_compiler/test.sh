#!/bin/bash

for i in ../compiler_tests/*/*.c; do
  if ! [[ $i =~ .+_driver.c$ ]]; then
      BASE=$(basename $i .c)
      DIR=$(dirname $i)
      NAME_WITHOUT_EXT="$DIR/$BASE"

      echo "Cleaning $i";
      rm -rf "${NAME_WITHOUT_EXT}" "${NAME_WITHOUT_EXT}.o" "${NAME_WITHOUT_EXT}.s";
  fi
done

echo "Cleaning done"