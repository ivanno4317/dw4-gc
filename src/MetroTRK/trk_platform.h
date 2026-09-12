/* Compatibility shim: the reference MetroTRK source (adapted from the
 * matched decompilation of a different GC title, which links this library
 * unmodified since it's Metrowerks/Nintendo SDK boilerplate rather than
 * game-specific code) expects a deeper <Runtime/platform.h>-style include
 * tree that this project doesn't have. Bridges to this project's own
 * top-level include/types.h instead -- only type availability matters for
 * byte-identical codegen, not which header technically provided it.
 */
#ifndef _METROTRK_TRK_PLATFORM_H
#define _METROTRK_TRK_PLATFORM_H

#include <dolphin/types.h>

typedef int bool;
#define true 1
#define false 0

#endif
