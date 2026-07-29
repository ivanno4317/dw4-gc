#ifndef _MSL_CSTDIO
#define _MSL_CSTDIO

#include "file_struc.h"
#include "stdarg.h"
#include "stddef.h"
#include "eof.h"

#ifdef __cplusplus
namespace std {
extern "C" {
#endif

FILE * fopen(const char* path, const char* mode);
FILE * freopen(const char * , const char * , FILE *  );

int fclose(FILE* stream);
size_t fread(void* ptr, size_t size, size_t n, FILE * file);
size_t fwrite(const void* ptr, size_t size, size_t n, FILE * stream);
char* fgets(char* s, int size, FILE* stream);


int fputs(const char* s, FILE* stream);

int feof(void* stream);
//int fseek(void* stream, long offset, int whence);
//int fflush(void* stream);
//int			fflush(FILE *  );
int fwide(FILE *stream, int mode);
//long ftell(void* stream);

int fprintf(FILE* stream, const char* format, ...);
int sprintf(char* str, const char* fmt, ...);
int vsprintf(char* str, const char* format, va_list ap);
int sscanf(const char* str, const char* format, ...);

int		putc(int c, FILE *  );

#define putc(c, file)	((fwide(file, -1) >= 0) ? EOF :\
    (file)->buffer_len-- ? (int) (*(file)->buffer_ptr++ = (unsigned char)(c)) : __std(__put_char)(c, file)) /*- mm 990202 -*/ /*- mm 990728 -*/


#ifdef __cplusplus
}
}

using std::fopen;
using std::fclose;
using std::fread;
using std::fwrite;
using std::fgets;
using std::fputs;
using std::feof;
using std::fseek;
using std::fflush;
using std::ftell;
using std::fprintf;
using std::sprintf;
using std::vsprintf;
using std::sscanf;
#endif

#endif
