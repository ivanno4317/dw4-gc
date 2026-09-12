#include <igCore/igCoreAll.h>
#include <igGap.h>

extern "C" {
    void *malloc(unsigned long size);
    void free(void *ptr);
}

namespace Gap{
    namespace Core{

        void *igArkCore::operator new(size_t size){
            return malloc(size);
        }

        void igArkCore::operator delete(void *ptr){
            free(ptr);
        }

    }
}
