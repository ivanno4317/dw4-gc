#pragma ANSI_strict off
#pragma tvectors off
#pragma internal on
#define PPC_RT_ROUND_NEAREST 1
#pragma longlong on

#ifdef __cplusplus
extern "C" {
#endif

#if __PPC_EABI__
#define SAVE_FPR(reg) _savefpr_ ## reg
#define RESTORE_FPR(reg) _restfpr_ ## reg
#define SAVE_GPR(reg) _savegpr_ ## reg
#define RESTORE_GPR(reg) _restgpr_ ## reg
#define SAVE_VPR(reg) _savev ## reg
#define RESTORE_VPR(reg) _restv ## reg

#define ENTRY_SAVE_FPR(reg) entry SAVE_FPR(reg)
#define ENTRY_RESTORE_FPR(reg) entry RESTORE_FPR(reg)
#define ENTRY_SAVE_GPR(reg) entry SAVE_GPR(reg)
#define ENTRY_RESTORE_GPR(reg) entry RESTORE_GPR(reg)
#define ENTRY_SAVE_VPR(reg) entry SAVE_VPR(reg)
#define ENTRY_RESTORE_VPR(reg) entry RESTORE_VPR(reg)

#define SAVE_FPR2(reg) _savef ## reg
#define RESTORE_FPR2(reg) _restf ## reg
#define ENTRY_SAVE_FPR2(reg)
#define ENTRY_RESTORE_FPR2(reg)

#define SAVE_VPR2(reg) _savevr ## reg
#define RESTORE_VPR2(reg) _restvr ## reg
#define ENTRY_SAVE_VPR2(reg) entry SAVE_VPR2(reg)
#define ENTRY_RESTORE_VPR2(reg) entry RESTORE_VPR2(reg)

#else

#define SAVE_FPR(reg) __save_fpr_ ## reg
#define RESTORE_FPR(reg) __restore_fpr_ ## reg
#define ENTRY_SAVE_FPR(reg) entry SAVE_FPR(reg)
#define ENTRY_RESTORE_FPR(reg) entry RESTORE_FPR(reg)

#define SAVE_FPR2(reg) _savef ## reg
#define RESTORE_FPR2(reg) _restf ## reg
#define ENTRY_SAVE_FPR2(reg) entry SAVE_FPR2(reg)
#define ENTRY_RESTORE_FPR2(reg) entry RESTORE_FPR2(reg)

#define SAVE_VPR(reg) _savev ## reg
#define RESTORE_VPR(reg) _restv ## reg
#define ENTRY_SAVE_VPR(reg) entry SAVE_VPR(reg)
#define ENTRY_RESTORE_VPR(reg) entry RESTORE_VPR(reg)

#define SAVE_VPR2(reg) __savev ## reg
#define RESTORE_VPR2(reg) __restv ## reg
#define ENTRY_SAVE_VPR2(reg) entry SAVE_VPR2(reg)
#define ENTRY_RESTORE_VPR(reg) entry RESTORE_VPR2(reg)

#endif

unsigned long __cvt_fp2unsigned(double d);
unsigned long __uitrunc(double d);
void __ptr_glue(void);
void _ptrgl12(void);
void _ptrgl(void);
asm void _ptrglpas(void);
void SAVE_FPR(14)(void);
void SAVE_FPR(15)(void);
void SAVE_FPR(16)(void);
void SAVE_FPR(17)(void);
void SAVE_FPR(18)(void);
void SAVE_FPR(19)(void);
void SAVE_FPR(20)(void);
void SAVE_FPR(21)(void);
void SAVE_FPR(22)(void);
void SAVE_FPR(23)(void);
void SAVE_FPR(24)(void);
void SAVE_FPR(25)(void);
void SAVE_FPR(26)(void);
void SAVE_FPR(27)(void);
void SAVE_FPR(28)(void);
void SAVE_FPR(29)(void);
void SAVE_FPR(30)(void);
void SAVE_FPR(31)(void);
void SAVE_FPR2(14)(void);
void SAVE_FPR2(15)(void);
void SAVE_FPR2(16)(void);
void SAVE_FPR2(17)(void);
void SAVE_FPR2(18)(void);
void SAVE_FPR2(19)(void);
void SAVE_FPR2(20)(void);
void SAVE_FPR2(21)(void);
void SAVE_FPR2(22)(void);
void SAVE_FPR2(23)(void);
void SAVE_FPR2(24)(void);
void SAVE_FPR2(25)(void);
void SAVE_FPR2(26)(void);
void SAVE_FPR2(27)(void);
void SAVE_FPR2(28)(void);
void SAVE_FPR2(29)(void);
void SAVE_FPR2(30)(void);
void SAVE_FPR2(31)(void);
#if __ALTIVEC__
void SAVE_VPR(20)(void);
void SAVE_VPR(21)(void);
void SAVE_VPR(22)(void);
void SAVE_VPR(23)(void);
void SAVE_VPR(24)(void);
void SAVE_VPR(25)(void);
void SAVE_VPR(26)(void);
void SAVE_VPR(27)(void);
void SAVE_VPR(28)(void);
void SAVE_VPR(29)(void);
void SAVE_VPR(30)(void);
void SAVE_VPR(31)(void);
void SAVE_VPR2(20)(void);
void SAVE_VPR2(21)(void);
void SAVE_VPR2(22)(void);
void SAVE_VPR2(23)(void);
void SAVE_VPR2(24)(void);
void SAVE_VPR2(25)(void);
void SAVE_VPR2(26)(void);
void SAVE_VPR2(27)(void);
void SAVE_VPR2(28)(void);
void SAVE_VPR2(29)(void);
void SAVE_VPR2(30)(void);
void SAVE_VPR2(31)(void);
#endif
void RESTORE_FPR(14)(void);
void RESTORE_FPR(15)(void);
void RESTORE_FPR(16)(void);
void RESTORE_FPR(17)(void);
void RESTORE_FPR(18)(void);
void RESTORE_FPR(19)(void);
void RESTORE_FPR(20)(void);
void RESTORE_FPR(21)(void);
void RESTORE_FPR(22)(void);
void RESTORE_FPR(23)(void);
void RESTORE_FPR(24)(void);
void RESTORE_FPR(25)(void);
void RESTORE_FPR(26)(void);
void RESTORE_FPR(27)(void);
void RESTORE_FPR(28)(void);
void RESTORE_FPR(29)(void);
void RESTORE_FPR(30)(void);
void RESTORE_FPR(31)(void);
void RESTORE_FPR2(14)(void);
void RESTORE_FPR2(15)(void);
void RESTORE_FPR2(16)(void);
void RESTORE_FPR2(17)(void);
void RESTORE_FPR2(18)(void);
void RESTORE_FPR2(19)(void);
void RESTORE_FPR2(20)(void);
void RESTORE_FPR2(21)(void);
void RESTORE_FPR2(22)(void);
void RESTORE_FPR2(23)(void);
void RESTORE_FPR2(24)(void);
void RESTORE_FPR2(25)(void);
void RESTORE_FPR2(26)(void);
void RESTORE_FPR2(27)(void);
void RESTORE_FPR2(28)(void);
void RESTORE_FPR2(29)(void);
void RESTORE_FPR2(30)(void);
void RESTORE_FPR2(31)(void);
#if __ALTIVEC__
void RESTORE_VPR(20)(void);
void RESTORE_VPR(21)(void);
void RESTORE_VPR(22)(void);
void RESTORE_VPR(23)(void);
void RESTORE_VPR(24)(void);
void RESTORE_VPR(25)(void);
void RESTORE_VPR(26)(void);
void RESTORE_VPR(27)(void);
void RESTORE_VPR(28)(void);
void RESTORE_VPR(29)(void);
void RESTORE_VPR(30)(void);
void RESTORE_VPR(31)(void);
void RESTORE_VPR2(20)(void);
void RESTORE_VPR2(21)(void);
void RESTORE_VPR2(22)(void);
void RESTORE_VPR2(23)(void);
void RESTORE_VPR2(24)(void);
void RESTORE_VPR2(25)(void);
void RESTORE_VPR2(26)(void);
void RESTORE_VPR2(27)(void);
void RESTORE_VPR2(28)(void);
void RESTORE_VPR2(29)(void);
void RESTORE_VPR2(30)(void);
void RESTORE_VPR2(31)(void);
#endif
#if __PPC_EABI__
void SAVE_GPR(14)(void);
void SAVE_GPR(15)(void);
void SAVE_GPR(16)(void);
void SAVE_GPR(17)(void);
void SAVE_GPR(18)(void);
void SAVE_GPR(19)(void);
void SAVE_GPR(20)(void);
void SAVE_GPR(21)(void);
void SAVE_GPR(22)(void);
void SAVE_GPR(23)(void);
void SAVE_GPR(24)(void);
void SAVE_GPR(25)(void);
void SAVE_GPR(26)(void);
void SAVE_GPR(27)(void);
void SAVE_GPR(28)(void);
void SAVE_GPR(29)(void);
void SAVE_GPR(30)(void);
void SAVE_GPR(31)(void);
void RESTORE_GPR(14)(void);
void RESTORE_GPR(15)(void);
void RESTORE_GPR(16)(void);
void RESTORE_GPR(17)(void);
void RESTORE_GPR(18)(void);
void RESTORE_GPR(19)(void);
void RESTORE_GPR(20)(void);
void RESTORE_GPR(21)(void);
void RESTORE_GPR(22)(void);
void RESTORE_GPR(23)(void);
void RESTORE_GPR(24)(void);
void RESTORE_GPR(25)(void);
void RESTORE_GPR(26)(void);
void RESTORE_GPR(27)(void);
void RESTORE_GPR(28)(void);
void RESTORE_GPR(29)(void);
void RESTORE_GPR(30)(void);
void RESTORE_GPR(31)(void);
#endif
asm void __div2u(void);
asm void __div2i(void);
asm void __mod2u(void);
asm void __mod2i(void);
asm void __shl2i(void);
asm void __shr2u(void);
asm void __shr2i(void);
asm void __cvt_sll_dbl(void);
asm void __cvt_ull_dbl(void);
asm void __cvt_sll_flt(void);
asm void __cvt_ull_flt(void);
asm void __cvt_dbl_usll(void);

#ifdef __cplusplus
}
#endif

