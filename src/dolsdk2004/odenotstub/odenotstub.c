#include <dolphin.h>
#include <dolphin/odemu/odemu.h>

#define ALIGN_PREV(X, N) ((X) & ~((N) - 1))
#define ALIGN_NEXT(X, N) ALIGN_PREV(((X) + (N) - 1), N)

u8 SendCount = 0x80;

u8 EXIInputFlag;
u8* pEXIInputFlag;
s32 RecvDataLeng;
u32 SendMailData;
// not __OSInterruptHandler because f u that's why
void (*DBGCallback)(u32, OSContext*);
__OSInterruptHandler MTRCallback;

BOOL DBGEXIImm(void* data, s32 byte_size, u32 write);
void DBGHandler(__OSInterrupt interrupt, OSContext* context);
void MWCallback(u32 interrupt, OSContext* context);
BOOL DBGReadStatus(void* param_1);
BOOL DBGWrite(u32 param1, u32* data, s32 byte_size);
BOOL DBGRead(u32 param1, u32* data, s32 byte_size);
BOOL DBGReadMailbox(void* param1);

static inline void DBGEXIInit(void) {
    __OSMaskInterrupts(0x18000);
    __EXIRegs[10] = 0;
}

static inline BOOL DBGEXISelect(u32 v) {
    u32 regs = __EXIRegs[10];
    regs &= 0x405;
    regs |= 0x80 | (v << 4);
    __EXIRegs[10] = regs;
    return TRUE;
}

static inline BOOL DBGEXIDeselect(void) {
    __EXIRegs[10] &= 0x405;
    return TRUE;
}

static inline BOOL DBGEXISync(void) {
    while (__EXIRegs[13] & 1)
        ;
    return TRUE;
}

static inline BOOL DBGWriteMailbox(u32 param_1) {
    BOOL error = FALSE;
    u32 value;

    if (!DBGEXISelect(4)) {
        return FALSE;
    }

    value = (param_1 & 0x1FFFFFFF) | 0xC0000000;
    error |= !DBGEXIImm((u8*)&value, sizeof(value), 1);
    error |= !DBGEXISync();
    error |= !DBGEXIDeselect();

    return !error;
}

static inline void CheckMailBox(void) {
    u32 local_8[2];

    DBGReadStatus(local_8);
    if (local_8[0] & 1) {
        DBGReadMailbox(local_8);
        local_8[0] &= ~0xE0000000;
        if ((local_8[0] & 0x1F000000) == 0x1F000000) {
            SendMailData = local_8[0];
            RecvDataLeng = local_8[0] & 0x7FFF;
            EXIInputFlag = 1;
        }
    }
}

void DBClose(void) {}

void DBOpen(void) {}

