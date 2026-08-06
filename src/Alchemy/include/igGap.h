#ifndef _IGGAP_H_F4505F75_
#define _IGGAP_H_F4505F75_

#define IG_ALCHEMY_VERSION 5000

#define NULL 0

namespace Gap{

    typedef bool			igBool;
    typedef char			igChar;
    typedef int				igInt;
    typedef unsigned int	igUnsignedInt;

    typedef unsigned long long   igUnsignedLong;

    void igRefAlchemy(igInt alchemyVersion = IG_ALCHEMY_VERSION);
    void igReleaseAlchemy();

    class igAlchemy{
    public:
        inline igAlchemy()	{ igRefAlchemy(); }
        inline ~igAlchemy()	{ igReleaseAlchemy(); }
    };
}

#endif