#if __PPC_EABI__
#define hilong				8
#define lolong				12
#define storedouble			hilong
#if !__option (little_endian)
#define getloword			lolong
#else
#define getloword			hilong
#endif
#define save_restore_reg	r11
#else
#define hilong				24
#define lolong				28
#define storedouble			-8
#if !__option (little_endian)
#define getloword			-4
#else
#define getloword			-8
#endif
#define save_restore_reg	SP
#endif

#ifndef _No_Floating_Point_Regs

static const unsigned long long __constants[] = {
		0x0000000000000000,
		0x41F0000000000000,
		0x41E0000000000000,
};

asm unsigned long __cvt_fp2unsigned(register double d)
{
#if __PPC_EABI__
		nofralloc
	    stwu    SP,-16(SP)
		lis		r4, __constants@h
		ori		r4, r4, __constants@l
#else
		entry	__uitrunc
		lwz		r4,__constants(RTOC)
#endif
		li		r3,0
		lfd		fp0,0(r4)
		lfd		fp3,8(r4)
		lfd		fp4,16(r4)
		fcmpu	cr0,fp1,fp0
		fcmpu	cr6,fp1,fp3
#if __PPC_EABI__
		blt		cr0, @fall_through
#else
		bltlr	cr0
#endif
		addi	r3,r3,-1
#if __PPC_EABI__
		bge		cr6,@fall_through
#else
		bgelr	cr6
#endif
		fcmpu	cr7,fp1,fp4
		fmr		fp2,fp1
		blt		cr7,@1
		fsub	fp2,fp1,fp4
@1		fctiwz	fp2,fp2
		stfd	fp2,storedouble(SP)
		lwz		r3,getloword(SP)
#if __PPC_EABI__
		blt		cr7,@fall_through
#else
		bltlr	cr7
#endif
		addis	r3,r3,-32768
#if __PPC_EABI__
@fall_through:
		addi    SP,SP,16
#endif
		blr
}
#endif

