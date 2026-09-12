.include "macros.inc"

.section .text, "ax"

.balign 4

.fn fn_800A6AB8, global
    stwu r1, -0x50(r1)
    mflr r0
    lis r4, lbl_804141F8@ha
    stw r0, 0x54(r1)
    stw r31, 0x4c(r1)
    addi r31, r4, lbl_804141F8@l
    stw r30, 0x48(r1)
    lbz r0, 0x18(r3)
    lbz r30, 0x1c(r3)
    cmplwi r0, 0x1
    bne .L_800A6B10
    addi r3, r31, 0x0
    bl usr_puts_serial
    cmplwi r30, 0x0
    beq .L_800A6B00
    addi r3, r31, 0x20
    bl usr_puts_serial
    b .L_800A6B08
.L_800A6B00:
    addi r3, r31, 0x28
    bl usr_puts_serial
.L_800A6B08:
    mr r3, r30
    bl fn_800AAF30
.L_800A6B10:
    addi r3, r1, 0x8
    li r4, 0x0
    li r5, 0x40
    bl memset
    li r3, 0x80
    li r5, 0x40
    li r0, 0x0
    stb r3, 0xc(r1)
    addi r3, r1, 0x8
    li r4, 0x40
    stw r5, 0x8(r1)
    stb r0, 0x10(r1)
    bl fn_800AAB08
    lwz r0, 0x54(r1)
    li r3, 0x0
    lwz r31, 0x4c(r1)
    lwz r30, 0x48(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
.endfn fn_800A6AB8
