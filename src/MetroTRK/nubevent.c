#include "nubevent.h"

extern void TRKReleaseBuffer(MessageBufferID id);
extern void TRKAcquireMutex(void* p1);
extern void TRKReleaseMutex(void* p1);
extern void TRKInitializeMutex(void* p1);
extern void* TRK_memcpy(void* dst, const void* src, unsigned long n);

typedef struct EventQueue {
    u8 pad[4];
    int fCount;
    int fFirst;
    NubEvent fEventList[2];
    NubEventID fEventID;
} EventQueue;

EventQueue gTRKEventQueue;

void TRKDestructEvent(NubEvent* event)
{
    TRKReleaseBuffer(event->fMessageBufferID);
}

void TRKConstructEvent(NubEvent* event, int eventType)
{
    event->fType = eventType;
    event->fID = 0;
    event->fMessageBufferID = -1;
}

DSError TRKPostEvent(NubEvent* ev)
{
    DSError ret = kNoError;
    int evID;

    TRKAcquireMutex(&gTRKEventQueue);

    if (gTRKEventQueue.fCount == 2) {
        ret = kEventQueueFull;
    } else {
        evID = (gTRKEventQueue.fFirst + gTRKEventQueue.fCount) % 2;
        TRK_memcpy(&gTRKEventQueue.fEventList[evID], ev, sizeof(NubEvent));
        gTRKEventQueue.fEventList[evID].fID = gTRKEventQueue.fEventID;
        gTRKEventQueue.fEventID++;

        if (gTRKEventQueue.fEventID < 256) {
            gTRKEventQueue.fEventID = 256;
        }

        gTRKEventQueue.fCount++;
    }

    TRKReleaseMutex(&gTRKEventQueue);
    return ret;
}

bool TRKGetNextEvent(NubEvent* ev)
{
    bool ret = false;

    TRKAcquireMutex(&gTRKEventQueue);

    if (gTRKEventQueue.fCount > 0) {
        TRK_memcpy(ev, &gTRKEventQueue.fEventList[gTRKEventQueue.fFirst], sizeof(NubEvent));
        gTRKEventQueue.fCount--;
        gTRKEventQueue.fFirst++;

        if (gTRKEventQueue.fFirst == 2) {
            gTRKEventQueue.fFirst = 0;
        }

        ret = true;
    }

    TRKReleaseMutex(&gTRKEventQueue);
    return ret;
}

DSError TRKInitializeEventQueue(void)
{
    TRKInitializeMutex(&gTRKEventQueue);
    TRKAcquireMutex(&gTRKEventQueue);
    gTRKEventQueue.fCount = 0;
    gTRKEventQueue.fFirst = 0;
    gTRKEventQueue.fEventID = 0x100;
    TRKReleaseMutex(&gTRKEventQueue);
    return kNoError;
}
