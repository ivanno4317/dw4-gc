#include "msgbuf.h"
#include "hwcc_ringbuf.h"

extern int fn_800A63C0(MessageBuffer* buf, u32 pos);
extern int fn_800A7A00(MessageBuffer* msg);
extern int fn_800A7988(MessageBuffer* msg);
extern int fn_800A7930(MessageBuffer* msg);
extern int fn_800A78D8(MessageBuffer* msg);
extern int fn_800A78D0(MessageBuffer* msg);
extern int fn_800A78C8(MessageBuffer* msg);
extern int fn_800A7684(MessageBuffer* msg);
extern int fn_800A7448(MessageBuffer* msg);
extern int fn_800A7168(MessageBuffer* msg);
extern int fn_800A6ED8(MessageBuffer* msg);
extern int fn_800A6E28(MessageBuffer* msg);
extern int fn_800A6C08(MessageBuffer* msg);
extern int fn_800A6B60(MessageBuffer* msg);
extern int fn_800A6AB8(MessageBuffer* msg);
extern const char lbl_804141B8[];
extern const char lbl_804141D4[];

int TRKDispatchMessage(MessageBuffer* msg) {
    int result = 0x500;

    fn_800A63C0(msg, 0);

    MWTRACE(1, lbl_804141B8, msg->fData[4]);

    switch (msg->fData[4]) {
    case 1:
        result = fn_800A7A00(msg);
        break;
    case 2:
        result = fn_800A7988(msg);
        break;
    case 3:
        result = fn_800A7930(msg);
        break;
    case 7:
        result = fn_800A78D8(msg);
        break;
    case 4:
        result = fn_800A78D0(msg);
        break;
    case 5:
        result = fn_800A78C8(msg);
        break;
    case 16:
        result = fn_800A7684(msg);
        break;
    case 17:
        result = fn_800A7448(msg);
        break;
    case 18:
        result = fn_800A7168(msg);
        break;
    case 19:
        result = fn_800A6ED8(msg);
        break;
    case 24:
        result = fn_800A6E28(msg);
        break;
    case 25:
        result = fn_800A6C08(msg);
        break;
    case 26:
        result = fn_800A6B60(msg);
        break;
    case 23:
        result = fn_800A6AB8(msg);
        break;
    }

    MWTRACE(1, lbl_804141D4, result);
    return result;
}
