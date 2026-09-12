.include "macros.inc"

.section .text, "ax"

.balign 4

.fn fn_800A8254, global
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r4, r1, 0x8
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r3
    addi r3, r1, 0xc
    bl TRKGetFreeBuffer
    mr. r31, r3
    bne .L_800A82D0
    bne .L_800A82A0
    cmpwi r30, 0x90
    bne .L_800A8298
    lwz r3, 0x8(r1)
    bl fn_800A8CBC
    b .L_800A82A0
.L_800A8298:
    lwz r3, 0x8(r1)
    bl fn_800A8C38
.L_800A82A0:
    lwz r3, 0x8(r1)
    addi r4, r1, 0x10
    li r5, 0x2
    li r6, 0x3
    li r7, 0x1
    bl fn_800A7E3C
    mr. r31, r3
    bne .L_800A82C8
    lwz r3, 0x10(r1)
    bl TRKReleaseBuffer
.L_800A82C8:
    lwz r3, 0xc(r1)
    bl TRKReleaseBuffer
.L_800A82D0:
    lwz r0, 0x24(r1)
    mr r3, r31
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
.endfn fn_800A8254

.fn fn_800A82EC, global
    lis r5, 0xffff
    ori r5, r5, 0xfff1
    and r5, r5, r3
    subf r3, r5, r3
    add r4, r4, r3
.L_800A8300:
    dcbst r0, r5
    dcbf r0, r5
    sync
    icbi r0, r5
    addic r5, r5, 0x8
    subic. r4, r4, 0x8
    bge .L_800A8300
    isync
    blr
.endfn fn_800A82EC

.fn fn_800A8324, global
    cmplwi r5, 0x20
    clrlwi r4, r4, 24
    subi r6, r3, 0x1
    mr r7, r4
    blt .L_800A83C4
    nor r0, r6, r6
    clrlwi. r3, r0, 30
    beq .L_800A8354
    subf r5, r3, r5
.L_800A8348:
    subic. r3, r3, 0x1
    stbu r7, 0x1(r6)
    bne .L_800A8348
.L_800A8354:
    cmplwi r7, 0x0
    beq .L_800A8374
    slwi r3, r7, 24
    slwi r0, r7, 16
    slwi r4, r7, 8
    or r0, r3, r0
    or r0, r4, r0
    or r7, r7, r0
.L_800A8374:
    srwi. r4, r5, 5
    subi r3, r6, 0x3
    beq .L_800A83A8
.L_800A8380:
    stw r7, 0x4(r3)
    subic. r4, r4, 0x1
    stw r7, 0x8(r3)
    stw r7, 0xc(r3)
    stw r7, 0x10(r3)
    stw r7, 0x14(r3)
    stw r7, 0x18(r3)
    stw r7, 0x1c(r3)
    stwu r7, 0x20(r3)
    bne .L_800A8380
.L_800A83A8:
    extrwi. r4, r5, 3, 27
    beq .L_800A83BC
.L_800A83B0:
    subic. r4, r4, 0x1
    stwu r7, 0x4(r3)
    bne .L_800A83B0
.L_800A83BC:
    addi r6, r3, 0x3
    clrlwi r5, r5, 30
.L_800A83C4:
    cmplwi r5, 0x0
    beqlr
.L_800A83CC:
    subic. r5, r5, 0x1
    stbu r7, 0x1(r6)
    bne .L_800A83CC
    blr
.endfn fn_800A8324

.fn fn_800A83DC, global
    mfmsr r3
    blr
.endfn fn_800A83DC

.fn fn_800A83E4, global
    mtmsr r3
    blr
.endfn fn_800A83E4

.fn fn_800A83EC, global
    mfmsr r8
    li r10, 0x0
.L_800A83F4:
    cmpw r10, r5
    beq .L_800A841C
    mtmsr r7
    sync
    lbzx r9, r10, r4
    mtmsr r6
    sync
    stbx r9, r10, r3
    addi r10, r10, 0x1
    b .L_800A83F4
.L_800A841C:
    mtmsr r8
    sync
    blr
.endfn fn_800A83EC

