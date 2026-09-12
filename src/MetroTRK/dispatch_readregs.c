#include <string.h>
#include "msgbuf.h"
#include "hwcc_ringbuf.h"

extern int fn_800A63C0(MessageBuffer* buf, u32 pos);
extern void fn_800A63F0(MessageBuffer* msg, int flag);
extern int fn_800A9A38(unsigned short start, unsigned short end, MessageBuffer* msg, void* out, int flag);
extern int fn_800A952C(unsigned short start, unsigned short end, MessageBuffer* msg, void* out, int flag);
extern int fn_800A93BC(unsigned short start, unsigned short end, MessageBuffer* msg, void* out, int flag);
extern int fn_800A8F84(unsigned short start, unsigned short end, MessageBuffer* msg, void* out, int flag);
extern int fn_800A631C(MessageBuffer* msg, void* buf, int len);
extern int fn_800A5D7C(MessageBuffer* msg);
extern int fn_800AAB08(void* buf, int len);
extern const char lbl_80414258[];
extern const char lbl_80414278[];

#define SEND_REPLY(status) \
    do { \
        unsigned char buf[0x40]; \
        memset(buf, 0, 0x40); \
        buf[0x4] = 0x80; \
        *(unsigned long*) (buf + 0x0) = 0x40; \
        buf[0x8] = (status); \
        fn_800AAB08(buf, 0x40); \
    } while (0)

int fn_800A6ED8(MessageBuffer* msg) {
    int result = msg->fData[8];
    unsigned short start = *(unsigned short*) (msg->fData + 0xc);
    unsigned short end = *(unsigned short*) (msg->fData + 0x10);
    int scratch;
    unsigned char buf2[0x40];

    fn_800A63C0(msg, 0);

    if (start > end) {
        SEND_REPLY(0x14);
        return 0;
    }

    fn_800A63C0(msg, 0x40);

    switch (result) {
    case 0:
        result = fn_800A9A38(start, end, msg, &scratch, 0);
        break;
    case 1:
        result = fn_800A952C(start, end, msg, &scratch, 0);
        break;
    case 2:
        result = fn_800A93BC(start, end, msg, &scratch, 0);
        break;
    case 3:
        result = fn_800A8F84(start, end, msg, &scratch, 0);
        break;
    default:
        result = 0x703;
        break;
    }

    fn_800A63F0(msg, 0);

    if (result == 0) {
        memset(buf2, 0, 0x40);
        *(unsigned long*) (buf2 + 0x0) = 0x40;
        buf2[0x4] = 0x80;
        buf2[0x8] = (unsigned char) result;
        result = fn_800A631C(msg, buf2, 0x40);
    }

    if (result != 0) {
        switch (result) {
        case 0x703:
            result = 0x12;
            break;
        case 0x701:
            result = 0x14;
            break;
        case 0x302:
            result = 0x2;
            break;
        case 0x702:
            result = 0x15;
            break;
        case 0x704:
            result = 0x21;
            break;
        case 0x705:
            result = 0x22;
            break;
        case 0x706:
            result = 0x20;
            break;
        default:
            result = 0x3;
            break;
        }

        SEND_REPLY((unsigned char) result);
        return 0;
    }

    MWTRACE(1, lbl_80414258);
    result = fn_800A5D7C(msg);
    MWTRACE(1, lbl_80414278, result);
    return result;
}
