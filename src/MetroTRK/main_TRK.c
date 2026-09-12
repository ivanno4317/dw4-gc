#include "main_TRK.h"

#include "mainloop.h"
#include "nubinit.h"

extern void MWTRACE(int level, const char* fmt, ...);

const char lbl_80414520[] = "TRK_Main \n";
int TRK_mainError;

int TRK_main(void)
{
    MWTRACE(1, lbl_80414520);

    TRK_mainError = TRKInitializeNub();

    if (!TRK_mainError) {
        TRKNubWelcome();
        TRKNubMainLoop();
    }

    return TRK_mainError = TRKTerminateNub();
}
