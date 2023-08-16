#!/usr/bin/python3
import random
import sys
import re

mem = []
for i in range(60): mem.append('00000000')

def generate_random_binary_string(length):
    binary_string = ''.join(random.choice('01') for _ in range(length))
    return binary_string

for i in range(32): mem[i] = generate_random_binary_string(8)
mem[32] = generate_random_binary_string(5) + '000'

def occurrences(text, sub):
    return len(re.findall('(?={0})'.format(re.escape(sub)), text))

def solve():
    pattern = mem[32][:5]
    dcrs = 0
    bs = 0
    tot = 0
    alls = ''
    for i in range(32):
        alls += mem[i]
        cnt = occurrences(mem[i], pattern)
        dcrs += cnt
        if (cnt > 0): bs += 1
    tot = occurrences(alls, pattern)
    print(dcrs, bs, tot, file=sys.stderr)
    print(hex(dcrs), hex(bs), hex(tot), file=sys.stderr)

for i in range(60):
    print(mem[i])
# for i in range(60):
#     mem[i] = input()

solve()