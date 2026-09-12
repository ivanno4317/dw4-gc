.include "macros.inc"

.section .text, "ax"

.balign 4

.fn fn_800A7684, global
    clrlwi r11, r1, 27
    mr r12, r1
    subfic r11, r11, -0x940
    stwux r1, r1, r11
    mflr r0
    stw r0, 0x4(r12)
    stmw r26, -0x18(r12)
    mr r31, r3
    lis r3, lbl_804141F8@ha
    addi r29, r3, lbl_804141F8@l
    addi r4, r29, 0x1b0
    li r3, 0x1
    lwz r26, 0x20(r31)
    lhz r27, 0x1c(r31)
    lbz r30, 0x18(r31)
    mr r6, r26
    lbz r5, 0x14(r31)
    mr r7, r27
    mr r8, r30
    crclr cr1eq
    bl MWTRACE
    rlwinm. r0, r30, 0, 30, 30
    beq .L_800A771C
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
    b .L_800A78B0
.L_800A771C:
    rlwinm. r28, r30, 0, 25, 25
    stw r27, 0x20(r1)
    beq .L_800A7744
    mr r4, r26
    addi r3, r1, 0x100
    addi r5, r1, 0x20
    li r6, 0x1
    bl fn_800A87B8
    mr r30, r3
    b .L_800A7764
.L_800A7744:
    extrwi r0, r30, 1, 28
    mr r4, r26
    addi r3, r1, 0x100
    addi r5, r1, 0x20
    xori r6, r0, 0x1
    li r7, 0x1
    bl fn_800A9B78
    mr r30, r3
.L_800A7764:
    mr r3, r31
    li r4, 0x0
    bl fn_800A63F0
    cmpwi r30, 0x0
    bne .L_800A77EC
    addi r3, r1, 0xa4
    li r4, 0x0
    li r5, 0x40
    bl memset
    lwz r4, 0x20(r1)
    li r0, 0x80
    stb r30, 0xac(r1)
    mr r3, r31
    addi r4, r4, 0x40
    li r5, 0x40
    stw r4, 0xa4(r1)
    addi r4, r1, 0xa4
    stb r0, 0xa8(r1)
    bl fn_800A631C
    cmpwi r28, 0x0
    beq .L_800A77D8
    clrlwi r0, r26, 27
    addi r4, r1, 0x100
    lwz r5, 0x20(r1)
    mr r3, r31
    add r4, r4, r0
    bl fn_800A631C
    mr r30, r3
    b .L_800A77EC
.L_800A77D8:
    lwz r5, 0x20(r1)
    mr r3, r31
    addi r4, r1, 0x100
    bl fn_800A631C
    mr r30, r3
.L_800A77EC:
    cmpwi r30, 0x0
    beq .L_800A787C
    subi r0, r30, 0x700
    cmplwi r0, 0x6
    bgt .L_800A7840
    lis r3, jumptable_80477C54@ha
    slwi r0, r0, 2
    addi r3, r3, jumptable_80477C54@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
.L_800A7818:
    li r28, 0x15
    b .L_800A7844
.L_800A7820:
    li r28, 0x13
    b .L_800A7844
.L_800A7828:
    li r28, 0x21
    b .L_800A7844
.L_800A7830:
    li r28, 0x22
    b .L_800A7844
.L_800A7838:
    li r28, 0x20
    b .L_800A7844
.L_800A7840:
    li r28, 0x3
.L_800A7844:
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
    stb r28, 0x2c(r1)
    bl fn_800AAB08
    li r3, 0x0
    b .L_800A78B0
.L_800A787C:
    addi r4, r29, 0x60
    li r3, 0x1
    crclr cr1eq
    bl MWTRACE
    mr r3, r31
    bl fn_800A5D7C
    addi r4, r29, 0x80
    mr r29, r3
    li r3, 0x1
    mr r5, r29
    crclr cr1eq
    bl MWTRACE
    mr r3, r29
.L_800A78B0:
    lwz r10, 0x0(r1)
    lmw r26, -0x18(r10)
    lwz r0, 0x4(r10)
    mtlr r0
    mr r1, r10
    blr
.endfn fn_800A7684

.section .data, "wa"
.balign 4

.obj jumptable_80477C54, local
    .rel fn_800A7684, .L_800A7820
    .rel fn_800A7684, .L_800A7840
    .rel fn_800A7684, .L_800A7818
    .rel fn_800A7684, .L_800A7840
    .rel fn_800A7684, .L_800A7828
    .rel fn_800A7684, .L_800A7830
    .rel fn_800A7684, .L_800A7838
.endobj jumptable_80477C54
