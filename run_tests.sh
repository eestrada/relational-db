#!/bin/sh

rm -rf ./output
rm -rf ./diffs
mkdir -p ./output
mkdir -p ./diffs

lab="4"

for i in 40 44 45 46 49 4A 61 62
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

