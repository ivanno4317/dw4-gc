#ifndef _IGREFMETAFIELD_H_A89FD711_
#define _IGREFMETAFIELD_H_A89FD711_

#include <igCore/igObject.h>
#include <igCore/igMetaField.h>

namespace Gap {
namespace Core {

class igRefMetaField : public igMetaField
{
	IG_BOOTSTRAP_ABSTRACT_OBJECT_DEFINE(igRefMetaField);
	IG_METAFIELD_SETUP(igRefMetaField);
};

}
}

#endif
