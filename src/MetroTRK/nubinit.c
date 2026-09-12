#include "nubinit.h"

#include "dispatch.h"
#include "dolphin_trk_glue.h"
#include "hwcc_ringbuf.h"
#include "msgbuf.h"
#include "nubevent.h"
#include "serpoll.h"
#include "targimpl.h"
#include "usr_put.h"

extern DSError TRKInitializeTarget(void);

bool gTRKBigEndian;

void TRKNubWelcome(void)
{
    TRK_board_display("MetroTRK for GAMECUBE v2.6");
}

DSError TRKTerminateNub(void)
{
    TRKTerminateSerialHandler();
    return kNoError;
}

static const char msg_initnub[] = "Initialize NUB\n";

asm DSError TRKInitializeNub(void)
{
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    li r5, 0x12
    li r4, 0x34
    stw r0, 0x24(r1)
    li r3, 0x56
    li r0, 0x78
    li r6, 0x1
    stb r5, 0x8(r1)
    lis r5, gTRKBigEndian@ha
    stw r31, 0x1c(r1)
    li r31, 0x0
    stw r30, 0x18(r1)
    stb r4, 0x9(r1)
    stb r3, 0xa(r1)
    stb r0, 0xb(r1)
    lwz r3, 0x8(r1)
    stwu r6, gTRKBigEndian@l(r5)
    subis r0, r3, 0x1234
    cmplwi r0, 0x5678
    bne L_bigendian_check
    stw r6, 0x0(r5)
    b L_endian_done
L_bigendian_check:
    subis r0, r3, 0x7856
    cmplwi r0, 0x3412
    bne L_result_true
    stw r31, 0x0(r5)
    b L_endian_done
L_result_true:
    mr r31, r6
L_endian_done:
    lis r3, msg_initnub@ha
    addi r4, r3, msg_initnub@l
    li r3, 0x1
    crclr 6
    bl MWTRACE
    cmpwi r31, 0x0
    bne L_skip_usrput
    bl usr_put_initialize
L_skip_usrput:
    cmpwi r31, 0x0
    bne L_skip_eventqueue
    bl TRKInitializeEventQueue
    mr r31, r3
L_skip_eventqueue:
    cmpwi r31, 0x0
    bne L_skip_msgbuf
    bl TRKInitializeMessageBuffers
    mr r31, r3
L_skip_msgbuf:
    cmpwi r31, 0x0
    bne L_skip_dispatcher
    bl TRKInitializeDispatcher
    mr r31, r3
L_skip_dispatcher:
    bl InitializeProgramEndTrap
    cmpwi r31, 0x0
    bne L_skip_serial
    bl TRKInitializeSerialHandler
    mr r31, r3
L_skip_serial:
    cmpwi r31, 0x0
    bne L_skip_target
    bl TRKInitializeTarget
    mr r31, r3
L_skip_target:
    cmpwi r31, 0x0
    bne L_done
    lis r3, gTRKInputPendingPtr@ha
    lis r5, 0x1
    addi r6, r3, gTRKInputPendingPtr@l
    li r4, 0x1
    subi r3, r5, 0x1f00
    li r5, 0x0
    bl TRKInitializeIntDrivenUART
    lis r4, gTRKInputPendingPtr@ha
    mr r0, r3
    addi r3, r4, gTRKInputPendingPtr@l
    lwz r3, 0x0(r3)
    mr r30, r0
    bl TRKTargetSetInputPendingPtr
    cmpwi r30, 0x0
    beq L_done
    mr r31, r30
L_done:
    lwz r0, 0x24(r1)
    mr r3, r31
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
