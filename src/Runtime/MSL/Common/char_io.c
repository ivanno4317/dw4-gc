#include <stdio.h>
#include "ansi_files.h"
#include "buffer_io.h"
#include "char_io.h"
#include "misc_io.h"
#include "critical_regions.h"					

int __put_char(int c, FILE * file)
{
	int	kind = file->mode.file_kind;
	
	file->buffer_len = 0;
	
	if (file->state.error || kind == __closed_file)
		return(EOF);
	
	if (kind == __console_file)
		__stdio_atexit();
	
	if (file->state.io_state == __neutral)
		if (file->mode.io_mode & __write)
		{

			if (file->mode.io_mode & __append)
				if (fseek(file, 0, SEEK_END))
					return(0);

			
			file->state.io_state = __writing;
			
			__prep_buffer(file);
		}
	
	if (file->state.io_state != __writing)
	{
		set_error(file);
		return(EOF);
	}
	
	if (file->mode.buffer_mode == _IOFBF || file->buffer_ptr - file->buffer == file->buffer_size)
		if (__flush_buffer(file, NULL))
		{
			set_error(file);
			return(EOF);
		}
	
	 file->buffer_len--;
	*file->buffer_ptr++ = c;
	
	if (file->mode.buffer_mode != _IOFBF)
	{
		if ((file->mode.buffer_mode == _IONBF || c == '\n'))
			if (__flush_buffer(file, NULL))
			{
				set_error(file);
				return(EOF);
			}
		
		file->buffer_len = 0;
	}
	
	return((unsigned char) c);
}

int fputs(const char * s, FILE * file)
{
	int	c;
	int retval = 0;								
  	__begin_critical_region(files_access);		
	while ((c = *s++) != 0)
		if (putc(c, file) == EOF)
		{
			retval = EOF;						
			break;								
		}
  	__end_critical_region(files_access);		
	return(retval);								
}

