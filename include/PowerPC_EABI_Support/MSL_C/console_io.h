#ifndef _MSL_CONSOLE_IO_H
#define _MSL_CONSOLE_IO_H

#include <ansi_parms.h>            
#include <stdio.h>               	

int	__read_console	  (__std(__file_handle) handle, unsigned char * buffer, __std(size_t) * count, __std(__idle_proc) idle_proc);
int	__write_console	  (__std(__file_handle) handle, unsigned char * buffer, __std(size_t) * count, __std(__idle_proc) idle_proc);
int	__close_console	  (__std(__file_handle) handle);

#endif