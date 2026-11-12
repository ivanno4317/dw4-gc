#ifndef _IG_STRINGREF_H_
#define _IG_STRINGREF_H_

#include <igCore/igInternalStringPool.h>
#include <igCore/igStringPoolItem.h>

namespace Gap {
namespace Core {

    class igStringRef{

        private:
            const igChar* _string;

            inline igBool isPooled() const{ return _string != NULL;}

            inline void ref() const { if (isPooled()) getId()->ref(); }
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

            inline igStringRef() : 
                _string(NULL)
            {
            }
            
            inline igStringRef(igString string) : 
            _string((string == NULL) ? NULL : igInternalStringPool::getDefault()->setString(string))
            {
            }
    
            inline const igStringRef& operator= (const igStringRef& other) 
            {
                other.ref();
                release();
                _string = other._string;
                return *this;
            }
            
            inline const igStringRef& operator= (igString string) 
            {
                igString data = igInternalStringPool::getDefault()->setString(string);
                release();
                _string = data;
                return *this;
            }
                
    };
}
}

#endif 
