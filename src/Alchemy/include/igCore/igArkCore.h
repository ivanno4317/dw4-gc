#ifndef __IG_ARKCORE_H__
#define __IG_ARKCORE_H__

#include <igGap.h>
#include <types.h>

namespace Gap{
    namespace Core{
        
        class igArkCore{

            public:
			    igArkCore();

            public:
                void			    preExit();
                void				exit();

                void				initBootstrap();
                void				exitBootstrap();
                void				initCore();

            public:
                igBool			_isBootstrapped;
                void checkAlchemyVersion(igInt alchemyVersion);

            public:
                void *operator new(size_t size);

            public:
                inline igBool isPreExitStarted()
			    { return _preExitStarted; }

            protected:
                igBool					_preExitStarted;

        };

        extern igUnsignedLong _initialized;

        extern igArkCore *ArkCore_function();
        #define ArkCore ArkCore_function()

        inline igBool	isBootstrapped()	{ return ArkCore->_isBootstrapped; }


        void igRefAlchemy(igInt version = IG_ALCHEMY_VERSION);
        void igReleaseAlchemy() ;
    }
}

#endif
