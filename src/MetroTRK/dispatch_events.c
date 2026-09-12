#include <string.h>

extern int fn_800AAB08(void* buf, int len);
extern int fn_800AA798(void);
extern int fn_800051C0(void);
extern unsigned long lbl_804F4548;
extern void TRKConstructEvent(void* event, int type);
extern void TRKPostEvent(void* event);

#define SEND_REPLY(status) \
    do { \
        unsigned char buf[0x40]; \
        memset(buf, 0, 0x40); \
        buf[0x4] = 0x80; \
        *(unsigned long*) (buf + 0x0) = 0x40; \
        buf[0x8] = (status); \
        fn_800AAB08(buf, 0x40); \
    } while (0)

int fn_800A78D8(void) {
    SEND_REPLY(0);
    fn_800AA798();
    return 0;
}

int fn_800A7930(void) {
    SEND_REPLY(0);
    fn_800051C0();
    return 0;
}

int fn_800A7988(void) {
    unsigned char event[0xc];

    lbl_804F4548 = 0;

    SEND_REPLY(0);

    TRKConstructEvent(event, 1);
    TRKPostEvent(event);

    return 0;
}

int fn_800A7A00(void) {
    lbl_804F4548 = 1;

    SEND_REPLY(0);

    return 0;
}
