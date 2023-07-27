#include <new>

namespace mystl
{
    template<class T1, class T2>
    void construct (T1* p, const T2& value) {
        new(p) T1(value);
    }

    template<class T>
    void destory (T* p) {
        p->~T();
    }
    

} // namespace mystl    