.include "macros.inc"

.section .text, "ax"

.balign 4

.fn fn_800A612C, global
    li r9, 0x0
    li r0, 0x0
    b .L_800A617C
.L_800A6138:
    lwz r7, 0xc(r3)
    lbz r8, 0x0(r4)
    cmplwi r7, 0x880
    blt .L_800A6150
    li r7, 0x301
    b .L_800A6170
.L_800A6150:
    addi r6, r7, 0x1
    addi r0, r7, 0x10
    stw r6, 0xc(r3)
    li r7, 0x0
    stbx r8, r3, r0
    lwz r6, 0x8(r3)
    addi r0, r6, 0x1
    stw r0, 0x8(r3)
.L_800A6170:
    mr r0, r7
    addi r9, r9, 0x1
    addi r4, r4, 0x1
.L_800A617C:
    cmpwi r0, 0x0
    bne .L_800A618C
    cmpw r9, r5
    blt .L_800A6138
.L_800A618C:
    mr r3, r0
    blr
.endfn fn_800A612C
