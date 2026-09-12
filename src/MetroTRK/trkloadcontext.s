.include "macros.inc"

.section .text, "ax"

.balign 4

.fn TRKLoadContext, global
    lwz r0, 0x0(r3)
    lwz r1, 0x4(r3)
    lwz r2, 0x8(r3)
    lhz r5, 0x1a2(r3)
    rlwinm. r6, r5, 0, 30, 30
    beq .L_800AA9BC
    rlwinm r5, r5, 0, 31, 29
    sth r5, 0x1a2(r3)
    lmw r5, 0x14(r3)
    b .L_800AA9C0
.L_800AA9BC:
    lmw r13, 0x34(r3)
.L_800AA9C0:
    mr r31, r3
    mr r3, r4
    lwz r4, 0x80(r31)
    mtcrf 255, r4
    lwz r4, 0x84(r31)
    mtlr r4
    lwz r4, 0x88(r31)
    mtctr r4
    lwz r4, 0x8c(r31)
    mtxer r4
    mfmsr r4
    rlwinm r4, r4, 0, 17, 15
    rlwinm r4, r4, 0, 31, 29
    mtmsr r4
    mtsprg 1, r2
    lwz r4, 0xc(r31)
    mtsprg 2, r4
    lwz r4, 0x10(r31)
    mtsprg 3, r4
    lwz r2, 0x198(r31)
    lwz r4, 0x19c(r31)
    lwz r31, 0x7c(r31)
    b TRKInterruptHandler
.endfn TRKLoadContext
