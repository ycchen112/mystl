/*
	此版本不使用内存池
*/
#include "construct.h"

namespace mystl {
template <class T>
class allocator {
public:
	typedef T		 value_type;
	typedef T*		 pointer;
	typedef const T* const_pointer;
	typedef T&		 reference;
	typedef const T& const_reference;
	typedef size_t	 size_type;

public:
	static T* allocate();
	static T* allocate(size_type n);
	// static T* allocate(size_type n, pointer p);

	static void deallocate(pointer p);
	static void deallocate(size_type n, pointer p);

	// 调用全局函数的construct
	static void construct(pointer p);
	static void construct(pointer p, const_reference value);

	static void destory(pointer p);
	static void destory(pointer first, pointer last);
};

template <class T>
T* allocator<T>::allocate() {
	return (T*)(::operator new(sizeof(T)));
}

template <class T>
T* allocator<T>::allocate(size_type n) {
	if (n == 0) {
		return nullptr;
	}
	return (T*)(::operator new(n * sizeof(T)));
}

// template <class T>
// T* allocator<T>::allocate(size_type n, pointer p) {
//     return (T*)(::operator new(p)(n * sizeof(T)));
// }

template <class T>
void allocator<T>::deallocate(pointer p) {
	::operator delete(p);
}

template <class T>
void allocator<T>::deallocate(size_type n, pointer p) {
	::operator delete(p);
}

template <class T>
void allocator<T>::construct(pointer p) {
	mystl::construct(p);
}

template <class T>
void allocator<T>::construct(pointer p, const_reference value) {
	mystl::construct(p, value);
}

template <class T>
void allocator<T>::destory(pointer p) {
	mystl::destory(p);
}

template <class T>
void allocator<T>::destory(pointer first, pointer last) {
	mystl::destory(first, last);
}


/*
	因为不使用内存池，直接指定配置器所以不需要对配置器进行封装
*/

// 简单封装
// template <class T, class Alloc>
// class simple_alloc {
// public:
// 	static T*	allocate(size_t n) { return 0 == n ? 0 : (T*)Alloc::allocate(n); }
// 	static T*	allocate() { return (T*)Alloc::allocate(); }
// 	static void deallocate(T* p) { Alloc::deallocate(p); }
// 	static void deallocate(size_t n, T* p) { Alloc::deallocate(n, p); }
// };

} //namespace mystl