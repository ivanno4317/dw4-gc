#include <stdio.h>                        

enum {
	__align_buffer,
	__dont_align_buffer
};

//void __convert_from_newlines(unsigned char * p, __std(size_t) * n); 	
//void __convert_to_newlines  (unsigned char * p, __std(size_t) * n);
//void __prep_buffer (__std(FILE) *  );													
//int	 __load_buffer (__std(FILE) *  , __std(size_t) * bytes_loaded, int alignment);  	
int	 __flush_buffer(__std(FILE) *  , __std(size_t) * bytes_flushed);  					
