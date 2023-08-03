#pragma once

namespace {
template <class T, class Category, class Distance, class Pointer = T*, class Reference = T&>
struct iterator {
	typedef T		  value_type;
	typedef Pointer	  pointer;
	typedef Reference reference;
	typedef Distance  difference_type;
	typedef Category  iterator_category;
};

// 定义空类作为标签tag
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// traits
template <class Iterator>
struct iterator_traits {
	typedef typename Iterator::value_type		 value_type;
	typedef typename Iterator::pointer			 pointer;
	typedef typename Iterator::reference		 reference;
	typedef typename Iterator::difference_type	 difference_type;
	typedef typename Iterator::iterator_category iterator_category;
};

// traits原生指针特化
template <class T>
struct iterator_traits<T*> {
	typedef T						   value_type;
	typedef T*						   pointer;
	typedef T&						   reference;
	typedef ptrdiff_t				   defference_type;
	typedef random_access_iterator_tag iterator_category;
};

// traits指向const常量的指针
template <class T>
struct iterator_traits<const T*> {
	typedef T						   value_type;
	typedef T*						   pointer;
	typedef T&						   reference;
	typedef ptrdiff_t				   difference_type;
	typedef random_access_iterator_tag iterator_category
};

// 识别判别器类型
template <class Iterator>
typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&) {
	typedef typename iterator_traits<Iterator>::iterator_category category;
	return category();
}

} //namespace