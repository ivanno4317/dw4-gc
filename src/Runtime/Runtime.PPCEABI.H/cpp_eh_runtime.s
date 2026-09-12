.include "macros.inc"

.section extab, "a"
.balign 4

.obj "@etb_800057C0", local
.hidden "@etb_800057C0"
    .4byte 0x08180000
    .4byte 0x00000020
    .4byte 0x00000018
    .4byte 0x0000002C
    .4byte 0x00000024
    .4byte 0x00000000
    .4byte 0x8F000000
    .4byte 0x00000024
    .4byte 0x00000008
    .4byte 0x8D000008
.endobj "@etb_800057C0"

.obj "@etb_800057E8", local
.hidden "@etb_800057E8"
    .4byte 0x10180000
    .4byte 0x00000054
    .4byte 0x00000020
    .4byte 0x00000060
    .4byte 0x00000038
    .4byte 0x00000074
    .4byte 0x00000048
    .4byte 0x00000000
    .4byte 0x0F000000
    .4byte 0x00000058
    .4byte 0x00000008
    .4byte 0x8F000000
    .4byte 0x0000006C
    .4byte 0x00000020
    .4byte 0x0D000008
    .4byte 0x8F000000
    .4byte 0x0000006C
    .4byte 0x00000020
    .4byte 0x8D000020
.endobj "@etb_800057E8"

.obj "@etb_80005834", local
.hidden "@etb_80005834"
    .4byte 0x08080000
    .4byte 0x00000000
.endobj "@etb_80005834"

.obj "@etb_8000583C", local
.hidden "@etb_8000583C"
    .4byte 0x08180000
    .4byte 0x00000020
    .4byte 0x00000018
    .4byte 0x0000002C
    .4byte 0x00000024
    .4byte 0x00000000
    .4byte 0x8F000000
    .4byte 0x00000024
    .4byte 0x00000008
    .4byte 0x8D000008
.endobj "@etb_8000583C"

.obj "@etb_80005864", local
.hidden "@etb_80005864"
    .4byte 0x08080000
    .4byte 0x00000000
.endobj "@etb_80005864"

.obj "@etb_8000586C", local
.hidden "@etb_8000586C"
    .4byte 0x20080000
    .4byte 0x00000000
.endobj "@etb_8000586C"

.obj "@etb_80005874", local
.hidden "@etb_80005874"
    .4byte 0x20080000
    .4byte 0x00000060
    .4byte 0x00000010
    .4byte 0x00000000
    .4byte 0x82000008
    .4byte dtor_800A34B4
.endobj "@etb_80005874"

.obj "@etb_8000588C", local
.hidden "@etb_8000588C"
    .4byte 0x18080000
    .4byte 0x00000000
.endobj "@etb_8000588C"

.obj "@etb_80005894", local
.hidden "@etb_80005894"
    .4byte 0x00080000
    .4byte 0x00000000
.endobj "@etb_80005894"

.obj "@etb_8000589C", local
.hidden "@etb_8000589C"
    .4byte 0x00080000
    .4byte 0x00000000
.endobj "@etb_8000589C"

.obj "@etb_800058A4", local
.hidden "@etb_800058A4"
    .4byte 0x00080000
    .4byte 0x00000000
.endobj "@etb_800058A4"

.obj "@etb_800058AC", local
.hidden "@etb_800058AC"
    .4byte 0x00080000
    .4byte 0x00000000
.endobj "@etb_800058AC"

.section extabindex, "a"
.balign 4

.obj "@eti_80012C9C", local
.hidden "@eti_80012C9C"
    .4byte fn_800A30E8
    .4byte 0x0000004C
    .4byte "@etb_800057C0"
.endobj "@eti_80012C9C"

.obj "@eti_80012CA8", local
.hidden "@eti_80012CA8"
    .4byte fn_800A3134
    .4byte 0x00000098
    .4byte "@etb_800057E8"
.endobj "@eti_80012CA8"

.obj "@eti_80012CB4", local
.hidden "@eti_80012CB4"
    .4byte fn_800A31CC
    .4byte 0x00000090
    .4byte "@etb_80005834"
.endobj "@eti_80012CB4"