#if !__PPC_EABI__

asm void __ptr_glue(void)
{
		smclass	GL
		lwz		r0,0(r12)
		stw		RTOC,20(SP)
		mtctr	r0
		lwz		RTOC,4(r12)
		bctr
}

asm void _ptrgl12(void)
{
		smclass	GL
		lwz		r0,0(r12)
		stw		RTOC,20(SP)
		mtctr	r0
		lwz		RTOC,4(r12)
		bctr
}

asm void _ptrgl(void)
{
		smclass	GL
		lwz		r0,0(r11)
		stw		RTOC,20(SP)
		mtctr	r0
		lwz		RTOC,4(r11)
		mr		r12,r11
		bctr
}

asm void _ptrglpas(void)
{
		smclass	GL
		lwz		r0,0(r11)
		stw		RTOC,20(SP)
		mtctr	r0
		lwz		RTOC,4(r11)
		lwz		r11,8(r11)
		bctr
}

#endif

#ifndef _No_Floating_Point_Regs

static asm void __save_fpr(void)
{
#if __PPC_EABI__
	nofralloc
#endif
	ENTRY_SAVE_FPR(14)
	ENTRY_SAVE_FPR2(14)
		stfd	fp14,-144(save_restore_reg)
	ENTRY_SAVE_FPR(15)
	ENTRY_SAVE_FPR2(15)
		stfd	fp15,-136(save_restore_reg)
	ENTRY_SAVE_FPR(16)
	ENTRY_SAVE_FPR2(16)
		stfd	fp16,-128(save_restore_reg)
	ENTRY_SAVE_FPR(17)
	ENTRY_SAVE_FPR2(17)
		stfd	fp17,-120(save_restore_reg)
	ENTRY_SAVE_FPR(18)
	ENTRY_SAVE_FPR2(18)
		stfd	fp18,-112(save_restore_reg)
	ENTRY_SAVE_FPR(19)
	ENTRY_SAVE_FPR2(19)
		stfd	fp19,-104(save_restore_reg)
	ENTRY_SAVE_FPR(20)
	ENTRY_SAVE_FPR2(20)
		stfd	fp20,-96(save_restore_reg)
	ENTRY_SAVE_FPR(21)
	ENTRY_SAVE_FPR2(21)
		stfd	fp21,-88(save_restore_reg)
	ENTRY_SAVE_FPR(22)
	ENTRY_SAVE_FPR2(22)
		stfd	fp22,-80(save_restore_reg)
	ENTRY_SAVE_FPR(23)
	ENTRY_SAVE_FPR2(23)
		stfd	fp23,-72(save_restore_reg)
	ENTRY_SAVE_FPR(24)
	ENTRY_SAVE_FPR2(24)
		stfd	fp24,-64(save_restore_reg)
	ENTRY_SAVE_FPR(25)
	ENTRY_SAVE_FPR2(25)
		stfd	fp25,-56(save_restore_reg)
	ENTRY_SAVE_FPR(26)
	ENTRY_SAVE_FPR2(26)
		stfd	fp26,-48(save_restore_reg)
	ENTRY_SAVE_FPR(27)
	ENTRY_SAVE_FPR2(27)
		stfd	fp27,-40(save_restore_reg)
	ENTRY_SAVE_FPR(28)
	ENTRY_SAVE_FPR2(28)
		stfd	fp28,-32(save_restore_reg)
	ENTRY_SAVE_FPR(29)
	ENTRY_SAVE_FPR2(29)
		stfd	fp29,-24(save_restore_reg)
	ENTRY_SAVE_FPR(30)
	ENTRY_SAVE_FPR2(30)
		stfd	fp30,-16(save_restore_reg)
	ENTRY_SAVE_FPR(31)
	ENTRY_SAVE_FPR2(31)
		stfd	fp31,-8(save_restore_reg)
		blr
}

static asm void __restore_fpr(void)
{
#if __PPC_EABI__
	nofralloc
#endif
	ENTRY_RESTORE_FPR(14)
	ENTRY_RESTORE_FPR2(14)
		lfd		fp14,-144(save_restore_reg)
	ENTRY_RESTORE_FPR(15)
	ENTRY_RESTORE_FPR2(15)
		lfd		fp15,-136(save_restore_reg)
	ENTRY_RESTORE_FPR(16)
	ENTRY_RESTORE_FPR2(16)
		lfd		fp16,-128(save_restore_reg)
	ENTRY_RESTORE_FPR(17)
	ENTRY_RESTORE_FPR2(17)
		lfd		fp17,-120(save_restore_reg)
	ENTRY_RESTORE_FPR(18)
	ENTRY_RESTORE_FPR2(18)
		lfd		fp18,-112(save_restore_reg)
	ENTRY_RESTORE_FPR(19)
	ENTRY_RESTORE_FPR2(19)
		lfd		fp19,-104(save_restore_reg)
	ENTRY_RESTORE_FPR(20)
	ENTRY_RESTORE_FPR2(20)
		lfd		fp20,-96(save_restore_reg)
	ENTRY_RESTORE_FPR(21)
	ENTRY_RESTORE_FPR2(21)
		lfd		fp21,-88(save_restore_reg)
	ENTRY_RESTORE_FPR(22)
	ENTRY_RESTORE_FPR2(22)
		lfd		fp22,-80(save_restore_reg)
	ENTRY_RESTORE_FPR(23)
	ENTRY_RESTORE_FPR2(23)
		lfd		fp23,-72(save_restore_reg)
	ENTRY_RESTORE_FPR(24)
	ENTRY_RESTORE_FPR2(24)
		lfd		fp24,-64(save_restore_reg)
	ENTRY_RESTORE_FPR(25)
	ENTRY_RESTORE_FPR2(25)
		lfd		fp25,-56(save_restore_reg)
	ENTRY_RESTORE_FPR(26)
	ENTRY_RESTORE_FPR2(26)
		lfd		fp26,-48(save_restore_reg)
	ENTRY_RESTORE_FPR(27)
	ENTRY_RESTORE_FPR2(27)
		lfd		fp27,-40(save_restore_reg)
	ENTRY_RESTORE_FPR(28)
	ENTRY_RESTORE_FPR2(28)
		lfd		fp28,-32(save_restore_reg)
	ENTRY_RESTORE_FPR(29)
	ENTRY_RESTORE_FPR2(29)
		lfd		fp29,-24(save_restore_reg)
	ENTRY_RESTORE_FPR(30)
	ENTRY_RESTORE_FPR2(30)
		lfd		fp30,-16(save_restore_reg)
	ENTRY_RESTORE_FPR(31)
	ENTRY_RESTORE_FPR2(31)
		lfd		fp31,-8(save_restore_reg)
		blr
}
#endif

