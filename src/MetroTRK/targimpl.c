#include "ppc_targimpl.h"

void TRKTargetSetInputPendingPtr(void* ptr)
{
    gTRKState.inputPendingPtr = ptr;
}

DSError TRKTargetStop(void)
{
    gTRKState.stopped = true;
    return kNoError;
}

void TRKTargetSetStopped(bool val)
{
    gTRKState.stopped = val;
}

bool TRKTargetStopped(void)
{
    return gTRKState.stopped;
}
