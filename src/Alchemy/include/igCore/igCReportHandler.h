#ifndef __IGCREPORTHANDLER_H__
#define __IGCREPORTHANDLER_H__

#ifdef __cplusplus
extern "C" {
#endif

#define IG_REPORT_RETURN_DEBUG     1
#define IG_REPORT_RETURN_NOT_AGAIN 2

int igReportError(const char *format, ...);

#ifdef __cplusplus
}
#endif


#endif