.fn TRKInterruptHandler, global
    mtsrr0 r2
    mtsrr1 r4
    mfsprg r4, 3
    mfcr r2
    mtsprg 3, r2
    lis r2, gTRKState@h
    ori r2, r2, gTRKState@l
    lwz r2, 0x8c(r2)
    ori r2, r2, 0x8002
    xori r2, r2, 0x8002
    sync
    mtmsr r2
    sync
    lis r2, TRK_saved_exceptionID@h
    ori r2, r2, TRK_saved_exceptionID@l
    sth r3, 0x0(r2)
    cmpwi r3, 0x500
    bne .L_800A84F0
    lis r2, gTRKCPUState@h
    ori r2, r2, gTRKCPUState@l
    mflr r3
    stw r3, 0x42c(r2)
    bl TRKUARTInterruptHandler
    lis r2, gTRKCPUState@h
    ori r2, r2, gTRKCPUState@l
    lwz r3, 0x42c(r2)
    mtlr r3
    lis r2, gTRKState@h
    ori r2, r2, gTRKState@l
    lwz r2, 0xa0(r2)
    lbz r2, 0x0(r2)
    cmpwi r2, 0x0
    beq .L_800A84D4
    lis r2, gTRKExceptionStatus@h
    ori r2, r2, gTRKExceptionStatus@l
    lbz r2, 0xc(r2)
    cmpwi r2, 0x1
    beq .L_800A84D4
    lis r2, gTRKState@h
    ori r2, r2, gTRKState@l
    li r3, 0x1
    stb r3, 0x9c(r2)
    b .L_800A84F0
.L_800A84D4:
    lis r2, gTRKSaveState@h
    ori r2, r2, gTRKSaveState@l
    lwz r3, 0x88(r2)
    mtcrf 255, r3
    lwz r3, 0xc(r2)
    lwz r2, 0x8(r2)
    rfi
.L_800A84F0:
    lis r2, TRK_saved_exceptionID@h
    ori r2, r2, TRK_saved_exceptionID@l
    lhz r3, 0x0(r2)
    lis r2, gTRKExceptionStatus@h
    ori r2, r2, gTRKExceptionStatus@l
    lbz r2, 0xc(r2)
    cmpwi r2, 0x0
    bne TRKExceptionHandler
    lis r2, gTRKCPUState@h
    ori r2, r2, gTRKCPUState@l
    stw r0, 0x0(r2)
    stw r1, 0x4(r2)
    mfsprg r0, 1
    stw r0, 0x8(r2)
    sth r3, 0x2f8(r2)
    sth r3, 0x2fa(r2)
    mfsprg r0, 2
    stw r0, 0xc(r2)
    stmw r4, 0x10(r2)
    mfsrr0 r27
    mflr r28
    mfsprg r29, 3
    mfctr r30
    mfxer r31
    stmw r27, 0x80(r2)
    bl TRKSaveExtended1Block
    lis r2, gTRKExceptionStatus@h
    ori r2, r2, gTRKExceptionStatus@l
    li r3, 0x1
    stb r3, 0xc(r2)
    lis r2, gTRKState@h
    ori r2, r2, gTRKState@l
    lwz r0, 0x8c(r2)
    sync
    mtmsr r0
    sync
    lwz r0, 0x80(r2)
    mtlr r0
    lwz r0, 0x84(r2)
    mtctr r0
    lwz r0, 0x88(r2)
    mtxer r0
    lwz r0, 0x94(r2)
    mtdsisr r0
    lwz r0, 0x90(r2)
    mtdar r0
    lmw r3, 0xc(r2)
    lwz r0, 0x0(r2)
    lwz r1, 0x4(r2)
    lwz r2, 0x8(r2)
    b TRKPostInterruptEvent
.endfn TRKInterruptHandler

.fn TRKExceptionHandler, global
    lis r2, gTRKExceptionStatus@h
    ori r2, r2, gTRKExceptionStatus@l
    sth r3, 0x8(r2)
    mfsrr0 r3
    stw r3, 0x0(r2)
    lhz r3, 0x8(r2)
    cmpwi r3, 0x200
    beq .L_800A8628
    cmpwi r3, 0x300
    beq .L_800A8628
    cmpwi r3, 0x400
    beq .L_800A8628
    cmpwi r3, 0x600
    beq .L_800A8628
    cmpwi r3, 0x700
    beq .L_800A8628
    cmpwi r3, 0x800
    beq .L_800A8628
    cmpwi r3, 0x1000
    beq .L_800A8628
    cmpwi r3, 0x1100
    beq .L_800A8628
    cmpwi r3, 0x1200
    beq .L_800A8628
    cmpwi r3, 0x1300
    beq .L_800A8628
    b .L_800A8634
.L_800A8628:
    mfsrr0 r3
    addi r3, r3, 0x4
    mtsrr0 r3
.L_800A8634:
    lis r2, gTRKExceptionStatus@h
    ori r2, r2, gTRKExceptionStatus@l
    li r3, 0x1
    stb r3, 0xd(r2)
    mfsprg r3, 3
    mtcrf 255, r3
    mfsprg r2, 1
    mfsprg r3, 2
    rfi
.endfn TRKExceptionHandler

