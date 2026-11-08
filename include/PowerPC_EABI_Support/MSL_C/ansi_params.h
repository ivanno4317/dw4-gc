#ifndef _MSL_ANSI_PARMS_H
#define _MSL_ANSI_PARMS_H

#ifdef __cplusplus
	#define _MSL_BEGIN_EXTERN_C extern "C" {
	#define _MSL_END_EXTERN_C }
	
	#ifdef _MSL_USING_NAMESPACE
		#define _MSL_BEGIN_NAMESPACE_STD namespace std {
		#define _MSL_END_NAMESPACE_STD }
		
		#define __std(ref) ::std::ref
		#define __global() ::
	#else
		#define _MSL_BEGIN_NAMESPACE_STD
		#define _MSL_END_NAMESPACE_STD
		
		#define __std(ref) ref
		#define __global()
	#endif
#else
