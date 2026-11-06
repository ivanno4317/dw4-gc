#ifndef _IGARENAMEMORYPOOL_H_925CEDA1_
#define _IGARENAMEMORYPOOL_H_925CEDA1_

#include <igGap.h>
#include <igCore/igCore.h>
#include <igCore/igObject.h>
#include <igCore/igMemoryPool.h>

namespace Gap {
namespace Core {

class igArenaMemoryPool : public igMemoryPool
{
    IG_BOOTSTRAP_OBJECT_DEFINE(igArenaMemoryPool);


    private:
        void igArenaInitState();
};

}
}


#endif
