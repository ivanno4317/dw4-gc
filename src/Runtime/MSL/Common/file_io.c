#include <stdio.h>
#include <stdlib.h>
#include "ansi_files.h"
#include "buffer_io.h"
#include "critical_regions.h"
#include "file_io.h"
#include "misc_io.h"
#include <ctype.h>
#include <string.h>

int fclose(FILE * file)
{
	int	flush_result, close_result;
	
	if (file == NULL)              
		return(EOF);               
	if (file->mode.file_kind == __closed_file)
		return(0);
	
	flush_result = fflush(file);
	
	close_result = (*file->close_proc)(file->handle);
	
	file->mode.file_kind = __closed_file;
	file->handle         = 0;
	
	if (file->state.free_buffer)
		free(file->buffer);

	return((flush_result || close_result) ? EOF : 0);
}

int fflush(FILE * file)
{
	fpos_t	position;                   
	
	if (!file)
		return(__flush_all());
	
	if (file->state.error || file->mode.file_kind == __closed_file)
		return(EOF);
	
	if (file->mode.io_mode == __read)	
		return 0;						
	
	if (file->state.io_state >= __rereading)
		file->state.io_state = __reading;
	
	if (file->state.io_state == __reading)
		file->buffer_len = 0;
	
	if (file->state.io_state != __writing)
	{
		file->state.io_state = __neutral; 
		return(0);
	}

	if (file->mode.file_kind != __disk_file || (position = ftell(file)) < 0)
		position = 0;

	if (__flush_buffer(file, NULL))
	{
		set_error(file);
		return(EOF);
	}
	
	file->state.io_state = __neutral;
	file->position       = position;
	file->buffer_len     = 0;
	
	return(0);
}


