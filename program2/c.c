// compile: gcc -o c c.c
// run: ./c < mem.in
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

unsigned char *read() {
    unsigned char *mem = malloc(60);
    if (mem == NULL) exit(1);
    for (int it = 0; it < 60; ++it) {
        unsigned char ch[8];
        int rtn = scanf("%s", ch);
        assert(rtn != EOF);
        unsigned char num = 0;
        for (int i = 0; i < 8; ++i) num = (num << 1) | (ch[i] - '0');
        mem[it] = num;
    }
    for (int it = 0; it < 30; ++it) mem[it] = 0;
    return mem;
}

unsigned char odd(unsigned char x) {
    unsigned char cnt = 0;
    while (x) {
        cnt ^= x & 1;
        x >>= 1;
    }
    return cnt;
}

unsigned char norr(unsigned char x) {
    return (x > 0) ? 0 : 1;
}


int main() {
    unsigned char *mem = read();

    int i = 0;
    while (i < 30) {
        unsigned char input_low = mem[30 + i];
        unsigned char input_high = mem[30 + (i | 1)];
        unsigned char bit = 0;

        unsigned char p8 = odd(input_high & 0b11111110);
        bit += ((input_high & 1) ^ p8) << 3;

        unsigned char p4 = odd(input_high & 0b11110000) ^ odd(input_low & 0b11100000);
        bit += ((((input_low >> 4) & 0b1)) ^ p4) << 2;

        unsigned char p2 = odd(input_high & 0b11001100) ^ odd(input_low & 0b11001000);
        bit += ((((input_low >> 2) & 0b1)) ^ p2) << 1;

        unsigned char p1 = odd(input_high & 0b10101010) ^ odd(input_low & 0b10101000);
        bit += (((input_low >> 1) & 0b1)) ^ p1;

        unsigned char p0 = odd(input_high) ^ odd(input_low & 0b11111110);
        unsigned char prt = (input_low & 0b00000001) ^ p0;

        if (prt == 1) {
            unsigned char mask;
            unsigned char c = (bit & 0b1000) >> 3;
            mask = c << (bit & 0b111);
            input_high ^= mask;
            c ^= 1;
            mask = c << (bit & 0b111);
            input_low ^= mask;
        }

        unsigned char output_high = 0, output_low = 0;
        output_high |= prt << 6;
        output_high |= ((prt | norr(bit)) ^ 1) << 7;

        output_high |= input_high >> 5;
        output_low |= (input_high >> 1) << 4;
        output_low |= (input_low >> 5) << 1;
        output_low |= (input_low & 0b1000) >> 3;

        mem[i] = output_low;
        mem[i | 1] = output_high;

        i += 2;
    }
    for (int i = 0; i < 60; ++i) {
        printf("%d: %02x\n", i, (unsigned char)mem[i]);
    }

    free(mem);
    return 0;
}