asm int DBWrite(register const void* data, register u32 size) {
    nofralloc
    mflr r0
    stw r0, 0x4(r1)
    stwu r1, -0x78(r1)
    stmw r24, 0x58(r1)
    addi r26, r3, 0x0
    addi r27, r4, 0x0
    bl OSDisableInterrupts
    addi r28, r3, 0x0
    lis r25, 0xcc00
    lis r31, 0x4000
L_loop1:
    lwz r0, 0x6828(r25)
    addi r30, r25, 0x6800
    addi r3, r1, 0x50
    andi. r0, r0, 0x405
    li r4, 0x2
    li r5, 0x1
    ori r0, r0, 0xc0
    stwu r0, 0x28(r30)
    stw r31, 0x50(r1)
    bl DBGEXIImm
    cntlzw r0, r3
    srwi r24, r0, 5
L_sync1a:
    addi r29, r25, 0x6800
    lwzu r0, 0x34(r29)
    clrlwi. r0, r0, 31
    bne L_sync1a
    addi r3, r1, 0x54
    li r4, 0x4
    li r5, 0x0
    bl DBGEXIImm
L_sync1b:
    lwz r0, 0x0(r29)
    clrlwi. r0, r0, 31
    bne L_sync1b
    lwz r0, 0x0(r30)
    andi. r0, r0, 0x405
    stw r0, 0x0(r30)
    lwz r0, 0x54(r1)
    rlwinm. r0, r0, 0, 30, 30
    bne L_loop1
    lbz r3, SendCount(r0)
    addi r0, r3, 0x1
    stb r0, SendCount(r0)
    lbz r0, SendCount(r0)
    clrlwi. r0, r0, 31
    beq L_zero1
    li r3, 0x1000
    b L_join1
L_zero1:
    li r3, 0x0
L_join1:
    addi r0, r27, 0x3
    oris r25, r3, 0x1
    clrrwi r24, r0, 2
    ori r25, r25, 0xc000
L_writeloop:
    addi r3, r25, 0x0
    addi r4, r26, 0x0
    addi r5, r24, 0x0
    bl DBGWrite
    cmpwi r3, 0x0
    beq L_writeloop
    lis r31, 0x4000
L_loop2:
    lwz r0, 0x0(r30)
    addi r3, r1, 0x4c
    li r4, 0x2
    andi. r0, r0, 0x405
    li r5, 0x1
    ori r0, r0, 0xc0
    stw r0, 0x0(r30)
    stw r31, 0x4c(r1)
    bl DBGEXIImm
    cntlzw r0, r3
    srwi r26, r0, 5
L_sync2a:
    lwz r0, 0x0(r29)
    clrlwi. r0, r0, 31
    bne L_sync2a
    addi r3, r1, 0x54
    li r4, 0x4
    li r5, 0x0
    bl DBGEXIImm
L_sync2b:
    lwz r0, 0x0(r29)
    clrlwi. r0, r0, 31
    bne L_sync2b
    lwz r0, 0x0(r30)
    andi. r0, r0, 0x405
    stw r0, 0x0(r30)
    lwz r0, 0x54(r1)
    rlwinm. r0, r0, 0, 30, 30
    bne L_loop2
    lbz r0, SendCount(r0)
    slwi r0, r0, 16
    oris r0, r0, 0x1f00
    or r0, r0, r27
    clrlwi r0, r0, 3
    oris r24, r0, 0xc000
L_mbloop:
    lwz r0, 0x0(r30)
    addi r3, r1, 0x44
    li r4, 0x4
    andi. r0, r0, 0x405
    li r5, 0x1
    ori r0, r0, 0xc0
    stw r0, 0x0(r30)
    stw r24, 0x44(r1)
    bl DBGEXIImm
    cntlzw r0, r3
    srwi r3, r0, 5
L_sync3a:
    lwz r0, 0x0(r29)
    clrlwi. r0, r0, 31
    bne L_sync3a
    lwz r0, 0x0(r30)
    andi. r0, r0, 0x405
    cmpwi r3, 0x0
    stw r0, 0x0(r30)
    bne L_mbloop
    lis r27, 0x4000
L_loop3:
    lwz r0, 0x0(r30)
    addi r3, r1, 0x3c
    li r4, 0x2
    andi. r0, r0, 0x405
    li r5, 0x1
    ori r0, r0, 0xc0
    stw r0, 0x0(r30)
    stw r27, 0x3c(r1)
    bl DBGEXIImm
    cntlzw r0, r3
    srwi r26, r0, 5
L_sync4a:
    lwz r0, 0x0(r29)
    clrlwi. r0, r0, 31
    bne L_sync4a
    addi r3, r1, 0x54
    li r4, 0x4
    li r5, 0x0
    bl DBGEXIImm
    cntlzw r0, r3
    srwi r0, r0, 5
    or r3, r26, r0
L_sync4b:
    lwz r0, 0x0(r29)
    clrlwi. r0, r0, 31
    bne L_sync4b
    lwz r0, 0x0(r30)
    andi. r0, r0, 0x405
    cmpwi r3, 0x0
    stw r0, 0x0(r30)
    bne L_loop3
    lwz r0, 0x54(r1)
    rlwinm. r0, r0, 0, 30, 30
    bne L_loop3
    mr r3, r28
    bl OSRestoreInterrupts
    lmw r24, 0x58(r1)
    li r3, 0x0
    lwz r0, 0x7c(r1)
    addi r1, r1, 0x78
    mtlr r0
    blr
}

