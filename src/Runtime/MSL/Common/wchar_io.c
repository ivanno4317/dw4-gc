#include "types.h"

#ifndef _MSL_WIDE_CHAR
#define _MSL_WIDE_CHAR
#endif

#include "ansi_files.h"

int fwide(FILE* stream, int mode)
{
    int res;
    int orientation;

    if (stream == NULL || stream->file_mode.file_kind == __closed_file)
        return 0;

    orientation = stream->file_mode.file_orientation;
    switch (orientation)
    {
    case __unoriented:
        if (mode > 0)
            stream->file_mode.file_orientation = __wide_oriented;
        else if (mode < 0)
            stream->file_mode.file_orientation = __char_oriented;

        res = mode;
        break;

    case __wide_oriented:
        res = 1;
        break;

    case __char_oriented:
        res = -1;
        break;
    }
    return res;
}
