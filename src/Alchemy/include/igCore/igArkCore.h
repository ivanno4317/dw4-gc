#ifndef __IG_ARKCORE_H__
#define __IG_ARKCORE_H__

#include <igGap.h>
#include <igCore/igStringRef.h>
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
            igBool			_isBootstrapped; //should be offset 0x79
            void checkAlchemyVersion(igInt alchemyVersion);

        public:
            void *operator new(size_t size);
            void operator delete(void *ptr);

        public:
            inline igBool isPreExitStarted()
            { return _preExitStarted; }

            igString getAlchemyPath();
			igString getApplicationPath();
			void setAlchemyPath(igString path);
			void setApplicationPath(igString path);

        protected:
            igBool					_initStarted;
            igBool					_preExitStarted;

        private:
            igStringRef _alchemyPath;
            igStringRef _applicationPath;

            void setupPaths();
    };

    extern igArkCore *ArkCore_function();
    #define ArkCore ArkCore_function()

    void igRefAlchemy(igInt version = IG_ALCHEMY_VERSION);
    void igReleaseAlchemy() ;
}
}

#endif
