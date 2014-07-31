#!/bin/sh

mkdir -p ./output
mkdir -p ./diffs

lab="4"

# for i in 1 2 3 4 5 6 7 8 9 A B C D E F
# for i in 1 2 3 4 5 6 7 8 9 A B C
# for i in 30 33 35 36 37 38 52
for i in 40 44 45 46 49 61 62
do
    ./test.bin "./tests/in${i}.txt" "./output/actual${i}.txt"
    diff -su ./tests/out${i}.txt ./output/actual${i}.txt >> ./diffs/diff${lab}.diff
    if [ $? != ''0 ]; then
        echo "diff failed for \"./tests/in${i}.txt\"!!!"
    else
        echo "diff succeeded for \"./tests/in${i}.txt\"..."
    fi
done

