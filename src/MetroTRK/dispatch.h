#ifndef _METROTRK_DISPATCH_H
#define _METROTRK_DISPATCH_H

#include "dserror.h"
#include "msgbuf.h"

/* 3276A8 */ DSError TRKInitializeDispatcher(void);
/* 3276BC */ DSError TRKDispatchMessage(MessageBuffer* buf);

#endif
