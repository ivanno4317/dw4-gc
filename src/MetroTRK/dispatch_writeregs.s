.include "macros.inc"

.section .text, "ax"

.balign 4

.fn fn_800A7448, global
    clrlwi r11, r1, 27
    mr r12, r1
    subfic r11, r11, -0x940
    stwux r1, r1, r11
    mflr r0
    stw r0, 0x4(r12)
    stmw r27, -0x14(r12)
    mr r27, r3
    lis r3, lbl_804141F8@ha
    addi r31, r3, lbl_804141F8@l
    addi r4, r31, 0x180
    li r3, 0x1
    lwz r28, 0x20(r27)
    lhz r29, 0x1c(r27)
    lbz r30, 0x18(r27)
    mr r6, r28
    lbz r5, 0x14(r27)
    mr r7, r29
    mr r8, r30
    crclr cr1eq
    bl MWTRACE
    rlwinm. r0, r30, 0, 30, 30
    beq .L_800A74E0
    addi r3, r1, 0x64
    li r4, 0x0
    li r5, 0x40
    bl memset
    li r3, 0x80
    li r5, 0x40
    li r0, 0x12
    stb r3, 0x68(r1)
    addi r3, r1, 0x64
    li r4, 0x40
    stw r5, 0x64(r1)
    stb r0, 0x6c(r1)
    bl fn_800AAB08
    li r3, 0x0
    b .L_800A766C
.L_800A74E0:
    stw r29, 0x20(r1)
    mr r3, r27
    li r4, 0x40
    bl fn_800A63C0
    rlwinm. r0, r30, 0, 25, 25
    beq .L_800A752C
    clrlwi r0, r28, 27
    addi r4, r1, 0x100
    lwz r5, 0x20(r1)
    mr r3, r27
    add r4, r4, r0
    bl fn_800A6290
    mr r4, r28
    addi r3, r1, 0x100
    addi r5, r1, 0x20
    li r6, 0x0
    bl fn_800A87B8
    mr r30, r3
    b .L_800A755C
.L_800A752C:
    lwz r5, 0x20(r1)
    mr r3, r27
    addi r4, r1, 0x100
    bl fn_800A6290
    extrwi r0, r30, 1, 28
    mr r4, r28
    addi r3, r1, 0x100
    addi r5, r1, 0x20
    xori r6, r0, 0x1
    li r7, 0x0
    bl fn_800A9B78
    mr r30, r3
.L_800A755C:
    mr r3, r27
    li r4, 0x0
    bl fn_800A63F0
    cmpwi r30, 0x0
    bne .L_800A75A8
    addi r3, r1, 0xa4
    li r4, 0x0
    li r5, 0x40
    bl memset
    li r3, 0x40
    li r0, 0x80
    stw r3, 0xa4(r1)
    mr r3, r27
    addi r4, r1, 0xa4
    li r5, 0x40
    stb r0, 0xa8(r1)
    stb r30, 0xac(r1)
    bl fn_800A631C
    mr r30, r3
.L_800A75A8:
    cmpwi r30, 0x0
    beq .L_800A7638
    subi r0, r30, 0x700
    cmplwi r0, 0x6
    bgt .L_800A75FC
    lis r3, jumptable_80477C38@ha
    slwi r0, r0, 2
    addi r3, r3, jumptable_80477C38@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
.L_800A75D4:
    li r30, 0x15
    b .L_800A7600
.L_800A75DC:
    li r30, 0x13
    b .L_800A7600
.L_800A75E4:
    li r30, 0x21
    b .L_800A7600
.L_800A75EC:
    li r30, 0x22
    b .L_800A7600
.L_800A75F4:
    li r30, 0x20
    b .L_800A7600
.L_800A75FC:
    li r30, 0x3
.L_800A7600:
    addi r3, r1, 0x24
    li r4, 0x0
    li r5, 0x40
    bl memset
    li r3, 0x80
    li r0, 0x40
    stb r3, 0x28(r1)
    addi r3, r1, 0x24
    li r4, 0x40
    stw r0, 0x24(r1)
    stb r30, 0x2c(r1)
    bl fn_800AAB08
    li r3, 0x0
    b .L_800A766C
.L_800A7638:
    addi r4, r31, 0x60
    li r3, 0x1
    crclr cr1eq
    bl MWTRACE
    mr r3, r27
    bl fn_800A5D7C
    addi r4, r31, 0x80
    mr r31, r3
    li r3, 0x1
    mr r5, r31
    crclr cr1eq
    bl MWTRACE
    mr r3, r31
.L_800A766C:
    lwz r10, 0x0(r1)
    lmw r27, -0x14(r10)
    lwz r0, 0x4(r10)
    mtlr r0
    mr r1, r10
    blr
.endfn fn_800A7448

.section .data, "wa"
.balign 4

.obj pad_07_80477C34_data, local
    .4byte 0x00000000
.endobj pad_07_80477C34_data

.obj jumptable_80477C38, local
    .rel fn_800A7448, .L_800A75DC
    .rel fn_800A7448, .L_800A75FC
    .rel fn_800A7448, .L_800A75D4
    .rel fn_800A7448, .L_800A75FC
    .rel fn_800A7448, .L_800A75E4
    .rel fn_800A7448, .L_800A75EC
    .rel fn_800A7448, .L_800A75F4
.endobj jumptable_80477C38
