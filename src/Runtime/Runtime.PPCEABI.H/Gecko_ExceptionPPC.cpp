#if __MWERKS__
#pragma exceptions on
#endif

#define __NOSTRING__

#include <stdlib.h>
#include <MWCPlusLib.h>
#include <exception.h>
#include "gecko_ExceptionPPC.h"
#include <NMWException.h>

#if __PPC_EABI__
#include <__ppc_eabi_linker.h>
#define RETURN_ADDRESS 4
#else
#define RETURN_ADDRESS 8
#define nofralloc
#endif

#if 1
#define INLINE			static
#else
#define INLINE			inline
#endif

#if __VEC__
#pragma options align=power
#endif

#if __VEC__
union MWEVector128 {
	__vector unsigned long			vul;
	unsigned long 					l[4];
	unsigned short 					s[8];
	unsigned char 					c[16];
};
typedef union MWEVector128 MWEVector128;
#endif

#if __PPCe500__
#warning elf support enabled!
union MWE_ElfVector64
{
	unsigned long				l[2];
	unsigned short				s[4];
	unsigned char 				c[8];
};

typedef union MWE_ElfVector64 MWE_ElfVector64;
#endif

#if __PPCGEKKO__
union MWE_GeckoVector64 
{
	double d;	 
	float f[2];
};

typedef union MWE_GeckoVector64 MWE_GeckoVector64;

struct GeckoFPRContext 
{
	double d;
	MWE_GeckoVector64 v;
};

typedef struct GeckoFPRContext GeckoFPRContext;
#endif

typedef struct ThrowContext {
#if __VEC__
	MWEVector128 VR[32];
	MWEVector128 vscr;
	unsigned long vrsave;
#endif
#ifndef _No_Floating_Point_Regs
 #if __PPCGEKKO__
	GeckoFPRContext  FPR[32];
 #else
	double		     FPR[32];
 #endif
#endif
#if __PPCe500__
#warning GPR throwcontext is a union, as vec64bit is not as functional as needed to work here
	MWE_ElfVector64	GPR[32];
#else
	long		    GPR[32];
#endif
	long		CR;
	char*		SP;
	char*		FP;
	char*		throwSP;
	char*		returnaddr;
	char*		throwtype;
	void*		location;
	void*		dtor;
	CatchInfo	*catchinfo;
}	ThrowContext;
typedef ThrowContext* ThrowContextPtr;

typedef struct MWExceptionInfo {
	ExceptionTableSmall*	exception_record;
	char*			current_function;
	char*			action_pointer;
	char*			code_section;
	char*			data_section;
	char*			TOC;
}	MWExceptionInfo;

typedef struct FragmentInfo {
	ExceptionTableIndex*	exception_start;
	ExceptionTableIndex*	exception_end;
	char*					code_start;
	char*					code_end;
	char*					data_start;
	char*					data_end;
	char*					TOC;
	int						active;
} FragmentInfo;

typedef struct ProcessInfo {
	__eti_init_info*		exception_info;
	char*					TOC;
	int						active;
} ProcessInfo;

typedef struct ActionIterator {
	MWExceptionInfo	info;
	char*			current_SP;
	char*			current_FP;
	long			current_R31;
}	ActionIterator;

#if __VEC__
#pragma options align=reset
#endif

#define	MAXFRAGMENTS __CW_MAX_PROCESSES__
static ProcessInfo fragmentinfo[MAXFRAGMENTS];

typedef void (*DeleteFunc)(void *);

static int ExPPC_FindExceptionFragment(char *returnaddr, FragmentInfo *frag)
{
	ProcessInfo *f;
	int i;
	__eti_init_info *eti_info;

	for(i=0,f=fragmentinfo;i<MAXFRAGMENTS;++i,++f) if(f->active)
	{
		eti_info = f->exception_info;
		while (1) {
			if (eti_info->code_size == 0) break;
			if(returnaddr>=eti_info->code_start && 
					returnaddr<(char*)eti_info->code_start+eti_info->code_size) {
				frag->exception_start = (ExceptionTableIndex *)eti_info->eti_start;
				frag->exception_end = (ExceptionTableIndex *)eti_info->eti_end;
				frag->code_start = 0;
				frag->code_end = 0;
				frag->data_start = 0;
				frag->data_end = 0;
				frag->TOC = f->TOC;
				frag->active = f->active;
				return(1);
			}
	 		eti_info++;
		}
	}

	return(0);
}

static void ExPPC_FindExceptionRecord(char *returnaddr,MWExceptionInfo *info)
{
	FragmentInfo *fragment;
	FragmentInfo frag;

	ExceptionTableIndex *exceptionindex,*p;
	unsigned long returnoffset;
	long i,m,n;

	info->exception_record=0;
	info->action_pointer=0;

	if ((ExPPC_FindExceptionFragment(returnaddr, &frag))==0) return;
	fragment = &frag;

	info->code_section=fragment->code_start;
	info->data_section=fragment->data_start;
	info->TOC=fragment->TOC;

	returnoffset=returnaddr-fragment->code_start;
	exceptionindex=fragment->exception_start;
	for(i=0,n=fragment->exception_end-fragment->exception_start;;)
	{
		if(i>n) return;
		p=&exceptionindex[m=(i+n)/2];
		if(returnoffset<p->functionoffset) n=m-1;
		else if(returnoffset>p->functionoffset+ETI_GetFunctionSize(p->eti_field)) i=m+1;
		else break;
	}
	info->current_function=fragment->code_start+p->functionoffset;
	info->exception_record=ETI_GetDirectStore(p->eti_field)?(ExceptionTableSmall *)(&p->exceptionoffset)
										:(ExceptionTableSmall *)(fragment->data_start+p->exceptionoffset);

	returnoffset-=p->functionoffset;

	if ( ET_IsLargeTable(info->exception_record->et_field) )
	{
		ExceptionTableLarge *etl = (ExceptionTableLarge *) info->exception_record;
		ExceptionRangeLarge *erl; 

		for( erl = etl->ranges; erl->start != 0; erl++ )
		{
			unsigned long range_end = erl->start + (erl->size * 4);

			if ( erl->start <= returnoffset && range_end >= returnoffset )
			{
				info->action_pointer = (char *) etl + erl->action; 
				break;
			}
		}
	}
	else
	{
		ExceptionTableSmall *ets = (ExceptionTableSmall *) info->exception_record;
		ExceptionRangeSmall *ers;

		for( ers = ets->ranges; ers->start != 0; ers++ )
		{
			if( ers->start <= returnoffset && ers->end >= returnoffset)
			{
				info->action_pointer = (char *) ets + ers->action; 
				break;
			}
		}
	}
}

static long ExPPC_PopR31(char *SP,MWExceptionInfo *info)
{
#ifndef _No_Floating_Point_Regs
	double *FPR_save_area;
#endif
	long *GPR_save_area;
	int saved_GPRs, saved_FPRs;

#ifndef _No_Floating_Point_Regs
	saved_FPRs=ET_GetSavedFPRs(info->exception_record->et_field);
	FPR_save_area=(double *)(SP-saved_FPRs*8);

    saved_GPRs=ET_GetSavedGPRs(info->exception_record->et_field);
    GPR_save_area=(long *)FPR_save_area;
#if !__PPC_EABI__
    if(saved_FPRs&1) GPR_save_area-=2;
#endif
#else
    saved_GPRs=ET_GetSavedGPRs(info->exception_record->et_field);
    GPR_save_area=(long *)SP;
#endif

#if __PPCe500__
	if (ET_HasElfVector(info->exception_record->et_field))
	{
		return(GPR_save_area[-2]);
	}
#endif

	return(GPR_save_area[-1]);
}

