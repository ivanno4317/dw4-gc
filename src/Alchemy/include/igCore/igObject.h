#ifndef __IG_OBJECT_H__
#define __IG_OBJECT_H__

#include <igCore.h>
#include <igCore/igObjectMacros.h>

namespace Gap{
    namespace Core { class igMemoryPool; }
}

namespace Gap{
namespace Core {

class igObject
{

    friend class igArkCore;

    public:
        static void	arkRegister();

    public:
	    igMemoryRef realloc(igMemoryRef ptr, igUnsignedInt n) const;
        void free(igMemoryRef ptr) const;

    public:
        enum CopyMethod { kShallowCopy, kDeepCopy, kConstructCopy };
        virtual igObject*	createCopy(CopyMethod copyMethod=kDeepCopy) const;

    public:
        igMemoryPool* getMemoryPool() const;

    protected:

        #define IG_OBJECT_MEMORY_POOL_INDEX_BITS 8
                
    	union
        {
            mutable igUnsignedInt _both;
            struct
            {
                igUnsignedInt _memPoolIndex : IG_OBJECT_MEMORY_POOL_INDEX_BITS;
                mutable igUnsignedInt _scriptFlag : 1;
                mutable igUnsignedInt _refCount : 22;
            } _either;
        } _refAndMemPool;

};


}
}


#endif
