#ifndef _IGGAMECUBECALLSTACKTRACER_H_
#define _IGGAMECUBECALLSTACKTRACER_H_

#include <igCore/igObject.h>
#include <igCore/igCallStackTracer.h>

/* Entirely new header file. It's platform specific and it's missing form the SDK
    At least there is igWin32CallStackTracer.h to help. 
*/

namespace Gap {
namespace Core {

class igGameCubeCallStackTracer : public igCallStackTracer
{
	IG_OBJECT_DEFINE(igGameCubeCallStackTracer);
};

}
}

#endif