static exaction_type ExPPC_CurrentAction(const ActionIterator *iter)
{
	if(iter->info.action_pointer==0) return EXACTION_ENDOFLIST;
	return ((ex_destroylocal *)iter->info.action_pointer)->action&EXACTION_MASK;
}

static exaction_type ExPPC_NextAction(ActionIterator *iter)
{
	exaction_type	action;

	for(;;)
	{
		if(	iter->info.action_pointer==0
		||	((action=((ex_destroylocal *)iter->info.action_pointer)->action)&EXACTION_ENDBIT)!=0 )
		{
			char *return_addr, *callers_SP;

			callers_SP=*(char **)iter->current_SP;
			if(ET_GetSavedGPRs(iter->info.exception_record->et_field)) iter->current_R31=ExPPC_PopR31(callers_SP,&iter->info);
			return_addr=*(char **)(callers_SP+RETURN_ADDRESS);
			ExPPC_FindExceptionRecord(return_addr,&iter->info);
			if(iter->info.exception_record==0) terminate();
			iter->current_SP=callers_SP;
			iter->current_FP=(ET_GetHasFramePtr(iter->info.exception_record->et_field))?(char *)iter->current_R31:iter->current_SP;
			if(iter->info.action_pointer==0) continue;
		}
		else
		{
			switch(action)
			{
			case EXACTION_DESTROYLOCAL:
				iter->info.action_pointer+=sizeof(ex_destroylocal); break;
			case EXACTION_DESTROYLOCALCOND:
				iter->info.action_pointer+=sizeof(ex_destroylocalcond); break;
			case EXACTION_DESTROYLOCALPOINTER:
				iter->info.action_pointer+=sizeof(ex_destroylocalpointer); break;
			case EXACTION_DESTROYLOCALARRAY:
				iter->info.action_pointer+=sizeof(ex_destroylocalarray); break;
			case EXACTION_DESTROYBASE:
			case EXACTION_DESTROYMEMBER:
				iter->info.action_pointer+=sizeof(ex_destroymember); break;
			case EXACTION_DESTROYMEMBERCOND:
				iter->info.action_pointer+=sizeof(ex_destroymembercond); break;
			case EXACTION_DESTROYMEMBERARRAY:
				iter->info.action_pointer+=sizeof(ex_destroymemberarray); break;
			case EXACTION_DELETEPOINTER:
				iter->info.action_pointer+=sizeof(ex_deletepointer); break;
			case EXACTION_DELETEPOINTERCOND:
				iter->info.action_pointer+=sizeof(ex_deletepointercond); break;
			case EXACTION_CATCHBLOCK:
				iter->info.action_pointer+=sizeof(ex_catchblock); break;
			case EXACTION_CATCHBLOCK_32:
				iter->info.action_pointer+=sizeof(ex_catchblock_32); break;
			case EXACTION_ACTIVECATCHBLOCK:
				iter->info.action_pointer+=sizeof(ex_activecatchblock); break;
			case EXACTION_SPECIFICATION:
				iter->info.action_pointer+=sizeof(ex_specification)+((ex_specification *)iter->info.action_pointer)->specs*sizeof(void *); break;
			default:
				terminate();
			}
		}
		action=((ex_destroylocal *)iter->info.action_pointer)->action&EXACTION_MASK;
		if(action==EXACTION_BRANCH)
		{
			iter->info.action_pointer=((char *)iter->info.exception_record)+((ex_branch *)iter->info.action_pointer)->target;
			action=((ex_destroylocal *)iter->info.action_pointer)->action&EXACTION_MASK;
		}
		return action;
	}
}

static char *ExPPC_PopStackFrame(ThrowContext *context,MWExceptionInfo *info)
{
	char *SP, *callers_SP;
#ifndef _No_Floating_Point_Regs
	double *FPR_save_area;
#endif
	long *GPR_save_area;
	int saved_GPRs, saved_FPRs;
#if __VEC__
	MWEVector128 *VR_save_area;
	int saved_VRs;
#endif
#if __PPCe500__
	MWE_ElfVector64 *Vector_save_area;	
#endif
#if __PPCGEKKO__
	GeckoFPRContext *Vector_save_area;	
#endif

	int i, j;

	SP=context->SP; callers_SP=*(char **)SP;

#ifndef _No_Floating_Point_Regs
	saved_FPRs=ET_GetSavedFPRs(info->exception_record->et_field);
#if __PPCGEKKO__
	if (ET_HasElfVector(info->exception_record->et_field))
	{
		Vector_save_area = (GeckoFPRContext *)(callers_SP-saved_FPRs*16);
		FPR_save_area=(double *)Vector_save_area;
	}
	else
#endif
	{
		FPR_save_area=(double *)(callers_SP-saved_FPRs*8);
	}
#if __PPCGEKKO__
	if (ET_HasElfVector(info->exception_record->et_field))
	{
	    for(i=32-saved_FPRs, j=0;i<32;++i,++j) 
	    {
	    	context->FPR[i].v.f[0] = Vector_save_area[j].v.f[0];
	    	context->FPR[i].v.f[1] = Vector_save_area[j].v.f[1];
	    	context->FPR[i].d = Vector_save_area[j].d;
	    }
	}
	else
	{
	    for(i=32-saved_FPRs, j=0;i<32;++i,++j)
	    {
	     	context->FPR[i].d = FPR_save_area[j];
	    }
	}
#else	
	for(i=32-saved_FPRs, j=0;i<32;++i,++j) context->FPR[i]=FPR_save_area[j];
#endif
#endif

    saved_GPRs=ET_GetSavedGPRs(info->exception_record->et_field);
#ifndef _No_Floating_Point_Regs
    GPR_save_area=(long *)FPR_save_area;
#if !__PPC_EABI__
    if(saved_FPRs&1) GPR_save_area-=2;
#endif
    GPR_save_area-=saved_GPRs;
#else
#if __PPCe500__
	if (ET_HasElfVector(info->exception_record->et_field))
		Vector_save_area = (MWE_ElfVector64 *)(callers_SP-saved_GPRs*8);
	else	
#endif
	GPR_save_area = (long *)(callers_SP-saved_GPRs*4);
#endif
#if __PPCe500__
	if (ET_HasElfVector(info->exception_record->et_field))
	{
#warning This will result in block copy rather then elf code, fix sometime
	    for(i=32-saved_GPRs, j=0;i<32;++i,++j) context->GPR[i]=Vector_save_area[j];
	}
	else
	{
	    for(i=32-saved_GPRs, j=0;i<32;++i,++j)
	    {
	    #if (__option(little_endian))
	    	context->GPR[i].l[0]=GPR_save_area[j];
	     	context->GPR[i].l[1]=0;
	    #else
	     	context->GPR[i].l[1]=GPR_save_area[j];
	     	context->GPR[i].l[0]=0;
	    #endif
	    }
	}
#else
    for(i=32-saved_GPRs, j=0;i<32;++i,++j) context->GPR[i]=GPR_save_area[j];

#endif

#if __VEC__
	if ( ET_HasVectorInfo(info->exception_record->et_field) )
	{
		ExceptionTableSmallVector *etsv = (ExceptionTableSmallVector *) info->exception_record;
		int vrsavesize 					= ET_GetSavedVRSAVE(etsv->et_field) ? sizeof(long) : 0;
    	saved_VRs						= ET_GetSavedVRs(etsv->et_field);

		VR_save_area	=	(MWEVector128 *) GPR_save_area;
		VR_save_area	-=	vrsavesize;
		VR_save_area	-= 	saved_VRs;

		VR_save_area	=  (MWEVector128 *) ( (unsigned int) VR_save_area & 0xFFFFFFF0 );

		for(i=32-saved_VRs, j=0;i<32;++i,++j) context->VR[i]=VR_save_area[j];
	}
#endif

#if !__PPC_EABI__
	if(ET_GetSavedCR(info->exception_record->et_field)) context->CR=*(long *)(callers_SP+4);
#endif

	context->SP=callers_SP;

	return(*(char **)(callers_SP+RETURN_ADDRESS));
}

