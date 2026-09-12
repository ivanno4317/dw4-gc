#include "dserror.h"

extern void DBInitInterrupts(void);

DSError gdev_cc_initinterrupts(void) {
    DBInitInterrupts();
    return kNoError;
}
