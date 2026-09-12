.include "macros.inc"

.section .text, "ax"

.balign 4

.fn fn_800A6C08, global
    stwu r1, -0x160(r1)
    mflr r0
    li r4, 0x0
    stw r0, 0x164(r1)
    stmw r27, 0x14c(r1)
    mr r27, r3
    bl fn_800A63C0
    lbz r31, 0x18(r27)
    lwz r29, 0x20(r27)
    cmpwi r31, 0x10
    lwz r28, 0x24(r27)
    beq .L_800A6C60
    bge .L_800A6C54
    cmpwi r31, 0x1
    beq .L_800A6CA8
    bge .L_800A6CF8
    cmpwi r31, 0x0
    bge .L_800A6C60
    b .L_800A6CF8
.L_800A6C54:
    cmpwi r31, 0x12
    bge .L_800A6CF8
    b .L_800A6CA8
.L_800A6C60:
    lbz r30, 0x1c(r27)
    cmplwi r30, 0x1
    bge .L_800A6D34
    addi r3, r1, 0x108
    li r4, 0x0
    li r5, 0x40
    bl memset
    li r3, 0x80
    li r5, 0x40
    li r0, 0x11
    stb r3, 0x10c(r1)
    addi r3, r1, 0x108
    li r4, 0x40
    stw r5, 0x108(r1)
    stb r0, 0x110(r1)
    bl fn_800AAB08
    li r3, 0x0
    b .L_800A6E14
.L_800A6CA8:
    bl fn_800A8AC4
    cmplw r3, r29
    blt .L_800A6CBC
    cmplw r3, r28
    ble .L_800A6D34
.L_800A6CBC:
    addi r3, r1, 0xc8
    li r4, 0x0
    li r5, 0x40
    bl memset
    li r3, 0x80
    li r5, 0x40
    li r0, 0x11
    stb r3, 0xcc(r1)
    addi r3, r1, 0xc8
    li r4, 0x40
    stw r5, 0xc8(r1)
    stb r0, 0xd0(r1)
    bl fn_800AAB08
    li r3, 0x0
    b .L_800A6E14
.L_800A6CF8:
    addi r3, r1, 0x88
    li r4, 0x0
    li r5, 0x40
    bl memset
    li r3, 0x80
    li r5, 0x40
    li r0, 0x12
    stb r3, 0x8c(r1)
    addi r3, r1, 0x88
    li r4, 0x40
    stw r5, 0x88(r1)
    stb r0, 0x90(r1)
    bl fn_800AAB08
    li r3, 0x0
    b .L_800A6E14
.L_800A6D34:
    bl TRKTargetStopped
    cmpwi r3, 0x0
    bne .L_800A6D7C
    addi r3, r1, 0x48
    li r4, 0x0
    li r5, 0x40
    bl memset
    li r3, 0x80
    li r5, 0x40
    li r0, 0x16
    stb r3, 0x4c(r1)
    addi r3, r1, 0x48
    li r4, 0x40
    stw r5, 0x48(r1)
    stb r0, 0x50(r1)
    bl fn_800AAB08
    li r3, 0x0
    b .L_800A6E14
.L_800A6D7C:
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
    cmpwi r31, 0x10
    li r3, 0x0
    beq .L_800A6DE4
    bge .L_800A6DD8
    cmpwi r31, 0x1
    beq .L_800A6DFC
    bge .L_800A6E14
    cmpwi r31, 0x0
    bge .L_800A6DE4
    b .L_800A6E14
.L_800A6DD8:
    cmpwi r31, 0x12
    bge .L_800A6E14
    b .L_800A6DFC
.L_800A6DE4:
    subfic r0, r31, 0x10
    mr r3, r30
    cntlzw r0, r0
    srwi r4, r0, 5
    bl fn_800A8B8C
    b .L_800A6E14
.L_800A6DFC:
    subfic r0, r31, 0x11
    mr r3, r29
    cntlzw r0, r0
    mr r4, r28
    srwi r5, r0, 5
    bl fn_800A8AD4
.L_800A6E14:
    lmw r27, 0x14c(r1)
    lwz r0, 0x164(r1)
    mtlr r0
    addi r1, r1, 0x160
    blr
.endfn fn_800A6C08
