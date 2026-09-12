.include "macros.inc"

.section .text, "ax"

.balign 4

.fn fn_800A7A64, global
    lis r4, lbl_804F4548@ha
    stw r3, lbl_804F4548@l(r4)
    blr
.endfn fn_800A7A64

.fn fn_800A7A70, global
    lis r3, lbl_804F4548@ha
    addi r3, r3, lbl_804F4548@l
    lwz r3, 0x0(r3)
    blr
.endfn fn_800A7A70

.fn fn_800A7A80, global
    stwu r1, -0x20(r1)
    mflr r0
    lis r6, lbl_804143D4@ha
    lis r5, lbl_804143DC@ha
    stw r0, 0x24(r1)
    stmw r27, 0xc(r1)
    mr r27, r4
    mr r31, r3
    addi r29, r6, lbl_804143D4@l
    addi r30, r5, lbl_804143DC@l
    li r28, 0x0
    b .L_800A7AF8
.L_800A7AB0:
    lbz r5, 0x0(r31)
    mr r4, r29
    li r3, 0x8
    crclr cr1eq
    bl MWTRACE
    slwi r0, r28, 28
    srwi r3, r28, 31
    subf r0, r3, r0
    rotlwi r0, r0, 4
    add r0, r0, r3
    cmpwi r0, 0xf
    bne .L_800A7AF0
    mr r4, r30
    li r3, 0x8
    crclr cr1eq
    bl MWTRACE
.L_800A7AF0:
    addi r28, r28, 0x1
    addi r31, r31, 0x1
