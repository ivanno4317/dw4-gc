#include <dolphin/exi.h>
#include <dolphin/os.h>

#include "__os.h"

// prototypes
static int GetRTC(u32* rtc);

static int GetRTC(u32* rtc) {
    int err;
    u32 cmd;

    if (EXILock(0, 1, NULL) == 0) {
        return 0;
    }
    if (EXISelect(0, 1, 3) == 0) {
        EXIUnlock(0);
        return 0;
    }
    cmd = 0x20000000;
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIImm(0, &cmd, 4, 0, 0);
    err |= !EXISync(0);
    err |= !EXIDeselect(0);
    EXIUnlock(0);
    rtc[0] = cmd;
    return !err;
}

int __OSGetRTC(u32* rtc) {
    int err;
    u32 t0;
    u32 t1;
    int i;

    for(i = 0; i < 16; i++) {
        err = 0;
        err |= !GetRTC(&t0);
        err |= !GetRTC(&t1);
        if (err) {
            break;
        }
        if (t0 == t1) {
            rtc[0] = t0;
            return 1;
        }
    }
    return 0;
}

int __OSSetRTC(u32 rtc) {
    int err;
    u32 cmd;

    if (EXILock(0, 1, NULL) == 0) {
        return 0;
    }
    if (EXISelect(0, 1, 3) == 0) {
        EXIUnlock(0);
        return 0;
    }
    cmd = 0xA0000000;
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIImm(0, &rtc, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIDeselect(0);
    EXIUnlock(0);
    return !err;
}

int __OSCheckSram(void) {
    u16* p;
    u16 checkSum;
    u16 checkSumInv;
    OSSram* sram;
    int unused;

    ASSERTLINE(466, Scb.locked);

    checkSum = checkSumInv = 0;

    sram = (OSSram*)Scb.sram;

    for (p = (void*)&sram->counterBias; p < (u16*)&Scb.sram[0x14]; p++) {
        checkSum += *p;
        checkSumInv += ~(*p);
    }

    return (sram->checkSum == checkSum && sram->checkSumInv == checkSumInv);
}

int __OSReadROM(void * buffer, s32 length, s32 offset) {
    int err;
    u32 cmd;

    ASSERTLINE(497, length <= 1024);
    DCInvalidateRange(buffer, length);
    if (EXILock(0, 1, NULL) == 0) {
        return 0;
    }
    if (EXISelect(0, 1, 3) == 0) {
        EXIUnlock(0);
        return 0;
    }
    cmd = offset << 6;
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIDma(0, buffer, length, 0, NULL);
    err |= !EXISync(0);
    err |= !EXIDeselect(0);
    EXIUnlock(0);
    return !err;
}

static void __OSReadROMCallback(s32 chan) {
    void (*callback)();

    EXIDeselect(chan);
    EXIUnlock(chan);
    callback = Scb.callback;
    if (callback) {
        Scb.callback = NULL;
        callback();
    }
}

int __OSReadROMAsync(void* buffer, s32 length, s32 offset, void (*callback)()) {
    int err;
    u32 cmd;

    ASSERTLINE(556, length <= 1024);
    ASSERTLINE(557, callback);
    DCInvalidateRange(buffer, length);
    Scb.callback = callback;
    if (EXILock(0, 1, NULL) == 0) {
        return 0;
    }
    if (EXISelect(0, 1, 3) == 0) {
        EXIUnlock(0);
        return 0;
    }
    cmd = offset << 6;
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIDma(0, buffer, length, 0, (void*)__OSReadROMCallback);
    return !err;
}

u32 OSGetSoundMode(void) {
    OSSram* sram = __OSLockSram();
    u32 mode = (sram->flags & 4) ? 1 : 0;

    __OSUnlockSram(0);
    return mode;
}

void OSSetSoundMode(u32 mode) {
    OSSram* sram;
    int unused;

    ASSERTLINE(617, mode == OS_SOUND_MODE_MONO || mode == OS_SOUND_MODE_STEREO);
    mode *= 4;
    mode &= 4;
    sram = __OSLockSram();
    if (mode == (sram->flags & 4)) {
        __OSUnlockSram(0);
        return;
    }
    sram->flags &= 0xFFFFFFFB;
    sram->flags |= mode;
    __OSUnlockSram(1);
}

u32 OSGetProgressiveMode(void) {
    OSSram* sram;
    u32 on;

    sram = __OSLockSram();
    on = (sram->flags & 0x80) >> 7;
    __OSUnlockSram(FALSE);
    return on;
}

void OSSetProgressiveMode(u32 on) {
#ifndef DEBUG
    u32 padding[1];
#endif
    OSSram* sram;

    ASSERTLINE(670, on == OS_PROGRESSIVE_MODE_OFF || on == OS_PROGRESSIVE_MODE_ON);

    on <<= 7;
    on &= 0x80;

    sram = __OSLockSram();
    if (on == (sram->flags & 0x80)) {
        __OSUnlockSram(FALSE);
        return;
    }

    sram->flags &= ~0x80;
    sram->flags |= on;
    __OSUnlockSram(TRUE);
}

u32 OSGetVideoMode(void) {
    OSSram* sram = __OSLockSram();
    u32 mode = sram->flags & 3;

    __OSUnlockSram(0);

    if (mode > 2) {
        mode = 0;
    }

    return mode;
}

void OSSetVideoMode(u32 mode) {
    OSSram* sram;
    int unused;

    ASSERTLINE(731, OS_VIDEO_MODE_NTSC <= mode && mode <= OS_VIDEO_MODE_MPAL);

    if (mode > 2) {
        mode = 0;
    }

    sram = __OSLockSram();

    if (mode == (sram->flags & 3)) {
        __OSUnlockSram(0);
        return;
    }
    sram->flags &= 0xFFFFFFFC;
    sram->flags |= mode;
    __OSUnlockSram(1);
}

u8 OSGetLanguage(void) {
    OSSram* sram = __OSLockSram();
    u8 language = sram->language;

    __OSUnlockSram(0);
    return language;
}

void OSSetLanguage(u8 language) {
    OSSram* sram = __OSLockSram();
    int unused;

    if (language == sram->language) {
        __OSUnlockSram(0);
        return;
    }
    sram->language = language;
    __OSUnlockSram(1);
}

u8 __OSGetBootMode(void) {
    OSSram* sram = __OSLockSram();
    u8 ntd = sram->ntd;
    __OSUnlockSram(0);
    return ntd & 0x80;
}

void __OSSetBootMode(u8 ntd) {
    OSSram* sram;
    int unused;

    ntd &= 0x80;
    sram = __OSLockSram();
    if (ntd == (sram->ntd & 0x80U)) {
        __OSUnlockSram(0);
        return;
    }
    sram->ntd &= 0xFFFFFF7F;
    sram->ntd |= ntd;
    __OSUnlockSram(1);
}

u32 OSGetEuRgb60Mode(void) {
    OSSram* sram;
    u32 on;

    sram = __OSLockSram();
    on = (sram->ntd & 0x40) >> 6;
    __OSUnlockSram(0);
    return on;
}

void OSSetEuRgb60Mode(u32 on) {
#ifndef DEBUG
    u32 padding[1];
#endif
    OSSram* sram;

    ASSERTLINE(895, on == OS_EURGB60_OFF || on == OS_EURGB60_ON);
    on <<= 6;
    on &= 0x40;

    sram = __OSLockSram();
    if (on == (sram->ntd & 0x40)) {
        __OSUnlockSram(0);
    } else {
        sram->ntd &= ~0x40;
        sram->ntd |= on;
        __OSUnlockSram(1);
    }
}
