#include "construct.h"

namespace mystl
{
    template<class T>
    class allocator
    {
    public:
        typedef T           value_type;
        typedef T*          pointer;
        typedef const T*    const_pointer;
        typedef T&          reference;
        typedef const T&    const_reference;
        typedef size_t      size_type;

    private:
        static void* allocate();
        static void deallocate();
        static void* allocate(size_type n, pointer p);
        
        
    };
}