#include <string.h>
#include "hwcc_ringbuf.h"

extern int TRKTargetStopped(void);
extern int TRKTargetContinue(void);
extern int fn_800AAB08(void* buf, int len);
extern const char lbl_8041422C[];

int fn_800A6E28(void) {
    int result;

    MWTRACE(1, lbl_8041422C);

    if (TRKTargetStopped() == 0) {
        unsigned char buf[0x40];
        memset(buf, 0, 0x40);
        buf[0x4] = 0x80;
        *(unsigned long*) (buf + 0x0) = 0x40;
        buf[0x8] = 0x16;
        fn_800AAB08(buf, 0x40);
        result = 0;
    } else {
        unsigned char buf[0x40];
        memset(buf, 0, 0x40);
        buf[0x4] = 0x80;
        *(unsigned long*) (buf + 0x0) = 0x40;
        buf[0x8] = 0x0;
        fn_800AAB08(buf, 0x40);
        result = TRKTargetContinue();
    }

    return result;
}
