#ifndef __IG_OBJECT_MACROS_H__
#define __IG_OBJECT_MACROS_H__

namespace Gap {
namespace Core {

#define IG_OBJECT_COMMON(CLASSNAME) \
	typedef CLASSNAME	ThisClass;	\
    friend class Gap::Core::igObject; \
	friend class Gap::Core::igArkCore; \
    static void arkRegister(); \


#define IG_OBJECT_NON_ABSTRACT(CLASSNAME) \
	public: \
	static void * retrieveVTablePointer();

#define IG_OBJECT_BOOTSTRAP(CLASSNAME) \
	public: \
	CLASSNAME (); \
	CLASSNAME (Gap::igBool boot); \
	CLASSNAME (const CLASSNAME& other); \
	virtual void __bootstrapDestruct ();

#define IG_OBJECT_BOOTSTRAP_NON_ABSTRACT(CLASSNAME) \
	virtual Gap::Core::igObject* createCopy(CopyMethod copyMethod=kDeepCopy) const;

#define IG_OBJECT_DEFINE(CLASSNAME) \
    IG_OBJECT_NON_ABSTRACT(CLASSNAME) \
    IG_OBJECT_COMMON(CLASSNAME)
    
#define IG_ABSTRACT_OBJECT_DEFINE(CLASSNAME) \
	IG_OBJECT_COMMON(CLASSNAME)

#define IG_BOOTSTRAP_OBJECT_DEFINE(CLASSNAME) \
	IG_OBJECT_NON_ABSTRACT(CLASSNAME) \
	IG_OBJECT_BOOTSTRAP_NON_ABSTRACT(CLASSNAME) \
	IG_OBJECT_BOOTSTRAP(CLASSNAME) \
	IG_OBJECT_COMMON(CLASSNAME)

#define IG_BOOTSTRAP_ABSTRACT_OBJECT_DEFINE(CLASSNAME) \
	IG_OBJECT_BOOTSTRAP(CLASSNAME) \
	IG_OBJECT_COMMON(CLASSNAME)
	
}
}

#endif // __IG_OBJECT_MACROS_H__
