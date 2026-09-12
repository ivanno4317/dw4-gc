#include "dolphin_trk_glue.h"

extern void* TRK_memcpy(void* dst, const void* src, unsigned long n);
extern void PPCHalt(void);
extern int (*gDBCommTable[10])();
extern const char lbl_80414534[];

const u32 EndofProgramInstruction = 0x00454E44;

void TRKUARTInterruptHandler(void) {}

void InitializeProgramEndTrap(void) {
    u8* base = (u8*) PPCHalt;

    TRK_memcpy(base + 4, &EndofProgramInstruction, 4);
    ICInvalidateRange(base + 4, 4);
    DCFlushRange(base + 4, 4);
}

void TRK_board_display(char* msg) {
    OSReport(lbl_80414534, msg);
}

void UnreserveEXI2Port(void) {
    gDBCommTable[8]();
}

void ReserveEXI2Port(void) {
    gDBCommTable[9]();
}
