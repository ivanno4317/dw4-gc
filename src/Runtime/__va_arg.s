.include "macros.inc"

.section .text, "ax"

.balign 4

.fn __va_arg, global
    lbz r7, 0x0(r3)
    cmpwi r4, 0x3
    mr r6, r3
    li r0, 0x8
    li r8, 0x4
    extsb r7, r7
    li r9, 0x1
    li r5, 0x0
    li r10, 0x0
    li r11, 0x4
    bne .L_800A3004
    lbz r7, 0x1(r3)
    addi r6, r3, 0x1
    li r8, 0x8
    li r10, 0x20
    extsb r7, r7
    li r11, 0x8
.L_800A3004:
    cmpwi r4, 0x2
    bne .L_800A3024
    clrlwi. r0, r7, 31
    li r8, 0x8
    li r0, 0x7
    beq .L_800A3020
    li r5, 0x1
.L_800A3020:
    li r9, 0x2
.L_800A3024:
    cmpw r7, r0
    bge .L_800A304C
    add r7, r7, r5
    lwz r5, 0x8(r3)
    mullw r3, r7, r11
    add r0, r7, r9
    stb r0, 0x0(r6)
    add r6, r10, r3
    add r6, r5, r6
    b .L_800A3074
.L_800A304C:
    li r5, 0x8
    subi r0, r8, 0x1
    stb r5, 0x0(r6)
    nor r6, r0, r0
    lwz r0, 0x4(r3)
    add r5, r8, r0
    subi r0, r5, 0x1
    and r6, r6, r0
    add r0, r6, r8
    stw r0, 0x4(r3)
.L_800A3074:
    cmpwi r4, 0x0
    bne .L_800A3080
    lwz r6, 0x0(r6)
.L_800A3080:
    mr r3, r6
    blr
.endfn __va_arg
