#include <igCore/igCoreAll.h>\
#include <igGap.h>   

namespace Gap{
    namespace Core{

        void igArkCore::checkAlchemyVersion(igInt alchemyVersion){

            if(alchemyVersion != IG_ALCHEMY_VERSION){
                    // IG_PRIVATE_REPORT_ERROR((
                    // "The headers used to build the Alchemy Core (version %d) do not match the currently registring dll or application (version %d).\n"
                    // "This usually means some API changed and you are likely to get unexpected behavior.\n"
                    // "To try and load the dll or application anyways, try putting failOnDllVersionMismatch = false in the CORE section of your alchemy.ini",
                    // IG_ALCHEMY_VERSION, alchemyVersion));
            }
        }

    }
}
