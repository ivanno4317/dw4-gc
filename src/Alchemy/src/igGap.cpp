#include <igCore/igCoreAll.h>
#include <igGap.h>
#include <igGapCore.h>

namespace Gap{
    namespace Core{

        igUnsignedLong _initialized;
 
        static igArkCore *_arkCore;

        inline igArkCore *ArkCore_function(){
            return _arkCore;
        }

    }

    void igRefAlchemy(igInt alchemyVersion){
        if (!Core::_initialized++)
        {
            Core::_arkCore = new Core::igArkCore();

            Core::ArkCore_function()->initBootstrap();

            Core::igStringObj::arkRegister();
            Core::igStringObjList::arkRegister();
            Core::igFile::arkRegister();
            Core::igRegistry::arkRegister();
            Core::igResource::arkRegister();

            Core::ArkCore_function()->initCore();
        }

        Core::ArkCore_function()->checkAlchemyVersion(alchemyVersion);
    }

    void igReleaseAlchemy(){
        if(!Core::ArkCore_function()->isPreExitStarted())
            //Core::ArkCore_function->preExit();

            if(!--Core::_initialized){
                Core::ArkCore_function()->exit();
                Core::ArkCore_function()->exitBootstrap();
                delete Core::_arkCore;
                Core::_arkCore = 0;
            }
    }
}
