/* Metrowerks Standard Library
 * Copyright 1995-2001 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2001/10/22 18:55:55 $
 * $Revision: 1.19 $
 */

#ifndef _MSL_CHAR_IO_H
#define _MSL_CHAR_IO_H

#include <ansi_parms.h>                  				
#include <stdio.h>                        				


	
int	__ungotten(__std(FILE) *  );



#endif /* _MSL_CHAR_IO_H */

/* Change record:
 * hh  971206 namespace support
 * hh  990121 fixed __std
 * mf  990715 Arg names in prototype cause conflicts
 * cc  010405 removed pragma options align native and reset
 * cc  010409 updated defines to JWW new namespace macros
 * JWW 010618 Use cname headers exclusively to prevent namespace pollution in C++
 */