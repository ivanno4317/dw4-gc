#ifndef _IGSTRINGOBJ_H_B7DC004C_
#define _IGSTRINGOBJ_H_B7DC004C_

namespace Gap{
    namespace Core {
        class igStringObj : public igObject {
        public:
            static void arkRegister();
        };

        class igStringObjList : public igObject {
        public:
            static void arkRegister();
        };
    }
}

#endif
