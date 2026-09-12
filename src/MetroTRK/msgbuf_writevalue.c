#include "msgbuf.h"

extern int gTRKBigEndian;
extern void* TRK_memcpy(void* dst, const void* src, unsigned long n);

int fn_800A6194(MessageBuffer* msg, int unused, unsigned long valueHi, unsigned long valueLo) {
    unsigned char swapped[8];
    unsigned char raw[8];
    unsigned char* src;
    unsigned int avail;
    int result;
    unsigned int len;

    *(unsigned long*) (raw + 0) = valueHi;
    *(unsigned long*) (raw + 4) = valueLo;

    if (gTRKBigEndian) {
        src = raw;
    } else {
        swapped[0] = raw[7];
        swapped[1] = raw[6];
        swapped[2] = raw[5];
        swapped[3] = raw[4];
        swapped[4] = raw[3];
        swapped[5] = raw[2];
        swapped[6] = raw[1];
        swapped[7] = raw[0];
        src = swapped;
    }

    len = 8;
    result = 0;

    avail = kMessageBufferSize - msg->fPosition;
    if (avail < len) {
        result = kMessageBufferOverflow;
        len = avail;
    }

    if (len == 1) {
        msg->fData[msg->fPosition] = *src;
    } else {
        TRK_memcpy(msg->fData + msg->fPosition, src, len);
    }

    msg->fPosition += len;
    msg->fLength = msg->fPosition;

    return result;
}