#if __PPC_EABI__

static asm void __save_gpr(void)
{
#if __PPC_EABI__
	nofralloc
#endif
	ENTRY_SAVE_GPR(14)
		stw		r14,-72(save_restore_reg)
	ENTRY_SAVE_GPR(15)
		stw		r15,-68(save_restore_reg)
	ENTRY_SAVE_GPR(16)
		stw		r16,-64(save_restore_reg)
	ENTRY_SAVE_GPR(17)
		stw		r17,-60(save_restore_reg)
	ENTRY_SAVE_GPR(18)
		stw		r18,-56(save_restore_reg)
	ENTRY_SAVE_GPR(19)
		stw		r19,-52(save_restore_reg)
	ENTRY_SAVE_GPR(20)
		stw		r20,-48(save_restore_reg)
	ENTRY_SAVE_GPR(21)
		stw		r21,-44(save_restore_reg)
	ENTRY_SAVE_GPR(22)
		stw		r22,-40(save_restore_reg)
	ENTRY_SAVE_GPR(23)
		stw		r23,-36(save_restore_reg)
	ENTRY_SAVE_GPR(24)
		stw		r24,-32(save_restore_reg)
	ENTRY_SAVE_GPR(25)
		stw		r25,-28(save_restore_reg)
	ENTRY_SAVE_GPR(26)
		stw		r26,-24(save_restore_reg)
	ENTRY_SAVE_GPR(27)
		stw		r27,-20(save_restore_reg)
	ENTRY_SAVE_GPR(28)
		stw		r28,-16(save_restore_reg)
	ENTRY_SAVE_GPR(29)
		stw		r29,-12(save_restore_reg)
	ENTRY_SAVE_GPR(30)
		stw		r30,-8(save_restore_reg)
	ENTRY_SAVE_GPR(31)
		stw		r31,-4(save_restore_reg)
		blr
}

static asm void __restore_gpr(void)
{
#if __PPC_EABI__
	nofralloc
#endif
	ENTRY_RESTORE_GPR(14)
		lwz		r14,-72(save_restore_reg)
	ENTRY_RESTORE_GPR(15)
		lwz		r15,-68(save_restore_reg)
	ENTRY_RESTORE_GPR(16)
		lwz		r16,-64(save_restore_reg)
	ENTRY_RESTORE_GPR(17)
		lwz		r17,-60(save_restore_reg)
	ENTRY_RESTORE_GPR(18)
		lwz		r18,-56(save_restore_reg)
	ENTRY_RESTORE_GPR(19)
		lwz		r19,-52(save_restore_reg)
	ENTRY_RESTORE_GPR(20)
		lwz		r20,-48(save_restore_reg)
	ENTRY_RESTORE_GPR(21)
		lwz		r21,-44(save_restore_reg)
	ENTRY_RESTORE_GPR(22)
		lwz		r22,-40(save_restore_reg)
	ENTRY_RESTORE_GPR(23)
		lwz		r23,-36(save_restore_reg)
	ENTRY_RESTORE_GPR(24)
		lwz		r24,-32(save_restore_reg)
	ENTRY_RESTORE_GPR(25)
		lwz		r25,-28(save_restore_reg)
	ENTRY_RESTORE_GPR(26)
		lwz		r26,-24(save_restore_reg)
	ENTRY_RESTORE_GPR(27)
		lwz		r27,-20(save_restore_reg)
	ENTRY_RESTORE_GPR(28)
		lwz		r28,-16(save_restore_reg)
	ENTRY_RESTORE_GPR(29)
		lwz		r29,-12(save_restore_reg)
	ENTRY_RESTORE_GPR(30)
		lwz		r30,-8(save_restore_reg)
	ENTRY_RESTORE_GPR(31)
		lwz		r31,-4(save_restore_reg)
		blr
}

#endif

#if __option(little_endian)
#define MSW(x,y) y
#define LSW(x,y) x
#else
#define MSW(x,y) x
#define LSW(x,y) y
#endif

