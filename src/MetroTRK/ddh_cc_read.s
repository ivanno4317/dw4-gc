.include "macros.inc"

.section .text, "ax"

.balign 4

.fn ddh_cc_read, global
    stwu r1, -0x820(r1)
    mflr r0
    stw r0, 0x824(r1)
    stmw r27, 0x80c(r1)
    mr r27, r3
    mr r30, r4
    li r29, 0x0
    lwz r0, lbl_805623F0@sda21(r0)
    cmpwi r0, 0x0
    bne .L_800AB2C8
    li r3, -0x2711
    b .L_800AB370
.L_800AB2C8:
    lis r3, lbl_80414694@ha
    mr r5, r30
    addi r4, r3, lbl_80414694@l
    mr r6, r30
    li r3, 0x1
    crclr cr1eq
    bl MWTRACE
    lis r3, lbl_804F52F0@ha
    addi r31, r3, lbl_804F52F0@l
    b .L_800AB324
.L_800AB2F0:
    li r29, 0x0
    bl EXI2_Poll
    mr. r28, r3
    beq .L_800AB324
    mr r4, r28
    addi r3, r1, 0x8
    bl EXI2_ReadN
    mr. r29, r3
    bne .L_800AB324
    mr r3, r31
    mr r5, r28
    addi r4, r1, 0x8
    bl fn_800AB548
.L_800AB324:
    mr r3, r31
    bl fn_800AB6A0
    cmplw r3, r30
    blt .L_800AB2F0
    cmplwi r29, 0x0
    bne .L_800AB354
    lis r3, lbl_804F52F0@ha
    mr r4, r27
    addi r3, r3, lbl_804F52F0@l
    mr r5, r30
    bl fn_800AB440
    b .L_800AB36C
.L_800AB354:
    lis r3, lbl_804146BC@ha
    mr r5, r29
    addi r4, r3, lbl_804146BC@l
    li r3, 0x8
    crclr cr1eq
    bl MWTRACE
.L_800AB36C:
    mr r3, r29
.L_800AB370:
    lmw r27, 0x80c(r1)
    lwz r0, 0x824(r1)
    mtlr r0
    addi r1, r1, 0x820
    blr
.endfn ddh_cc_read