.obj "@eti_80012CC0", local
.hidden "@eti_80012CC0"
    .4byte fn_800A325C
    .4byte 0x0000004C
    .4byte "@etb_8000583C"
.endobj "@eti_80012CC0"

.obj "@eti_80012CCC", local
.hidden "@eti_80012CCC"
    .4byte fn_800A32A8
    .4byte 0x0000008C
    .4byte "@etb_80005864"
.endobj "@eti_80012CCC"

.obj "@eti_80012CD8", local
.hidden "@eti_80012CD8"
    .4byte fn_800A3340
    .4byte 0x00000078
    .4byte "@etb_8000586C"
.endobj "@eti_80012CD8"

.obj "@eti_80012CE4", local
.hidden "@eti_80012CE4"
    .4byte fn_800A33B8
    .4byte 0x000000FC
    .4byte "@etb_80005874"
.endobj "@eti_80012CE4"

.obj "@eti_80012CF0", local
.hidden "@eti_80012CF0"
    .4byte dtor_800A34B4
    .4byte 0x000000B8
    .4byte "@etb_8000588C"
.endobj "@eti_80012CF0"

.obj "@eti_80012CFC", local
.hidden "@eti_80012CFC"
    .4byte fn_800A3798
    .4byte 0x00000028
    .4byte "@etb_80005894"
.endobj "@eti_80012CFC"

.obj "@eti_80012D08", local
.hidden "@eti_80012D08"
    .4byte fn_800A37C0
    .4byte 0x00000028
    .4byte "@etb_8000589C"
.endobj "@eti_80012D08"

.obj "@eti_80012D14", local
.hidden "@eti_80012D14"
    .4byte fn_800A37E8
    .4byte 0x00000028
    .4byte "@etb_800058A4"
.endobj "@eti_80012D14"

.obj "@eti_80012D20", local
.hidden "@eti_80012D20"
    .4byte fn_800A3810
    .4byte 0x00000020
    .4byte "@etb_800058AC"
.endobj "@eti_80012D20"

.section .text, "ax"

.balign 4

.fn fn_800A30E8, global
    stwu r1, -0x30(r1)
    mflr r0
    cmplwi r3, 0x0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    mr r31, r1
    beq .L_800A3118
    bl free
    b .L_800A3118
    addi r3, r31, 0x8
    bl fn_800A4B28
.L_800A3114:
    b .L_800A3114
.L_800A3118:
    mr r10, r31
    lwz r31, 0x2c(r31)
    lwz r10, 0x0(r1)
    lwz r0, 0x4(r10)
    mr r1, r10
    mtlr r0
    blr
.endfn fn_800A30E8

.fn fn_800A3134, global
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stw r31, 0x3c(r1)
    mr r31, r1
    stw r30, 0x38(r1)
    mr. r30, r3
    beq .L_800A3198
    lis r3, lbl_80477ACC@ha
    addi r0, r3, lbl_80477ACC@l
    stw r0, 0x0(r30)
    beq .L_800A3170
    lis r3, lbl_80477148@ha
    addi r0, r3, lbl_80477148@l
    stw r0, 0x0(r30)
.L_800A3170:
    extsh. r0, r4
    ble .L_800A3198
    cmplwi r30, 0x0
    beq .L_800A3198
    mr r3, r30
    bl free
    b .L_800A3198
    addi r3, r31, 0x8
    bl fn_800A4B28
.L_800A3194:
    b .L_800A3194
.L_800A3198:
    mr r3, r30
    b .L_800A31AC
    addi r3, r31, 0x20
    bl fn_800A4B28
.L_800A31A8:
    b .L_800A31A8
.L_800A31AC:
    mr r10, r31
    lwz r31, 0x3c(r31)
    lwz r30, 0x38(r10)
    lwz r10, 0x0(r1)
    lwz r0, 0x4(r10)
    mr r1, r10
    mtlr r0
    blr
.endfn fn_800A3134

.fn fn_800A31CC, global
    stwu r1, -0x20(r1)
    mflr r0
    cmplwi r3, 0x0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    bne .L_800A31EC
    li r31, 0x4
