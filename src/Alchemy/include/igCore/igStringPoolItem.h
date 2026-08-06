#ifndef _IG_STRINGPOOLITEM_H_
#define _IG_STRINGPOOLITEM_H_

#include <igCore/igAtomic.h>
#include <igCore/igStringPoolContainer.h>

namespace Gap {
    namespace Core {


        class igStringPoolItem {

            private:
                igStringPoolContainer* _pool;
                mutable igAtomicUnsignedInt _refCount;
                
                igStringPoolItem();
                igStringPoolItem( const igStringPoolItem& that );
                igStringPoolItem& operator=( const igStringPoolItem& that );


            public:
                inline void release() const { 
                    if ( --_refCount == 0) 
                        _pool->internalRelease(this);
                }
        };

                
        typedef const igStringPoolItem* igStringPoolItemId;
    }
}

#endif
