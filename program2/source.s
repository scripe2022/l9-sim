#define input_low r6
#define input_high r7
#define N r9
mov 0b01111
lsl 1
mvt r9

mov 0
mvt r8 // r8: i

.loop:
    mvf N
    add r8
    ldr r0
    mvt input_low // r6: input_low
    mvf N
    add r8
    or 1
    ldr r0
    mvt input_high // r7: input_high

    // r5: bit
    mov -2
    and input_high
    prt r0
    mvt r1 // r1: p8
    mvf input_high
    and 1
    xor r1
    lsl 3
    mvt r5 // bit = ((input_high & 1) ^ p8) << 3

    mov 0b1111
    lsl 4
    and input_high
    prt r0
    mvt r1 // r1: odd(input_high & 0b11110000)
    mov 0b111
    lsl 5
    and input_low
    prt r0
    xor r1
    mvt r1 // r1: p4
    mvf input_low
    lsr 4
    and 0b1
    xor r1
    lsl 2
    add r5
    mvt r5 // bit += ((((input_low >> 4) & 0b1)) ^ p4) << 2

    mov 0b11
    lsl 6
    or 0b1100
    and input_high
    prt r0
    mvt r1 // r1: odd(input_high & 0b11001100)
    mov 0b11
    lsl 6
    or 0b1000
    and input_low
    prt r0
    xor r1
    mvt r1 // r1: p2
    mvf input_low
    lsr 2
    and 0b1
    xor r1
    lsl 1
    add r5
    mvt r5 // bit += ((((input_low >> 2) & 0b1)) ^ p2) << 1

    mov 0b1010
    lsl 4
    or 0b1010
    and input_high
    prt r0
    mvt r1 // r1: odd(input_high & 0b10101010)
    mov 0b1010
    lsl 4
    or 0b1000
    and input_low
    prt r0
    xor r1
    mvt r1 // r1: p1
    mvf input_low
    lsr 1
    and 0b1
    xor r1
    add r5
    mvt r5
    // bit done

    mvf input_high
    prt r0
    mvt r1 // r1: odd(input_high)
    mov -2
    and input_low
    prt r0
    xor r1
    mvt r1 // r1: p0
    mvf input_low
    and 1
    xor r1
    mvt r4 // r4: prt

    mov 0
    ceq r4
    bt .done // if (prt == 0) goto .done
        mvf r5
        and 0b1000
        lsr 3
        mvt r3 // r3: c
        mvf r5
        and 0b111
        mvt r1 // (bit & 0b111)
        mvf r3
        lsl r1
        mvt r2 // r2: mask
        mvf input_high
        xor r2
        mvt input_high
        mvf r3
        xor 0b1
        lsl r1
        mvt r2 // r2: mask
        mvf input_low
        xor r2
        mvt input_low
    .done:

    // output_high
    // addr
    mvf r8
    or 1
    mvt r3 // r3: addr
    // body
    mvf r4
    lsl 6
    mvt r1 // r1: prt << 6
    norr r5
    or r4
    xor 1
    lsl 7
    mvt r2 // r2: ((prt | norr(bit)) ^ 1) << 7
    mvf input_high
    lsr 5
    or r1
    or r2
    str r3 // mem[addr] = output_high

    // output_low
    // addr: r8
    // body
    mvf input_high
    lsr 1
    lsl 4
    mvt r1
    mvf input_low
    lsr 5
    lsl 1
    mvt r2
    mvf input_low
    and 0b1000
    lsr 3
    or r1
    or r2
    str r8

    // i += 2
    // if (i < 30) goto .loop
    mvf r8
    add 2
    mvt r8
    clt r9
    bt .loop