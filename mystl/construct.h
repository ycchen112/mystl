#pragma once

#include "iterator.h"
#include "type_traits.h"
#include <new>

namespace mystl {
template <class T1, class T2>
inline void construct(T1* p, const T2& value) {
	::operator new((void*)p) T1(value);
}

template <class T>
inline void construct(T* p) {
	::operator new((void*)p) T();
}

template <class T>
inline void destory(T* p) {
	p->~T();
}

//判断元素型别
template <class ForwardIterator>
inline void destory(ForwardIterator first, ForwardIterator last) {
	__destory(first, last, value_type(first));
}

// 判断是否有trivial destructor
template <class ForwardIterator, class T>
inline void __destory(ForwardIterator first, ForwardIterator last, T*) {
	typedef typename __type_trivial<T>::has_trivial_destructor trivial_destructor;
	__destory_aux(first, last, trivial_destructor());
}

//有trivial destructor
template <class ForwardIterator>
void __destory_aux(ForwardIterator, ForwardIterator, __true_type) {}

//有non-trivial destructor
template <class ForwardIterator>
void __destory_aux(ForwardIterator first, ForwardIterator last, __false_type) {
	for (; first < last; first++) {
		destory(&*first); //? 加&
	}
}

} // namespace mystl