.include "macros.inc"

.section .text, "ax"

.balign 4

.fn ddh_cc_write, global
    stwu r1, -0x20(r1)
    mflr r0
    lis r5, lbl_80414638@ha
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    addi r31, r5, lbl_80414638@l
    stw r30, 0x18(r1)
    mr r30, r4
    stw r29, 0x14(r1)
    mr r29, r3
    lwz r0, lbl_805623F0@sda21(r0)
    cmpwi r0, 0x0
    bne .L_800AB224
    addi r4, r31, 0x0
    li r3, 0x8
    crclr cr1eq
    bl MWTRACE
    li r3, -0x2711
    b .L_800AB27C
.L_800AB224:
    mr r5, r3
    mr r6, r4
    addi r4, r31, 0x14
    li r3, 0x8
    crclr cr1eq
    bl MWTRACE
    b .L_800AB270
.L_800AB240:
    mr r5, r30
    addi r4, r31, 0x40
    li r3, 0x1
    crclr cr1eq
    bl MWTRACE
    mr r3, r29
    mr r4, r30
    bl EXI2_WriteN
    cmpwi r3, 0x0
    beq .L_800AB278
    add r29, r29, r3
    subf r30, r3, r30
.L_800AB270:
    cmpwi r30, 0x0
    bgt .L_800AB240
.L_800AB278:
    li r3, 0x0
.L_800AB27C:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
.endfn ddh_cc_write
