#ifndef _IGATOMIC_H_394A7AC6_
#define _IGATOMIC_H_394A7AC6_

#include <igGap.h>

namespace Gap {
    namespace Core {

        template <class T>

        class igAtomic{
            protected:
                T _data;

            public:
                igAtomic();

                T operator--()
                {
                    return --_data;
                }
        };




        typedef igAtomic<igInt> igAtomicInt;
        typedef igAtomic<igUnsignedInt> igAtomicUnsignedInt;
    }
}

#endif
