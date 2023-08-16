// compile: gcc -o c c.c
// run: ./c < mem.in
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

unsigned char *read() {
    unsigned char *mem = malloc(60);
    if (mem == NULL) exit(1);
    // for (int it = 0; it < 15; ++it) {
    //     unsigned char ch[11]; scanf("%s", ch);
    //     unsigned char low = 0, high = 0;
    //     for (int i = 7; i >= 0; --i) low = (low << 1) | (ch[i] - '0');
    //     for (int i = 10; i >= 8; --i) high = (high << 1) | (ch[i] - '0');
    //     mem[it*2] = low;
    //     mem[it*2 + 1] = high;
    // }
    for (int it = 0; it < 60; ++it) {
        unsigned char ch[8];
        int rtn = scanf("%s", ch);
        assert(rtn != EOF);
        if (rtn == EOF) break;
        unsigned char num = 0;
        for (int i = 0; i < 8; ++i) num = (num << 1) | (ch[i] - '0');
        mem[it] = num;
    }
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

int main() {
    unsigned char *mem = read();

    int i = 0;
    while (i < 30) {
        unsigned char input_low = mem[i];
        unsigned char input_high = mem[i | 1];


        unsigned char output_high;
        output_high = input_high << 5;
        output_high |= ((input_low >> 4) << 1);
        output_high |= odd(output_high);

        unsigned char output_low;
        output_low = (input_low >> 1) << 5;
        output_low |= (input_low & 1) << 3;
        output_low |= (odd(input_high) ^ odd(input_low & 0b10001110)) << 4;
        output_low |= (odd(input_high & 0b00000110) ^ odd(input_low & 0b01101101)) << 2;
        output_low |= (odd(input_high & 0b00000101) ^ odd(input_low & 0b01011011)) << 1;
        output_low |= (odd(input_high & 0b00000100) ^ odd(input_low & 0b10110111));

//        printf("%02x %02x\n", output_low, output_high);
        mem[30 + i] = output_low;
        mem[(30 + i) | 1] = output_high;

        // if (i == 0) {
        //     printf("%d %d\n", i, i|1);
        //     printf("%d: %02x %02x %02x %02x\n", i, input_high, input_low, output_high, output_low);
        // }

        i += 2;
    }
    for (int i = 0; i < 60; ++i) {
        printf("%d: %02x\n", i, mem[i]);
    }

    free(mem);
    return 0;
}