asm void __div2u(void)
{
#if __PPC_EABI__
	   nofralloc
#endif
       cmpwi	cr0,MSW(r3,r4),0
       cntlzw	r0,MSW(r3,r4)
       cntlzw	r9,LSW(r3,r4)
       bne		cr0,lab1
       addi		r0,r9,32
 lab1: 
       cmpwi	cr0,MSW(r5,r6),0
       cntlzw	r9,MSW(r5,r6)
       cntlzw	r10,LSW(r5,r6)
       bne		cr0,lab2
       addi		r9,r10,32
 lab2: 
       cmpw		cr0,r0,r9
       subfic	r10,r0,64
       bgt		cr0,lab9
       addi		r9,r9,1
       subfic	r9,r9,64
       add		r0,r0,r9
       subf		r9,r9,r10
       mtctr	r9

       cmpwi	cr0,r9,32
       addi		MSW(r7,r8),r9,-32 
       blt		cr0,lab3
       srw		LSW(r7,r8),MSW(r3,r4),MSW(r7,r8)
       li		MSW(r7,r8),0
       b		lab4 
 lab3: 
       srw		LSW(r7,r8),LSW(r3,r4),r9
       subfic	MSW(r7,r8),r9,32 
       slw		MSW(r7,r8),MSW(r3,r4),MSW(r7,r8)
       or		LSW(r7,r8),LSW(r7,r8),MSW(r7,r8)
       srw		MSW(r7,r8),MSW(r3,r4),r9
 lab4: 
       cmpwi	cr0,r0,32
       addic	r9,r0,-32 
       blt		cr0,lab5
       slw		MSW(r3,r4),LSW(r3,r4),r9
       li		LSW(r3,r4),0
       b		lab6 
 lab5: 
       slw		MSW(r3,r4),MSW(r3,r4),r0
       subfic	r9,r0,32 
       srw		r9,LSW(r3,r4),r9
       or		MSW(r3,r4),MSW(r3,r4),r9
       slw		LSW(r3,r4),LSW(r3,r4),r0
 lab6: 
       li		r10,-1
       addic	MSW(r7,r8),MSW(r7,r8),0
 lab7: 
       adde		LSW(r3,r4),LSW(r3,r4),LSW(r3,r4)
       adde		MSW(r3,r4),MSW(r3,r4),MSW(r3,r4)
       adde		LSW(r7,r8),LSW(r7,r8),LSW(r7,r8)
       adde		MSW(r7,r8),MSW(r7,r8),MSW(r7,r8)
       subfc	r0,LSW(r5,r6),LSW(r7,r8)
       subfe.	r9,MSW(r5,r6),MSW(r7,r8)
       blt		cr0,lab8
       mr		LSW(r7,r8),r0
       mr		MSW(r7,r8),r9
       addic	r0,r10,1
 lab8: 
       bdnz		lab7

       adde		LSW(r3,r4),LSW(r3,r4),LSW(r3,r4)
       adde		MSW(r3,r4),MSW(r3,r4),MSW(r3,r4)
       blr
 lab9: 
       li		LSW(r3,r4),0
       li		MSW(r3,r4),0
       blr
}

asm void __div2i(void)
{
#if __PPC_EABI__
	   nofralloc
	   stwu     SP,-16(SP)
#endif
       rlwinm.  MSW(r9,r10),MSW(r3,r4),0,0,0
       beq      cr0,positive1
       subfic   LSW(r3,r4),LSW(r3,r4),0
       subfze   MSW(r3,r4),MSW(r3,r4)
positive1:
       stw      MSW(r9,r10),hilong(r1)
       rlwinm.  LSW(r9,r10),MSW(r5,r6),0,0,0
       beq      cr0,positive2
       subfic   LSW(r5,r6),LSW(r5,r6),0
       subfze   MSW(r5,r6),MSW(r5,r6)
positive2:
       stw      LSW(r9,r10),lolong(r1)

       cmpwi	cr0,MSW(r3,r4),0
       cntlzw	r0,MSW(r3,r4)
       cntlzw	r9,LSW(r3,r4)
       bne		cr0,lab1
       addi		r0,r9,32
 lab1: 
       cmpwi	cr0,MSW(r5,r6),0
       cntlzw	r9,MSW(r5,r6)
       cntlzw	r10,LSW(r5,r6)
       bne		cr0,lab2
       addi		r9,r10,32
 lab2: 
       cmpw		cr0,r0,r9
       subfic	r10,r0,64
       bgt		cr0,lab9
       addi		r9,r9,1
       subfic	r9,r9,64
       add		r0,r0,r9
       subf		r9,r9,r10
       mtctr	r9

       cmpwi	cr0,r9,32
       addi		MSW(r7,r8),r9,-32 
       blt		cr0,lab3
       srw		LSW(r7,r8),MSW(r3,r4),MSW(r7,r8)
       li		MSW(r7,r8),0
       b		lab4 
 lab3: 
       srw		LSW(r7,r8),LSW(r3,r4),r9
       subfic	MSW(r7,r8),r9,32 
       slw		MSW(r7,r8),MSW(r3,r4),MSW(r7,r8)
       or		LSW(r7,r8),LSW(r7,r8),MSW(r7,r8)
       srw		MSW(r7,r8),MSW(r3,r4),r9
 lab4: 
       cmpwi	cr0,r0,32
       addic	r9,r0,-32 
       blt		cr0,lab5
       slw		MSW(r3,r4),LSW(r3,r4),r9
       li		LSW(r3,r4),0
       b		lab6 
 lab5: 
       slw		MSW(r3,r4),MSW(r3,r4),r0
       subfic	r9,r0,32 
       srw		r9,LSW(r3,r4),r9
       or		MSW(r3,r4),MSW(r3,r4),r9
       slw		LSW(r3,r4),LSW(r3,r4),r0
 lab6: 
       li		r10,-1
       addic	MSW(r7,r8),MSW(r7,r8),0
 lab7: 
       adde		LSW(r3,r4),LSW(r3,r4),LSW(r3,r4)
       adde		MSW(r3,r4),MSW(r3,r4),MSW(r3,r4)
       adde		LSW(r7,r8),LSW(r7,r8),LSW(r7,r8)
       adde		MSW(r7,r8),MSW(r7,r8),MSW(r7,r8)
       subfc	r0,LSW(r5,r6),LSW(r7,r8)
       subfe.	r9,MSW(r5,r6),MSW(r7,r8)
       blt		cr0,lab8
       mr		LSW(r7,r8),r0
       mr		MSW(r7,r8),r9
       addic	r0,r10,1
 lab8: 
       bdnz		lab7

       adde		LSW(r3,r4),LSW(r3,r4),LSW(r3,r4)
       adde		MSW(r3,r4),MSW(r3,r4),MSW(r3,r4)

       lwz		MSW(r9,r10),hilong(r1)
       lwz		LSW(r9,r10),lolong(r1)
       xor.		r7,MSW(r9,r10),LSW(r9,r10)
       beq		cr0,no_adjust
       cmpwi	cr0,MSW(r9,r10),0		
       subfic   LSW(r3,r4),LSW(r3,r4),0
       subfze   MSW(r3,r4),MSW(r3,r4)       
 no_adjust:
#if __PPC_EABI__
       b		func_end 
#else
       blr
#endif

 lab9: 
       li		LSW(r3,r4),0
       li		MSW(r3,r4),0
#if __PPC_EABI__
 func_end: 
	   addi     SP,SP,16
#endif
       blr
}

