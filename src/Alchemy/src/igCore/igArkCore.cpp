#include <igCore/igCoreAll.h>
#include <igGap.h>   

#include <igCore/igPrivateReportHandlerMacros.h>

#include <stdlib.h>

using namespace Gap::Core;

void igArkCore::checkAlchemyVersion(igInt alchemyVersion){

    //I'm not really sure if the check should be on igArkCore::_isBootstrapped
    if((alchemyVersion != IG_ALCHEMY_VERSION && igArkCore::_isBootstrapped == 1 )){
        IG_PRIVATE_REPORT_ERROR((
        "The headers used to build the Alchemy Core (version %d) do not match the currently registring dll or application (version %d).\n"
        "This usually means some API changed and you are likely to get unexpected behaviour.\n"
        "To try and load the dll or application anyways, try putting \n"
        "failOnDllVersionMismatch = false in the CORE section of your alchemy.ini",
        IG_ALCHEMY_VERSION, alchemyVersion));
    }    
}

void igArkCore::initBootstrap(){

    igRawRefMetaField *rawMetaField;

    _initStarted = true;

    igSystemMemoryStartup();


    igMetaObject::arkRegister();

    igMetaEnum::arkRegister();
    igMallocMemoryPool::arkRegister();
    igArenaMemoryPool::arkRegister();
    igAliasMemoryPool::arkRegister();
    igPageMemoryPool::arkRegister();
    igMemoryDictionary::arkRegister();
    igCharList::arkRegister();
    igCharListNoClean::arkRegister();
    igIntList::arkRegister();
    igIntListNoClean::arkRegister();
    igUnsignedIntList::arkRegister();
    igUnsignedIntListNoClean::arkRegister();
    igStringTable::arkRegister();
    igSymbolTable::arkRegister();
    igCallStackTable::arkRegister();
    igCallStackTracer::arkRegister();
    igGameCubeCallStackTracer::arkRegister();
    igLocationTable::arkRegister();
    igEventTracker::arkRegister();
    igFloatMetaField::arkRegister();
    igLongMetaField::arkRegister();
    igUnsignedCharMetaField::arkRegister();

    rawMetaField = Gap::Core::igRawRefMetaField::getMetaField();
    Gap::Core::igRefMetaField::setMetaField(rawMetaField);

}

void igArkCore::setupPaths(){

    getenv("IG_ROOT");
}
