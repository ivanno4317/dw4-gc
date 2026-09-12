#include "msgbuf.h"
#include "hwcc_ringbuf.h"

extern int fn_800AAB08(void* buf, int len);
extern const char lbl_80413FE0[];

int fn_800A5D7C(MessageBuffer* msg) {
    int result = fn_800AAB08(msg->fData, msg->fLength);
    MWTRACE(1, lbl_80413FE0, result);
    return 0;
}