.fn TRKSwapAndGo, global
    lis r3, gTRKState@h
    ori r3, r3, gTRKState@l
    stmw r0, 0x0(r3)
    mfmsr r0
    stw r0, 0x8c(r3)
    mflr r0
    stw r0, 0x80(r3)
    mfctr r0
    stw r0, 0x84(r3)
    mfxer r0
    stw r0, 0x88(r3)
    mfdsisr r0
    stw r0, 0x94(r3)
    mfdar r0
    stw r0, 0x90(r3)
    li r1, -0x7ffe
    nor r1, r1, r1
    mfmsr r3
    and r3, r3, r1
    mtmsr r3
    lis r2, gTRKState@h
    ori r2, r2, gTRKState@l
    lwz r2, 0xa0(r2)
    lbz r2, 0x0(r2)
    cmpwi r2, 0x0
    beq .L_800A86D4
    lis r2, gTRKState@h
    ori r2, r2, gTRKState@l
    li r3, 0x1
    stb r3, 0x9c(r2)
    b TRKInterruptHandlerEnableInterrupts
.L_800A86D4:
    lis r2, gTRKExceptionStatus@h
    ori r2, r2, gTRKExceptionStatus@l
    li r3, 0x0
    stb r3, 0xc(r2)
    bl TRKRestoreExtended1Block
    lis r2, gTRKCPUState@h
    ori r2, r2, gTRKCPUState@l
    lmw r27, 0x80(r2)
    mtsrr0 r27
    mtlr r28
    mtcrf 255, r29
    mtctr r30
    mtxer r31
    lmw r3, 0xc(r2)
    lwz r0, 0x0(r2)
    lwz r1, 0x4(r2)
    lwz r2, 0x8(r2)
    rfi
.endfn TRKSwapAndGo

.fn TRKInterruptHandlerEnableInterrupts, global
    lis r2, gTRKState@h
    ori r2, r2, gTRKState@l
    lwz r0, 0x8c(r2)
    sync
    mtmsr r0
    sync
    lwz r0, 0x80(r2)
    mtlr r0
    lwz r0, 0x84(r2)
    mtctr r0
    lwz r0, 0x88(r2)
    mtxer r0
    lwz r0, 0x94(r2)
    mtdsisr r0
    lwz r0, 0x90(r2)
    mtdar r0
    lmw r3, 0xc(r2)
    lwz r0, 0x0(r2)
    lwz r1, 0x4(r2)
    lwz r2, 0x8(r2)
    b TRKPostInterruptEvent
.endfn TRKInterruptHandlerEnableInterrupts

.fn fn_800A8770, global
    stwu r1, -0x40(r1)
    stfd f31, 0x10(r1)
    psq_st f31, 0x20(r1), 0, qr0
    mffs f31
    stfd f31, 0x0(r3)
    psq_l f31, 0x20(r1), 0, qr0
    lfd f31, 0x10(r1)
    addi r1, r1, 0x40
    blr
.endfn fn_800A8770

.fn fn_800A8794, global
    stwu r1, -0x40(r1)
    stfd f31, 0x10(r1)
    psq_st f31, 0x20(r1), 0, qr0
    lfd f31, 0x0(r3)
    mtfsf 255, f31
    psq_l f31, 0x20(r1), 0, qr0
    lfd f31, 0x10(r1)
    addi r1, r1, 0x40
    blr
.endfn fn_800A8794

.fn fn_800A87B8, global
    stwu r1, -0x30(r1)
    mflr r0
    lis r7, gTRKExceptionStatus@ha
    cmpwi r6, 0x0
    stw r0, 0x34(r1)
    li r0, 0x0
    stw r31, 0x2c(r1)
    addi r31, r7, gTRKExceptionStatus@l
    stw r30, 0x28(r1)
    li r30, 0x0
    stw r29, 0x24(r1)
    mr r29, r5
    lwz r6, 0xc(r31)
    lwz r9, 0x0(r31)
    lwz r8, 0x4(r31)
    lwz r7, 0x8(r31)
    stw r9, 0x8(r1)
    stw r8, 0xc(r1)
    stw r7, 0x10(r1)
    stw r6, 0x14(r1)
    stb r0, 0xd(r31)
    beq .L_800A8818
    bl fn_800AA618
    b .L_800A881C
.L_800A8818:
    bl fn_800AA42C
.L_800A881C:
    lbz r0, 0xd(r31)
    cmplwi r0, 0x0
    beq .L_800A8834
    li r0, 0x0
    li r30, 0x702
    stw r0, 0x0(r29)
.L_800A8834:
    lis r3, gTRKExceptionStatus@ha
    lwz r6, 0x8(r1)
    addi r7, r3, gTRKExceptionStatus@l
    lwz r5, 0xc(r1)
    lwz r4, 0x10(r1)
    mr r3, r30
    lwz r0, 0x14(r1)
    stw r6, 0x0(r7)
    stw r5, 0x4(r7)
    stw r4, 0x8(r7)
    stw r0, 0xc(r7)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
.endfn fn_800A87B8
