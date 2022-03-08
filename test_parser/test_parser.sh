#!/bin/bash

echo "========================================"
echo " Testing parser"
echo "========================================"

if which dos2unix ; then
    DOS2UNIX="dos2unix"
elif which fromdos ; then
    DOS2UNIX="fromdos"
else
    >&2 echo "warning: dos2unix is not installed."
    DOS2UNIX="tr -d \r"
fi

echo "========================================"
echo " Cleaning the temporaries and outputs"
make clean
echo " Force building parser"
make parser -B
if [[ "$?" -ne 0 ]]; then
    echo "Build failed.";
fi
echo ""

echo "========================================="

for i in test_parser/in/*.txt; do
    echo "==========================="
    echo ""
    echo "Input file : ${i}"
    BASENAME=$(basename $i .txt);
    cat $i | ${DOS2UNIX} | ./bin/parser  > test_parser/out/$BASENAME.stdout.txt  2> test_parser/out/$BASENAME.stderr.txt

    diff <(cat test_parser/ref/$BASENAME.stdout.txt | ${DOS2UNIX}) <(cat test_parser/out/$BASENAME.stdout.txt) > test_parser/out/$BASENAME.diff.txt
    if [[ "$?" -ne "0" ]]; then
        echo -e "\nERROR"
    else
        PASSED=$(( ${PASSED}+1 ));
    fi
    CHECKED=$(( ${CHECKED}+1 ));
done


echo "########################################"
echo "Passed ${PASSED} out of ${CHECKED}".
echo ""