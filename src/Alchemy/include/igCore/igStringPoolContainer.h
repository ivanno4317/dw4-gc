#ifndef _IGSTRINGPOOLCONTAINER_H_
#define _IGSTRINGPOOLCONTAINER_H_

#include <igGap.h>

namespace Gap {
    namespace Core {

        class igStringPoolItem;

        class igStringPoolContainer{
            private:
                igChar _memoryPool;

            public:
                void internalRelease(const igStringPoolItem* id);
        };
    }
}

#endif
