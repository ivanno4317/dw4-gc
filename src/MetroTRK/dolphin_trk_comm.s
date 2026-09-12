.include "macros.inc"

.section .text, "ax"

.balign 4

.fn EnableEXI2Interrupts, global
    stwu r1, -0x10(r1)
    mflr r0
    lis r3, TRK_Use_BBA@ha
    stw r0, 0x14(r1)
    lbz r0, TRK_Use_BBA@l(r3)
    cmplwi r0, 0x0
    bne .L_800AABE8
    lis r3, gDBCommTable@ha
    addi r3, r3, gDBCommTable@l
    lwz r12, 0x4(r3)
    cmplwi r12, 0x0
    beq .L_800AABE8
    mtctr r12
    bctrl
.L_800AABE8:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
.endfn EnableEXI2Interrupts

.fn TRKInitializeIntDrivenUART, global
    stwu r1, -0x10(r1)
    mflr r0
    lis r4, TRKEXICallBack@ha
    lis r3, gDBCommTable@ha
    stw r0, 0x14(r1)
    addi r4, r4, TRKEXICallBack@l
    lwz r12, gDBCommTable@l(r3)
    mr r3, r6
    mtctr r12
    bctrl
    lis r3, gDBCommTable@ha
    addi r3, r3, gDBCommTable@l
    lwz r12, 0x18(r3)
    mtctr r12
    bctrl
    lwz r0, 0x14(r1)
    li r3, 0x0
    mtlr r0
    addi r1, r1, 0x10
    blr
.endfn TRKInitializeIntDrivenUART

.fn InitMetroTRKCommTable, global
    stwu r1, -0x20(r1)
    mflr r0
    lis r4, EndofProgramInstruction@ha
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    li r31, 0x1
    stw r30, 0x18(r1)
    mr r30, r3
    stw r29, 0x14(r1)
    addi r29, r4, EndofProgramInstruction@l
    mr r4, r30
    addi r3, r29, 0x8
    crclr cr1eq
    bl OSReport
    lis r3, TRK_Use_BBA@ha
    li r0, 0x0
    cmpwi r30, 0x2
    stb r0, TRK_Use_BBA@l(r3)
    bne .L_800AAD34
    addi r3, r29, 0x20
    crclr cr1eq
    bl OSReport
    lis r30, TRK_Use_BBA@ha
    lis r12, udp_cc_initialize@ha
    lis r11, gDBCommTable@ha
    lis r10, udp_cc_open@ha
    lis r9, udp_cc_close@ha
    lis r8, udp_cc_read@ha
    lis r7, udp_cc_write@ha
    lis r6, udp_cc_shutdown@ha
    lis r5, udp_cc_peek@ha
    lis r4, udp_cc_pre_continue@ha
    lis r3, udp_cc_post_stop@ha
    addi r31, r30, TRK_Use_BBA@l
    li r29, 0x1
    addi r30, r12, udp_cc_initialize@l
    addi r12, r11, gDBCommTable@l
    addi r11, r10, udp_cc_open@l
    addi r10, r9, udp_cc_close@l
    addi r9, r8, udp_cc_read@l
    addi r8, r7, udp_cc_write@l
    addi r7, r6, udp_cc_shutdown@l
    addi r6, r5, udp_cc_peek@l
    addi r5, r4, udp_cc_pre_continue@l
    addi r4, r3, udp_cc_post_stop@l
    li r0, 0x0
    stb r29, 0x0(r31)
    li r3, 0x0
    stw r30, 0x0(r12)
    stw r11, 0x18(r12)
    stw r10, 0x1c(r12)
    stw r9, 0x10(r12)
    stw r8, 0x14(r12)
    stw r7, 0x8(r12)
    stw r6, 0xc(r12)
    stw r5, 0x20(r12)
    stw r4, 0x24(r12)
    stw r0, 0x4(r12)
    b .L_800AAE98
.L_800AAD34:
    cmpwi r30, 0x1
    bne .L_800AADD0
    addi r3, r29, 0x38
    crclr cr1eq
    bl OSReport
    bl Hu_IsStub
    lis r31, gdev_cc_initialize@ha
    lis r12, gdev_cc_open@ha
    addi r31, r31, gdev_cc_initialize@l
    lis r30, gDBCommTable@ha
    lis r11, gdev_cc_close@ha
    lis r10, gdev_cc_read@ha
    lis r9, gdev_cc_write@ha
    lis r8, gdev_cc_shutdown@ha
    lis r7, gdev_cc_peek@ha
    lis r6, gdev_cc_pre_continue@ha
    lis r5, gdev_cc_post_stop@ha
    lis r4, gdev_cc_initinterrupts@ha
    stwu r31, gDBCommTable@l(r30)
    addi r12, r12, gdev_cc_open@l
    addi r11, r11, gdev_cc_close@l
    addi r10, r10, gdev_cc_read@l
    addi r9, r9, gdev_cc_write@l
    addi r8, r8, gdev_cc_shutdown@l
    addi r7, r7, gdev_cc_peek@l
    addi r6, r6, gdev_cc_pre_continue@l
    addi r5, r5, gdev_cc_post_stop@l
    addi r0, r4, gdev_cc_initinterrupts@l
    stw r12, 0x18(r30)
    mr r31, r3
    stw r11, 0x1c(r30)
    stw r10, 0x10(r30)
    stw r9, 0x14(r30)
    stw r8, 0x8(r30)
    stw r7, 0xc(r30)
    stw r6, 0x20(r30)
    stw r5, 0x24(r30)
    stw r0, 0x4(r30)
    b .L_800AAE94
