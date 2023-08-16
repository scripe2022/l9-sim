#define accumulate r0
upper: 20
ldr =upper
mvt r3 // r3: n
mov 0  // r2: sum
mvt r1 // r1: i
.loop:
    mvf r1
    add r2
    mvt r2
    mvf r1
    clt r3
    add 1
    mvt r1
    bt .loop
mvf r2