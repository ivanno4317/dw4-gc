#include "msgbuf.h"

extern void* fn_80003238(void* dest, int val, int len);

void fn_800A63F0(MessageBuffer* buf, int flag) {
    buf->fLength = 0;
    buf->fPosition = 0;

    if (flag == 0) {
        fn_80003238(buf->fData, 0, kMessageBufferSize);
    }
}
