#define pattern r9
#define dcrs r5
#define bs r6
#define tot r7
#define cur r3
#define nxt r4

size:
    32
mask:
    0b00011111

ldr =size
ldr r0
lsr 3
mvt r9 // r9: pattern
mov 0
mvt r8 // r8: i
mvt r7 // r7: tot
mvt r6 // r6: bs
mvt r5 // r5: dcrs

.loop:
    ldr =mask
    mvt r4 // r4: mask
    ldr r8
    mvt r3 // r3: cur
    mov 0
    mvt r2 // r2: tb

    // xxxxx000
    mvf r3
    lsr 3
    and r4
    xor pattern
    norr r0
    add r2
    mvt r2

    // 0xxxxx00
    mvf r3
    lsr 2
    and r4
    xor pattern
    norr r0
    add r2
    mvt r2

    // 00xxxxx0
    mvf r3
    lsr 1
    and r4
    xor pattern
    norr r0
    add r2
    mvt r2

    // 000xxxxx
    mvf r3
    and r4
    xor pattern
    norr r0
    add r2
    mvt r2

    // dcrs += tb
    add dcrs
    mvt dcrs

    // bs += norr(tb) ^ 1
    norr r2
    xor 1
    add bs
    mvt bs

    // if (i == 31) break
    ldr =size
    sub 1
    ceq r8
    bt .done

    // nxt = mem[i+1] >> 4
    mvf r8
    add 1
    mvt r8
    ldr r0
    lsr 4
    mvt nxt

    // ....xxxx x.......
    lsr 3
    mvt r2 // r2: nxt >> 3
    mvf cur
    and 0b01111
    lsl 1
    or r2
    xor pattern
    norr r0
    add tot
    mvt tot

    // .....xxx xx......
    mvf nxt
    lsr 2
    mvt r2 // r2: nxt >> 2
    mvf cur
    and 0b00111
    lsl 2
    or r2
    xor pattern
    norr r0
    add tot
    mvt tot

    // ......xx xxx.....
    mvf nxt
    lsr 1
    mvt r2 // r2: nxt >> 1
    mvf cur
    and 0b00011
    lsl 3
    or r2
    xor pattern
    norr r0
    add tot
    mvt tot

    // .....00x xxxx....
    mvf cur
    and 0b00001
    lsl 4
    or nxt
    xor pattern
    norr r0
    add tot
    mvt tot

    b .loop
.done:

mvf tot
add dcrs
mvt tot

ldr =size
add 1
mvt r2 // r2: 33
add 1
mvt r3 // r3: 34
add 1
mvt r4 // r4: 35

mvf dcrs
str r2
mvf bs
str r3
mvf tot
str r4