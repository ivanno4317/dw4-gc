#include <stdlib.h>
#include <string.h>
#include <stddef.h>           					
#include "buffer_io.h"
#include "critical_regions.h"					

extern int txtbinFlag;

void __convert_from_newlines(unsigned char * buf, size_t * n)   
{                                                               
	unsigned char *	p = buf;                                    
	size_t			i = *n;                                     
	while (i--)                                                 
	{                                                           
		if (*p=='\r') *p = '\n';                                
		else if (*p=='\n') *p = '\r';                           
		p++;                                                    
	}                                                           
}

void __convert_to_newlines(unsigned char * buf, size_t * n)     
{                                                               
	unsigned char *	p = buf;                                    
	size_t			i = *n;                                     
	while (i--)                                                 
	{                                                           
		if (*p=='\n') *p = '\r';                                
		else if (*p=='\r') *p = '\n';                           
		p++;                                                    
	}                                                           
}

void __prep_buffer(FILE * file)
{
	file->buffer_ptr    = file->buffer;
	file->buffer_len    = file->buffer_size;	
	file->buffer_len   -= file->position & file->buffer_alignment;
	file->buffer_pos    = file->position;
}

int __load_buffer(FILE * file, size_t * bytes_loaded, int alignment)
{
	int	ioresult;
	
	__prep_buffer(file);
	
	if (alignment == __dont_align_buffer)
		file->buffer_len = file->buffer_size;	
		
	ioresult = (*file->read_proc)(file->handle, file->buffer, (size_t *) &file->buffer_len, file->idle_proc);
	
	if (ioresult == __io_EOF)     							
		file->buffer_len = 0;
	
	if (bytes_loaded)
		*bytes_loaded = file->buffer_len;
	
	if (ioresult)
		return(ioresult);
	
	file->position += file->buffer_len;
  
	if (!file->mode.binary_io)
	{
		ptrdiff_t		n = file->buffer_len;
		unsigned char *	p = file->buffer;
		
		while (n--)                    						
			if (*p++ == '\n')
				file->position++;
	}

	return(__no_io_error);
}

int __flush_buffer(FILE * file, size_t * bytes_flushed)
{
	size_t buffer_len;
	int ioresult;

	buffer_len = file->buffer_ptr - file->buffer;
	
	if (buffer_len)
	{
		file->buffer_len = buffer_len;
		
		ioresult = (*file->write_proc)(file->handle, file->buffer, (size_t *) &file->buffer_len, file->idle_proc);
		
		if (bytes_flushed)
			*bytes_flushed = file->buffer_len;
		
		if (ioresult)
			return(ioresult);
		
		file->position += file->buffer_len;
	}
	
	__prep_buffer(file);
	
	return(__no_io_error);
}

