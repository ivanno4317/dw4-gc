#ifndef _IGMETAFIELD_H_B994D832_
#define _IGMETAFIELD_H_B994D832_

	#define IG_METAFIELD_DEFINITION(METAFIELDTYPE) \
	METAFIELDTYPE* METAFIELDTYPE::getMetaField() \
	{ \
		if (_MetaField == NULL) \
			METAFIELDTYPE::arkRegister(); \
		return _MetaField; \
	}

	#define IG_METAFIELD_SETUP(METAFIELDTYPE) \
	protected: \
	static METAFIELDTYPE* _MetaField; \
	public: \
	static METAFIELDTYPE* getMetaField(); \
	static void setMetaField(METAFIELDTYPE* val) { _MetaField = val; }	

#include <igCore/igObject.h>

namespace Gap {
namespace Core {

class igMetaField : public igObject
{
	IG_BOOTSTRAP_ABSTRACT_OBJECT_DEFINE(igMetaField);


	protected:
		static igMetaField* _MetaField;

	public:
		static inline igMetaField* getMetaField()
		{ return _MetaField; }
};

}
}
#endif
