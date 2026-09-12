#include <NMWException.h>

typedef void (*Destructor)(void*, int);

void* __register_global_object(void* object, void* destructor, void* regmem)
{
    DestructorChain* newNode = (DestructorChain*) regmem;

    newNode->next = __global_destructor_chain;
    newNode->destructor = destructor;
    newNode->object = object;
    __global_destructor_chain = newNode;

    return object;
}

void __destroy_global_chain(void)
{
    while (__global_destructor_chain) {
        DestructorChain* cur = __global_destructor_chain;
        __global_destructor_chain = cur->next;
        ((Destructor) cur->destructor)(cur->object, -1);
    }
}

__declspec(section ".dtors")
static void* const __destroy_global_chain_reference = __destroy_global_chain;
