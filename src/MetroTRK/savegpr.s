.include "macros.inc"

.section .text, "ax"

.balign 4

.fn __save_fpr, global
.sym _savefpr_14, global
    stfd f14, -0x90(r11)
.endsym _savefpr_14
.sym _savefpr_15, global
    stfd f15, -0x88(r11)
.endsym _savefpr_15
.sym _savefpr_16, global
    stfd f16, -0x80(r11)
.endsym _savefpr_16
.sym _savefpr_17, global
    stfd f17, -0x78(r11)
.endsym _savefpr_17
.sym _savefpr_18, global
    stfd f18, -0x70(r11)
.endsym _savefpr_18
.sym _savefpr_19, global
    stfd f19, -0x68(r11)
.endsym _savefpr_19
.sym _savefpr_20, global
    stfd f20, -0x60(r11)
.endsym _savefpr_20
.sym _savefpr_21, global
    stfd f21, -0x58(r11)
.endsym _savefpr_21
.sym _savefpr_22, global
    stfd f22, -0x50(r11)
.endsym _savefpr_22
.sym _savefpr_23, global
    stfd f23, -0x48(r11)
.endsym _savefpr_23
.sym _savefpr_24, global
    stfd f24, -0x40(r11)
.endsym _savefpr_24
.sym _savefpr_25, global
    stfd f25, -0x38(r11)
.endsym _savefpr_25
.sym _savefpr_26, global
    stfd f26, -0x30(r11)
.endsym _savefpr_26
.sym _savefpr_27, global
    stfd f27, -0x28(r11)
.endsym _savefpr_27
.sym _savefpr_28, global
    stfd f28, -0x20(r11)
.endsym _savefpr_28
.sym _savefpr_29, global
    stfd f29, -0x18(r11)
.endsym _savefpr_29
.sym _savefpr_30, global
    stfd f30, -0x10(r11)
.endsym _savefpr_30
.sym _savefpr_31, global
    stfd f31, -0x8(r11)
.endsym _savefpr_31
    blr
.endfn __save_fpr

.fn __restore_fpr, global
.sym _restfpr_14, global
    lfd f14, -0x90(r11)
.endsym _restfpr_14
.sym _restfpr_15, global
    lfd f15, -0x88(r11)
.endsym _restfpr_15
.sym _restfpr_16, global
    lfd f16, -0x80(r11)
.endsym _restfpr_16
.sym _restfpr_17, global
    lfd f17, -0x78(r11)
.endsym _restfpr_17
.sym _restfpr_18, global
    lfd f18, -0x70(r11)
.endsym _restfpr_18
.sym _restfpr_19, global
    lfd f19, -0x68(r11)
.endsym _restfpr_19
.sym _restfpr_20, global
    lfd f20, -0x60(r11)
.endsym _restfpr_20
.sym _restfpr_21, global
    lfd f21, -0x58(r11)
.endsym _restfpr_21
.sym _restfpr_22, global
    lfd f22, -0x50(r11)
.endsym _restfpr_22
.sym _restfpr_23, global
    lfd f23, -0x48(r11)
.endsym _restfpr_23
.sym _restfpr_24, global
    lfd f24, -0x40(r11)
.endsym _restfpr_24
.sym _restfpr_25, global
    lfd f25, -0x38(r11)
.endsym _restfpr_25
.sym _restfpr_26, global
    lfd f26, -0x30(r11)
.endsym _restfpr_26
.sym _restfpr_27, global
    lfd f27, -0x28(r11)
.endsym _restfpr_27
.sym _restfpr_28, global
    lfd f28, -0x20(r11)
.endsym _restfpr_28
.sym _restfpr_29, global
    lfd f29, -0x18(r11)
.endsym _restfpr_29
.sym _restfpr_30, global
    lfd f30, -0x10(r11)
.endsym _restfpr_30
.sym _restfpr_31, global
    lfd f31, -0x8(r11)