asm void __mod2u(void)
{
#if __PPC_EABI__
	   nofralloc
#endif
       cmpwi	cr0,MSW(r3,r4),0
       cntlzw	r0,MSW(r3,r4)
       cntlzw	r9,LSW(r3,r4)
       bne		cr0,lab1
       addi		r0,r9,32
 lab1: 
       cmpwi	cr0,MSW(r5,r6),0
       cntlzw	r9,MSW(r5,r6)
       cntlzw	r10,LSW(r5,r6)
       bne		cr0,lab2
       addi		r9,r10,32
 lab2: 
       cmpw		cr0,r0,r9
       subfic	r10,r0,64
       bgt		cr0,lab9
       addi		r9,r9,1
       subfic	r9,r9,64
       add		r0,r0,r9
       subf		r9,r9,r10
       mtctr	r9

       cmpwi	cr0,r9,32
       addi		MSW(r7,r8),r9,-32 
       blt		cr0,lab3
       srw		LSW(r7,r8),MSW(r3,r4),MSW(r7,r8)
       li		MSW(r7,r8),0
       b		lab4 
 lab3: 
       srw		LSW(r7,r8),LSW(r3,r4),r9
       subfic	MSW(r7,r8),r9,32 
       slw		MSW(r7,r8),MSW(r3,r4),MSW(r7,r8)
       or		LSW(r7,r8),LSW(r7,r8),MSW(r7,r8)
       srw		MSW(r7,r8),MSW(r3,r4),r9
 lab4: 
       cmpwi	cr0,r0,32
       addic	r9,r0,-32 
       blt		cr0,lab5
       slw		MSW(r3,r4),LSW(r3,r4),r9
       li		LSW(r3,r4),0
       b		lab6 
 lab5: 
       slw		MSW(r3,r4),MSW(r3,r4),r0
       subfic	r9,r0,32 
       srw		r9,LSW(r3,r4),r9
       or		MSW(r3,r4),MSW(r3,r4),r9
       slw		LSW(r3,r4),LSW(r3,r4),r0
 lab6: 
       li		r10,-1
       addic	MSW(r7,r8),MSW(r7,r8),0
 lab7: 
       adde		LSW(r3,r4),LSW(r3,r4),LSW(r3,r4)
       adde		MSW(r3,r4),MSW(r3,r4),MSW(r3,r4)
       adde		LSW(r7,r8),LSW(r7,r8),LSW(r7,r8)
       adde		MSW(r7,r8),MSW(r7,r8),MSW(r7,r8)
       subfc	r0,LSW(r5,r6),LSW(r7,r8)
       subfe.	r9,MSW(r5,r6),MSW(r7,r8)
       blt		cr0,lab8
       mr		LSW(r7,r8),r0
       mr		MSW(r7,r8),r9
       addic	r0,r10,1
 lab8: 
       bdnz		lab7

       mr		LSW(r3,r4),LSW(r7,r8)
       mr		MSW(r3,r4),MSW(r7,r8)
       blr
 lab9: 
      blr
}

asm void __mod2i(void)
{
#if __PPC_EABI__
	   nofralloc
#endif
       cmpwi	cr7,MSW(r3,r4),0
       bge	cr7,positive1
       subfic   LSW(r3,r4),LSW(r3,r4),0
       subfze   MSW(r3,r4),MSW(r3,r4)
positive1:
       cmpwi	cr0,MSW(r5,r6),0
       bge      cr0,positive2
       subfic   LSW(r5,r6),LSW(r5,r6),0
       subfze   MSW(r5,r6),MSW(r5,r6)
positive2:

       cmpwi	cr0,MSW(r3,r4),0
       cntlzw	r0,MSW(r3,r4)
       cntlzw	r9,LSW(r3,r4)
       bne	cr0,lab1
       addi	r0,r9,32
 lab1:
       cmpwi	cr0,MSW(r5,r6),0
       cntlzw	r9,MSW(r5,r6)
       cntlzw	r10,LSW(r5,r6)
       bne	cr0,lab2
       addi	r9,r10,32
 lab2:
       cmpw	cr0,r0,r9
       subfic	r10,r0,64
       bgt	cr0,lab9
       addi	r9,r9,1
       subfic	r9,r9,64
       add	r0,r0,r9
       subf	r9,r9,r10
       mtctr	r9

       cmpwi	cr0,r9,32
       addi	MSW(r7,r8),r9,-32
       blt	cr0,lab3
       srw	LSW(r7,r8),MSW(r3,r4),MSW(r7,r8)
       li	MSW(r7,r8),0
       b	lab4
 lab3:
       srw	LSW(r7,r8),LSW(r3,r4),r9
       subfic	MSW(r7,r8),r9,32
       slw	MSW(r7,r8),MSW(r3,r4),MSW(r7,r8)
       or	LSW(r7,r8),LSW(r7,r8),MSW(r7,r8)
       srw	MSW(r7,r8),MSW(r3,r4),r9
 lab4:
       cmpwi	cr0,r0,32
       addic	r9,r0,-32
       blt	cr0,lab5
       slw	MSW(r3,r4),LSW(r3,r4),r9
       li	LSW(r3,r4),0
       b	lab6
 lab5:
       slw	MSW(r3,r4),MSW(r3,r4),r0
       subfic	r9,r0,32
       srw	r9,LSW(r3,r4),r9
       or	MSW(r3,r4),MSW(r3,r4),r9
       slw	LSW(r3,r4),LSW(r3,r4),r0
 lab6:
       li	r10,-1
       addic	MSW(r7,r8),MSW(r7,r8),0
 lab7:
       adde	LSW(r3,r4),LSW(r3,r4),LSW(r3,r4)
       adde	MSW(r3,r4),MSW(r3,r4),MSW(r3,r4)
       adde	LSW(r7,r8),LSW(r7,r8),LSW(r7,r8)
       adde	MSW(r7,r8),MSW(r7,r8),MSW(r7,r8)
       subfc	r0,LSW(r5,r6),LSW(r7,r8)
       subfe.	r9,MSW(r5,r6),MSW(r7,r8)
       blt	cr0,lab8
       mr	LSW(r7,r8),r0
       mr	MSW(r7,r8),r9
       addic	r0,r10,1
 lab8:
       bdnz	lab7

       mr	LSW(r3,r4),LSW(r7,r8)
       mr	MSW(r3,r4),MSW(r7,r8)

 lab9:
       bge	cr7,no_adjust
       subfic   LSW(r3,r4),LSW(r3,r4),0
       subfze   MSW(r3,r4),MSW(r3,r4)
 no_adjust:
      blr
}

