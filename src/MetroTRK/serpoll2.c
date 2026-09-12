#include "nubevent.h"
#include "msgbuf.h"

typedef struct SerialHandlerState {
    int lastId;
    int unk4;
    int field8;
    int field0xc;
} SerialHandlerState;

extern SerialHandlerState lbl_804F4530;
extern int fn_800A6778(void);

void fn_800A66C8(int messageBufferID) {
    NubEvent event;
    TRKConstructEvent(&event, kRequestEvent);
    event.fMessageBufferID = messageBufferID;
    lbl_804F4530.lastId = -1;
    TRKPostEvent(&event);
}

void TRKGetInput(void) {
    int result = fn_800A6778();
    if (result != -1) {
        NubEvent event;
        TRKGetBuffer(result);
        TRKConstructEvent(&event, kRequestEvent);
        event.fMessageBufferID = result;
        lbl_804F4530.lastId = -1;
        TRKPostEvent(&event);
    }
}
