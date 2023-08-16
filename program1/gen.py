#!/usr/bin/python3
import random

mem = []
for i in range(60): mem.append('00000000')

def generate_random_binary_string(length):
    binary_string = ''.join(random.choice('01') for _ in range(length))
    return binary_string

def encode(b):
    b = b[::-1]
    p8 = int(b[10]) ^ int(b[9]) ^ int(b[8]) ^ int(b[7]) ^ int(b[6]) ^ int(b[5]) ^ int(b[4])
    p4 = int(b[10]) ^ int(b[9]) ^ int(b[8]) ^ int(b[7]) ^ int(b[3]) ^ int(b[2]) ^ int(b[1])
    p2 = int(b[10]) ^ int(b[9]) ^ int(b[6]) ^ int(b[5]) ^ int(b[3]) ^ int(b[2]) ^ int(b[0])
    p1 = int(b[10]) ^ int(b[8]) ^ int(b[6]) ^ int(b[4]) ^ int(b[3]) ^ int(b[1]) ^ int(b[0])
    p0 = int(b[10]) ^ int(b[9]) ^ int(b[8]) ^ int(b[7]) ^ int(b[6]) ^ int(b[5]) ^ int(b[4]) ^ int(b[3]) ^ int(b[2]) ^ int(b[1]) ^ int(b[0]) ^ p8 ^ p4 ^ p2 ^ p1
    s = b[10] + b[9] + b[8] + b[7] + b[6] + b[5] + b[4] + str(p8)
    s += b[3] + b[2] + b[1] + str(p4) + b[0] + str(p2) + str(p1) + str(p0)
    return s

def sp(b):
    assert(len(b) == 11 or len(b) == 16)
    if (len(b) == 11):
        return b[-8:], '00000' + b[:3]
    elif (len(b) == 16):
        return b[-8:], b[:8]

for i in range(15):
    s = generate_random_binary_string(11)
    mem[2*i], mem[2*i+1] = sp(s)
    mem[30 + 2*i], mem[30 + 2*i + 1] = sp(encode(s))

for i in range(60):
    print(mem[i])