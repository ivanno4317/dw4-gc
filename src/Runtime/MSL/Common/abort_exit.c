#include <ansi_parms.h>
#include <abort_exit.h>
#include <critical_regions.h>
#include <misc_io.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#define max_funcs	64
#define SIGABRT		1
#define EXIT_FAILURE			1

extern void __destroy_global_chain(void);

int	__aborting = 0;       									
											
void (*__atexit_funcs[max_funcs])(void);
long	__atexit_curr_func = 0;
extern int __atexit(void (*func)(void));


void (* __stdio_exit)  (void) = 0;
void (* __console_exit)(void) = 0;


void abort(void)
{
	raise(SIGABRT);
	__aborting = 1;
	exit(EXIT_FAILURE);
}

int __register_atexit(void (*func)(void));

int atexit(void (*func)(void))
{	
	int result;
	__begin_critical_region(atexit_funcs_access);
	__setup_exit();
	result = __register_atexit(func);
	__end_critical_region(atexit_funcs_access);
	return(result);
}
									
void exit(int status){
    if (!__aborting)
	{
		__begin_critical_region(atexit_funcs_access);
		__end_critical_region(atexit_funcs_access);
		__destroy_global_chain();
	 
		{
			typedef void (*voidfunctionptr) (void);
			extern voidfunctionptr _dtors[];
			voidfunctionptr *destructor;

			for (destructor = _dtors; *destructor; destructor++) {
			(*destructor)();
			}
		}
				if (__stdio_exit)
		{
			(*__stdio_exit)();
			__stdio_exit = 0;
		}
	}
	__exit(status);
}

void __exit(int status)
{
	#pragma unused(status)
	
	__begin_critical_region(atexit_funcs_access);
		while (__atexit_curr_func > 0)
			(*__atexit_funcs[--__atexit_curr_func])();

	__end_critical_region(atexit_funcs_access);
	__kill_critical_regions(); 

	if (__console_exit)
	{
		(*__console_exit)();
		__console_exit = 0;
	}
	_ExitProcess();													
}
