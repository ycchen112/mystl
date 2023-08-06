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
} //namespace mystl