INLINE void ExPPC_DestroyLocal(ThrowContext *context,const ex_destroylocal *ex)
{
	DTORCALL_COMPLETE(ex->dtor,context->FP+ex->local);
}

INLINE void ExPPC_DestroyLocalCond(ThrowContext *context,const ex_destroylocalcond *ex)
{
#if __PPCe500__
	#if (__option(little_endian))
		int cond = ex_destroylocalcond_GetRegCond(ex->dlc_field)	? (local_cond_type) context->GPR[ex->cond].c[0]
							: *(local_cond_type *)(context->FP+ex->cond);
	#else
		int cond = ex_destroylocalcond_GetRegCond(ex->dlc_field)	? (local_cond_type) context->GPR[ex->cond].c[7]
							: *(local_cond_type *)(context->FP+ex->cond);
	#endif
#else
	int cond = ex_destroylocalcond_GetRegCond(ex->dlc_field)	? (local_cond_type) context->GPR[ex->cond]
							: *(local_cond_type *)(context->FP+ex->cond);
#endif							

	if(cond) DTORCALL_COMPLETE(ex->dtor,context->FP+ex->local);
}

INLINE void ExPPC_DestroyLocalPointer(ThrowContext *context,const ex_destroylocalpointer *ex)
{
#if __PPCe500__
	#if (__option(little_endian))
		void *pointer = ex_destroylocalpointer_GetRegPointer(ex->dlp_field)	? (void *) context->GPR[ex->pointer].l[0]
									: *(void **)(context->FP+ex->pointer);
	#else
		void *pointer = ex_destroylocalpointer_GetRegPointer(ex->dlp_field)	? (void *) context->GPR[ex->pointer].l[1]
									: *(void **)(context->FP+ex->pointer);
	#endif
#else
	void *pointer = ex_destroylocalpointer_GetRegPointer(ex->dlp_field)	? (void *) context->GPR[ex->pointer]
									: *(void **)(context->FP+ex->pointer);
#endif

	DTORCALL_COMPLETE(ex->dtor,pointer);
}

INLINE void ExPPC_DestroyLocalArray(ThrowContext *context,const ex_destroylocalarray *ex)
{
	char *ptr	= context->FP+ex->localarray;
	long n		= ex->elements;
	long size	= ex->element_size;

	for(ptr=ptr+size*n; n>0; n--)
	{
		ptr-=size; DTORCALL_COMPLETE(ex->dtor,ptr);
	}
}

INLINE void ExPPC_DestroyMember(ThrowContext *context,const ex_destroymember *ex)
{
#if __PPCe500__
	#if (__option(little_endian))
		char *objectptr = ex_destroymember_GetRegPointer(ex->dm_field)	? (char *) context->GPR[ex->objectptr].l[0]
										: *(char **)(context->FP+ex->objectptr);
	#else
		char *objectptr = ex_destroymember_GetRegPointer(ex->dm_field)	? (char *) context->GPR[ex->objectptr].l[1]
										: *(char **)(context->FP+ex->objectptr);
	#endif							
#else
	char *objectptr = ex_destroymember_GetRegPointer(ex->dm_field)	? (char *) context->GPR[ex->objectptr]
										: *(char **)(context->FP+ex->objectptr);
#endif

	DTORCALL_COMPLETE(ex->dtor,objectptr+ex->offset);
}

INLINE void ExPPC_DestroyBase(ThrowContext *context,const ex_destroymember *ex)
{
#if __PPCe500__
	#if (__option(little_endian))
		char *objectptr = ex_destroymember_GetRegPointer(ex->dm_field)	? (char *) context->GPR[ex->objectptr].l[0]
										: *(char **)(context->FP+ex->objectptr);
	#else
		char *objectptr = ex_destroymember_GetRegPointer(ex->dm_field)	? (char *) context->GPR[ex->objectptr].l[1]
										: *(char **)(context->FP+ex->objectptr);
	#endif
#else
	char *objectptr = ex_destroymember_GetRegPointer(ex->dm_field)	? (char *) context->GPR[ex->objectptr]
										: *(char **)(context->FP+ex->objectptr);
#endif

	DTORCALL_PARTIAL(ex->dtor,objectptr+ex->offset);
}

INLINE void ExPPC_DestroyMemberCond(ThrowContext *context,const ex_destroymembercond *ex)
{
#if __PPCe500__
	#if (__option(little_endian))
		char *objectptr = ex_destroymembercond_GetRegPointer(ex->dmc_field)	? (char *) context->GPR[ex->objectptr].l[0]
										: *(char **)(context->FP+ex->objectptr);
		int cond = ex_destroymembercond_GetRegCond(ex->dmc_field)	? (vbase_ctor_arg_type) context->GPR[ex->cond].l[0]
								: *(vbase_ctor_arg_type *)(context->FP+ex->cond);
	#else
		char *objectptr = ex_destroymembercond_GetRegPointer(ex->dmc_field)	? (char *) context->GPR[ex->objectptr].l[1]
										: *(char **)(context->FP+ex->objectptr);
		int cond = ex_destroymembercond_GetRegCond(ex->dmc_field)	? (vbase_ctor_arg_type) context->GPR[ex->cond].l[1]
								: *(vbase_ctor_arg_type *)(context->FP+ex->cond);
	#endif
#else
	char *objectptr = ex_destroymembercond_GetRegPointer(ex->dmc_field)	? (char *) context->GPR[ex->objectptr]
										: *(char **)(context->FP+ex->objectptr);
	int cond = ex_destroymembercond_GetRegCond(ex->dmc_field)	? (vbase_ctor_arg_type) context->GPR[ex->cond]
							: *(vbase_ctor_arg_type *)(context->FP+ex->cond);
#endif

	if(cond) DTORCALL_PARTIAL(ex->dtor,objectptr+ex->offset);
}

