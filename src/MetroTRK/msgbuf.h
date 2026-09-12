#ifndef _METROTRK_MSGBUF_H
#define _METROTRK_MSGBUF_H

#include "trk_platform.h"

#include "dserror.h"
#include "mutex_TRK.h"

typedef int MessageBufferID;

#define kMessageBufferSize (0x800 + 0x80)
#define NUM_BUFFERS 3

typedef struct MessageBuffer {
    /* 0x00 */ DSMutex fMutex;
    /* 0x04 */ bool fInUse;
    /* 0x08 */ u32 fLength;
    /* 0x0C */ u32 fPosition;
    /* 0x10 */ u8 fData[kMessageBufferSize];
} MessageBuffer; // size = 0x890

typedef struct TRKMsgBufs {
    /* 0x00 */ MessageBuffer buffers[NUM_BUFFERS];
} TRKMsgBufs;

extern TRKMsgBufs gTRKMsgBufs;

MessageBuffer* TRKGetBuffer(int index);
void TRKReleaseBuffer(int index);
DSError TRKGetFreeBuffer(int* bufferIndexPtr, MessageBuffer** destBufPtr);
DSError TRKInitializeMessageBuffers(void);

#endif
