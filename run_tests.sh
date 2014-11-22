#!/bin/sh

rm -rf ./output
rm -rf ./diffs
mkdir -p ./output
mkdir -p ./diffs

lab="5"

for i in 50 54 55 56 58 59 61 62
do
    ./test.bin "./tests/in${i}.txt" "./output/actual${i}.txt"
    diff -s -U 20 ./tests/out${i}.txt ./output/actual${i}.txt >> ./diffs/diff${lab}.diff
    if [ $? != '0' ]; then
        echo "diff failed for \"./tests/in${i}.txt\"!!!"
        echo
    else
        echo "diff succeeded for \"./tests/in${i}.txt\"..."
        echo
    fi
done

