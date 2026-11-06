#ifndef _IGPAGEMEMORYPOOL_H_E2B63126_
#define _IGPAGEMEMORYPOOL_H_E2B63126_

#include <igCore/igObject.h>
#include <igCore/igMemoryPool.h>

namespace Gap {
namespace Core {

class igPageMemoryPool : public igMemoryPool
{
	IG_BOOTSTRAP_OBJECT_DEFINE(igPageMemoryPool);
};

}
}
#endif
