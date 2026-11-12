#ifndef _IGINTERNALSTRINGPOOL_H_
#define _IGINTERNALSTRINGPOOL_H_

namespace Gap {
namespace Core {

class igInternalStringPool
{
    private:
    	static igInternalStringPool* _defaultStringPool;

    public:
        void *operator new(size_t size);
        void operator delete(void *ptr);

        igInternalStringPool();

        static igInternalStringPool* getDefault()
        {
            if (_defaultStringPool == NULL)
                _defaultStringPool = new igInternalStringPool();
            return _defaultStringPool;
        }
        igString setString(igString string);
};

}
}

#endif
