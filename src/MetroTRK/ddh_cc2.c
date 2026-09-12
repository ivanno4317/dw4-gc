#include <dolphin/amc/AmcExi2Comm.h>
#include "dserror.h"

DSError ddh_cc_post_stop(void) {
    EXI2_Reserve();
    return kNoError;
}

DSError ddh_cc_pre_continue(void) {
    EXI2_Unreserve();
    return kNoError;
}
