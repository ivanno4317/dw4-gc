#ifndef _MSL_ANSI_FILES_H
#define _MSL_ANSI_FILES_H

#include <ansi_parms.h>  
#include <stdio.h>

#define set_eof(file)					\
do										\
{										\
	(file)->state.io_state = __neutral;	\
	(file)->state.eof = 1;				\
	(file)->buffer_len = 0;				\
}										\
while (0)

#define set_error(file)			\
do								\
{								\
	(file)->state.error = 1;	\
	(file)->buffer_len = 0;		\
}								\
while (0)



#define console_buff_mode	_IOLBF

#define console_buff_size	256

typedef unsigned char	console_buff[console_buff_size];


__std(FILE) *	__find_unopened_file(void); 	/*- hh 990121 -*/
void			__init_file(__std(FILE) *  , __std(__file_modes) mode, char * buff, __std(size_t)  ); /*- mf 990715 -*/
void			__close_all(void);
int				__flush_all(void);
int 			__flush_line_buffered_output_files(void);


#endif