.L_800A31EC:
    mr r3, r31
    bl malloc
    cmplwi r3, 0x0
    bne .L_800A3248
    lwz r12, lbl_805623E0@sda21(r0)
    cmplwi r12, 0x0
    beq .L_800A3214
    mtctr r12
    bctrl
    b .L_800A31EC
.L_800A3214:
    lis r3, lbl_80477148@ha
    lis r4, lbl_80477ACC@ha
    addi r0, r3, lbl_80477148@l
    stw r0, 0x8(r1)
    addi r0, r4, lbl_80477ACC@l
    lis r3, lbl_80413EA0@ha
    lis r4, fn_800A3134@ha
    stw r0, 0x8(r1)
    addi r5, r4, fn_800A3134@l
    addi r3, r3, lbl_80413EA0@l
    addi r4, r1, 0x8
    bl fn_800A4590
    b .L_800A31EC
.L_800A3248:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
.endfn fn_800A31CC

.fn fn_800A325C, global
    stwu r1, -0x30(r1)
    mflr r0
    cmplwi r3, 0x0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    mr r31, r1
    beq .L_800A328C
    bl free
    b .L_800A328C
    addi r3, r31, 0x8
    bl fn_800A4B28
.L_800A3288:
    b .L_800A3288
.L_800A328C:
    mr r10, r31
    lwz r31, 0x2c(r31)
    lwz r10, 0x0(r1)
    lwz r0, 0x4(r10)
    mr r1, r10
    mtlr r0
    blr
.endfn fn_800A325C

.fn fn_800A32A8, global
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr. r31, r3
    bne .L_800A32C4
    li r31, 0x4
.L_800A32C4:
    mr r3, r31
    bl malloc
    cmplwi r3, 0x0
    bne .L_800A3320
    lwz r12, lbl_805623E0@sda21(r0)
    cmplwi r12, 0x0
    beq .L_800A32EC
    mtctr r12
    bctrl
    b .L_800A32C4
.L_800A32EC:
    lis r3, lbl_80477148@ha
    lis r4, lbl_80477ACC@ha
    addi r0, r3, lbl_80477148@l
    stw r0, 0x8(r1)
    addi r0, r4, lbl_80477ACC@l
    lis r3, lbl_80413EA0@ha
    lis r4, fn_800A3134@ha
    stw r0, 0x8(r1)
    addi r5, r4, fn_800A3134@l
    addi r3, r3, lbl_80413EA0@l
    addi r4, r1, 0x8
    bl fn_800A4590
    b .L_800A32C4
.L_800A3320:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
.endfn fn_800A32A8

.fn fn_800A3334, global
    lis r3, lbl_80413EE4@ha
    addi r3, r3, lbl_80413EE4@l
    blr
.endfn fn_800A3334

.fn fn_800A3340, global
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r6
    stw r29, 0x14(r1)
    mr r29, r5
    mullw r0, r29, r30
    stw r28, 0x10(r1)
    mr r28, r4
    add r31, r3, r0
    b .L_800A3390
.L_800A3374:
    subf r31, r29, r31
    mr r12, r28
    mr r3, r31
    li r4, -0x1
    mtctr r12
    bctrl
    subi r30, r30, 0x1
.L_800A3390:
    cmplwi r30, 0x0
    bne .L_800A3374
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
.endfn fn_800A3340

.fn fn_800A33B8, global
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    li r0, 0x0
    stw r31, 0x2c(r1)
    mr r31, r3
    stw r30, 0x28(r1)
    mr r30, r7
    stw r29, 0x24(r1)
    mr r29, r6
    stw r30, 0x18(r1)
    stw r28, 0x20(r1)
    mr r28, r4
    stw r3, 0x8(r1)
    stw r29, 0xc(r1)
    stw r30, 0x10(r1)
    stw r5, 0x14(r1)
    stw r0, 0x18(r1)
    b .L_800A3428
.L_800A3404:
    mr r12, r28
    mr r3, r31
    li r4, 0x1
    mtctr r12
    bctrl
    lwz r3, 0x18(r1)
    add r31, r31, r29
    addi r0, r3, 0x1
    stw r0, 0x18(r1)
