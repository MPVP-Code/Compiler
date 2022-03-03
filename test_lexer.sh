#!/bin/bash

echo "========================================"
echo " Testing lexer"
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
echo " Force building lexer"
make lexer -B
if [[ "$?" -ne 0 ]]; then
    echo "Build failed.";
fi
echo ""
mkdir -p test/out

echo "========================================="

PASSED=0
CHECKED=0

for i in test_lexer/in/*.txt; do
    echo "==========================="
    echo ""
    echo "Input file : ${i}"
    BASENAME=$(basename $i .txt);
    cat $i | ${DOS2UNIX} | ./bin/lexer  > test_lexer/out/$BASENAME.stdout.txt  2> test_lexer/out/$BASENAME.stderr.txt

    diff <(cat test_lexer/ref/$BASENAME.stdout.txt | ${DOS2UNIX}) <(cat test_lexer/out/$BASENAME.stdout.txt) > test_lexer/out/$BASENAME.diff.txt
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