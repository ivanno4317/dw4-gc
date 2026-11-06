#ifndef _IGMALLOCMEMORYPOOL_H
#define _IGMALLOCMEMORYPOOL_H

#include <igCore/igObject.h>

namespace Gap {
namespace Core {

class igMallocMemoryPool : public igMemoryPool
{
    IG_BOOTSTRAP_OBJECT_DEFINE(igMallocMemoryPool);
};

}
}

#endif
