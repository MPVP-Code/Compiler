#!/bin/bash

for i in ./compiler_tests/*/*.c; do
  if ! [[ $i =~ .+_driver.c$ ]]; then
      BASE=$(basename $i .c)
      DIR=$(dirname $i)
      NAME_WITHOUT_EXT="$DIR/$BASE"
      rm -rf "$NAME_WITHOUT_EXT"
      rm -rf "$NAME_WITHOUT_EXT.s"
      rm -rf "$NAME_WITHOUT_EXT.o"
      rm -rf "$NAME_WITHOUT_EXT.errorlog"
      rm -rf "$NAME_WITHOUT_EXT.s.stderr.txt"
  fi
done