.L_800A3428:
    lwz r4, 0x18(r1)
    cmplw r4, r30
    blt .L_800A3404
    lwz r0, 0x10(r1)
    cmplw r4, r0
    bge .L_800A3494
    lwz r0, 0x14(r1)
    cmplwi r0, 0x0
    beq .L_800A3494
    lwz r0, 0xc(r1)
    lwz r3, 0x8(r1)
    mullw r0, r0, r4
    add r31, r3, r0
    b .L_800A3488
.L_800A3460:
    lwz r0, 0xc(r1)
    li r4, -0x1
    lwz r12, 0x14(r1)
    subf r31, r0, r31
    mr r3, r31
    mtctr r12
    bctrl
    lwz r3, 0x18(r1)
    subi r0, r3, 0x1
    stw r0, 0x18(r1)
.L_800A3488:
    lwz r0, 0x18(r1)
    cmplwi r0, 0x0
    bne .L_800A3460
.L_800A3494:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    lwz r28, 0x20(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
.endfn fn_800A33B8

.fn dtor_800A34B4, global
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r4
    stw r29, 0x14(r1)
    mr. r29, r3
    beq .L_800A354C
    lwz r4, 0x10(r29)
    lwz r0, 0x8(r29)
    cmplw r4, r0
    bge .L_800A353C
    lwz r0, 0xc(r29)
    cmplwi r0, 0x0
    beq .L_800A353C
    lwz r0, 0x4(r29)
    lwz r3, 0x0(r29)
    mullw r0, r0, r4
    add r31, r3, r0
    b .L_800A3530
.L_800A3508:
    lwz r0, 0x4(r29)
    li r4, -0x1
    lwz r12, 0xc(r29)
    subf r31, r0, r31
    mr r3, r31
    mtctr r12
    bctrl
    lwz r3, 0x10(r29)
    subi r0, r3, 0x1
    stw r0, 0x10(r29)
.L_800A3530:
    lwz r0, 0x10(r29)
    cmplwi r0, 0x0
    bne .L_800A3508
.L_800A353C:
    extsh. r0, r30
    ble .L_800A354C
    mr r3, r29
    bl fn_800A325C
.L_800A354C:
    lwz r0, 0x24(r1)
    mr r3, r29
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
.endfn dtor_800A34B4

.fn fn_800A356C, global
    li r0, 0x0
    mr. r6, r4
    stw r0, 0x0(r5)
    bne .L_800A3584
    li r3, 0x1
    blr
.L_800A3584:
    lbz r0, 0x0(r4)
    cmpwi r0, 0x50
    bne .L_800A35E0
    lbzu r0, 0x1(r6)
    cmpwi r0, 0x43
    bne .L_800A35A0
    addi r6, r6, 0x1
.L_800A35A0:
    lbz r0, 0x0(r6)
    cmpwi r0, 0x56
    bne .L_800A35B0
    addi r6, r6, 0x1
.L_800A35B0:
    lbz r0, 0x0(r6)
    cmpwi r0, 0x76
    bne .L_800A35DC
    lbz r0, 0x0(r3)
    extsb r0, r0
    cmpwi r0, 0x50
    beq .L_800A35D4
    cmpwi r0, 0x2a
    bne .L_800A35DC
.L_800A35D4:
    li r3, 0x1
    blr
.L_800A35DC:
    mr r6, r4
.L_800A35E0:
    lbz r0, 0x0(r3)
    extsb r0, r0
    cmpwi r0, 0x2a
    beq .L_800A3600
    bge .L_800A3730
    cmpwi r0, 0x21
    beq .L_800A3600
    b .L_800A3730
.L_800A3600:
    lbz r7, 0x0(r3)
    addi r3, r3, 0x1
    lbz r0, 0x0(r6)
    addi r6, r6, 0x1
    extsb r7, r7
    extsb r0, r0
    cmpw r7, r0
    beq .L_800A3628
    li r3, 0x0
    blr
.L_800A3628:
    lbz r0, 0x0(r6)
    addi r6, r6, 0x1
    lbz r7, 0x0(r3)
    extsb r0, r0
    extsb r7, r7
    cmpw r7, r0
    bne .L_800A3688
    cmpwi r7, 0x21
    addi r3, r3, 0x1
    bne .L_800A3628
    li r4, 0x0
    b .L_800A3670
.L_800A3658:
    mulli r4, r4, 0xa
    lbz r0, 0x0(r3)
    addi r3, r3, 0x1
    extsb r0, r0
    subi r4, r4, 0x30
    add r4, r0, r4
.L_800A3670:
    lbz r0, 0x0(r3)
    cmpwi r0, 0x21
    bne .L_800A3658
    stw r4, 0x0(r5)
    li r3, 0x1
    blr
.L_800A3688:
    lbz r0, 0x0(r3)
    addi r3, r3, 0x1
    cmpwi r0, 0x21
    bne .L_800A3688
.L_800A3698:
    lbz r0, 0x0(r3)
    addi r3, r3, 0x1
    cmpwi r0, 0x21
    bne .L_800A3698
    lbz r0, 0x0(r3)
    extsb. r0, r0
    bne .L_800A36BC
    li r3, 0x0
    blr
.L_800A36BC:
    addi r6, r4, 0x1
    b .L_800A3628
.L_800A36C4:
    lbzu r0, 0x1(r6)
    addi r3, r3, 0x1
    cmpwi r0, 0x43
    bne .L_800A36E8
    lbz r0, 0x0(r3)
    cmpwi r0, 0x43
    bne .L_800A36E4
    addi r3, r3, 0x1
.L_800A36E4:
    addi r6, r6, 0x1
.L_800A36E8:
    lbz r0, 0x0(r3)
    extsb r4, r0
    cmpwi r4, 0x43
    bne .L_800A3700
    li r3, 0x0
    blr
.L_800A3700:
    lbz r0, 0x0(r6)
    cmpwi r0, 0x56
    bne .L_800A371C
    cmpwi r4, 0x56
    bne .L_800A3718
    addi r3, r3, 0x1
.L_800A3718:
    addi r6, r6, 0x1
.L_800A371C:
    lbz r0, 0x0(r3)
    cmpwi r0, 0x56
    bne .L_800A3730
    li r3, 0x0
    blr
.L_800A3730:
    lbz r4, 0x0(r3)
    extsb r0, r4
    cmpwi r0, 0x50
    beq .L_800A3748
    cmpwi r0, 0x52
    bne .L_800A3778
.L_800A3748:
    lbz r0, 0x0(r6)
    extsb r4, r4
    extsb r0, r0
    cmpw r4, r0
    beq .L_800A36C4
    b .L_800A3778
.L_800A3760:
    extsb. r0, r5
    bne .L_800A3770
    li r3, 0x1
    blr
.L_800A3770:
    addi r3, r3, 0x1
    addi r6, r6, 0x1
.L_800A3778:
    lbz r5, 0x0(r3)
    lbz r0, 0x0(r6)
    extsb r4, r5
    extsb r0, r0
    cmpw r4, r0
    beq .L_800A3760
    li r3, 0x0
    blr
.endfn fn_800A356C

.fn fn_800A3798, global
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lwz r12, lbl_8055DE44@sda21(r0)
    mtctr r12
    bctrl
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
.endfn fn_800A3798

.fn fn_800A37C0, global
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lwz r12, lbl_8055DE40@sda21(r0)
    mtctr r12
    bctrl
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
.endfn fn_800A37C0

.fn fn_800A37E8, global
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lwz r12, lbl_8055DE40@sda21(r0)
    mtctr r12
    bctrl
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
.endfn fn_800A37E8

.fn fn_800A3810, global
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    bl abort
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
.endfn fn_800A3810

.fn fn_800A3830, global
    lwz r0, 0x0(r12)
    lwz r11, 0x4(r12)
    lwz r12, 0x8(r12)
    add r3, r3, r0
    cmpwi r11, 0x0
    blt .L_800A3850
    lwzx r12, r3, r12
    lwzx r12, r12, r11
.L_800A3850:
    mtctr r12
    bctr
.endfn fn_800A3830

.fn fn_800A3858, global
    lwz r0, 0x0(r12)
    lwz r11, 0x4(r12)
    lwz r12, 0x8(r12)
    add r4, r4, r0
    cmpwi r11, 0x0
    blt .L_800A3878
    lwzx r12, r4, r12
    lwzx r12, r12, r11
.L_800A3878:
    mtctr r12
    bctr
.endfn fn_800A3858
