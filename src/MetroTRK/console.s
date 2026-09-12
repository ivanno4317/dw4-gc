.include "macros.inc"

.section .text, "ax"

.balign 4

.fn fn_800AAF20, global
    lis r3, lbl_804F4AE8@ha
    addi r3, r3, lbl_804F4AE8@l
    lbz r3, 0x0(r3)
    blr
.endfn fn_800AAF20

.fn fn_800AAF30, global
    lis r4, lbl_804F4AE8@ha
    stb r3, lbl_804F4AE8@l(r4)
    blr
.endfn fn_800AAF30

.fn __TRK_write_console, global
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r5
    stw r30, 0x18(r1)
    mr r30, r4
    bl fn_800AAF20
    clrlwi. r0, r3, 24
    bne .L_800AAF6C
    li r3, 0x1
    b .L_800AAFE0
.L_800AAF6C:
    bl fn_800A7A70
    cmpwi r3, 0x0
    bne .L_800AAF80
    li r3, 0x1
    b .L_800AAFE0
.L_800AAF80:
    lwz r0, 0x0(r31)
    mr r6, r30
    addi r5, r1, 0x8
    li r3, 0xd0
    stw r0, 0x8(r1)
    li r4, 0x1
    bl fn_800A9F70
    clrlwi r0, r3, 24
    lwz r3, 0x8(r1)
    cmpwi r0, 0x1
    stw r3, 0x0(r31)
    beq .L_800AAFDC
    bge .L_800AAFC0
    cmpwi r0, 0x0
    bge .L_800AAFCC
    b .L_800AAFDC
.L_800AAFC0:
    cmpwi r0, 0x3
    bge .L_800AAFDC
    b .L_800AAFD4
.L_800AAFCC:
    li r3, 0x0
    b .L_800AAFE0
.L_800AAFD4:
    li r3, 0x2
    b .L_800AAFE0
.L_800AAFDC:
    li r3, 0x1
.L_800AAFE0:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
.endfn __TRK_write_console

.fn __TRK_read_console, global
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r5
    stw r30, 0x18(r1)
    mr r30, r4
    bl fn_800AAF20
    clrlwi. r0, r3, 24
    bne .L_800AB028
    li r3, 0x1
    b .L_800AB09C
.L_800AB028:
    bl fn_800A7A70
    cmpwi r3, 0x0
    bne .L_800AB03C
    li r3, 0x1
    b .L_800AB09C
.L_800AB03C:
    lwz r0, 0x0(r31)
    mr r6, r30
    addi r5, r1, 0x8
    li r3, 0xd1
    stw r0, 0x8(r1)
    li r4, 0x0
    bl fn_800A9F70
    clrlwi r0, r3, 24
    lwz r3, 0x8(r1)
    cmpwi r0, 0x1
    stw r3, 0x0(r31)
    beq .L_800AB098
    bge .L_800AB07C
    cmpwi r0, 0x0
    bge .L_800AB088
    b .L_800AB098
.L_800AB07C:
    cmpwi r0, 0x3
    bge .L_800AB098
    b .L_800AB090
.L_800AB088:
    li r3, 0x0
    b .L_800AB09C
.L_800AB090:
    li r3, 0x2
    b .L_800AB09C
.L_800AB098:
    li r3, 0x1
.L_800AB09C:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
.endfn __TRK_read_console

.section .bss, "wa", @nobits
.balign 8

.obj lbl_804F4AE8, global
    .skip 0x8
.endobj lbl_804F4AE8
