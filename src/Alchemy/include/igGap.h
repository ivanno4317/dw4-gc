#ifndef _IGGAP_H_F4505F75_
#define _IGGAP_H_F4505F75_

#define IG_ALCHEMY_VERSION 3200
#define NULL 0

namespace Gap {
    namespace Core{
        class igMemory;
		typedef igMemory* igMemoryRef;
        typedef const igMemory* igConstMemoryRef;
    }
}

namespace Gap {

    typedef bool			igBool;
    typedef char			igChar;
    typedef int				igInt;
    typedef unsigned int	igUnsignedInt;
    
    typedef unsigned long long   igUnsignedLong;

}

#endif