.L_800A7AF8:
    cmpw r28, r27
    blt .L_800A7AB0
    lis r4, lbl_804143DC@ha
    li r3, 0x8
    addi r4, r4, lbl_804143DC@l
    crclr cr1eq
    bl MWTRACE
    lmw r27, 0xc(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
.endfn fn_800A7A80

.fn fn_800A7B28, global
    stwu r1, -0x70(r1)
    mflr r0
    stw r0, 0x74(r1)
    stw r31, 0x6c(r1)
    mr r31, r5
    li r5, 0x40
    stw r30, 0x68(r1)
    mr r30, r6
    stw r29, 0x64(r1)
    mr r29, r4
    li r4, 0x0
    stw r28, 0x60(r1)
    mr r28, r3
    addi r3, r1, 0x14
    bl memset
    li r3, 0xd4
    li r0, 0x40
    stb r3, 0x18(r1)
    addi r3, r1, 0xc
    addi r4, r1, 0x8
    stw r0, 0x14(r1)
    stw r28, 0x1c(r1)
    lwz r0, 0x0(r29)
    stw r0, 0x20(r1)
    stb r31, 0x24(r1)
    bl TRKGetFreeBuffer
    mr. r31, r3
    bne .L_800A7BAC
    lwz r3, 0x8(r1)
    addi r4, r1, 0x14
    li r5, 0x40
    bl fn_800A612C
    mr r31, r3
.L_800A7BAC:
    cmpwi r31, 0x0
    bne .L_800A7C0C
    li r3, 0x0
    li r0, -0x1
    stw r3, 0x0(r30)
    addi r4, r1, 0x10
    li r5, 0x3
    li r6, 0x3
    stw r0, 0x0(r29)
    li r7, 0x0
    lwz r3, 0x8(r1)
    bl fn_800A7E3C
    mr. r31, r3
    bne .L_800A7C04
    lwz r3, 0x10(r1)
    bl TRKGetBuffer
    cmplwi r3, 0x0
    beq .L_800A7C04
    lwz r0, 0x20(r3)
    stw r0, 0x0(r30)
    lwz r0, 0x28(r3)
    stw r0, 0x0(r29)
.L_800A7C04:
    lwz r3, 0x10(r1)
    bl TRKReleaseBuffer
.L_800A7C0C:
    lwz r3, 0xc(r1)
    bl TRKReleaseBuffer
    lwz r0, 0x74(r1)
    mr r3, r31
    lwz r31, 0x6c(r1)
    lwz r30, 0x68(r1)
    lwz r29, 0x64(r1)
    lwz r28, 0x60(r1)
    mtlr r0
    addi r1, r1, 0x70
    blr
.endfn fn_800A7B28

.fn fn_800A7C38, global
    stwu r1, -0x70(r1)
    mflr r0
    li r5, 0x40
    stw r0, 0x74(r1)
    stw r31, 0x6c(r1)
    mr r31, r3
    addi r3, r1, 0x14
    stw r30, 0x68(r1)
    stw r29, 0x64(r1)
    mr r29, r4
    li r4, 0x0
    bl memset
    li r3, 0xd3
    li r0, 0x40
    stb r3, 0x18(r1)
    addi r3, r1, 0xc
    addi r4, r1, 0x8
    stw r0, 0x14(r1)
    stw r31, 0x1c(r1)
    bl TRKGetFreeBuffer
    mr. r31, r3
    bne .L_800A7CA4
    lwz r3, 0x8(r1)
    addi r4, r1, 0x14
    li r5, 0x40
    bl fn_800A612C
    mr r31, r3
.L_800A7CA4:
    cmpwi r31, 0x0
    bne .L_800A7CF8
    li r0, 0x0
    addi r4, r1, 0x10
    stw r0, 0x0(r29)
    li r5, 0x3
    li r6, 0x3
    li r7, 0x0
    lwz r3, 0x8(r1)
    bl fn_800A7E3C
    mr. r31, r3
    bne .L_800A7CE0
    lwz r3, 0x10(r1)
    bl TRKGetBuffer
    mr r30, r3
.L_800A7CE0:
    cmpwi r31, 0x0
    bne .L_800A7CF0
    lwz r0, 0x20(r30)
    stw r0, 0x0(r29)
.L_800A7CF0:
    lwz r3, 0x10(r1)
    bl TRKReleaseBuffer
.L_800A7CF8:
    lwz r3, 0xc(r1)
    bl TRKReleaseBuffer
    lwz r0, 0x74(r1)
    mr r3, r31
    lwz r31, 0x6c(r1)
    lwz r30, 0x68(r1)
    lwz r29, 0x64(r1)
    mtlr r0
    addi r1, r1, 0x70
    blr
.endfn fn_800A7C38

.fn fn_800A7D20, global
    stwu r1, -0x70(r1)
    mflr r0
    stw r0, 0x74(r1)
    stmw r27, 0x5c(r1)
    mr r27, r3
    mr r31, r4
    mr r28, r5
    mr r29, r6
    addi r3, r1, 0x14
    li r4, 0x0
    li r5, 0x40
    bl memset
    li r3, 0x0
    li r0, 0xd2
    stw r3, 0x0(r28)
    mr r3, r27
    stb r0, 0x18(r1)
    bl strlen
    addi r0, r3, 0x41
    stb r31, 0x1c(r1)
    mr r3, r27
    stw r0, 0x14(r1)
    bl strlen
    addi r0, r3, 0x1
    addi r3, r1, 0xc
    sth r0, 0x20(r1)
    addi r4, r1, 0x8
    bl TRKGetFreeBuffer
    lwz r3, 0x8(r1)
    addi r4, r1, 0x14
    li r5, 0x40
    bl fn_800A612C
    mr. r31, r3
    bne .L_800A7DC8
    mr r3, r27
    bl strlen
    mr r5, r3
    lwz r3, 0x8(r1)
    mr r4, r27
    addi r5, r5, 0x1
    bl fn_800A612C
    mr r31, r3
.L_800A7DC8:
    cmpwi r31, 0x0
    bne .L_800A7E1C
    li r0, 0x0
    addi r4, r1, 0x10
    stw r0, 0x0(r29)
    li r5, 0x7
    li r6, 0x3
    li r7, 0x0
    lwz r3, 0x8(r1)
    bl fn_800A7E3C
    mr. r31, r3
    bne .L_800A7E04
    lwz r3, 0x10(r1)
    bl TRKGetBuffer
    mr r30, r3
.L_800A7E04:
    lwz r0, 0x20(r30)
    stw r0, 0x0(r29)
    lwz r0, 0x18(r30)
    stw r0, 0x0(r28)
    lwz r3, 0x10(r1)
    bl TRKReleaseBuffer
.L_800A7E1C:
    lwz r3, 0xc(r1)
    bl TRKReleaseBuffer
    mr r3, r31
    lmw r27, 0x5c(r1)
    lwz r0, 0x74(r1)
    mtlr r0
    addi r1, r1, 0x70
    blr
.endfn fn_800A7D20

.fn fn_800A7E3C, global
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    li r0, -0x1
    stmw r21, 0x14(r1)
    mr r22, r4
    lis r4, lbl_804143E0@ha
    mr r21, r3
    mr r23, r7
    addi r27, r6, 0x1
    addi r31, r4, lbl_804143E0@l
    li r30, 0x0
    li r24, 0x1
    stw r0, 0x0(r22)
    b .L_800A7FD8
.L_800A7E78:
    addi r4, r31, 0x0
    li r3, 0x1
    crclr cr1eq
    bl MWTRACE
    mr r3, r21
    bl fn_800A5D7C
    mr. r30, r3
    bne .L_800A7FD4
    cmpwi r23, 0x0
    beq .L_800A7EA4
    li r28, 0x0
.L_800A7EA4:
    bl fn_800A6778
    stw r3, 0x0(r22)
    lwz r3, 0x0(r22)
    cmpwi r3, -0x1
    bne .L_800A7ED4
    cmpwi r23, 0x0
    beq .L_800A7EA4
    lis r4, 0x4c5
    addi r28, r28, 0x1
    subi r0, r4, 0x4c14
    cmplw r28, r0
    blt .L_800A7EA4
.L_800A7ED4:
    cmpwi r3, -0x1
    beq .L_800A7F34
    li r24, 0x0
    bl TRKGetBuffer
    li r4, 0x0
    mr r29, r3
    bl fn_800A63C0
    lwz r4, 0x8(r29)
    addi r3, r29, 0x10
    bl fn_800A7A80
    lbz r26, 0x14(r29)
    addi r4, r31, 0x18
    li r3, 0x1
    mr r5, r26
    mr r6, r26
    crclr cr1eq
    bl MWTRACE
    cmplwi r26, 0x80
    bge .L_800A7F34
    lwz r3, 0x0(r22)
    bl fn_800A66C8
    li r0, -0x1
    stw r0, 0x0(r22)
    b .L_800A7EA4
.L_800A7F34:
    lwz r0, 0x0(r22)
    cmpwi r0, -0x1
    beq .L_800A7FD4
    lwz r0, 0x8(r29)
    cmplwi r0, 0x40
    bge .L_800A7F50
    li r24, 0x1
.L_800A7F50:
    cmpwi r30, 0x0
    bne .L_800A7F78
    cmpwi r24, 0x0
    bne .L_800A7F78
    lbz r25, 0x18(r29)
    addi r4, r31, 0x40
    li r3, 0x1
    mr r5, r25
    crclr cr1eq
    bl MWTRACE
.L_800A7F78:
    cmpwi r30, 0x0
    bne .L_800A7FB4
    cmpwi r24, 0x0
    bne .L_800A7FB4
    cmpwi r26, 0x80
    mr r5, r26
    bne .L_800A7F9C
    cmpwi r25, 0x0
    beq .L_800A7FB4
.L_800A7F9C:
    mr r6, r25
    addi r4, r31, 0x54
    li r3, 0x8
    crclr cr1eq
    bl MWTRACE
    li r24, 0x1
.L_800A7FB4:
    cmpwi r30, 0x0
    bne .L_800A7FC4
    cmpwi r24, 0x0
    beq .L_800A7FD4
.L_800A7FC4:
    lwz r3, 0x0(r22)
    bl TRKReleaseBuffer
    li r0, -0x1
    stw r0, 0x0(r22)
.L_800A7FD4:
    subi r27, r27, 0x1
.L_800A7FD8:
    cmpwi r27, 0x0
    beq .L_800A7FF4
    lwz r0, 0x0(r22)
    cmpwi r0, -0x1
    bne .L_800A7FF4
    cmpwi r30, 0x0
    beq .L_800A7E78
.L_800A7FF4:
    lwz r0, 0x0(r22)
    cmpwi r0, -0x1
    bne .L_800A8004
    li r30, 0x800
.L_800A8004:
    mr r3, r30
    lmw r21, 0x14(r1)
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
.endfn fn_800A7E3C

.fn fn_800A801C, global
    stwu r1, -0x90(r1)
    mflr r0
    stw r0, 0x94(r1)
    stmw r19, 0x5c(r1)
    mr. r24, r4
    mr r23, r3
    mr r25, r5
    mr r26, r6
    mr r27, r7
    mr r28, r8
    beq .L_800A8054
    lwz r0, 0x0(r25)
    cmplwi r0, 0x0
    bne .L_800A805C
.L_800A8054:
    li r3, 0x2
    b .L_800A8228
.L_800A805C:
    li r0, 0x0
    li r29, 0x0
    stw r0, 0x0(r26)
    li r30, 0x0
    li r21, 0x0
    b .L_800A81F8
.L_800A8074:
    addi r3, r1, 0x14
    li r4, 0x0
    li r5, 0x40
    bl memset
    lwz r0, 0x0(r25)
    li r3, 0x800
    subf r0, r30, r0
    cmplwi r0, 0x800
    bgt .L_800A809C
    mr r3, r0
.L_800A809C:
    cmpwi r28, 0x0
    mr r31, r3
    li r0, 0xd0
    beq .L_800A80B0
    li r0, 0xd1
.L_800A80B0:
    cmpwi r28, 0x0
    stb r0, 0x18(r1)
    li r0, 0x40
    bne .L_800A80C4
    addi r0, r31, 0x40
.L_800A80C4:
    stw r0, 0x14(r1)
    addi r3, r1, 0xc
    addi r4, r1, 0x8
    stw r23, 0x1c(r1)
    sth r31, 0x20(r1)
    bl TRKGetFreeBuffer
    lwz r3, 0x8(r1)
    addi r4, r1, 0x14
    li r5, 0x40
    bl fn_800A612C
    cmpwi r28, 0x0
    mr r21, r3
    bne .L_800A8114
    cmpwi r21, 0x0
    bne .L_800A8114
    lwz r3, 0x8(r1)
    mr r5, r31
    add r4, r24, r30
    bl fn_800A612C
    mr r21, r3
.L_800A8114:
    cmpwi r21, 0x0
    bne .L_800A81EC
    cmpwi r27, 0x0
    beq .L_800A81E0
    cmpwi r28, 0x0
    li r0, 0x0
    beq .L_800A813C
    cmplwi r23, 0x0
    bne .L_800A813C
    li r0, 0x1
.L_800A813C:
    cmpwi r28, 0x0
    lwz r3, 0x8(r1)
    addi r4, r1, 0x10
    li r5, 0x5
    cntlzw r0, r0
    li r6, 0x3
    srwi r7, r0, 5
    bl fn_800A7E3C
    mr. r21, r3
    bne .L_800A8170
    lwz r3, 0x10(r1)
    bl TRKGetBuffer
    mr r22, r3
.L_800A8170:
    lwz r0, 0x20(r22)
    cmpwi r28, 0x0
    lhz r19, 0x24(r22)
    clrlwi r20, r0, 24
    beq .L_800A81C0
    cmpwi r21, 0x0
    bne .L_800A81C0
    cmplw r19, r31
    bgt .L_800A81C0
    mr r3, r22
    li r4, 0x40
    bl fn_800A63C0
    mr r3, r22
    mr r5, r19
    add r4, r24, r30
    bl fn_800A5EB0
    mr r21, r3
    cmpwi r21, 0x302
    bne .L_800A81C0
    li r21, 0x0
.L_800A81C0:
    cmplw r19, r31
    beq .L_800A81D0
    mr r31, r19
    li r29, 0x1
.L_800A81D0:
    stw r20, 0x0(r26)
    lwz r3, 0x10(r1)
    bl TRKReleaseBuffer
    b .L_800A81EC
.L_800A81E0:
    lwz r3, 0x8(r1)
    bl fn_800A5D7C
    mr r21, r3
.L_800A81EC:
    lwz r3, 0xc(r1)
    bl TRKReleaseBuffer
    add r30, r30, r31
.L_800A81F8:
    cmpwi r29, 0x0
    bne .L_800A8220
    lwz r0, 0x0(r25)
    cmplw r30, r0
    bge .L_800A8220
    cmpwi r21, 0x0
    bne .L_800A8220
    lwz r0, 0x0(r26)
    cmpwi r0, 0x0
    beq .L_800A8074
.L_800A8220:
    stw r30, 0x0(r25)
    mr r3, r21
.L_800A8228:
    lmw r19, 0x5c(r1)
    lwz r0, 0x94(r1)
    mtlr r0
    addi r1, r1, 0x90
    blr
.endfn fn_800A801C
