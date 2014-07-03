#!/bin/sh

mkdir -p ./output
mkdir -p ./diffs

#for i in 1 2 3 4 5 6 7 8 9 A B C D E F
for i in  1 2 3 4 5 6 7 8 
do
    ./test.bin ./tests/in2${i}.txt ./output/actual2${i}.txt
    diff -su ./tests/out2${i}.txt ./output/actual2${i}.txt >> ./diffs/diff2.diff
    if [ $? != ''0 ]; then
        echo "diff failed for \"./tests/in2${i}.txt\"!!!"
    else
        echo "diff succeeded for \"./tests/in2${i}.txt\"..."
    fi
done

