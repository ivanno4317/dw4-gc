.include "macros.inc"

.section .text, "ax"

.balign 4

.fn usr_puts_serial, global
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    li r31, 0x0
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    mr r29, r3
    li r3, 0x0
    b .L_800A690C
.L_800A68E0:
    bl fn_800A7A70
    stb r30, 0x8(r1)
    mr r30, r3
    li r3, 0x0
    stb r31, 0x9(r1)
    bl fn_800A7A64
    addi r3, r1, 0x8
    bl OSReport
    mr r3, r30
    bl fn_800A7A64
    li r3, 0x0
.L_800A690C:
    cmpwi r3, 0x0
    bne .L_800A6924
    lbz r0, 0x0(r29)
    addi r29, r29, 0x1
    extsb. r30, r0
    bne .L_800A68E0
.L_800A6924:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
.endfn usr_puts_serial
