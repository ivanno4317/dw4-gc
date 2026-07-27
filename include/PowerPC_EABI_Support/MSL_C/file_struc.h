#ifndef _FILE_STRUCT_H
#define _FILE_STRUCT_H

#include <cstddef>

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

typedef unsigned long __file_handle;
typedef unsigned long fpos_t;

enum __file_kinds 
{
	__closed_file,
	__disk_file,
	__console_file,
	__unavailable_file
};

enum __file_orientation
{
    __unoriented,
    __char_oriented,
    __wide_oriented
};

typedef struct 
{
	unsigned int	open_mode		: 2;
	unsigned int	io_mode			: 3;
	unsigned int	buffer_mode		: 2;
	unsigned int	file_kind		: 3;
    unsigned int	file_orientation: 2;
	unsigned int	binary_io		: 1;
} __file_modes;

typedef struct 
{
	unsigned int	io_state	: 3;
	unsigned int	free_buffer	: 1;
	unsigned char	eof;
	unsigned char	error;
} __file_state;

#define __ungetc_buffer_size	2

typedef void (* __idle_proc)  (void);
typedef int  (* __pos_proc)   (__file_handle file, fpos_t * position, int mode, __idle_proc idle_proc);
typedef int  (* __io_proc)    (__file_handle file, unsigned char * buff, size_t * count, __idle_proc idle_proc);
typedef int	 (* __close_proc) (__file_handle file);

struct _FILE {
	__file_handle		handle;
	__file_modes		mode;
	__file_state		state;
    unsigned char       is_dynamically_allocated;
	unsigned char		char_buffer;
	unsigned char		char_buffer_overflow;
	unsigned char		ungetc_buffer[__ungetc_buffer_size];
    unsigned short      ungetwc_buffer[__ungetc_buffer_size];
	unsigned long		position;
	unsigned char *		buffer;
	unsigned long		buffer_size;
	unsigned char *		buffer_ptr;
	unsigned long		buffer_len;
	unsigned long		buffer_alignment;
	unsigned long		saved_buffer_len;
	unsigned long		buffer_pos;
	__pos_proc			position_proc;
	__io_proc			read_proc;
	__io_proc			write_proc;
	__close_proc		close_proc;
	__idle_proc			idle_proc;
    struct _FILE *      next_file_struct;
};

typedef struct _FILE FILE;

typedef struct _files {
    FILE _stdin;
    FILE _stdout;
    FILE _stderr;
    FILE empty;
} files;

#define stdin &__files._stdin
#define stdout &__files._stdout
#define stderr &__files._stderr

extern files __files;

#endif /* _FILE_STRUCT_H */