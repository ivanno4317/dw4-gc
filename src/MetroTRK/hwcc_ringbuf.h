#ifndef _METROTRK_HWCC_RINGBUF_H
#define _METROTRK_HWCC_RINGBUF_H

#include <dolphin/os.h>

typedef struct RingBuffer {
    unsigned char* readPtr;
    unsigned char* writePtr;
    unsigned char* bufBase;
    unsigned long bufSize;
    unsigned long available;
    unsigned long freeSpace;
    BOOL lockState;
} RingBuffer;

extern void fn_800ABA44(BOOL* state);
extern void fn_800ABA68(BOOL* state);
extern void fn_800ABA98(void* unused);
extern int fn_800AB440(RingBuffer* rb, void* dst, unsigned long len);
extern int fn_800AB548(RingBuffer* rb, const void* src, unsigned long len);
extern void fn_800AB650(RingBuffer* rb, void* buf, unsigned long size);
extern unsigned long fn_800AB6A0(RingBuffer* rb);

extern void MWTRACE(int level, const char* fmt, ...);

#endif