INLINE void ExPPC_DestroyMemberArray(ThrowContext *context,const ex_destroymemberarray *ex)
{
#if __PPCe500__
	#if (__option(little_endian))
		char *ptr	= ex_destroymemberarray_GetRegPointer(ex->dma_field)	? (char *) context->GPR[ex->objectptr].l[0]
									: *(char **)(context->FP+ex->objectptr);
	#else
		char *ptr	= ex_destroymemberarray_GetRegPointer(ex->dma_field)	? (char *) context->GPR[ex->objectptr].l[1]
									: *(char **)(context->FP+ex->objectptr);
	#endif
#else
	char *ptr	= ex_destroymemberarray_GetRegPointer(ex->dma_field)	? (char *) context->GPR[ex->objectptr]
									: *(char **)(context->FP+ex->objectptr);
#endif

	long n		= ex->elements;
	long size	= ex->element_size;

	ptr += ex->offset;

	for(ptr=ptr+size*n; n>0; n--)
	{
		ptr-=size; DTORCALL_COMPLETE(ex->dtor,ptr);
	}
}

INLINE void ExPPC_DeletePointer(ThrowContext *context,const ex_deletepointer *ex)
{
#if __PPCe500__
	#if (__option(little_endian))
		char *objectptr = ex_deletepointer_GetRegPointer(ex->dp_field)	? (char *) context->GPR[ex->objectptr].l[0]
										: *(char **)(context->FP+ex->objectptr);
	#else
		char *objectptr = ex_deletepointer_GetRegPointer(ex->dp_field)	? (char *) context->GPR[ex->objectptr].l[1]
										: *(char **)(context->FP+ex->objectptr);
	#endif
#else
	char *objectptr = ex_deletepointer_GetRegPointer(ex->dp_field)	? (char *) context->GPR[ex->objectptr]
										: *(char **)(context->FP+ex->objectptr);
#endif

	((DeleteFunc) ex->deletefunc)(objectptr);
}

INLINE void ExPPC_DeletePointerCond(ThrowContext *context,const ex_deletepointercond *ex)
{
#if __PPCe500__
	#if (__option(little_endian))
		char *objectptr = ex_deletepointercond_GetRegPointer(ex->dpc_field) ? (char *) context->GPR[ex->objectptr].l[0]
										: *(char **)(context->FP+ex->objectptr);
		int cond = ex_deletepointercond_GetRegCond(ex->dpc_field)	? (local_cond_type) context->GPR[ex->cond].c[0]
							: *(local_cond_type *)(context->FP+ex->cond);
	#else
		char *objectptr = ex_deletepointercond_GetRegPointer(ex->dpc_field) ? (char *) context->GPR[ex->objectptr].l[1]
										: *(char **)(context->FP+ex->objectptr);
		int cond = ex_deletepointercond_GetRegCond(ex->dpc_field)	? (local_cond_type) context->GPR[ex->cond].c[7]
							: *(local_cond_type *)(context->FP+ex->cond);
	#endif
#else
	char *objectptr = ex_deletepointercond_GetRegPointer(ex->dpc_field) ? (char *) context->GPR[ex->objectptr]
										: *(char **)(context->FP+ex->objectptr);
	int cond = ex_deletepointercond_GetRegCond(ex->dpc_field)	? (local_cond_type) context->GPR[ex->cond]
							: *(local_cond_type *)(context->FP+ex->cond);
#endif

	if(cond) ((DeleteFunc) ex->deletefunc)(objectptr);
}

static void ExPPC_UnwindStack(ThrowContext *context,MWExceptionInfo *info,void *catcher)
{
	exaction_type	action;

#pragma exception_terminate

	for(;;)
	{
		if(info->action_pointer==0)
		{
			char *return_addr;

			return_addr=ExPPC_PopStackFrame(context,info);
			ExPPC_FindExceptionRecord(return_addr,info);
			if(info->exception_record==0) terminate();
	#if __PPCe500__
		#if (__option(little_endian))
			context->FP=(ET_GetHasFramePtr(info->exception_record->et_field))?(char *)context->GPR[31].c[0]:context->SP;
		#else
			context->FP=(ET_GetHasFramePtr(info->exception_record->et_field))?(char *)context->GPR[31].c[7]:context->SP;
		#endif		
	#else
			context->FP=(ET_GetHasFramePtr(info->exception_record->et_field))?(char *)context->GPR[31]:context->SP;
	#endif
			continue;
		}

		action=((ex_destroylocal *)info->action_pointer)->action;
		switch(action&EXACTION_MASK)
		{
		case EXACTION_BRANCH:
			info->action_pointer=((char *)info->exception_record)+((ex_branch *)info->action_pointer)->target; break;

		case EXACTION_DESTROYLOCAL:
			ExPPC_DestroyLocal(context,(ex_destroylocal *)info->action_pointer);
			info->action_pointer+=sizeof(ex_destroylocal); break;

		case EXACTION_DESTROYLOCALCOND:
			ExPPC_DestroyLocalCond(context,(ex_destroylocalcond *)info->action_pointer);
			info->action_pointer+=sizeof(ex_destroylocalcond); break;

		case EXACTION_DESTROYLOCALPOINTER:
			ExPPC_DestroyLocalPointer(context,(ex_destroylocalpointer *)info->action_pointer);
			info->action_pointer+=sizeof(ex_destroylocalpointer); break;

		case EXACTION_DESTROYLOCALARRAY:
			ExPPC_DestroyLocalArray(context,(ex_destroylocalarray *)info->action_pointer);
			info->action_pointer+=sizeof(ex_destroylocalarray); break;

		case EXACTION_DESTROYBASE:
			ExPPC_DestroyBase(context,(ex_destroymember *)info->action_pointer);
			info->action_pointer+=sizeof(ex_destroymember); break;

		case EXACTION_DESTROYMEMBER:
			ExPPC_DestroyMember(context,(ex_destroymember *)info->action_pointer);
			info->action_pointer+=sizeof(ex_destroymember); break;

		case EXACTION_DESTROYMEMBERCOND:
			ExPPC_DestroyMemberCond(context,(ex_destroymembercond *)info->action_pointer);
			info->action_pointer+=sizeof(ex_destroymembercond); break;

		case EXACTION_DESTROYMEMBERARRAY:
			ExPPC_DestroyMemberArray(context,(ex_destroymemberarray *)info->action_pointer);
			info->action_pointer+=sizeof(ex_destroymemberarray); break;

		case EXACTION_DELETEPOINTER:
			ExPPC_DeletePointer(context,(ex_deletepointer *)info->action_pointer);
			info->action_pointer+=sizeof(ex_deletepointer); break;

		case EXACTION_DELETEPOINTERCOND:
			ExPPC_DeletePointerCond(context,(ex_deletepointercond *)info->action_pointer);
			info->action_pointer+=sizeof(ex_deletepointercond); break;

		case EXACTION_CATCHBLOCK:
			if(catcher==(void *)info->action_pointer) return;
			info->action_pointer+=sizeof(ex_catchblock); break;

		case EXACTION_CATCHBLOCK_32:
			if(catcher==(void *)info->action_pointer) return;
			info->action_pointer+=sizeof(ex_catchblock_32); break;

		case EXACTION_ACTIVECATCHBLOCK:
			{
				CatchInfo		*catchinfo;

				catchinfo=(CatchInfo *)(context->FP+((ex_activecatchblock *)info->action_pointer)->cinfo_ref);
            	if ( catchinfo->dtor )
           		{
                	if ( context->location == catchinfo->location )
                	{
                    	context->dtor = catchinfo->dtor;
                	}
                	else
                	{
                    	DTORCALL_COMPLETE(catchinfo->dtor,catchinfo->location);
                	}
           		}
				info->action_pointer+=sizeof(ex_activecatchblock);
			}
			break;

		case EXACTION_SPECIFICATION:
			if(catcher==(void *)info->action_pointer) return;
			info->action_pointer+=sizeof(ex_specification)+((ex_specification *)info->action_pointer)->specs*sizeof(void *);
			break;

		default:
			terminate();
		}
		if(action&EXACTION_ENDBIT) info->action_pointer=0;
	}
}

