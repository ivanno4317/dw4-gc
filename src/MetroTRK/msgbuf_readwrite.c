#include "msgbuf.h"

extern void* TRK_memcpy(void* dst, const void* src, unsigned long n);

int fn_800A6290(MessageBuffer* msg, void* dest, unsigned int len) {
    int result = 0;
    unsigned int avail;

    if (len == 0) {
        return 0;
    }

    avail = msg->fLength - msg->fPosition;
    if (len > avail) {
        result = 0x302;
        len = avail;
    }

    TRK_memcpy(dest, msg->fData + msg->fPosition, len);

    msg->fPosition += len;

    return result;
}

int fn_800A631C(MessageBuffer* msg, const void* src, unsigned int len) {
    int result = 0;
    unsigned int avail;

    if (len == 0) {
        return 0;
    }

    avail = kMessageBufferSize - msg->fPosition;
    if (avail < len) {
        result = kMessageBufferOverflow;
        len = avail;
    }

    if (len == 1) {
        msg->fData[msg->fPosition] = *(const unsigned char*) src;
    } else {
        TRK_memcpy(msg->fData + msg->fPosition, src, len);
    }

    msg->fPosition += len;
    msg->fLength = msg->fPosition;

    return result;
}
