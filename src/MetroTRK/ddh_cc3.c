#include <dolphin/amc/AmcExi2Comm.h>
#include "dserror.h"
#include "hwcc_ringbuf.h"

extern int lbl_805623F0;
extern const char lbl_804146EC[];
extern const char lbl_80414700[];
extern RingBuffer lbl_804F52F0;
extern unsigned char lbl_804F4AF0[0x800];

DSError ddh_cc_close(void) {
    return kNoError;
}

DSError ddh_cc_open(void) {
    if (lbl_805623F0 != 0) {
        return -0x2715;
    }
    lbl_805623F0 = 1;
    return kNoError;
}

DSError ddh_cc_shutdown(void) {
    return kNoError;
}

DSError ddh_cc_initialize(volatile unsigned char** inputPendingPtrRef, EXICallback monitorCallback) {
    MWTRACE(1, lbl_804146EC);
    EXI2_Init(inputPendingPtrRef, monitorCallback);
    MWTRACE(1, lbl_80414700);
    fn_800AB650(&lbl_804F52F0, lbl_804F4AF0, 0x800);
    return kNoError;
}