static int ExPPC_IsInSpecification(char *extype,ex_specification *spec)
{
	long	i,offset;

	for(i=0; i<spec->specs; i++)
	{
		if(__throw_catch_compare(extype,spec->spec[i],&offset)) return 1;
	}
	return 0;
}

extern void __unexpected(CatchInfo* catchinfo)
{	
	ex_specification *unexp=(ex_specification *)catchinfo->stacktop;

#pragma exception_magic

	try {
		unexpected();
	}
	catch(...)
	{
		if(ExPPC_IsInSpecification((char *)((CatchInfo *)&__exception_magic)->typeinfo,unexp))
		{
			throw;
		}
		if(ExPPC_IsInSpecification("!bad_exception!!",unexp))
		{
			throw bad_exception();
		}
		if(ExPPC_IsInSpecification("!std::bad_exception!!",unexp))
		{
			throw bad_exception();
		}
	}
	terminate();
}

static asm void ExPPC_LongJump(register ThrowContext *context, register void *newRTOC, register void *newPC)
{
#if __ALTIVEC__ || __PPC_EABI__
		nofralloc
#endif

		mr			r8,newPC	
		mr			RTOC,newRTOC
		lwz			r0,context->CR
		mtcrf		255,r0

#if !__PPC_EABI__
#if __VEC__
		lwz			r5,context->vrsave	
		bl			__setLR
__setLR:	

		oris	 	r5,r5,0x8000
		mtvrsave 	r5
		clrlwi		r5,r5,20
		cntlzw		r5,r5
		slwi		r5,r5,3
		mflr		r6

		addi		r6,r6,__longjmpv20 - __setLR - (20 * 8)
		add			r6,r6,r5
		mtlr		r6
		blr

__longjmpv20:		
#endif
		la			r31,context->VR[20]
		lvx			vr20,0,r31
		la			r31,context->VR[21]
		lvx			vr21,0,r31
		la			r31,context->VR[22]
		lvx			vr22,0,r31
		la			r31,context->VR[23]
		lvx			vr23,0,r31
		la			r31,context->VR[24]
		lvx			vr24,0,r31
		la			r31,context->VR[25]
		lvx			vr25,0,r31
		la			r31,context->VR[26]
		lvx			vr26,0,r31
		la			r31,context->VR[27]
		lvx			vr27,0,r31
		la			r31,context->VR[28]
		lvx			vr28,0,r31
		la			r31,context->VR[29]
		lvx			vr29,0,r31
		la			r31,context->VR[30]
		lvx			vr30,0,r31
		la			r31,context->VR[31]
		lvx			vr31,0,r31
#endif

#if __PPC_EABI__
	#if __PPCe500__
			la			r31,context->GPR[13]
			evlddx		r13, 0, r31
			la			r31,context->GPR[14]
			evlddx		r14, 0, r31
			la			r31,context->GPR[15]
			evlddx		r15, 0, r31
			la			r31,context->GPR[16]
			evlddx		r16, 0, r31
			la			r31,context->GPR[17]
			evlddx		r17, 0, r31
			la			r31,context->GPR[18]
			evlddx		r18, 0, r31
			la			r31,context->GPR[19]
			evlddx		r19, 0, r31
			la			r31,context->GPR[20]
			evlddx		r20, 0, r31
			la			r31,context->GPR[21]
			evlddx		r21, 0, r31
			la			r31,context->GPR[22]
			evlddx		r22, 0, r31
			la			r31,context->GPR[23]
			evlddx		r23, 0, r31
			la			r31,context->GPR[24]
			evlddx		r24, 0, r31
			la			r31,context->GPR[25]
			evlddx		r25, 0, r31
			la			r31,context->GPR[26]
			evlddx		r26, 0, r31
			la			r31,context->GPR[27]
			evlddx		r27, 0, r31
			la			r31,context->GPR[28]
			evlddx		r28, 0, r31
			la			r31,context->GPR[29]
			evlddx		r29, 0, r31
			la			r31,context->GPR[30]
			evlddx		r30, 0, r31
			la			r31,context->GPR[31]
			evlddx		r31, 0, r31
	#else
	#if !__option(use_lmw_stmw) || __option(little_endian)
		lwz			r13,context->GPR[13]
		lwz			r14,context->GPR[14]
		lwz			r15,context->GPR[15]
		lwz			r16,context->GPR[16]
		lwz			r17,context->GPR[17]
		lwz			r18,context->GPR[18]
		lwz			r19,context->GPR[19]
		lwz			r20,context->GPR[20]
		lwz			r21,context->GPR[21]
		lwz			r22,context->GPR[22]
		lwz			r23,context->GPR[23]
		lwz			r24,context->GPR[24]
		lwz			r25,context->GPR[25]
		lwz			r26,context->GPR[26]
		lwz			r27,context->GPR[27]
		lwz			r28,context->GPR[28]
		lwz			r29,context->GPR[29]
		lwz			r30,context->GPR[30]
		lwz			r31,context->GPR[31]
	#else
		lmw			r13,context->GPR[13]
	#endif
    #endif	
#else
		lmw			r13,context->GPR[13]

#endif

#ifndef _No_Floating_Point_Regs
#if __PPCGEKKO__
.machine gecko
		la			r7, context->FPR[14].v
		psq_lx		fp14,0,r7,0,0
		lfd			fp14,context->FPR[14].d

		la			r7, context->FPR[15].v
		psq_lx		fp15,0,r7,0,0
		lfd			fp15,context->FPR[15].d

		la			r7, context->FPR[16].v
		psq_lx		fp16,0,r7,0,0
		lfd			fp16,context->FPR[16].d

		la			r7, context->FPR[17].v
		psq_lx		fp17,0,r7,0,0
		lfd			fp17,context->FPR[17].d

		la			r7, context->FPR[18].v
		psq_lx		fp18,0,r7,0,0
		lfd			fp18,context->FPR[18].d

		la			r7, context->FPR[19].v
		psq_lx		fp19,0,r7,0,0
		lfd			fp19,context->FPR[19].d

		la			r7, context->FPR[20].v
		psq_lx		fp20,0,r7,0,0
		lfd			fp20,context->FPR[20].d

		la			r7, context->FPR[21].v
		psq_lx		fp21,0,r7,0,0
		lfd			fp21,context->FPR[21].d

		la			r7, context->FPR[22].v
		psq_lx		fp22,0,r7,0,0
		lfd			fp22,context->FPR[22].d

		la			r7, context->FPR[23].v
		psq_lx		fp23,0,r7,0,0
		lfd			fp23,context->FPR[23].d

		la			r7, context->FPR[24].v
		psq_lx		fp24,0,r7,0,0
		lfd			fp24,context->FPR[24].d

		la			r7, context->FPR[25].v
		psq_lx		fp25,0,r7,0,0
		lfd			fp25,context->FPR[25].d

		la			r7, context->FPR[26].v
		psq_lx		fp26,0,r7,0,0
		lfd			fp26,context->FPR[26].d

		la			r7, context->FPR[27].v
		psq_lx		fp27,0,r7,0,0
		lfd			fp27,context->FPR[27].d

		la			r7, context->FPR[28].v
		psq_lx		fp28,0,r7,0,0
		lfd			fp28,context->FPR[28].d

		la			r7, context->FPR[29].v
		psq_lx		fp29,0,r7,0,0
		lfd			fp29,context->FPR[29].d

		la			r7, context->FPR[30].v
		psq_lx		fp30,0,r7,0,0
		lfd			fp30,context->FPR[30].d

		la			r7, context->FPR[31].v
		psq_lx		fp31,0,r7,0,0
		lfd			fp31,context->FPR[31].d
#else
		lfd			fp14,context->FPR[14]
		lfd			fp15,context->FPR[15]
		lfd			fp16,context->FPR[16]
		lfd			fp17,context->FPR[17]
		lfd			fp18,context->FPR[18]
		lfd			fp19,context->FPR[19]
		lfd			fp20,context->FPR[20]
		lfd			fp21,context->FPR[21]
		lfd			fp22,context->FPR[22]
		lfd			fp23,context->FPR[23]
		lfd			fp24,context->FPR[24]
		lfd			fp25,context->FPR[25]
		lfd			fp26,context->FPR[26]
		lfd			fp27,context->FPR[27]
		lfd			fp28,context->FPR[28]
		lfd			fp29,context->FPR[29]
		lfd			fp30,context->FPR[30]
		lfd			fp31,context->FPR[31]
#endif

#endif

		mtlr		r8

#if __VEC__
#if __PPC_EABI__
		lwz			r5,context->vrsave	
		oris	 	r5,r5,0x8000
		mtvrsave 	r5
#endif
		la			r5,context->vscr
		lvewx		vr0,0,r5
		mtvscr		vr0

		lwz			r5,context->vrsave
		mtvrsave 	r5
#endif

		lwz			SP,context->throwSP
		lwz			r3,context->SP
		lwz			r3,0(r3)
		stw			r3,0(SP)
		blr
}

