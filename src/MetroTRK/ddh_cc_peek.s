.include "macros.inc"

.section .text, "ax"

.balign 4

.fn ddh_cc_peek, global
    stwu r1, -0x810(r1)
    mflr r0
    stw r0, 0x814(r1)
    stw r31, 0x80c(r1)
    bl EXI2_Poll
    mr. r31, r3
    bgt .L_800AB144
    li r3, 0x0
    b .L_800AB17C
.L_800AB144:
    mr r4, r31
    addi r3, r1, 0x8
    bl EXI2_ReadN
    cmpwi r3, 0x0
    bne .L_800AB170
    lis r3, lbl_804F52F0@ha
    mr r5, r31
    addi r3, r3, lbl_804F52F0@l
    addi r4, r1, 0x8
    bl fn_800AB548
    b .L_800AB178
.L_800AB170:
    li r3, -0x2719
    b .L_800AB17C
.L_800AB178:
    mr r3, r31
.L_800AB17C:
    lwz r0, 0x814(r1)
    lwz r31, 0x80c(r1)
    mtlr r0
    addi r1, r1, 0x810
    blr
.endfn ddh_cc_peek
