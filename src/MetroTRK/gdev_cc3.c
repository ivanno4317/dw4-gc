#include <dolphin/amc/AmcTypes.h>
#include "dserror.h"
#include "hwcc_ringbuf.h"

extern void DBInitComm(volatile unsigned char** inputPendingPtrRef, EXICallback monitorCallback);

extern int lbl_805623F8;
extern const char lbl_804147CC[];
extern const char lbl_804147E0[];
extern RingBuffer lbl_804F5810;
extern unsigned char lbl_804F5310[0x500];

DSError gdev_cc_close(void) {
    return kNoError;
}

DSError gdev_cc_open(void) {
    if (lbl_805623F8 != 0) {
        return -0x2715;
    }
    lbl_805623F8 = 1;
    return kNoError;
}

DSError gdev_cc_shutdown(void) {
    return kNoError;
}

DSError gdev_cc_initialize(volatile unsigned char** inputPendingPtrRef, EXICallback monitorCallback) {
    MWTRACE(1, lbl_804147CC);
    DBInitComm(inputPendingPtrRef, monitorCallback);
    MWTRACE(1, lbl_804147E0);
    fn_800AB650(&lbl_804F5810, lbl_804F5310, 0x500);
    return kNoError;
}