asm void __shl2i(void)
{
#if __PPC_EABI__
	nofralloc
#endif
	subfic	r8,r5,32
	subic	r9,r5,32
	slw		MSW(r3,r4),MSW(r3,r4),r5
	srw		r10,LSW(r3,r4),r8
	or		MSW(r3,r4),MSW(r3,r4),r10
	slw		r10,LSW(r3,r4),r9
	or		MSW(r3,r4),MSW(r3,r4),r10
	slw		LSW(r3,r4),LSW(r3,r4),r5
	blr
}

asm void __shr2u(void)
{
#if __PPC_EABI__
	nofralloc
#endif
	subfic	r8,r5,32
	subic	r9,r5,32
	srw		LSW(r3,r4),LSW(r3,r4),r5
	slw		r10,MSW(r3,r4),r8
	or		LSW(r3,r4),LSW(r3,r4),r10
	srw		r10,MSW(r3,r4),r9
	or		LSW(r3,r4),LSW(r3,r4),r10
	srw		MSW(r3,r4),MSW(r3,r4),r5
	blr
}

asm void __shr2i(void)
{
#if __PPC_EABI__
	nofralloc
#endif
	subfic	r8,r5,32
	subic.	r9,r5,32
	srw		LSW(r3,r4),LSW(r3,r4),r5
	slw		r10,MSW(r3,r4),r8
	or		LSW(r3,r4),LSW(r3,r4),r10
	sraw	r10,MSW(r3,r4),r9
	ble		around
	or		LSW(r3,r4),LSW(r3,r4),r10
around:
	sraw	MSW(r3,r4),MSW(r3,r4),r5
	blr	
}

#ifndef _No_Floating_Point_Regs

asm void __cvt_sll_dbl(void)
{
#if __PPC_EABI__
	nofralloc
	stwu    SP,-16(SP)
#endif

  	rlwinm.	r5,MSW(r3,r4),0,0,0
	beq		cr0,positive
	subfic	LSW(r3,r4),LSW(r3,r4),0
	subfze	MSW(r3,r4),MSW(r3,r4)
positive:
	or.		r7,MSW(r3,r4),LSW(r3,r4)
	li		r6,0
	beq		cr0,zero
	cntlzw	r7,MSW(r3,r4)
	cntlzw	r8,LSW(r3,r4)
	rlwinm	r9,r7,26,0,4
	srawi	r9,r9,31
	and		r9,r9,r8
	add		r7,r7,r9
	subfic	r8,r7,32
	subic	r9,r7,32
	slw		MSW(r3,r4),MSW(r3,r4),r7
	srw		r10,LSW(r3,r4),r8
	or		MSW(r3,r4),MSW(r3,r4),r10
	slw		r10,LSW(r3,r4),r9
	or		MSW(r3,r4),MSW(r3,r4),r10
	slw		LSW(r3,r4),LSW(r3,r4),r7
	sub		r6,r6,r7
#if PPC_RT_ROUND_NEAREST
	rlwinm	r7,LSW(r3,r4),0,21,31
	cmpi	cr0,r7,0x400
	addi	r6,r6,1086
	blt		noround
	bgt		round
	rlwinm.	r7,LSW(r3,r4),0,20,20
	beq		noround
round:
	addic	LSW(r3,r4),LSW(r3,r4),0x0800
	addze	MSW(r3,r4),MSW(r3,r4)
	addze	r6,r6
noround:
#else
	addi	r6,r6,1086
#endif
	rlwinm	LSW(r3,r4),LSW(r3,r4),21,0,31
	rlwimi	LSW(r3,r4),MSW(r3,r4),21,0,10
	rlwinm	MSW(r3,r4),MSW(r3,r4),21,12,31
	rlwinm	r6,r6,20,0,11
	or		MSW(r3,r4),r6,MSW(r3,r4)
	or		MSW(r3,r4),r5,MSW(r3,r4)
zero:
#if !__option (little_endian)
	stw		MSW(r3,r4),hilong(r1)
	stw		LSW(r3,r4),lolong(r1)
#else
	stw		LSW(r3,r4),hilong(r1)
	stw		MSW(r3,r4),lolong(r1)
#endif
	lfd		f1,hilong(r1)
#if __PPC_EABI__
	addi    SP,SP,16
#endif
	blr 
}

