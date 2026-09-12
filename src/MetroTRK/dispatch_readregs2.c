#include <string.h>
#include "msgbuf.h"
#include "hwcc_ringbuf.h"

extern void fn_800A63F0(MessageBuffer* msg, int flag);
extern int fn_800A612C(MessageBuffer* buf, const char* src, int count);
extern int fn_800A9A38(unsigned short start, unsigned short end, MessageBuffer* msg, void* out, int flag);
extern int fn_800A952C(unsigned short start, unsigned short end, MessageBuffer* msg, void* out, int flag);
extern int fn_800A93BC(unsigned short start, unsigned short end, MessageBuffer* msg, void* out, int flag);
extern int fn_800A8F84(unsigned short start, unsigned short end, MessageBuffer* msg, void* out, int flag);
extern int fn_800A5D7C(MessageBuffer* msg);
extern int fn_800AAB08(void* buf, int len);
extern const char lbl_804141F8[];

#define SEND_REPLY(status) \
    do { \
        unsigned char buf[0x40]; \
        memset(buf, 0, 0x40); \
        buf[0x4] = 0x80; \
        *(unsigned long*) (buf + 0x0) = 0x40; \
        buf[0x8] = (status); \
        fn_800AAB08(buf, 0x40); \
    } while (0)

int fn_800A7168(MessageBuffer* msg) {
    const char* base = lbl_804141F8;
    unsigned short start = *(unsigned short*) (msg->fData + 0xc);
    unsigned short end = *(unsigned short*) (msg->fData + 0x10);
    int result;
    int out;
    unsigned char header[0x40];

    if (start > end) {
        SEND_REPLY(0x14);
        return 0;
    }

    {
        header[0x4] = 0x80;
        *(unsigned long*) (header + 0x0) = 0x468;

        fn_800A63F0(msg, 0);

        MWTRACE(4, base + 0x98, msg->fLength);
        fn_800A612C(msg, (const char*) header, 0x40);
        MWTRACE(4, base + 0x98, msg->fLength);
    }

    result = fn_800A9A38(0, 0x24, msg, &out, 1);
    MWTRACE(4, base + 0xc0, result);
    MWTRACE(4, base + 0x98, msg->fLength);

    if (result == 0) {
        result = fn_800A952C(0, 0x21, msg, &out, 1);
    }
    MWTRACE(4, base + 0xf8, result);
    MWTRACE(4, base + 0x98, msg->fLength);

    if (result == 0) {
        result = fn_800A93BC(0, 0x60, msg, &out, 1);
    }
    MWTRACE(4, base + 0x120, result);
    MWTRACE(4, base + 0x98, msg->fLength);

    if (result == 0) {
        result = fn_800A8F84(0, 0x1f, msg, &out, 1);
    }
    MWTRACE(4, base + 0x150, result);
    MWTRACE(4, base + 0x98, msg->fLength);

    if (result != 0) {
        int status;
        switch (result) {
        case 0x703:
            status = 0x12;
            break;
        case 0x701:
            status = 0x14;
            break;
        case 0x702:
            status = 0x15;
            break;
        case 0x704:
            status = 0x21;
            break;
        case 0x705:
            status = 0x22;
            break;
        case 0x706:
            status = 0x20;
            break;
        default:
            status = 0x3;
            break;
        }

        SEND_REPLY((unsigned char) status);
        return 0;
    }

    MWTRACE(1, base + 0x60);
    result = fn_800A5D7C(msg);
    MWTRACE(1, base + 0x80, result);
    return result;
}
