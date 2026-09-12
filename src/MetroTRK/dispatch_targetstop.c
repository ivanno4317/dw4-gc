#include <string.h>

extern int TRKTargetStop(void);
extern int fn_800AAB08(void* buf, int len);

int fn_800A6B60(void) {
    int result;
    unsigned char buf[0x40];

    switch (TRKTargetStop()) {
    case 0:
        result = 0;
        break;
    case 0x704:
        result = 0x21;
        break;
    case 0x705:
        result = 0x22;
        break;
    case 0x706:
        result = 0x20;
        break;
    default:
        result = 1;
        break;
    }

    memset(buf, 0, 0x40);
    buf[0x4] = 0x80;
    *(unsigned long*) (buf + 0x0) = 0x40;
    buf[0x8] = (unsigned char) result;
    fn_800AAB08(buf, 0x40);

    return 0;
}
