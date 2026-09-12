#include "msgbuf.h"
#include "usr_put.h"

extern const char lbl_80414008[];

TRKMsgBufs gTRKMsgBufs;

void TRKReleaseBuffer(int index)
{
    MessageBuffer* buf;

    if (index == -1) {
        return;
    }

    if (index >= 0 && index < 3) {
        buf = &gTRKMsgBufs.buffers[index];
        TRKAcquireMutex(buf);
        buf->fInUse = false;
        TRKReleaseMutex(buf);
    }
}

MessageBuffer* TRKGetBuffer(int index)
{
    MessageBuffer* buf = NULL;

    if (index >= 0 && index < NUM_BUFFERS) {
        buf = &gTRKMsgBufs.buffers[index];
    }

    return buf;
}

DSError TRKGetFreeBuffer(int* bufferIndexPtr, MessageBuffer** destBufPtr)
{
    MessageBuffer* buf;
    DSError error = kNoMessageBufferAvailable;
    int i;

    *destBufPtr = NULL;

    for (i = 0; i < NUM_BUFFERS; i++) {
        buf = NULL;

        if (i >= 0 && i < 3) {
            buf = &gTRKMsgBufs.buffers[i];
        }

        TRKAcquireMutex(buf);

        if (!buf->fInUse) {
            buf->fLength = 0;
            error = kNoError;
            buf->fPosition = 0;
            buf->fInUse = true;
            *destBufPtr = buf;
            *bufferIndexPtr = i;
            i = NUM_BUFFERS;
        }

        TRKReleaseMutex(buf);
    }

    if (error == kNoMessageBufferAvailable) {
        usr_puts_serial(lbl_80414008);
    }

    return error;
}

DSError TRKInitializeMessageBuffers(void) {
    int i;

    for (i = 0; i < NUM_BUFFERS; i++) {
        MessageBuffer* buf = &gTRKMsgBufs.buffers[i];
        TRKInitializeMutex(buf);
        TRKAcquireMutex(buf);
        buf->fInUse = false;
        TRKReleaseMutex(buf);
    }

    return kNoError;
}