static void ExPPC_HandleUnexpected(ThrowContext *context,MWExceptionInfo *info,ex_specification *unexp)
{
	CatchInfo	*catchinfo;

#pragma exception_terminate

	ExPPC_UnwindStack(context,info,unexp);

	catchinfo=(CatchInfo *)(context->FP+unexp->cinfo_ref);
	catchinfo->location		= context->location;
	catchinfo->typeinfo		= context->throwtype;
	catchinfo->dtor			= context->dtor;
	catchinfo->stacktop		= unexp;
	ExPPC_LongJump(context,info->TOC,info->current_function+unexp->pcoffset);
}

static void ExPPC_ThrowHandler(ThrowContext *context)
{
	ActionIterator	iter;
	MWExceptionInfo	info;
	exaction_type	action;
	CatchInfo		*catchinfo;
	long			offset;

	ExPPC_FindExceptionRecord(context->returnaddr, &info);
	if(info.exception_record==0) terminate();

#if __PPCe500__
	#if (__option(little_endian))
		context->FP=(ET_GetHasFramePtr(info.exception_record->et_field))?(char *)context->GPR[31].c[0]:context->SP;
	#else
		context->FP=(ET_GetHasFramePtr(info.exception_record->et_field))?(char *)context->GPR[31].c[7]:context->SP;
	#endif	
#else
	context->FP=(ET_GetHasFramePtr(info.exception_record->et_field))?(char *)context->GPR[31]:context->SP;
#endif
	if(context->throwtype==0)
	{
		iter.info		= info;
		iter.current_SP	= context->SP;
		iter.current_FP	= context->FP;
	#if __PPCe500__
		#if (__option(little_endian))
			iter.current_R31 = context->GPR[31].l[0];
		#else
			iter.current_R31 = context->GPR[31].l[1];
		#endif
	#else
		iter.current_R31 = context->GPR[31];
	#endif
		for(action=ExPPC_CurrentAction(&iter);; action=ExPPC_NextAction(&iter))
		{
			switch(action)
			{
			case EXACTION_ACTIVECATCHBLOCK:
				break;

			case EXACTION_ENDOFLIST:
			case EXACTION_DESTROYLOCAL:
			case EXACTION_DESTROYLOCALCOND:
			case EXACTION_DESTROYLOCALPOINTER:
			case EXACTION_DESTROYLOCALARRAY:
			case EXACTION_DESTROYBASE:
			case EXACTION_DESTROYMEMBER:
			case EXACTION_DESTROYMEMBERCOND:
			case EXACTION_DESTROYMEMBERARRAY:
			case EXACTION_DELETEPOINTER:
			case EXACTION_DELETEPOINTERCOND:
			case EXACTION_CATCHBLOCK:
			case EXACTION_CATCHBLOCK_32:
			case EXACTION_SPECIFICATION:
				continue;

			case EXACTION_TERMINATE:
			default:
				terminate();
			}
			break;
		}
		catchinfo=(CatchInfo *)(iter.current_FP+((ex_activecatchblock *)iter.info.action_pointer)->cinfo_ref);
		context->throwtype	= (char *)catchinfo->typeinfo;
		context->location	= catchinfo->location;
		context->dtor		= 0;
		context->catchinfo	= catchinfo;
	}
	else context->catchinfo=0L;

	iter.info		= info;
	iter.current_SP	= context->SP;
	iter.current_FP	= context->FP;
#if __PPCe500__
	#if (__option(little_endian))
		iter.current_R31 = context->GPR[31].l[0];
	#else
		iter.current_R31 = context->GPR[31].l[1];
	#endif
#else
	iter.current_R31 = context->GPR[31];
#endif
	for(action=ExPPC_CurrentAction(&iter);; action=ExPPC_NextAction(&iter))
	{
		switch(action)
		{
		case EXACTION_CATCHBLOCK_32:
			if(__throw_catch_compare(context->throwtype,((ex_catchblock_32 *)iter.info.action_pointer)->catch_type,&offset))
			{
				break;
			}
			continue;
		case EXACTION_CATCHBLOCK:
			if(__throw_catch_compare(context->throwtype,((ex_catchblock *)iter.info.action_pointer)->catch_type,&offset))
			{
				break;
			}
			continue;

		case EXACTION_SPECIFICATION:
			if(!ExPPC_IsInSpecification(context->throwtype,(ex_specification *)iter.info.action_pointer))
			{
				ExPPC_HandleUnexpected(context,&info,(ex_specification *)iter.info.action_pointer);
			}
			continue;

		case EXACTION_ENDOFLIST:
		case EXACTION_DESTROYLOCAL:
		case EXACTION_DESTROYLOCALCOND:
		case EXACTION_DESTROYLOCALPOINTER:
		case EXACTION_DESTROYLOCALARRAY:
		case EXACTION_DESTROYBASE:
		case EXACTION_DESTROYMEMBER:
		case EXACTION_DESTROYMEMBERCOND:
		case EXACTION_DESTROYMEMBERARRAY:
		case EXACTION_DELETEPOINTER:
		case EXACTION_DELETEPOINTERCOND:
		case EXACTION_ACTIVECATCHBLOCK:
			continue;

		case EXACTION_TERMINATE:
		default:
			terminate();
		}
		break;
	}

	if (action == EXACTION_CATCHBLOCK_32) {
		ex_catchblock_32	*catchblock_32;
		catchblock_32=(ex_catchblock_32 *)iter.info.action_pointer;

		ExPPC_UnwindStack(context,&info,catchblock_32);

		catchinfo=(CatchInfo *)(context->FP+catchblock_32->cinfo_ref);
		catchinfo->location		= context->location;
		catchinfo->typeinfo		= context->throwtype;
		catchinfo->dtor			= context->dtor;

		if(*context->throwtype=='*')
		{
			catchinfo->sublocation	= &catchinfo->pointercopy;
			catchinfo->pointercopy	= *(long *)context->location+offset;
		}
		else
		{
			catchinfo->sublocation	= (char *)context->location+offset;
		}

		ExPPC_LongJump(context,info.TOC,info.current_function+catchblock_32->catch_pcoffset);
	} else {
		ex_catchblock	*catchblock;

		catchblock=(ex_catchblock *)iter.info.action_pointer;
		ExPPC_UnwindStack(context,&info,catchblock);

		catchinfo=(CatchInfo *)(context->FP+catchblock->cinfo_ref);
		catchinfo->location		= context->location;
		catchinfo->typeinfo		= context->throwtype;
		catchinfo->dtor			= context->dtor;
		if(*context->throwtype=='*')
		{
			catchinfo->sublocation	= &catchinfo->pointercopy;
			catchinfo->pointercopy	= *(long *)context->location+offset;
		}
		else
		{
			catchinfo->sublocation	= (char *)context->location+offset;
		}

		ExPPC_LongJump(context,info.TOC,info.current_function+catchblock->catch_pcoffset);
	}
}

