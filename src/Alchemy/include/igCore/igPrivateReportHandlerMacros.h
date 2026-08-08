#ifndef __IGPRIVATEREPORTHANDLERMACROS_H__
#define __IGPRIVATEREPORTHANDLERMACROS_H__

#define ASSERTLINE(line, cond) (void)0
#define ASSERT(cond) ASSERTLINE(__LINE__, cond)

#define IG_PRIVATE_REPORT_MACRO_DEBUG_BREAK ASSERT(0);

/*
#define IG_PRIVATE_REPORT_MACRO(Type, X) \
{ \
    int igret = ::igReport##Type X ; \
    if (igret == IG_REPORT_RETURN_DEBUG) { \
      IG_PRIVATE_REPORT_MACRO_DEBUG_BREAK \
    } \
} 
*/

 #define IG_PRIVATE_REPORT_MACRO(Type, X) \
 { \
   static bool igonce; \
   if (!igonce) { \
     int igret = ::igReport##Type X ; \
     if (igret == IG_REPORT_RETURN_DEBUG) { \
       IG_PRIVATE_REPORT_MACRO_DEBUG_BREAK \
     } else if (igret == IG_REPORT_RETURN_NOT_AGAIN) { \
       igonce = true; \
     } \
   } \
 }


#define IG_PRIVATE_REPORT_ERROR(X) IG_PRIVATE_REPORT_MACRO(Error, X)

#endif