asm int DBRead(register void* param1, register u32 param2) {
    nofralloc
    mflr r0
    stw r0, 0x4(r1)
    stwu r1, -0x20(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    addi r30, r4, 0x0
    stw r29, 0x14(r1)
    addi r29, r3, 0x0
    bl OSDisableInterrupts
    lwz r0, SendMailData(r0)
    addi r31, r3, 0x0
    rlwinm. r0, r0, 0, 15, 15
    beq L_zero
    li r3, 0x1000
    b L_join
L_zero:
    li r3, 0x0
L_join:
    addis r3, r3, 0x2
    addi r0, r30, 0x3
    addi r4, r29, 0x0
    clrrwi r5, r0, 2
    subi r3, r3, 0x2000
    bl DBGRead
    li r0, 0x0
    stw r0, RecvDataLeng(r0)
    mr r3, r31
    stb r0, EXIInputFlag(r0)
    bl OSRestoreInterrupts
    lwz r0, 0x24(r1)
    li r3, 0x0
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    addi r1, r1, 0x20
    mtlr r0
    blr
}

asm int DBQueryData(void) {
    nofralloc
    mflr r0
    li r3, 0x0
    stw r0, 0x4(r1)
    stwu r1, -0x18(r1)
    stw r31, 0x14(r1)
    lwz r0, RecvDataLeng(r0)
    stb r3, EXIInputFlag(r0)
    cmpwi r0, 0x0
    bne L_done
    bl OSDisableInterrupts
    addi r31, r3, 0x0
    addi r3, r1, 0x8
    bl DBGReadStatus
    lwz r0, 0x8(r1)
    clrlwi. r0, r0, 31
    beq L_restore
    addi r3, r1, 0x8
    bl DBGReadMailbox
    lwz r0, 0x8(r1)
    clrlwi r0, r0, 3
    stw r0, 0x8(r1)
    lwz r4, 0x8(r1)
    rlwinm r3, r4, 0, 3, 7
    subis r0, r3, 0x1f00
    cmplwi r0, 0x0
    bne L_restore
    clrlwi r3, r4, 17
    stw r4, SendMailData(r0)
    li r0, 0x1
    stw r3, RecvDataLeng(r0)
    stb r0, EXIInputFlag(r0)
L_restore:
    mr r3, r31
    bl OSRestoreInterrupts
L_done:
    lwz r3, RecvDataLeng(r0)
    lwz r0, 0x1c(r1)
    lwz r31, 0x14(r1)
    addi r1, r1, 0x18
    mtlr r0
    blr
}

asm int DBInitInterrupts(void) {
    nofralloc
    mflr r0
    lis r3, 0x2
    stw r0, 0x4(r1)
    addi r3, r3, -0x8000
    stwu r1, -0x8(r1)
    bl __OSMaskInterrupts
    li r3, 0x40
    bl __OSMaskInterrupts
    lis r3, MWCallback@ha
    addi r0, r3, MWCallback@l
    lis r3, DBGHandler@ha
    stw r0, DBGCallback(r0)
    addi r4, r3, DBGHandler@l
    li r3, 0x19
    bl __OSSetInterruptHandler
    li r3, 0x40
    bl __OSUnmaskInterrupts
    lwz r0, 0xc(r1)
    addi r1, r1, 0x8
    mtlr r0
    blr
}

asm void DBInitComm(register int* inputFlagPtr, register int* mtrCallback) {
    nofralloc
    mflr r0
    stw r0, 0x4(r1)
    stwu r1, -0x20(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    addi r30, r4, 0x0
    stw r29, 0x14(r1)
    addi r29, r3, 0x0
    bl OSDisableInterrupts
    la r0, EXIInputFlag(r0)
    stw r0, pEXIInputFlag(r0)
    lis r4, 0x2
    addi r31, r3, 0x0
    lwz r0, pEXIInputFlag(r0)
    addi r3, r4, -0x8000
    stw r0, 0x0(r29)
    stw r30, MTRCallback(r0)
    bl __OSMaskInterrupts
    lis r3, 0xcc00
    li r0, 0x0
    stw r0, 0x6828(r3)
    mr r3, r31
    bl OSRestoreInterrupts
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    addi r1, r1, 0x20
    mtlr r0
    blr
}

asm void DBGHandler(register __OSInterrupt interrupt, register OSContext* context) {
    nofralloc
    mflr r0
    lis r5, 0xcc00
    stw r0, 0x4(r1)
    li r0, 0x1000
    stwu r1, -0x8(r1)
    lwz r12, DBGCallback(r0)
    stw r0, 0x3000(r5)
    cmplwi r12, 0x0
    beq L_dbgh1
    mtlr r12
    extsh r3, r3
    blrl
L_dbgh1:
    lwz r0, 0xc(r1)
    addi r1, r1, 0x8
    mtlr r0
    blr
}

asm void MWCallback(register u32 interrupt, register OSContext* context) {
    nofralloc
    mflr r0
    stw r0, 0x4(r1)
    li r0, 0x1
    stwu r1, -0x8(r1)
    lwz r12, MTRCallback(r0)
    stb r0, EXIInputFlag(r0)
    cmplwi r12, 0x0
    beq L_mwcb1
    mtlr r12
    li r3, 0x0
    blrl
L_mwcb1:
    lwz r0, 0xc(r1)
    addi r1, r1, 0x8
    mtlr r0
    blr
}

asm BOOL DBGReadStatus(register void* param_1) {
    nofralloc
    mflr r0
    li r4, 0x2
    stw r0, 0x4(r1)
    lis r0, 0x4000
    stwu r1, -0x38(r1)
    stmw r27, 0x24(r1)
    lis r30, 0xcc00
    addi r27, r3, 0x0
    addi r29, r30, 0x6800
    addi r3, r1, 0x18
    lwz r5, 0x6828(r30)
    andi. r5, r5, 0x405
    ori r5, r5, 0xc0
    stwu r5, 0x28(r29)
    li r5, 0x1
    stw r0, 0x18(r1)
    bl DBGEXIImm
    cntlzw r0, r3
    srwi r31, r0, 5
L_rdstat1:
    addi r28, r30, 0x6800
    lwzu r0, 0x34(r28)
    clrlwi. r0, r0, 31
    bne L_rdstat1
    addi r3, r27, 0x0
    li r4, 0x4
    li r5, 0x0
    bl DBGEXIImm
    cntlzw r0, r3
    srwi r0, r0, 5
    or r3, r31, r0
L_rdstat2:
    lwz r0, 0x0(r28)
    clrlwi. r0, r0, 31
    bne L_rdstat2
    lwz r4, 0x0(r29)
    cntlzw r0, r3
    srwi r3, r0, 5
    andi. r0, r4, 0x405
    stw r0, 0x0(r29)
    lmw r27, 0x24(r1)
    lwz r0, 0x3c(r1)
    addi r1, r1, 0x38
    mtlr r0
    blr
}

asm BOOL DBGWrite(register u32 param1, register u32* data, register s32 byte_size) {
    nofralloc
    mflr r0
    stw r0, 0x4(r1)
    rlwinm r0, r3, 8, 7, 21
    oris r0, r0, 0xa000
    stwu r1, -0x40(r1)
    stmw r26, 0x28(r1)
    lis r29, 0xcc00
    addi r30, r5, 0x0
    addi r26, r4, 0x0
    addi r31, r29, 0x6800
    addi r3, r1, 0x24
    li r4, 0x4
    li r5, 0x1
    lwz r6, 0x6828(r29)
    andi. r6, r6, 0x405
    ori r6, r6, 0xc0
    stwu r6, 0x28(r31)
    stw r0, 0x24(r1)
    bl DBGEXIImm
    cntlzw r0, r3
    srwi r0, r0, 5
    mr r27, r0
L_wr1:
    addi r28, r29, 0x6800
    lwzu r0, 0x34(r28)
    clrlwi. r0, r0, 31
    bne L_wr1
    b L_wr4
L_wr2:
    lwz r0, 0x0(r26)
    addi r3, r1, 0x20
    li r4, 0x4
    stw r0, 0x20(r1)
    li r5, 0x1
    addi r26, r26, 0x4
    bl DBGEXIImm
    cntlzw r0, r3
    srwi r0, r0, 5
    or r27, r27, r0
L_wr3:
    lwz r0, 0x0(r28)
    clrlwi. r0, r0, 31
    bne L_wr3
    subic. r30, r30, 0x4
    bge L_wr4
    li r30, 0x0
L_wr4:
    cmpwi r30, 0x0
    bne L_wr2
    lwz r4, 0x0(r31)
    cntlzw r0, r27
    srwi r3, r0, 5
    andi. r0, r4, 0x405
    stw r0, 0x0(r31)
    lmw r26, 0x28(r1)
    lwz r0, 0x44(r1)
    addi r1, r1, 0x40
    mtlr r0
    blr
}

asm BOOL DBGRead(register u32 param1, register u32* data, register s32 byte_size) {
    nofralloc
    mflr r0
    stw r0, 0x4(r1)
    rlwinm r0, r3, 8, 7, 21
    oris r0, r0, 0x2000
    stwu r1, -0x40(r1)
    stmw r26, 0x28(r1)
    lis r29, 0xcc00
    addi r30, r5, 0x0
    addi r26, r4, 0x0
    addi r31, r29, 0x6800
    addi r3, r1, 0x24
    li r4, 0x4
    li r5, 0x1
    lwz r6, 0x6828(r29)
    andi. r6, r6, 0x405
    ori r6, r6, 0xc0
    stwu r6, 0x28(r31)
    stw r0, 0x24(r1)
    bl DBGEXIImm
    cntlzw r0, r3
    srwi r0, r0, 5
    mr r27, r0
L_rd1:
    addi r28, r29, 0x6800
    lwzu r0, 0x34(r28)
    clrlwi. r0, r0, 31
    bne L_rd1
    b L_rd4
L_rd2:
    addi r3, r1, 0x20
    li r4, 0x4
    li r5, 0x0
    bl DBGEXIImm
    cntlzw r0, r3
    srwi r0, r0, 5
    or r27, r27, r0
L_rd3:
    lwz r0, 0x0(r28)
    clrlwi. r0, r0, 31
    bne L_rd3
    lwz r0, 0x20(r1)
    subic. r30, r30, 0x4
    stw r0, 0x0(r26)
    addi r26, r26, 0x4
    bge L_rd4
    li r30, 0x0
L_rd4:
    cmpwi r30, 0x0
    bne L_rd2
    lwz r4, 0x0(r31)
    cntlzw r0, r27
    srwi r3, r0, 5
    andi. r0, r4, 0x405
    stw r0, 0x0(r31)
    lmw r26, 0x28(r1)
    lwz r0, 0x44(r1)
    addi r1, r1, 0x40
    mtlr r0
    blr
}

asm BOOL DBGReadMailbox(register void* param1) {
    nofralloc
    mflr r0
    li r4, 0x2
    stw r0, 0x4(r1)
    lis r0, 0x6000
    stwu r1, -0x38(r1)
    stmw r27, 0x24(r1)
    lis r30, 0xcc00
    addi r27, r3, 0x0
    addi r29, r30, 0x6800
    addi r3, r1, 0x18
    lwz r5, 0x6828(r30)
    andi. r5, r5, 0x405
    ori r5, r5, 0xc0
    stwu r5, 0x28(r29)
    li r5, 0x1
    stw r0, 0x18(r1)
    bl DBGEXIImm
    cntlzw r0, r3
    srwi r31, r0, 5
L_rdmb1:
    addi r28, r30, 0x6800
    lwzu r0, 0x34(r28)
    clrlwi. r0, r0, 31
    bne L_rdmb1
    addi r3, r27, 0x0
    li r4, 0x4
    li r5, 0x0
    bl DBGEXIImm
    cntlzw r0, r3
    srwi r0, r0, 5
    or r3, r31, r0
L_rdmb2:
    lwz r0, 0x0(r28)
    clrlwi. r0, r0, 31
    bne L_rdmb2
    lwz r4, 0x0(r29)
    cntlzw r0, r3
    srwi r3, r0, 5
    andi. r0, r4, 0x405
    stw r0, 0x0(r29)
    lmw r27, 0x24(r1)
    lwz r0, 0x3c(r1)
    addi r1, r1, 0x38
    mtlr r0
    blr
}

asm BOOL DBGEXIImm(register void* data, register s32 byte_size, register u32 write) {
    nofralloc
    stwu r1, -0x48(r1)
    cmplwi r5, 0x0
    stmw r22, 0x20(r1)
    beq L_exi1
    li r29, 0x0
    cmpw r29, r4
    li r30, 0x0
    bge L_exi2
    cmpwi r4, 0x8
    subi r6, r4, 0x8
    ble L_exi11
    addi r0, r6, 0x7
    srwi r0, r0, 3
    cmpwi r6, 0x0
    mtctr r0
    addi r31, r3, 0x0
    ble L_exi11
L_exi3:
    subfic r6, r29, 0x3
    lbz r12, 0x0(r31)
    addi r0, r29, 0x1
    lbz r11, 0x1(r31)
    slwi r10, r6, 3
    lbz r9, 0x2(r31)
    subfic r8, r0, 0x3
    lbz r7, 0x3(r31)
    addi r6, r29, 0x2
    lbz r0, 0x4(r31)
    slw r12, r12, r10
    lbz r23, 0x5(r31)
    slwi r10, r8, 3
    lbz r25, 0x6(r31)
    subfic r6, r6, 0x3
    lbz r27, 0x7(r31)
    slwi r8, r6, 3
    neg r6, r29
    addi r22, r29, 0x4
    slwi r6, r6, 3
    subfic r22, r22, 0x3
    addi r24, r29, 0x5
    slwi r22, r22, 3
    subfic r24, r24, 0x3
    addi r26, r29, 0x6
    slwi r24, r24, 3
    subfic r26, r26, 0x3
    addi r28, r29, 0x7
    slwi r26, r26, 3
    subfic r28, r28, 0x3
    slwi r28, r28, 3
    or r30, r30, r12
    slw r10, r11, r10
    or r30, r30, r10
    slw r8, r9, r8
    or r30, r30, r8
    slw r6, r7, r6
    or r30, r30, r6
    slw r0, r0, r22
    or r30, r30, r0
    slw r0, r23, r24
    or r30, r30, r0
    slw r0, r25, r26
    or r30, r30, r0
    slw r0, r27, r28
    or r30, r30, r0
    addi r31, r31, 0x8
    addi r29, r29, 0x8
    bdnz L_exi3
    b L_exi11
L_exi4:
    subf r0, r29, r4
    cmpw r29, r4
    mtctr r0
    bge L_exi2
L_exi5:
    subfic r0, r29, 0x3
    lbz r6, 0x0(r7)
    slwi r0, r0, 3
    slw r0, r6, r0
    or r30, r30, r0
    addi r7, r7, 0x1
    addi r29, r29, 0x1
    bdnz L_exi5
L_exi2:
    lis r6, 0xcc00
    stw r30, 0x6838(r6)
L_exi1:
    subi r0, r4, 0x1
    lis r6, 0xcc00
    slwi r7, r5, 2
    addi r8, r6, 0x6800
    ori r6, r7, 0x1
    slwi r0, r0, 4
    or r0, r6, r0
    stwu r0, 0x34(r8)
L_exi6:
    lwz r0, 0x0(r8)
    clrlwi. r0, r0, 31
    bne L_exi6
    cmplwi r5, 0x0
    bne L_exi7
    li r5, 0x0
    lis r6, 0xcc00
    cmpw r5, r4
    lwz r0, 0x6838(r6)
    bge L_exi7
    cmpwi r4, 0x8
    subi r7, r4, 0x8
    ble L_exi8
    addi r6, r7, 0x7
    srwi r6, r6, 3
    cmpwi r7, 0x0
    mtctr r6
    ble L_exi8
L_exi9:
    subfic r6, r5, 0x3
    slwi r7, r6, 3
    addi r6, r5, 0x1
    srw r8, r0, r7
    subfic r6, r6, 0x3
    stb r8, 0x0(r3)
    slwi r7, r6, 3
    addi r6, r5, 0x2
    srw r12, r0, r7
    subfic r6, r6, 0x3
    stb r12, 0x1(r3)
    slwi r6, r6, 3
    srw r11, r0, r6
    neg r6, r5
    stb r11, 0x2(r3)
    slwi r7, r6, 3
    addi r6, r5, 0x4
    srw r10, r0, r7
    subfic r6, r6, 0x3
    stb r10, 0x3(r3)
    slwi r7, r6, 3
    addi r6, r5, 0x5
    srw r9, r0, r7
    subfic r6, r6, 0x3
    stb r9, 0x4(r3)
    slwi r7, r6, 3
    srw r8, r0, r7
    addi r6, r5, 0x6
    stb r8, 0x5(r3)
    subfic r7, r6, 0x3
    addi r6, r5, 0x7
    slwi r7, r7, 3
    srw r7, r0, r7
    subfic r6, r6, 0x3
    stb r7, 0x6(r3)
    slwi r6, r6, 3
    srw r6, r0, r6
    stb r6, 0x7(r3)
    addi r3, r3, 0x8
    addi r5, r5, 0x8
    bdnz L_exi9
L_exi8:
    subf r6, r5, r4
    cmpw r5, r4
    mtctr r6
    bge L_exi7
L_exi10:
    subfic r4, r5, 0x3
    slwi r4, r4, 3
    srw r4, r0, r4
    stb r4, 0x0(r3)
    addi r3, r3, 0x1
    addi r5, r5, 0x1
    bdnz L_exi10
L_exi7:
    li r3, 0x1
    b L_exi12
L_exi11:
    add r7, r3, r29
    b L_exi4
L_exi12:
    lmw r22, 0x20(r1)
    addi r1, r1, 0x48
    blr
}
