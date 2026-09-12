extern double lbl_80413F00[];

asm unsigned long __cvt_fp2unsigned(register double d)
{
    nofralloc
    stwu    r1,-16(r1)
    lis     r4, lbl_80413F00@ha
    ori     r4, r4, lbl_80413F00@l
    li      r3,0
    lfd     f0,0(r4)
    lfd     f3,8(r4)
    lfd     f4,16(r4)
    fcmpu   cr0,f1,f0
    fcmpu   cr6,f1,f3
    blt     cr0, exit1
    subi    r3,r3,1
    bge     cr6,exit1
    fcmpu   cr7,f1,f4
    fmr     f2,f1
    blt     cr7,L1
    fsub    f2,f1,f4
L1:
    fctiwz  f2,f2
    stfd    f2,8(r1)
    lwz     r3,12(r1)
    blt     cr7,exit1
    addis   r3,r3,0x8000
exit1:
    addi    r1,r1,16
    blr
}