.L_800AADD0:
    cmpwi r30, 0x0
    bne .L_800AAE6C
    addi r3, r29, 0x5c
    crclr cr1eq
    bl OSReport
    bl AMC_IsStub
    lis r31, ddh_cc_initialize@ha
    lis r12, ddh_cc_open@ha
    addi r31, r31, ddh_cc_initialize@l
    lis r30, gDBCommTable@ha
    lis r11, ddh_cc_close@ha
    lis r10, ddh_cc_read@ha
    lis r9, ddh_cc_write@ha
    lis r8, ddh_cc_shutdown@ha
    lis r7, ddh_cc_peek@ha
    lis r6, ddh_cc_pre_continue@ha
    lis r5, ddh_cc_post_stop@ha
    lis r4, ddh_cc_initinterrupts@ha
    stwu r31, gDBCommTable@l(r30)
    addi r12, r12, ddh_cc_open@l
    addi r11, r11, ddh_cc_close@l
    addi r10, r10, ddh_cc_read@l
    addi r9, r9, ddh_cc_write@l
    addi r8, r8, ddh_cc_shutdown@l
    addi r7, r7, ddh_cc_peek@l
    addi r6, r6, ddh_cc_pre_continue@l
    addi r5, r5, ddh_cc_post_stop@l
    addi r0, r4, ddh_cc_initinterrupts@l
    stw r12, 0x18(r30)
    mr r31, r3
    stw r11, 0x1c(r30)
    stw r10, 0x10(r30)
    stw r9, 0x14(r30)
    stw r8, 0x8(r30)
    stw r7, 0xc(r30)
    stw r6, 0x20(r30)
    stw r5, 0x24(r30)
    stw r0, 0x4(r30)
    b .L_800AAE94
.L_800AAE6C:
    mr r4, r30
    addi r3, r29, 0x80
    crclr cr1eq
    bl OSReport
    addi r3, r29, 0xac
    crclr cr1eq
    bl OSReport
    addi r3, r29, 0xdc
    crclr cr1eq
    bl OSReport
.L_800AAE94:
    mr r3, r31
.L_800AAE98:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
.endfn InitMetroTRKCommTable

.fn TRKEXICallBack, global
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    bl OSEnableScheduler
    mr r3, r31
    li r4, 0x500
    bl TRKLoadContext
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
.endfn TRKEXICallBack

.section .rodata, "a"
.balign 4

.obj lbl_80414534, global
    .4byte 0x25730A00
    .4byte 0x4465766B
    .4byte 0x69742073
    .4byte 0x65742074
    .4byte 0x6F203A20
    .4byte 0x256C640A
    .4byte 0x00000000
    .4byte 0x4D657472
    .4byte 0x6F54524B
    .4byte 0x203A2053
    .4byte 0x65742074
    .4byte 0x6F204242
    .4byte 0x410A0000
    .4byte 0x4D657472
    .4byte 0x6F54524B
    .4byte 0x203A2053
    .4byte 0x65742074
    .4byte 0x6F204744
    .4byte 0x45562068
    .4byte 0x61726477
    .4byte 0x6172650A
    .4byte 0x00000000
    .4byte 0x4D657472
    .4byte 0x6F54524B
    .4byte 0x203A2053
    .4byte 0x65742074
    .4byte 0x6F20414D
    .4byte 0x43204444
    .4byte 0x48206861
    .4byte 0x72647761
    .4byte 0x72650A00
    .4byte 0x4D657472
    .4byte 0x6F54524B
    .4byte 0x203A2053
    .4byte 0x65742074
    .4byte 0x6F20554E
    .4byte 0x4B4E4F57
    .4byte 0x4E206861
    .4byte 0x72647761
    .4byte 0x72652E20
    .4byte 0x28256C64
    .4byte 0x290A0000
    .4byte 0x4D657472
    .4byte 0x6F54524B
    .4byte 0x203A2049
    .4byte 0x6E76616C
    .4byte 0x69642068
    .4byte 0x61726477
    .4byte 0x61726520
    .4byte 0x49442070
    .4byte 0x61737365
    .4byte 0x64206672
    .4byte 0x6F6D204F
    .4byte 0x530A0000
    .4byte 0x4D657472
    .4byte 0x6F54524B
    .4byte 0x203A2044
    .4byte 0x65666175
    .4byte 0x6C74696E
    .4byte 0x6720746F
    .4byte 0x20474445
    .4byte 0x56204861
    .4byte 0x72647761
    .4byte 0x72650A00
    .4byte 0x00000000
.endobj lbl_80414534
