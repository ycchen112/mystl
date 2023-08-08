#pragma once

#include "allocator.h"
#include "config.h"
#include "construct.h"
#include "uninitialized.h"

namespace mystl {

// list节点
template <class T>
struct __list_node {
	__list_node<T>* prev;
	__list_node<T>* next;
	T				data;
};

// list迭代器
template <class T>
class __list_iterator {
	typedef __list_node<T>*			   link_type;
	typedef __list_iterator<T>		   iterator;
	typedef T						   value_type;
	typedef T*						   pointer;
	typedef T&						   reference;
	typedef size_t					   size_type;
	typedef ptrdiff_t				   deference_type;
	typedef bidirectional_iterator_tag iterator_category;

public:
	// 成员变量为一个指向链表节点的指针
	link_type node;

	// 构造
	__list_iterator(link_type node) :
			node(node) {}
	__list_iterator(const iterator& x) :
			node(x.node) {}
	__list_iterator() {}

	// 运算符重载
	bool	  operator==(const iterator& x) const { return node == x.node; }
	bool	  operator!=(const iterator& x) const { return node != x.node; }
	reference operator*() const { return (*node).data; }
	iterator  operator++() {
		 node = (*node).next;
		 return *this;
	}
	iterator operator--() {
		node = (*node).prev;
		return *this;
	}
	pointer operator->() { return &(operator*()); }
};

// list
template <class T, class Alloc = mystl::allocator<T>>
class list {
public:
	// 内嵌定义
	typedef T				   value_type;
	typedef T&				   reference;
	typedef T*				   pointer;
	typedef const T&		   const_reference;
	typedef const T*		   const_pointer;
	typedef Alloc			   list_node_allocator;
	typedef __list_iterator<T> iterator;
	typedef size_t			   size_type;
	typedef ptrdiff_t		   difference_type;

private:
	iterator node_iterator;

public:
	// 构造
	list() {}
	list(size_type n, const T& = T()) {
		// data_allocate::allocator();
	}

	// 迭代器相关
	iterator  begin() { return (*node_iterator).next; }
	iterator  end() { return node_iterator; }
	bool	  empty() const { return node_iterator.next == node_iterator; }
	reference font() { return *begin(); }
	reference back() { return *(--end()); }
};
} //namespace mystl