#if __VEC__
#pragma altivec_vrsave off

asm void __throw(char *throwtype, void *location, void *dtor)
{
		ThrowContext throwcontext;

#if __PPC_EABI__
#if !__option(use_lmw_stmw) || __option(little_endian)
		stw			r13,throwcontext.GPR[13]
		stw			r14,throwcontext.GPR[14]
		stw			r15,throwcontext.GPR[15]
		stw			r16,throwcontext.GPR[16]
		stw			r17,throwcontext.GPR[17]
		stw			r18,throwcontext.GPR[18]
		stw			r19,throwcontext.GPR[19]
		stw			r20,throwcontext.GPR[20]
		stw			r21,throwcontext.GPR[21]
		stw			r22,throwcontext.GPR[22]
		stw			r23,throwcontext.GPR[23]
		stw			r24,throwcontext.GPR[24]
		stw			r25,throwcontext.GPR[25]
		stw			r26,throwcontext.GPR[26]
		stw			r27,throwcontext.GPR[27]
		stw			r28,throwcontext.GPR[28]
		stw			r29,throwcontext.GPR[29]
		stw			r30,throwcontext.GPR[30]
		stw			r31,throwcontext.GPR[31]
	#else
		stmw		r13,throwcontext.GPR[13]
	#endif
#else
		stmw		r13,throwcontext.GPR[13]
#endif

#ifndef _No_Floating_Point_Regs
		stfd		fp14,throwcontext.FPR[14]
		stfd		fp15,throwcontext.FPR[15]
		stfd		fp16,throwcontext.FPR[16]
		stfd		fp17,throwcontext.FPR[17]
		stfd		fp18,throwcontext.FPR[18]
		stfd		fp19,throwcontext.FPR[19]
		stfd		fp20,throwcontext.FPR[20]
		stfd		fp21,throwcontext.FPR[21]
		stfd		fp22,throwcontext.FPR[22]
		stfd		fp23,throwcontext.FPR[23]
		stfd		fp24,throwcontext.FPR[24]
		stfd		fp25,throwcontext.FPR[25]
		stfd		fp26,throwcontext.FPR[26]
		stfd		fp27,throwcontext.FPR[27]
		stfd		fp28,throwcontext.FPR[28]
		stfd		fp29,throwcontext.FPR[29]
		stfd		fp30,throwcontext.FPR[30]
		stfd		fp31,throwcontext.FPR[31]
#endif

		mfcr		r3
		stw			r3,throwcontext.CR
		lwz			r3,0(sp)
		lwz			r4,RETURN_ADDRESS(r3)
		stw			r3,throwcontext.SP
		stw			r3,throwcontext.throwSP
		stw			r4,throwcontext.returnaddr
		lwz			r3,throwtype
		stw			r3,throwcontext.throwtype
		lwz			r3,location
		stw			r3,throwcontext.location
		lwz			r3,dtor
		stw			r3,throwcontext.dtor

#if !__PPC_EABI__
		mfvrsave 	r5

		bl			__setLR
__setLR:	

		stw			r5,throwcontext.vrsave
		clrlwi		r5,r5,20
		cntlzw		r5,r5
		slwi		r5,r5,3
		mflr		r4

		addi		r4,r4,__setjmpv20 - __setLR	- (20 * 8)
		add			r4,r4,r5
		mtlr		r4

		blr

__setjmpv20:		
#endif
		la 			r3,throwcontext.VR[20]
		stvx		vr20,r0,r3
		la 			r3,throwcontext.VR[21]
		stvx		vr21,r0,r3
		la 			r3,throwcontext.VR[22]
		stvx		vr22,r0,r3
		la 			r3,throwcontext.VR[23]
		stvx		vr23,r0,r3
		la 			r3,throwcontext.VR[24]
		stvx		vr24,r0,r3
		la 			r3,throwcontext.VR[25]
		stvx		vr25,r0,r3
		la 			r3,throwcontext.VR[26]
		stvx		vr26,r0,r3
		la 			r3,throwcontext.VR[27]
		stvx		vr27,r0,r3
		la 			r3,throwcontext.VR[28]
		stvx		vr28,r0,r3
		la 			r3,throwcontext.VR[29]
		stvx		vr29,r0,r3
		la 			r3,throwcontext.VR[30]
		stvx		vr30,r0,r3
		la 			r3,throwcontext.VR[31]
		stvx		vr31,r0,r3

		mfvrsave 	r6
		oris	 	r6,r6,0x8000
		mtvrsave 	r6

		mfvscr		vr0
		la 			r5,throwcontext.vscr
		stvewx		vr0,r0,r5

		li			r5,0x0000
		mtvrsave	r5

		la			r3,throwcontext
		bl			ExPPC_ThrowHandler
		nop
		frfree
		blr
}

#pragma debug_listing  off
#pragma altivec_vrsave reset

#else

