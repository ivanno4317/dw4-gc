#ifndef _STDIO_API_H
#define _STDIO_API_H

#include "types.h"
#include "file_struc.h"
#include <size_t.h>

enum __ReadProcActions { __GetAChar, __UngetAChar, __TestForError };

enum __WReadProcActions { __GetAwChar, __UngetAwChar, __TestForwcsError };

typedef struct {
	char* CharStr;
	size_t MaxCharCount;
	size_t CharsWritten;
} __OutStrCtrl;

typedef struct {
	char* NextChar;
	int NullCharDetected;
} __InStrCtrl;

typedef struct {
	wchar_t* wCharStr;
	size_t MaxCharCount;
	size_t CharsWritten;
} __wOutStrCtrl;

typedef struct {
	wchar_t* wNextChar;
	int wNullCharDetected;
} __wInStrCtrl;

size_t 		__fread(void *, size_t, size_t, FILE *);	
size_t __fwrite(const void* pPtr, size_t memb_size, size_t num_memb, FILE* pFile);
int __StringRead(void*, int, int);
// wint_t __wStringRead(void*, wint_t, int);

#endif // STDIO_API_H
