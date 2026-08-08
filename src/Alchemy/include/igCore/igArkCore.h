#ifndef __IG_ARKCORE_H__
#define __IG_ARKCORE_H__

#include <igGap.h>
#include <igCore/igStringRef.h>

typedef unsigned long size_t;

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
                igInt			_numBSMetaObjects;
                igInt			_numBSMetaFields;
                igInt			_numTrackedObjects;
                igInt			_numTrackedFields;
                void checkAlchemyVersion(igInt alchemyVersion);

            public:
                void *operator new(size_t size);
                void operator delete(void *ptr);

            public:
                inline igBool isPreExitStarted()
			    { return _preExitStarted; }

            protected:
                igBool			_preExitStarted;

            private:
                igStringRef _alchemyPath;
			    igStringRef _applicationPath;

                

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
