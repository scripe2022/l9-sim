#!/usr/bin/python3
import random

mem = []
for i in range(90): mem.append('00000000')

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

def corrupt(b):
    bt = random.randint(0, 2)
    if (bt == 0):
        return b, 0
    elif (bt == 1):
        p = random.randint(0, len(b) - 1)
        b = b[:p] + str(int(b[p]) ^ 1) + b[p+1:]
        return b, 1
    elif (bt == 2):
        p1 = random.randint(0, len(b) - 1)
        b = b[:p1] + str(int(b[p1]) ^ 1) + b[p1+1:]
        p2 = random.randint(0, len(b) - 1)
        while (p1 == p2): p2 = random.randint(0, len(b) - 1)
        b = b[:p2] + str(int(b[p2]) ^ 1) + b[p2+1:]
        return b, 2

for i in range(15):
    s = generate_random_binary_string(11)
    mem[2*i], mem[2*i+1] = sp(s)
    e = encode(s)
    mem[60 + 2*i], mem[60 + 2*i + 1] = sp(e)
    e, bt = corrupt(e)
    mem[30 + 2*i], mem[30 + 2*i + 1] = sp(e)
    if (bt == 1):
        mem[2*i+1] = '01' + mem[2*i+1][2:]
    elif (bt == 2):
        mem[2*i+1] = '10' + mem[2*i+1][2:]


for i in range(60):
    print(mem[i])