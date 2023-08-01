#pragma once

#include <memory>

#include "construct.h"

// TODO 异常处理
// TODO 函数体内容

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

}
