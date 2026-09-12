#ifndef METROTRK_DOLPHIN_TRK_H
#define METROTRK_DOLPHIN_TRK_H

#include "trk_platform.h"

#include "dserror.h"

SECTION_INIT void __TRK_reset(void);
void InitMetroTRK(void);
void EnableMetroTRKInterrupts(void);
u32 TRKTargetTranslate(u32 addr);
DSError TRKInitializeTarget(void);

#endif