asm void __cvt_ull_dbl(void)
{
#if __PPC_EABI__
	nofralloc
	stwu    SP,-16(SP)
#endif

	or.		r7,MSW(r3,r4),LSW(r3,r4)
	li		r6,0
	beq		cr0,zero
	cntlzw	r7,MSW(r3,r4)
	cntlzw	r8,LSW(r3,r4)
	rlwinm	r9,r7,26,0,4
	srawi	r9,r9,31
	and		r9,r9,r8
	add		r7,r7,r9
	subfic	r8,r7,32
	subic	r9,r7,32
	slw		MSW(r3,r4),MSW(r3,r4),r7
	srw		r10,LSW(r3,r4),r8
	or		MSW(r3,r4),MSW(r3,r4),r10
	slw		r10,LSW(r3,r4),r9
	or		MSW(r3,r4),MSW(r3,r4),r10
	slw		LSW(r3,r4),LSW(r3,r4),r7
	sub		r6,r6,r7
#if PPC_RT_ROUND_NEAREST
	rlwinm	r7,LSW(r3,r4),0,21,31
	cmpi	cr0,r7,0x400
	addi	r6,r6,1086
	blt		noround
	bgt		round
	rlwinm.	r7,LSW(r3,r4),0,20,20
	beq		noround
round:
	addic	LSW(r3,r4),LSW(r3,r4),0x0800
	addze	MSW(r3,r4),MSW(r3,r4)
	addze	r6,r6
noround:
#else
	addi	r6,r6,1086
#endif
	rlwinm	LSW(r3,r4),LSW(r3,r4),21,0,31
	rlwimi	LSW(r3,r4),MSW(r3,r4),21,0,10
	rlwinm	MSW(r3,r4),MSW(r3,r4),21,12,31
	rlwinm	r6,r6,20,0,11
	or		MSW(r3,r4),r6,MSW(r3,r4)
zero:
#if !__option (little_endian)
	stw		MSW(r3,r4),hilong(r1)
	stw		LSW(r3,r4),lolong(r1)
#else
	stw		LSW(r3,r4),hilong(r1)
	stw		MSW(r3,r4),lolong(r1)
#endif
	lfd		f1,hilong(r1)
#if __PPC_EABI__
	addi    SP,SP,16
#endif
	blr 
}

asm void __cvt_sll_flt(void)
{
#if __PPC_EABI__
	nofralloc
	stwu    SP,-16(SP)
#endif

  	rlwinm.	r5,MSW(r3,r4),0,0,0
	beq		cr0,positive
	subfic	LSW(r3,r4),LSW(r3,r4),0
	subfze	MSW(r3,r4),MSW(r3,r4)
positive:
	or.		r7,MSW(r3,r4),LSW(r3,r4)
	li		r6,0
	beq		cr0,zero
	cntlzw	r7,MSW(r3,r4)
	cntlzw	r8,LSW(r3,r4)
	rlwinm	r9,r7,26,0,4
	srawi	r9,r9,31
	and		r9,r9,r8
	add		r7,r7,r9
	subfic	r8,r7,32
	subic	r9,r7,32
	slw		MSW(r3,r4),MSW(r3,r4),r7
	srw		r10,LSW(r3,r4),r8
	or		MSW(r3,r4),MSW(r3,r4),r10
	slw		r10,LSW(r3,r4),r9
	or		MSW(r3,r4),MSW(r3,r4),r10
	slw		LSW(r3,r4),LSW(r3,r4),r7
	sub		r6,r6,r7
#if PPC_RT_ROUND_NEAREST
	rlwinm	r7,LSW(r3,r4),0,21,31
	cmpi	cr0,r7,0x400
	addi	r6,r6,1086
	blt		noround
	bgt		round
	rlwinm.	r7,LSW(r3,r4),0,20,20
	beq		noround
round:
	addic	LSW(r3,r4),LSW(r3,r4),0x0800
	addze	MSW(r3,r4),MSW(r3,r4)
	addze	r6,r6
noround:
#else
	addi	r6,r6,1086
#endif
	rlwinm	LSW(r3,r4),LSW(r3,r4),21,0,31
	rlwimi	LSW(r3,r4),MSW(r3,r4),21,0,10
	rlwinm	MSW(r3,r4),MSW(r3,r4),21,12,31
	rlwinm	r6,r6,20,0,11
	or		MSW(r3,r4),r6,MSW(r3,r4)
	or		MSW(r3,r4),r5,MSW(r3,r4)
zero:
#if !__option (little_endian)
	stw		MSW(r3,r4),hilong(r1)
	stw		LSW(r3,r4),lolong(r1)
#else
	stw		LSW(r3,r4),hilong(r1)
	stw		MSW(r3,r4),lolong(r1)
#endif
	lfd		f1,hilong(r1)
	frsp	f1,f1
#if __PPC_EABI__
	addi    SP,SP,16
#endif
	blr 
}

asm void __cvt_ull_flt(void)
{
#if __PPC_EABI__
	nofralloc
	stwu    SP,-16(SP)
#endif

	or.		r7,MSW(r3,r4),LSW(r3,r4)
	li		r6,0
	beq		cr0,zero
	cntlzw	r7,MSW(r3,r4)
	cntlzw	r8,LSW(r3,r4)
	rlwinm	r9,r7,26,0,4
	srawi	r9,r9,31
	and		r9,r9,r8
	add		r7,r7,r9
	subfic	r8,r7,32
	subic	r9,r7,32
	slw		MSW(r3,r4),MSW(r3,r4),r7
	srw		r10,LSW(r3,r4),r8
	or		MSW(r3,r4),MSW(r3,r4),r10
	slw		r10,LSW(r3,r4),r9
	or		MSW(r3,r4),MSW(r3,r4),r10
	slw		LSW(r3,r4),LSW(r3,r4),r7
	sub		r6,r6,r7
#if PPC_RT_ROUND_NEAREST
	rlwinm	r7,LSW(r3,r4),0,21,31
	cmpi	cr0,r7,0x400
	addi	r6,r6,1086
	blt		noround
	bgt		round
	rlwinm.	r7,LSW(r3,r4),0,20,20
	beq		noround
round:
	addic	LSW(r3,r4),LSW(r3,r4),0x0800
	addze	MSW(r3,r4),MSW(r3,r4)
	addze	r6,r6
noround:
#else
	addi	r6,r6,1086
#endif
	rlwinm	LSW(r3,r4),LSW(r3,r4),21,0,31
	rlwimi	LSW(r3,r4),MSW(r3,r4),21,0,10
	rlwinm	MSW(r3,r4),MSW(r3,r4),21,12,31
	rlwinm	r6,r6,20,0,11
	or		MSW(r3,r4),r6,MSW(r3,r4)
zero:
#if !__option (little_endian)
	stw		MSW(r3,r4),hilong(r1)
	stw		LSW(r3,r4),lolong(r1)
#else
	stw		LSW(r3,r4),hilong(r1)
	stw		MSW(r3,r4),lolong(r1)
#endif
	lfd		f1,hilong(r1)
	frsp	f1,f1
#if __PPC_EABI__
	addi    SP,SP,16
#endif
	blr 
}


#endif
