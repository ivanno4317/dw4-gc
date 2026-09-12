.include "macros.inc"

.section .text, "ax"

.balign 4

.fn gdev_cc_peek, global
    stwu r1, -0x510(r1)
    mflr r0
    stw r0, 0x514(r1)
    stw r31, 0x50c(r1)
    bl DBQueryData
    mr. r31, r3
    bgt .L_800AB6F0
    li r3, 0x0
    b .L_800AB728
.L_800AB6F0:
    mr r4, r31
    addi r3, r1, 0x8
    bl DBRead
    cmpwi r3, 0x0
    bne .L_800AB71C
    lis r3, lbl_804F5810@ha
    mr r5, r31
    addi r3, r3, lbl_804F5810@l
    addi r4, r1, 0x8
    bl fn_800AB548
    b .L_800AB724
.L_800AB71C:
    li r3, -0x2719
    b .L_800AB728
.L_800AB724:
    mr r3, r31
.L_800AB728:
    lwz r0, 0x514(r1)
    lwz r31, 0x50c(r1)
    mtlr r0
    addi r1, r1, 0x510
    blr
.endfn gdev_cc_peek
