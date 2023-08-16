#!/usr/bin/bash
gcc -o c c.c -O3
make asm
for i in $(seq 1 1 1000)
do
    if [[ $(($i % 100)) -eq 0 ]]; then
        echo $i
    fi
    make gen
    ./c < mem.in > mem.ans
    make run
    make diff
    if [[ $? -ne 0 ]]; then
        break
    fi
done