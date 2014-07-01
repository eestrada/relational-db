#!/bin/sh

mkdir -p ./output
mkdir -p ./diffs

#for i in 1 2 3 4 5 6 7 8 9 A B C D E F
for i in 0 1 2 3 4 5 6 7 8 9 A
do
    ./test.bin ./tests/in1${i}.txt ./output/actual1${i}.txt
    diff -su ./tests/out1${i}.txt ./output/actual1${i}.txt >> ./diffs/diff1.diff
    if [ $? != ''0 ]; then
        echo "diff failed for \"./tests/in1${i}.txt\"!!!"
    else
        echo "diff succeeded for \"./tests/in1${i}.txt\"..."
    fi
done

