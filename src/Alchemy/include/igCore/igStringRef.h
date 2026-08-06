#ifndef _IG_STRINGREF_H_
#define _IG_STRINGREF_H_

#include <igCore/igStringPoolItem.h>

namespace Gap {
    namespace Core {
        //class igStringPool;

        class igStringRef{
            private:
                const igChar* _string;

                inline igBool isPooled() const{ return _string != NULL;}
                inline void release() const { if (isPooled()) getId()->release(); }
        
            public:
            
                inline igStringPoolItemId getId() const
                {
                    return (igStringPoolItemId)(_string-sizeof(igStringPoolItem));
                }

                inline ~igStringRef()
                {
                    release();
                }
        
        
        
        };
    }
}

#endif 
