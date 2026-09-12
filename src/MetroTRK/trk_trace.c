#include <dolphin/os.h>

void MWTRACE(int level, const char* fmt, ...) {}

void fn_800ABA44(BOOL* state) {
    OSRestoreInterrupts(*state);
}

void fn_800ABA68(BOOL* state) {
    *state = OSDisableInterrupts();
}

void fn_800ABA98(void* unused) {}
