#include "msgbuf.h"

int fn_800A63C0(MessageBuffer* buf, u32 pos) {
    int result = 0;

    if (pos > kMessageBufferSize) {
        result = kMessageBufferOverflow;
    } else {
        buf->fPosition = pos;
        if (pos > buf->fLength) {
            buf->fLength = pos;
        }
    }

    return result;
}
