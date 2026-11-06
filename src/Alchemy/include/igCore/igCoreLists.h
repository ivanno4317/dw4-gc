#ifndef _IGCORELISTS_H_E8F2CC98_
#define _IGCORELISTS_H_E8F2CC98_

#include <igGap.h>
#include <igCore/igObject.h>
#include <igCore/igTDataList.h>

namespace Gap {
namespace Core {

class igCharList : public igTDataList<igChar>
{
	IG_OBJECT_DEFINE(igCharList);
};

class igCharListNoClean : public igCharList
{
	IG_OBJECT_DEFINE(igCharListNoClean);
};

class igIntList : public igTDataList<igInt>
{
	IG_OBJECT_DEFINE(igIntList);
};

class igIntListNoClean : public igIntList
{
	IG_OBJECT_DEFINE(igIntListNoClean);
};

class igUnsignedIntList : public igTDataList<igUnsignedInt>
{
	IG_OBJECT_DEFINE(igUnsignedIntList);
};

class  igUnsignedIntListNoClean : public igUnsignedIntList
{
	IG_OBJECT_DEFINE(igUnsignedIntListNoClean);
};

}
}
#endif
