#!/bin/bash
make
function print(){
    echo $'\n'
    echo "------------------------------$1------------------------------"
}
RES_FILE=./parser_test.txt
for filename in ./samples/*.decaf; do
    ./dcc < $filename > $RES_FILE 2>&1
    EXE_ANS="${filename%.*}.out"
    DIFF_RES="$(diff -w ./parser_test.txt $EXE_ANS)"

    if [ ! -z "$DIFF_RES" ]; then
        echo "$filename failed the test !"
        print reference
        more $EXE_ANS

        print "your answer"
        more $RES_FILE

        print "test file"
        more $filename

        print "diff result"
        echo $DIFF_RES
        break
    fi
    echo "$filename pass the test !"
done