asm void __throw(char *throwtype, void *location, void *dtor)
{
		ThrowContext throwcontext;

		fralloc

#if __PPC_EABI__
    #if __PPCe500__
		la 			r3,throwcontext.GPR[13]
		evstddx		r13, 0, r3
		la			r3,throwcontext.GPR[14]
		evstddx		r14, 0, r3
		la			r3,throwcontext.GPR[15]
		evstddx		r15, 0, r3
		la			r3,throwcontext.GPR[16]
		evstddx		r16, 0, r3
		la			r3,throwcontext.GPR[17]
		evstddx		r17, 0, r3
		la			r3,throwcontext.GPR[18]
		evstddx		r18, 0, r3
		la			r3,throwcontext.GPR[19]
		evstddx		r19, 0, r3
		la			r3,throwcontext.GPR[20]
		evstddx		r20, 0, r3
		la			r3,throwcontext.GPR[21]
		evstddx		r21, 0, r3
		la			r3,throwcontext.GPR[22]
		evstddx		r22, 0, r3
		la			r3,throwcontext.GPR[23]
		evstddx		r23, 0, r3
		la			r3,throwcontext.GPR[24]
		evstddx		r24, 0, r3
		la			r3,throwcontext.GPR[25]
		evstddx		r25, 0, r3
		la			r3,throwcontext.GPR[26]
		evstddx		r26, 0, r3
		la			r3,throwcontext.GPR[27]
		evstddx		r27, 0, r3
		la			r3,throwcontext.GPR[28]
		evstddx		r28, 0, r3
		la			r3,throwcontext.GPR[29]
		evstddx		r29, 0, r3
		la			r3,throwcontext.GPR[30]
		evstddx		r30, 0, r3
		la			r3,throwcontext.GPR[31]
		evstddx		r3, 0, r3
    #else
		#if !__option(use_lmw_stmw) || __option(little_endian)
			stw			r13,throwcontext.GPR[13]
			stw			r14,throwcontext.GPR[14]
			stw			r15,throwcontext.GPR[15]
			stw			r16,throwcontext.GPR[16]
			stw			r17,throwcontext.GPR[17]
			stw			r18,throwcontext.GPR[18]
			stw			r19,throwcontext.GPR[19]
			stw			r20,throwcontext.GPR[20]
			stw			r21,throwcontext.GPR[21]
			stw			r22,throwcontext.GPR[22]
			stw			r23,throwcontext.GPR[23]
			stw			r24,throwcontext.GPR[24]
			stw			r25,throwcontext.GPR[25]
			stw			r26,throwcontext.GPR[26]
			stw			r27,throwcontext.GPR[27]
			stw			r28,throwcontext.GPR[28]
			stw			r29,throwcontext.GPR[29]
			stw			r30,throwcontext.GPR[30]
			stw			r31,throwcontext.GPR[31]
		#else
			stmw		r13,throwcontext.GPR[13]
		#endif

	#endif

#else

	stmw		r13,throwcontext.GPR[13]
#endif

#ifndef _No_Floating_Point_Regs
#if __PPCGEKKO__
.machine gecko
		stfd		fp14,throwcontext.FPR[14].d
		la			r3,throwcontext.FPR[14].v
		psq_stx		fp14, 0, r3,0,0

		stfd		fp15,throwcontext.FPR[15].d
		la			r3,throwcontext.FPR[15].v
		psq_stx		fp15, 0, r3,0,0

		stfd		fp16,throwcontext.FPR[16].d
		la			r3,throwcontext.FPR[16].v
		psq_stx		fp16, 0, r3,0,0

		stfd		fp17,throwcontext.FPR[17].d
		la			r3,throwcontext.FPR[17].v
		psq_stx		fp17, 0, r3,0,0

		stfd		fp18,throwcontext.FPR[18].d
		la			r3,throwcontext.FPR[18].v
		psq_stx		fp18, 0, r3,0,0

		stfd		fp19,throwcontext.FPR[19].d
		la			r3,throwcontext.FPR[19].v
		psq_stx		fp19, 0, r3,0,0

		stfd		fp20,throwcontext.FPR[20].d
		la			r3,throwcontext.FPR[20].v
		psq_stx		fp20, 0, r3,0,0

		stfd		fp21,throwcontext.FPR[21].d
		la			r3,throwcontext.FPR[21].v
		psq_stx		fp21, 0, r3,0,0

		stfd		fp22,throwcontext.FPR[22].d
		la			r3,throwcontext.FPR[22].v
		psq_stx		fp22, 0, r3,0,0

		stfd		fp23,throwcontext.FPR[23].d
		la			r3,throwcontext.FPR[23].v
		psq_stx		fp23, 0, r3,0,0

		stfd		fp24,throwcontext.FPR[24].d
		la			r3,throwcontext.FPR[24].v
		psq_stx		fp24, 0, r3,0,0

		stfd		fp25,throwcontext.FPR[25].d
		la			r3,throwcontext.FPR[25].v
		psq_stx		fp25, 0, r3,0,0

		stfd		fp26,throwcontext.FPR[26].d
		la			r3,throwcontext.FPR[26].v
		psq_stx		fp26, 0, r3,0,0

		stfd		fp27,throwcontext.FPR[27].d
		la			r3,throwcontext.FPR[27].v
		psq_stx		fp27, 0, r3,0,0

		stfd		fp28,throwcontext.FPR[28].d
		la			r3,throwcontext.FPR[28].v
		psq_stx		fp28, 0, r3,0,0

		stfd		fp29,throwcontext.FPR[29].d
		la			r3,throwcontext.FPR[29].v
		psq_stx		fp29, 0, r3,0,0

		stfd		fp30,throwcontext.FPR[30].d
		la			r3,throwcontext.FPR[30].v
		psq_stx		fp30, 0, r3,0,0

		stfd		fp31,throwcontext.FPR[31].d
		la			r3,throwcontext.FPR[31].v
		psq_stx		fp31, 0, r3,0,0
#else
		stfd		fp14,throwcontext.FPR[14]
		stfd		fp15,throwcontext.FPR[15]
		stfd		fp16,throwcontext.FPR[16]
		stfd		fp17,throwcontext.FPR[17]
		stfd		fp18,throwcontext.FPR[18]
		stfd		fp19,throwcontext.FPR[19]
		stfd		fp20,throwcontext.FPR[20]
		stfd		fp21,throwcontext.FPR[21]
		stfd		fp22,throwcontext.FPR[22]
		stfd		fp23,throwcontext.FPR[23]
		stfd		fp24,throwcontext.FPR[24]
		stfd		fp25,throwcontext.FPR[25]
		stfd		fp26,throwcontext.FPR[26]
		stfd		fp27,throwcontext.FPR[27]
		stfd		fp28,throwcontext.FPR[28]
		stfd		fp29,throwcontext.FPR[29]
		stfd		fp30,throwcontext.FPR[30]
		stfd		fp31,throwcontext.FPR[31]
#endif
#endif
		mfcr		r3
		stw			r3,throwcontext.CR;
		lwz			r3,0(sp)
		lwz			r4,RETURN_ADDRESS(r3)
		stw			r3,throwcontext.SP;
		stw			r3,throwcontext.throwSP;
		stw			r4,throwcontext.returnaddr;
		lwz			r3,throwtype
		stw			r3,throwcontext.throwtype
		lwz			r3,location
		stw			r3,throwcontext.location
		lwz			r3,dtor
		stw			r3,throwcontext.dtor

		la			r3,throwcontext
		bl			ExPPC_ThrowHandler
		nop
		frfree
		blr
}

#endif

void __end__catch(CatchInfo *catchinfo)
{
	if (catchinfo->location && catchinfo->dtor)
		DTORCALL_COMPLETE(catchinfo->dtor,catchinfo->location);
}
