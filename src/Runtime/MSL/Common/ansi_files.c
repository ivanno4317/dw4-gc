#include <stdio.h>
#include "console_io.h"
#include "ansi_files.h"

#include "critical_regions.h"
#include "file_io.h"
#include <stdlib.h>  
#include <string.h> 

static console_buff	stdin_buff;
static console_buff	stdout_buff;
static console_buff	stderr_buff;

	FILE	__files[_STATIC_FILES] =   
	{
		{
			0,											
			{											
				__must_exist,							
				__read,									
				console_buff_mode,						   
				__console_file,							
				__unoriented,							
				0										
			},
			{																	
				__neutral, 		
				0,										
				0,										
				0										
			},										
			0,											 											
			0,											
			0,											
			{0, 0},											
			{0, 0},										
			0,											
			stdin_buff,									
			console_buff_size,							
			stdin_buff,									
			0,											
			0,											
			0,											
			0,											
			0,																		
			__read_console,								
			__write_console,							
			__close_console,							
			0,																
			&__files[1]																		
		},
		{
			1,											
			{											
				__must_exist,							
				__write,								
				console_buff_mode,						       
				__console_file,							
				__unoriented,								
				0										
			},
			{																							
				__neutral,								
				0,										
				0,										
				0										
			},										
			0,											 										
			0,											
			0,											
			{0, 0},																								
			{0, 0},																						
			0,											
			stdout_buff,								
			console_buff_size,							
			stdout_buff,								
			0,											
			0,											
			0,											
			0,											
			0,											
			__read_console,								
			__write_console,							
			__close_console,							
			0,																					
			&__files[2]																		
		},
		{
			2,											
			{											
				__must_exist,							
				__write,								
				_IONBF,									  
				__console_file,								
				__unoriented,							
				0										
			},
			{											
				__neutral,
				0,										
				0,										
				0										
			},											
			0,											 											
			0,											
			0,											
			{0, 0},											
			{0, 0},										
			0,											
			stderr_buff,								
			console_buff_size,							
			stderr_buff,								
			0,											
			0,											
			0,											
			0,											
			0,											
			__read_console,								
			__write_console,							
			__close_console,							
			0,																							
			&__files[3]																							
		},
	};

#ifndef _No_Disk_File_OS_Support
FILE * __find_unopened_file(void)
{
	FILE *	p = __files[2].next_file_struct;
	FILE *  plast;							
	
	while(p != NULL)   	
	{
		if (p->mode.file_kind == __closed_file)
			return(p);
		else								
		{									
			plast = p;						
			p = p->next_file_struct;		
		}									
	}
	
	if ((p = malloc(sizeof (FILE))) != NULL)
	{										
		memset((void *)p, 0, sizeof(FILE));	
		p->is_dynamically_allocated = 1;	
		plast->next_file_struct = p;		
		return(p);							
	}
	return(NULL);
}
#endif

void __init_file(FILE * file, __file_modes mode, char * buff, size_t size)
{
	file->handle            = 0;
	file->mode              = mode;
	file->state.io_state    = __neutral;
	file->state.free_buffer = 0;
	file->state.eof         = 0;
	file->state.error       = 0;
	file->position          = 0;
	
	if (size)
		setvbuf(file, buff, _IOFBF, size);
	else
		setvbuf(file, 0,    _IONBF, 0);
	
	file->buffer_ptr = file->buffer;
	file->buffer_len = 0;
	
#ifndef _No_Disk_File_OS_Support
	if (file->mode.file_kind  == __disk_file)				
	{
		file->position_proc    = __position_file;
		file->read_proc        = __read_file;
		file->write_proc       = __write_file;
		file->close_proc       = __close_file;
	}
#endif

	file->idle_proc = 0;
}

void __close_all(void)
{
	FILE *	p = &__files[0];								
	FILE *  plast;											
#ifdef _No_Disk_File_OS_Support								
#pragma unused(plast)
	int file_index = 1;										
#endif						
	
	__begin_critical_region(files_access);
	
	while(p != NULL)   										
	{
		if (p->mode.file_kind != __closed_file) 			
			fclose(p);
#ifndef _No_Disk_File_OS_Support							
		plast = p;											
		p     = p->next_file_struct;						
		if (plast->is_dynamically_allocated)				
			free(plast);									
		else												
		{													
			plast->mode.file_kind = __unavailable_file;		
			if ((p != NULL) && p->is_dynamically_allocated)	
				plast->next_file_struct = NULL;				
		}													
#else														
		if (file_index < _STATIC_FILES)						
			p = &__files[file_index++];						
		else												
			p = NULL;										
#endif						
	}
	
	__end_critical_region(files_access);
}

int __flush_all(void)
{
	int		result = 0;
	FILE *	p = &__files[0];								
#ifdef _No_Disk_File_OS_Support								
	int file_index = 1;										
#endif						
	
	while (p != NULL)										
	{
		if (p->mode.file_kind != __closed_file)
			if (fflush(p))
				result = EOF;
#ifndef _No_Disk_File_OS_Support							
		p = p->next_file_struct;							
#else														
		if (file_index < _STATIC_FILES)						
			p = &__files[file_index++];						
		else												
			p = NULL;										
#endif						
	}
	
	return(result);
}

int __flush_line_buffered_output_files(void)
{
	int		result = 0;										
	FILE *	p = &__files[0];								
#ifdef _No_Disk_File_OS_Support								
	int file_index = 1;										
#endif						
	
	while (p != NULL)										
	{
		if (p->mode.file_kind != __closed_file  &&
			(p->mode.buffer_mode & _IOLBF)  &&
			p->state.io_state == __writing) 
		{
			if (fflush(p)) 
			{
				result = EOF;
			}
		}
#ifndef _No_Disk_File_OS_Support							
		p = p->next_file_struct;							
#else														
		if (file_index < _STATIC_FILES)						
			p = &__files[file_index++];						
		else												
			p = NULL;										
#endif						
	}
	
	return(result);
}
