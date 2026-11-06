#ifndef __IG_OBJECT_H__
#define __IG_OBJECT_H__

#include <igCore/igObjectMacros.h>

namespace Gap{
namespace Core {

    class igObject{

        friend class igArkCore;

        public:
            static void	arkRegister();

        public:
            enum CopyMethod { kShallowCopy, kDeepCopy, kConstructCopy };
            virtual igObject*	createCopy(CopyMethod copyMethod=kDeepCopy) const;


    };


}
}


#endif
