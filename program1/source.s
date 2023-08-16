// r9: 30
size:
    30
mask10001110:
    0b10001110
mask01101101:
    0b01101101
mask01011011:
    0b01011011
mask10110111:
    0b10110111
ldr =size
mvt r9

// r8: i
mov 0
mvt r8

.loop:
    // r6: input_low
    ldr r8
    mvt r6
    // r7: input_high
    mvf r8
    or 1
    ldr r0
    mvt r7

    // processing output_high
    mvf r7
    lsl 5
    mvt r1 // input_high << 5
    mvf r6
    lsr 4
    lsl 1
    mvt r2 // (input_low >> 4) << 1
    mvf r1
    or r2
    mvt r1 // (input_high << 5) | ((input_low >> 4) << 1)
    prt r1
    or r1
    mvt r2 // output_high
    mvf r9
    add r8
    or 1
    mvt r1 // (30 + i) | 0b1
    mvf r2
    str r1 // mem[addr] = output_high

    // processing output_low
    mvf r6
    lsr 1
    lsl 5
    mvt r5
    // r5 = (input_low >> 1) << 5
    mvf r6
    and 1
    lsl 3
    mvt r4
    // r4 = (input_low & 1) << 3
    prt r7
    mvt r1 // r1 = odd(input_high)
    ldr =mask10001110
    and r6
    prt r0
    xor r1
    lsl 4
    mvt r3
    // r3 = (odd(input_high) ^ odd(input_low & 0b10001110)) << 4
    mvf r7
    and 0b00110
    prt r0
    mvt r1 // r1 = odd(input_high & 0b00000110)
    ldr =mask01101101
    and r6
    prt r0
    xor r1
    lsl 2
    mvt r2
    // r2 = (odd(input_high & 0b00000110) ^ odd(input_low & 0b01101101)) << 2
    mvf r7
    and 0b00101
    prt r0
    mvt r1 // r1 = odd(input_high & 0b00000101)
    ldr =mask01011011
    and r6
    prt r0
    xor r1
    lsl 1
    mvt r1
    // r1 = (odd(input_high & 0b00000101) ^ odd(input_low & 0b01011011)) << 1
    mvf r5
    or r4
    or r3
    or r2
    or r1
    mvt r5
    // r5 = first 4
    mvf r7
    and 0b00100
    prt r0
    mvt r1 // r1 = odd(input_high & 0b00000101)
    ldr =mask10110111
    and r6
    prt r0
    xor r1
    or r5
    mvt r2 // r2 = output_low
    mvf r9
    add r8
    mvt r1
    mvf r2
    str r1 // mem[addr] = output_low


    // i += 2
    mvf r8
    add 2
    mvt r8
    // if (i < 30) goto .loop
    clt r9
    bt .loop