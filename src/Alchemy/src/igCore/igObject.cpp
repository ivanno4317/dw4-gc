#include <igGap.h>
#include <igCore/igCoreAll.h>

namespace Gap{
namespace Core{

igMemoryRef igObject::realloc(igMemoryRef ptr, igUnsignedInt n) const{

    igMemoryPool *memoryPool;
    memoryPool = igObject::getMemoryPool();
}

void igObject::free(igMemoryRef ptr) const{
    igMemoryPool *memoryPool;

    if(ptr != NULL){
        memoryPool = igObject::getMemoryPool();
    }
}

igMemoryPool* igObject::getMemoryPool() const{
    return igMemoryPool::getMemoryPoolByIndex(_refAndMemPool._either._memPoolIndex);
}

}
}
