#ifndef __IGPRIVATEREPORTHANDLERMACROS_H__
#define __IGPRIVATEREPORTHANDLERMACROS_H__


#define IG_PRIVATE_REPORT_MACRO(Type, X) \
 { \
     int igret = ::igReport##Type X ; \
     if (igret == IG_REPORT_RETURN_DEBUG) { \
       IG_PRIVATE_REPORT_MACRO_DEBUG_BREAK \
     } \
 }


#define IG_PRIVATE_REPORT_ERROR(X) IG_PRIVATE_REPORT_MACRO(Error, X)

#endif
