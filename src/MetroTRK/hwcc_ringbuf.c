#include <string.h>
#include "hwcc_ringbuf.h"

int fn_800AB440(RingBuffer* rb, void* dst, unsigned long len) {
    unsigned long spaceToEnd;

    if (len > rb->available) {
        return -1;
    }

    fn_800ABA68(&rb->lockState);

    spaceToEnd = rb->bufSize - (rb->readPtr - rb->bufBase);
    if (len < spaceToEnd) {
        memcpy(dst, rb->readPtr, len);
        rb->readPtr += len;
    } else {
        memcpy(dst, rb->readPtr, spaceToEnd);
        memcpy((unsigned char*) dst + spaceToEnd, rb->bufBase, len - spaceToEnd);
        rb->readPtr = rb->bufBase + len - spaceToEnd;
    }

    if (rb->readPtr - rb->bufBase == rb->bufSize) {
        rb->readPtr = rb->bufBase;
    }

    rb->freeSpace += len;
    rb->available -= len;
    fn_800ABA44(&rb->lockState);
    return 0;
}

int fn_800AB548(RingBuffer* rb, const void* src, unsigned long len) {
    unsigned long spaceToEnd;

    if (len > rb->freeSpace) {
        return -1;
    }

    fn_800ABA68(&rb->lockState);

    spaceToEnd = rb->bufSize - (rb->writePtr - rb->bufBase);
    if (spaceToEnd >= len) {
        memcpy(rb->writePtr, src, len);
        rb->writePtr += len;
    } else {
        memcpy(rb->writePtr, src, spaceToEnd);
        memcpy(rb->bufBase, (const unsigned char*) src + spaceToEnd, len - spaceToEnd);
        rb->writePtr = rb->bufBase + len - spaceToEnd;
    }

    if (rb->writePtr - rb->bufBase == rb->bufSize) {
        rb->writePtr = rb->bufBase;
    }

    rb->freeSpace -= len;
    rb->available += len;
    fn_800ABA44(&rb->lockState);
    return 0;
}

void fn_800AB650(RingBuffer* rb, void* buf, unsigned long size) {
    rb->bufBase = buf;
    rb->bufSize = size;
    rb->readPtr = rb->bufBase;
    rb->writePtr = rb->bufBase;
    rb->available = 0;
    rb->freeSpace = rb->bufSize;
    fn_800ABA98(&rb->lockState);
}

unsigned long fn_800AB6A0(RingBuffer* rb) {
    return rb->available;
}
