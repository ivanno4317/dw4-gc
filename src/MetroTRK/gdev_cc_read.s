.include "macros.inc"

.section .text, "ax"

.balign 4

.fn gdev_cc_read, global
    stwu r1, -0x520(r1)
    mflr r0
    stw r0, 0x524(r1)
    stmw r26, 0x508(r1)
    mr r26, r3
    mr r27, r4
    li r28, 0x0
    lwz r0, lbl_805623F8@sda21(r0)
    cmpwi r0, 0x0
    bne .L_800AB874
    li r3, -0x2711
    b .L_800AB924
.L_800AB874:
    lis r3, lbl_80414774@ha
    mr r5, r27
    addi r4, r3, lbl_80414774@l
    mr r6, r27
    li r3, 0x1
    crclr cr1eq
    bl MWTRACE
    lis r3, lbl_804F5810@ha
    mr r29, r27
    addi r31, r3, lbl_804F5810@l
    mr r30, r27
    b .L_800AB8D8
.L_800AB8A4:
    li r28, 0x0
    bl DBQueryData
    mr. r27, r3
    beq .L_800AB8D8
    mr r4, r30
    addi r3, r1, 0x8
    bl DBRead
    mr. r28, r3
    bne .L_800AB8D8
    mr r3, r31
    mr r5, r27
    addi r4, r1, 0x8
    bl fn_800AB548
.L_800AB8D8:
    mr r3, r31
    bl fn_800AB6A0
    cmplw r3, r30
    blt .L_800AB8A4
    cmplwi r28, 0x0
    bne .L_800AB908
    lis r3, lbl_804F5810@ha
    mr r4, r26
    addi r3, r3, lbl_804F5810@l
    mr r5, r29
    bl fn_800AB440
    b .L_800AB920
.L_800AB908:
    lis r3, lbl_8041479C@ha
    mr r5, r28
    addi r4, r3, lbl_8041479C@l
    li r3, 0x8
    crclr cr1eq
    bl MWTRACE
.L_800AB920:
    mr r3, r28
.L_800AB924:
    lmw r26, 0x508(r1)
    lwz r0, 0x524(r1)
    mtlr r0
    addi r1, r1, 0x520
    blr
.endfn gdev_cc_read
