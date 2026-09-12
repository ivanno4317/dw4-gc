.include "macros.inc"

.section .text, "ax"

.balign 4

.fn fn_800A5DC0, global
    stwu r1, -0x30(r1)
    mflr r0
    lis r6, gTRKBigEndian@ha
    stw r0, 0x34(r1)
    stmw r24, 0x10(r1)
    mr r28, r3
    mr r29, r5
    mr r31, r4
    addi r27, r6, gTRKBigEndian@l
    li r30, 0x0
    li r3, 0x0
    b .L_800A5E8C
.L_800A5DF0:
    lwz r0, 0x0(r27)
    cmpwi r0, 0x0
    beq .L_800A5E04
    mr r25, r31
    b .L_800A5E08
.L_800A5E04:
    addi r25, r1, 0x8
.L_800A5E08:
    lwz r3, 0xc(r28)
    li r24, 0x4
    lwz r0, 0x8(r28)
    li r26, 0x0
    subf r0, r3, r0
    cmplw r24, r0
    ble .L_800A5E2C
    li r26, 0x302
    mr r24, r0
.L_800A5E2C:
    addi r4, r3, 0x10
    mr r3, r25
    mr r5, r24
    add r4, r28, r4
    bl TRK_memcpy
    lwz r0, 0xc(r28)
    add r0, r0, r24
    stw r0, 0xc(r28)
    lwz r0, 0x0(r27)
    cmpwi r0, 0x0
    bne .L_800A5E80
    cmpwi r26, 0x0
    bne .L_800A5E80
    lbz r0, 0x3(r25)
    stb r0, 0x0(r31)
    lbz r0, 0x2(r25)
    stb r0, 0x1(r31)
    lbz r0, 0x1(r25)
    stb r0, 0x2(r31)
    lbz r0, 0x0(r25)
    stb r0, 0x3(r31)
.L_800A5E80:
    mr r3, r26
    addi r31, r31, 0x4
    addi r30, r30, 0x1
.L_800A5E8C:
    cmpwi r3, 0x0
    bne .L_800A5E9C
    cmpw r30, r29
    blt .L_800A5DF0
.L_800A5E9C:
    lmw r24, 0x10(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
.endfn fn_800A5DC0

.fn fn_800A5EB0, global
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r26, 0x8(r1)
    mr r26, r3
    mr r27, r4
    mr r28, r5
    li r29, 0x0
    li r3, 0x0
    b .L_800A5F24
.L_800A5ED8:
    lwz r3, 0xc(r26)
    li r30, 0x1
    lwz r0, 0x8(r26)
    li r31, 0x0
    subf r0, r3, r0
    cmplw r30, r0
    ble .L_800A5EFC
    li r31, 0x302
    mr r30, r0
.L_800A5EFC:
    addi r4, r3, 0x10
    mr r5, r30
    add r3, r27, r29
    add r4, r26, r4
    bl TRK_memcpy
    lwz r0, 0xc(r26)
    mr r3, r31
    addi r29, r29, 0x1
    add r0, r0, r30
    stw r0, 0xc(r26)
.L_800A5F24:
    cmpwi r3, 0x0
    bne .L_800A5F34
    cmpw r29, r28
    blt .L_800A5ED8
.L_800A5F34:
    lmw r26, 0x8(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
.endfn fn_800A5EB0

.fn fn_800A5F48, global
    stwu r1, -0x30(r1)
    mflr r0
    lis r5, gTRKBigEndian@ha
    stw r0, 0x34(r1)
    stmw r27, 0x1c(r1)
    mr r27, r3
    mr r30, r4
    lwz r0, gTRKBigEndian@l(r5)
    cmpwi r0, 0x0
    beq .L_800A5F78
    mr r31, r30
    b .L_800A5F7C
.L_800A5F78:
    addi r31, r1, 0x8
.L_800A5F7C:
    lwz r3, 0xc(r27)
    li r28, 0x8
    lwz r0, 0x8(r27)
    li r29, 0x0
    subf r0, r3, r0
    cmplw r28, r0
    ble .L_800A5FA0
    li r29, 0x302
    mr r28, r0
.L_800A5FA0:
    addi r4, r3, 0x10
    mr r3, r31
    mr r5, r28
    add r4, r27, r4
    bl TRK_memcpy
    lwz r0, 0xc(r27)
    lis r3, gTRKBigEndian@ha
    add r0, r0, r28
    stw r0, 0xc(r27)
    lwz r0, gTRKBigEndian@l(r3)
    cmpwi r0, 0x0
    bne .L_800A6018
    cmpwi r29, 0x0
    bne .L_800A6018
    lbz r0, 0x7(r31)
    stb r0, 0x0(r30)
    lbz r0, 0x6(r31)
    stb r0, 0x1(r30)
    lbz r0, 0x5(r31)
    stb r0, 0x2(r30)
    lbz r0, 0x4(r31)
    stb r0, 0x3(r30)
    lbz r0, 0x3(r31)
    stb r0, 0x4(r30)
    lbz r0, 0x2(r31)
    stb r0, 0x5(r30)
    lbz r0, 0x1(r31)
    stb r0, 0x6(r30)
    lbz r0, 0x0(r31)
    stb r0, 0x7(r30)
.L_800A6018:
    mr r3, r29
    lmw r27, 0x1c(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
.endfn fn_800A5F48

.fn fn_800A6030, global
    stwu r1, -0x30(r1)
    mflr r0
    lis r6, gTRKBigEndian@ha
    stw r0, 0x34(r1)
    stmw r25, 0x14(r1)
    mr r27, r3
    mr r28, r5
    mr r30, r4
    addi r31, r6, gTRKBigEndian@l
    li r29, 0x0
    li r3, 0x0
    b .L_800A6108
.L_800A6060:
    lwz r0, 0x0(r31)
    lwz r3, 0x0(r30)
    cmpwi r0, 0x0
    stw r3, 0x8(r1)
    beq .L_800A607C
    addi r4, r1, 0x8
    b .L_800A60A0
.L_800A607C:
    lbz r6, 0xb(r1)
    addi r4, r1, 0xc
    lbz r5, 0xa(r1)
    lbz r3, 0x9(r1)
    lbz r0, 0x8(r1)
    stb r6, 0xc(r1)
    stb r5, 0xd(r1)
    stb r3, 0xe(r1)
    stb r0, 0xf(r1)
.L_800A60A0:
    lwz r5, 0xc(r27)
    li r25, 0x4
    li r26, 0x0
    subfic r0, r5, 0x880
    cmplwi r0, 0x4
    bge .L_800A60C0
    li r26, 0x301
    mr r25, r0
.L_800A60C0:
    cmplwi r25, 0x1
    bne .L_800A60D8
    lbz r3, 0x0(r4)
    addi r0, r5, 0x10
    stbx r3, r27, r0
    b .L_800A60E8
.L_800A60D8:
    addi r3, r5, 0x10
    mr r5, r25
    add r3, r27, r3
    bl TRK_memcpy
.L_800A60E8:
    lwz r0, 0xc(r27)
    mr r3, r26
    addi r30, r30, 0x4
    addi r29, r29, 0x1
    add r0, r0, r25
    stw r0, 0xc(r27)
    lwz r0, 0xc(r27)
    stw r0, 0x8(r27)
.L_800A6108:
    cmpwi r3, 0x0
    bne .L_800A6118
    cmpw r29, r28
    blt .L_800A6060
.L_800A6118:
    lmw r25, 0x14(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
.endfn fn_800A6030
