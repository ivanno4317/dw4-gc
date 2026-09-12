.include "macros.inc"

.section .text, "ax"

.balign 4

.fn TRKInitializeSerialHandler, global
    stwu r1, -0x10(r1)
    mflr r0
    lis r3, lbl_804F4530@ha
    lis r4, lbl_80414028@ha
    stw r0, 0x14(r1)
    addi r6, r3, lbl_804F4530@l
    li r0, 0x0
    li r3, -0x1
    stw r31, 0xc(r1)
    addi r31, r4, lbl_80414028@l
    addi r4, r31, 0x0
    li r5, 0x40
    stw r3, 0x0(r6)
    li r3, 0x1
    stw r0, 0x8(r6)
    stw r0, 0xc(r6)
    crclr cr1eq
    bl MWTRACE
    addi r4, r31, 0x24
    li r3, 0x1
    li r5, 0x40
    crclr cr1eq
    bl MWTRACE
    addi r4, r31, 0x48
    li r3, 0x1
    li r5, 0x40
    crclr cr1eq
    bl MWTRACE
    addi r4, r31, 0x6c
    li r3, 0x1
    li r5, 0x40
    crclr cr1eq
    bl MWTRACE
    addi r4, r31, 0x8c
    li r3, 0x1
    li r5, 0x40
    crclr cr1eq
    bl MWTRACE
    addi r4, r31, 0xac
    li r3, 0x1
    li r5, 0x40
    crclr cr1eq
    bl MWTRACE
    lwz r0, 0x14(r1)
    li r3, 0x0
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
.endfn TRKInitializeSerialHandler
