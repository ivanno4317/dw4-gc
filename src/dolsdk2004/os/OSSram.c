#include <dolphin/exi.h>
#include <dolphin/os.h>

#include "__os.h"

static SramControl Scb ATTRIBUTE_ALIGN(DOLPHIN_ALIGNMENT);

// prototypes
static int ReadSram(void* buffer);
static void WriteSramCallback(s32, OSContext*);
static int WriteSram(void* buffer, u32 offset, u32 size);
static void* LockSram(u32 offset);
static int UnlockSram(int commit, u32 offset);

static int ReadSram(void* buffer) {
    int err;
    u32 cmd;

    DCInvalidateRange(buffer, SRAM_SIZE);
    if (!EXILock(0, 1, NULL) ) {
        return 0;
    }
    if (!EXISelect(0, 1, 3)) {
        EXIUnlock(0);
        return 0;
    }
    cmd = 0x20000100;
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIDma(0, buffer, SRAM_SIZE, 0, NULL);
    err |= !EXISync(0);
    err |= !EXIDeselect(0);
    EXIUnlock(0);
    return !err;
}

static void WriteSramCallback(s32, OSContext*) {
    ASSERTLINE(258, !Scb.locked);
    Scb.sync = WriteSram(&Scb.sram[Scb.offset], Scb.offset, SRAM_SIZE - Scb.offset);
    if (Scb.sync != 0) {
        Scb.offset = SRAM_SIZE;
    }
    ASSERTLINE(264, Scb.sync);
}

static int WriteSram(void* buffer, u32 offset, u32 size) {
    int err;
    u32 cmd;

    if (!EXILock(0, 1, WriteSramCallback)) {
        return 0;
    }
    if (!EXISelect(0, 1, 3)) {
        EXIUnlock(0);
        return 0;
    }
    offset <<= 6;
    cmd = ((offset + 0x100) | 0xA0000000);
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIImmEx(0, buffer, size, 1);
    err |= !EXIDeselect(0);
    EXIUnlock(0);
    return !err;
}

void __OSInitSram(void) {
    Scb.locked = Scb.enabled = FALSE;
    Scb.sync = ReadSram(&Scb);
    ASSERTLINE(318, Scb.sync);
    Scb.offset = SRAM_SIZE;

    OSSetGbsMode(OSGetGbsMode());
}

static void* LockSram(u32 offset) {
    BOOL enabled;

    enabled = OSDisableInterrupts();
    ASSERTLINE(341, !Scb.locked);
    if (Scb.locked) {
        OSRestoreInterrupts(enabled);
        return NULL;
    }
    Scb.enabled = enabled;
    Scb.locked = TRUE;
    return &Scb.sram[offset];
}

OSSram* __OSLockSram(void) {
    return (OSSram*)LockSram(0);
}

OSSramEx* __OSLockSramEx(void) {
    return (OSSramEx*)LockSram(sizeof(OSSram));
}

static int UnlockSram(int commit, u32 offset) {
    u16* p;

    ASSERTLINE(375, Scb.locked);
    if (commit != 0) {
        if (offset == 0) {
            OSSram* sram  = (OSSram*)Scb.sram;
            if (2u < (sram->flags & 3)) {
                sram->flags &= ~3;
            }

            sram->checkSum = sram->checkSumInv = 0;
            for(p = (u16*)&sram->counterBias; p < ((u16*)&Scb.sram[0x14]); p++) {
                sram->checkSum += *p;
                sram->checkSumInv += ~(*p);
            }
        }
        if (offset < Scb.offset) {
            Scb.offset = offset;
        }

        if (Scb.offset <= 0x14) {
            OSSramEx* sram = (OSSramEx*)(Scb.sram + sizeof(OSSram));
            if (((u32)sram->gbs & 0x7c00) == 0x5000 || ((u32)sram->gbs & 0xc0) == 0xc0) {
                sram->gbs = 0;
            }
        }

        Scb.sync = WriteSram(&Scb.sram[Scb.offset], Scb.offset, SRAM_SIZE - Scb.offset);
        if (Scb.sync != 0) {
            Scb.offset = SRAM_SIZE;
        }
    }
    Scb.locked = FALSE;
    OSRestoreInterrupts(Scb.enabled);
    return Scb.sync;
}

int __OSUnlockSram(int commit) {
    UnlockSram(commit, 0);
}

int __OSUnlockSramEx(int commit) {
    UnlockSram(commit, sizeof(OSSram));
}

int __OSSyncSram(void) {
    return Scb.sync;
}

u16 OSGetWirelessID(s32 chan) {
    OSSramEx* sram;
    u16 id;

    sram = __OSLockSramEx();
    id = sram->wirelessPadID[chan];
    __OSUnlockSramEx(FALSE);
    return id;
}

void OSSetWirelessID(s32 chan, u16 id) {
    OSSramEx* sram;

    sram = __OSLockSramEx();
    if (sram->wirelessPadID[chan] != id) {
        sram->wirelessPadID[chan] = id;
        __OSUnlockSramEx(TRUE);
        return;
    }

    __OSUnlockSramEx(FALSE);
}

u16 OSGetGbsMode(void) {
    OSSramEx* sram;
    u16 mode;

    sram = __OSLockSramEx();
    mode = sram->gbs;
    __OSUnlockSramEx(FALSE);
    return mode;
}

void OSSetGbsMode(u16 mode) {
#ifndef DEBUG
    u32 padding[1];
#endif
    OSSramEx* sram;

    if (((u32)mode & 0x7c00) == 0x5000 || ((u32)mode & 0xc0) == 0xc0) {
        mode = 0;
    }

    sram = __OSLockSramEx();

    if (mode == sram->gbs) {
        __OSUnlockSramEx(FALSE);
        return;
    }
    sram->gbs = mode;

    __OSUnlockSramEx(TRUE);
}
