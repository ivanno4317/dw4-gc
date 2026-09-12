.include "macros.inc"

.section .text, "ax"

.balign 4

.fn OSInitSemaphore, global
    mflr r0
    stw r0, 0x4(r1)
    stwu r1, -0x20(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    addi r30, r4, 0x0
    stw r29, 0x14(r1)
    addi r29, r3, 0x0
    bl OSDisableInterrupts
    addi r31, r3, 0x0
    addi r3, r29, 0x4
    bl OSInitThreadQueue
    stw r30, 0x0(r29)
    mr r3, r31
    bl OSRestoreInterrupts
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    addi r1, r1, 0x20
    mtlr r0
    blr
.endfn OSInitSemaphore

.fn OSWaitSemaphore, global
    mflr r0
    stw r0, 0x4(r1)
    stwu r1, -0x20(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    mr r29, r3
    bl OSDisableInterrupts
    mr r31, r3
    b .L_800AAABB0_0
.L_800AAABB0_1:
    addi r3, r29, 0x4
    bl OSSleepThread
.L_800AAABB0_0:
    lwz r30, 0x0(r29)
    cmpwi r30, 0x0
    ble .L_800AAABB0_1
    lwz r4, 0x0(r29)
    addi r3, r31, 0x0
    subi r0, r4, 0x1
    stw r0, 0x0(r29)
    bl OSRestoreInterrupts
    mr r3, r30
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    addi r1, r1, 0x20
    mtlr r0
    blr
.endfn OSWaitSemaphore

.fn OSTryWaitSemaphore, global
    mflr r0
    stw r0, 0x4(r1)
    stwu r1, -0x18(r1)
    stw r31, 0x14(r1)
    stw r30, 0x10(r1)
    mr r30, r3
    bl OSDisableInterrupts
    lwz r4, 0x0(r30)
    cmpwi r4, 0x0
    addi r31, r4, 0x0
    ble .L_800AAABB0_2
    subi r0, r4, 0x1
    stw r0, 0x0(r30)
.L_800AAABB0_2:
    bl OSRestoreInterrupts
    mr r3, r31
    lwz r0, 0x1c(r1)
    lwz r31, 0x14(r1)
    lwz r30, 0x10(r1)
    addi r1, r1, 0x18
    mtlr r0
    blr
.endfn OSTryWaitSemaphore

.fn OSSignalSemaphore, global
    mflr r0
    stw r0, 0x4(r1)
    stwu r1, -0x20(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    mr r29, r3
    bl OSDisableInterrupts
    lwz r30, 0x0(r29)
    addi r31, r3, 0x0
    addi r3, r29, 0x4
    addi r0, r30, 0x1
    stw r0, 0x0(r29)
    bl OSWakeupThread
    mr r3, r31
    bl OSRestoreInterrupts
    mr r3, r30
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    addi r1, r1, 0x20
    mtlr r0
    blr
.endfn OSSignalSemaphore

.fn OSGetSemaphoreCount, global
    lwz r3, 0x0(r3)
    blr
.endfn OSGetSemaphoreCount

.sym __OSSystemCallVectorStart, global

.fn fn_80260F2C, global
    mfspr r9, HID0
    ori r10, r9, 0x8
    mtspr HID0, r10
    isync
    sync
    mtspr HID0, r9
    rfi
.sym __OSSystemCallVectorEnd, global
    nop
.endfn fn_80260F2C

.fn __OSInitSystemCall, global
    mflr r0
    stw r0, 0x4(r1)
    stwu r1, -0x10(r1)
    stw r31, 0xc(r1)
    lis r5, 0x8000
    lis r4, __OSSystemCallVectorStart@ha
    lis r3, __OSSystemCallVectorEnd@ha
    addi r31, r5, 0xc00
    addi r0, r3, __OSSystemCallVectorEnd@l
    addi r4, r4, __OSSystemCallVectorStart@l
    mr r3, r31
    subf r5, r4, r0
    bl memcpy
    mr r3, r31
    li r4, 0x100
    bl DCFlushRangeNoSync
    sync
    mr r3, r31
    li r4, 0x100
    bl ICInvalidateRange
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    addi r1, r1, 0x10
    mtlr r0
    blr
.endfn __OSInitSystemCall
