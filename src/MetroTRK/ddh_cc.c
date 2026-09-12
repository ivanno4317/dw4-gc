#include <dolphin/amc/AmcExi2Comm.h>
#include "dserror.h"

DSError ddh_cc_initinterrupts(void) {
    EXI2_EnableInterrupts();
    return kNoError;
}
