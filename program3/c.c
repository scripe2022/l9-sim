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

    unsigned char pattern = mem[32] >> 3;
    unsigned char mask = 0b00011111;
    unsigned char i = 0;
    unsigned char dcrs = 0, bs = 0, tot = 0;
    while (1) {
        unsigned char cur = mem[i];
        unsigned char tb = 0;
        unsigned char s = 0;
        s = norr(((cur >> 3) & mask) ^ pattern);
        tb += s;
        s = norr(((cur >> 2) & mask) ^ pattern);
        tb += s;
        s = norr(((cur >> 1) & mask) ^ pattern);
        tb += s;
        s = norr((cur & mask) ^ pattern);
        tb += s;

        dcrs += tb;
        bs += norr(tb) ^ 1;
        if (i == 31) break;

        unsigned char nxt = mem[i+1] >> 4;
        s = norr((((cur & 0b01111) << 1) || (nxt >> 3)) ^ pattern);
        tot += s;
        s = norr((((cur & 0b00111) << 2) || (nxt >> 2)) ^ pattern);
        tot += s;
        s = norr((((cur & 0b00011) << 3) || (nxt >> 1)) ^ pattern);
        tot += s;
        s = norr((((cur & 0b00001) << 4) || (nxt)) ^ pattern);
        tot += s;

        i += 1;
    }
    tot += dcrs;

    printf("%d %d %d\n", dcrs, bs, tot);

    // for (int i = 0; i < 60; ++i) {
    //     printf("%d: %02x\n", i, (unsigned char)mem[i]);
    // }

    free(mem);
    return 0;
}
