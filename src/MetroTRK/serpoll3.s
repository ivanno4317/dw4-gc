.include "macros.inc"
.file "serpoll3"

.section .text, "ax"
.balign 4

.fn fn_800A6778, global
	stwu r1, -0x8e0(r1)
	mflr r0
	lis r3, lbl_80414028@ha
	stw r0, 0x8e4(r1)
	stw r31, 0x8dc(r1)
	addi r31, r3, lbl_80414028@l
	stw r30, 0x8d8(r1)
	bl fn_800AAB80
	cmpwi r3, 0x0
	bgt .L_800A67A8
	li r3, -0x1
	b .L_800A689C
.L_800A67A8:
	addi r3, r1, 0xc
	addi r4, r1, 0x8
	bl TRKGetFreeBuffer
	mr r30, r3
	addi r4, r31, 0xd0
	li r3, 0x4
	mr r5, r30
	crclr cr1eq
	bl MWTRACE
	lwz r3, 0x8(r1)
	li r4, 0x0
	bl fn_800A63C0
	addi r3, r1, 0x10
	li r4, 0x40
	bl fn_800AAB44
	cmpwi r3, 0x0
	bne .L_800A6868
	lwz r3, 0x8(r1)
	addi r4, r1, 0x10
	li r5, 0x40
	bl fn_800A612C
	lwz r3, 0x10(r1)
	lwz r30, 0xc(r1)
	subic. r5, r3, 0x40
	ble .L_800A6884
	addi r4, r31, 0xf4
	li r3, 0x1
	crclr cr1eq
	bl MWTRACE
	lwz r4, 0x10(r1)
	addi r3, r1, 0x50
	subi r4, r4, 0x40
	bl fn_800AAB44
	cmpwi r3, 0x0
	bne .L_800A6848
	lwz r3, 0x8(r1)
	addi r4, r1, 0x50
	lwz r5, 0x10(r1)
	bl fn_800A612C
	b .L_800A6884
.L_800A6848:
	addi r4, r31, 0x110
	li r3, 0x8
	crclr cr1eq
	bl MWTRACE
	mr r3, r30
	bl TRKReleaseBuffer
	li r30, -0x1
	b .L_800A6884
.L_800A6868:
	addi r4, r31, 0x144
	li r3, 0x8
	crclr cr1eq
	bl MWTRACE
	mr r3, r30
	bl TRKReleaseBuffer
	li r30, -0x1
.L_800A6884:
	mr r5, r30
	addi r4, r31, 0x16c
	li r3, 0x1
	crclr cr1eq
	bl MWTRACE
	mr r3, r30
.L_800A689C:
	lwz r0, 0x8e4(r1)
	lwz r31, 0x8dc(r1)
	lwz r30, 0x8d8(r1)
	mtlr r0
	addi r1, r1, 0x8e0
	blr
.endfn fn_800A6778
