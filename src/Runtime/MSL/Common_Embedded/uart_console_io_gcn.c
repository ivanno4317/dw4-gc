#include "types.h"

s32 InitializeUART(u32);                     
s32 OSGetConsoleType();                      
s32 WriteUARTN(s32, s32);                    
s32 __TRK_write_console(s32, s32, s32*, s32);

BOOL __write_console(s32 arg0, s32 arg1, s32* arg2, s32 arg3)
{
	static BOOL initialized;

	if ((OSGetConsoleType() & 0x20000000) == 0) {
		int ret = 0;
		if (initialized == 0) {
			ret = InitializeUART(0xE100);
			if (ret == 0) {
				initialized = 1;
			}
		}
		if (ret != 0) {
			return TRUE;
		}
		if (WriteUARTN(arg1, *arg2) != 0) {
			*arg2 = 0;
			return TRUE;
		}
	}
	__TRK_write_console(arg0, arg1, arg2, arg3);
	return FALSE;
}

int __close_console()
{
	return 0;
}

BOOL __read_console(s32 arg0, s32 arg1, s32* arg2, s32 arg3)
{
	return 0;
}
