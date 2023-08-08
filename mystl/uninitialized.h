#pragma once

#include <memory>

#include "algorithm.h"
#include "construct.h"

// TODO 函数功能、异常处理

namespace mystl {

template <class InputIterator, class ForwardIterator>
ForwardIterator
__uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __true_type) {
	return copy(first, last, result);
}

template <class InputIterator, class ForwardIterator>
ForwardIterator
__uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __false_type) {
	ForwardIterator cur = result;
	try {
		for (; first != last; first++, cur++) {
			construct(&*cur, *first);
		}
		return cur;
	} catch (...) {
		destory(result, cur);
	}
}

template <class InputIterator, class ForwardIterator, class T>
ForwardIterator
__uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, T) {
	typedef typename __type_traits<T>::is_POD_type is_POD;
	return __uninitialized_copy_aux(first, last, result, is_POD());
}

// uninitialized_copy
// 在[result, result + (last - first))范围内产生[first, last)上对象的复制
template <class InputIterator, class ForwardIterator>
ForwardIterator
uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result) {
	typedef typename iterator_traits<ForwardIterator>::value_type value_type;
	return __uninitialized_copy(first, last, result, value_type());
}

template <class ForwardIterator, class T>
inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& x, __true_type) {
	fill(first, last, x);
}

template <class ForwardIterator, class T>
inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& x, __false_type) {
	ForwardIterator cur = first;
	try {
		for (; first != last; first++) {
			construct(&*first, x);
		}
	} catch (...) {
		// commit or rollback
		destory(cur, first);
	}
}

template <class ForwardIterator, class T, class T_>
inline void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x, T_) {
	typedef typename __type_traits<T_>::is_POD_type is_POD;
	__uninitialized_fill_aux(first, last, x, is_POD());
}

// uninitialized_fill
// 在[first, last)上产生x的复制
template <class ForwardIterator, class T>
inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x) {
	typedef typename iterator_traits<ForwardIterator>::value_type value_type;
	return __uninitialized_fill(first, last, x, value_type());
}

// 是POD类型，调用fill_n()
template <class ForwardIterator, class Size, class T>
inline ForwardIterator
__uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, __true_type) {
	return fill_n(first, n, x);
}

// 不是POD类型，则需要调用construct一个个创建
template <class ForwardIterator, class Size, class T>
inline ForwardIterator
__uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, __false_type) {
	ForwardIterator cur = first;
	for (; n > 0; n--, cur++) {
		construct(&*cur, x);
	}
	return cur;
}

// 根据first指向的value_type的POD型别判断使用不同的函数（为了高效）
template <class ForwardIterator, class Size, class T, class T_>
inline ForwardIterator
__uninitialized_fill_n(ForwardIterator first, Size n, const T& x, T_) {
	typedef typename __type_traits<T_>::is_POD_type is_POD;
	return __uninitialized_fill_n_aux(first, n, x, is_POD());
}

// uninitialized_fill_n
// 在[first, first + n)上产生x的复制
template <class ForwardIterator, class Size, class T>
inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x) {
	typedef typename iterator_traits<ForwardIterator>::value_type value_type;
	return __uninitialized_fill_n(first, n, x, value_type());
}

} //namespace mystl