.endsym _restfpr_31
    blr
.endfn __restore_fpr

.fn __save_gpr, global
.sym _savegpr_14, global
    stw r14, -0x48(r11)
.endsym _savegpr_14
.sym _savegpr_15, global
    stw r15, -0x44(r11)
.endsym _savegpr_15
.sym _savegpr_16, global
    stw r16, -0x40(r11)
.endsym _savegpr_16
.sym _savegpr_17, global
    stw r17, -0x3c(r11)
.endsym _savegpr_17
.sym _savegpr_18, global
    stw r18, -0x38(r11)
.endsym _savegpr_18
.sym _savegpr_19, global
    stw r19, -0x34(r11)
.endsym _savegpr_19
.sym _savegpr_20, global
    stw r20, -0x30(r11)
.endsym _savegpr_20
.sym _savegpr_21, global
    stw r21, -0x2c(r11)
.endsym _savegpr_21
.sym _savegpr_22, global
    stw r22, -0x28(r11)
.endsym _savegpr_22
.sym _savegpr_23, global
    stw r23, -0x24(r11)
.endsym _savegpr_23
.sym _savegpr_24, global
    stw r24, -0x20(r11)
.endsym _savegpr_24
.sym _savegpr_25, global
    stw r25, -0x1c(r11)
.endsym _savegpr_25
.sym _savegpr_26, global
    stw r26, -0x18(r11)
.endsym _savegpr_26
.sym _savegpr_27, global
    stw r27, -0x14(r11)
.endsym _savegpr_27
.sym _savegpr_28, global
    stw r28, -0x10(r11)
.endsym _savegpr_28
.sym _savegpr_29, global
    stw r29, -0xc(r11)
.endsym _savegpr_29
.sym _savegpr_30, global
    stw r30, -0x8(r11)
.endsym _savegpr_30
.sym _savegpr_31, global
    stw r31, -0x4(r11)
.endsym _savegpr_31
    blr
.endfn __save_gpr

.fn __restore_gpr, global
.sym _restgpr_14, global
    lwz r14, -0x48(r11)
.endsym _restgpr_14
.sym _restgpr_15, global
    lwz r15, -0x44(r11)
.endsym _restgpr_15
.sym _restgpr_16, global
    lwz r16, -0x40(r11)
.endsym _restgpr_16
.sym _restgpr_17, global
    lwz r17, -0x3c(r11)
.endsym _restgpr_17
.sym _restgpr_18, global
    lwz r18, -0x38(r11)
.endsym _restgpr_18
.sym _restgpr_19, global
    lwz r19, -0x34(r11)
.endsym _restgpr_19
.sym _restgpr_20, global
    lwz r20, -0x30(r11)
.endsym _restgpr_20
.sym _restgpr_21, global
    lwz r21, -0x2c(r11)
.endsym _restgpr_21
.sym _restgpr_22, global
    lwz r22, -0x28(r11)
.endsym _restgpr_22
.sym _restgpr_23, global
    lwz r23, -0x24(r11)
.endsym _restgpr_23
.sym _restgpr_24, global
    lwz r24, -0x20(r11)
.endsym _restgpr_24
.sym _restgpr_25, global
    lwz r25, -0x1c(r11)
.endsym _restgpr_25
.sym _restgpr_26, global
    lwz r26, -0x18(r11)
.endsym _restgpr_26
.sym _restgpr_27, global
    lwz r27, -0x14(r11)
.endsym _restgpr_27
.sym _restgpr_28, global
    lwz r28, -0x10(r11)
.endsym _restgpr_28
.sym _restgpr_29, global
    lwz r29, -0xc(r11)
.endsym _restgpr_29
.sym _restgpr_30, global
    lwz r30, -0x8(r11)
.endsym _restgpr_30
.sym _restgpr_31, global
    lwz r31, -0x4(r11)
.endsym _restgpr_31
    blr
.endfn __restore_gpr
