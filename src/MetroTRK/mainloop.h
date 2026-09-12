#ifndef _METROTRK_MAINLOOP_H
#define _METROTRK_MAINLOOP_H

#include "nubevent.h"

void TRKHandleRequestEvent(NubEvent*);
void TRKHandleSupportEvent(NubEvent* ev);
void TRKIdle(void);
void TRKNubMainLoop(void);

#endif
