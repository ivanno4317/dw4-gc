#include "dserror.h"

extern void DBOpen(void);
extern void DBClose(void);

DSError gdev_cc_post_stop(void) {
    DBOpen();
    return kNoError;
}

DSError gdev_cc_pre_continue(void) {
    DBClose();
    return kNoError;
}
