#pragma once

#include <memory>

#include "construct.h"

// TODO 函数功能、异常处理

namespace mystl {
// uninitialized_copy
// 在[result, result + (last - first))范围内产生[first, last)上对象的复制
template <class InputIterator, class ForwardIterator>
ForwardIterator
uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result) {
}

// uninitialized_fill
// 在[first, last)上产生x的复制
template <class ForwardIterator, class T>
void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x) {
}

// uninitialized_fill_n
// 在[first, first + n)上产生x的复制
template <class ForwardIterator, class Size, class T>
inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x) {
	return __uninitialized_fill_n(first, n, x, mystdl::iterator_traits<first>::value_type());
}

// 根据first指向的value_type的POD型别判断使用不同的函数（为了高效）
template <class ForwardIterator, class Size, class T, class T_>
inline ForwardIterator
__uninitialized_fill_n(ForwardIterator first, Size n, const T& x, T_*) {
	typedef typename __type_traits<T_>::is_POD_type is_POD;
	return __uninitialized_fill_n_aux(first, n, x, is_POD());
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

} //namespace mystl
