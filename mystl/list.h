#pragma once

#include "allocator.h"
#include "config.h"
#include "construct.h"
#include "iterator.h"
#include "uninitialized.h"

namespace mystl {
// list节点
template <class T>
struct __list_node {
	T				data;
	__list_node<T>* prev;
	__list_node<T>* next;
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
template <class T>
class list {
public:
	// 内嵌定义
	typedef T				   value_type;
	typedef T&				   reference;
	typedef T*				   pointer;
	typedef const T&		   const_reference;
	typedef const T*		   const_pointer;
	typedef __list_iterator<T> iterator;
	typedef __list_node<T>	   list_node;
	typedef size_t			   size_type;
	typedef ptrdiff_t		   difference_type;

	typedef mystl::allocator<list_node> list_node_allocator;

private:
	iterator node_iterator;

protected:
	// 配置一个节点空间(只申请内存)
	iterator get_node() { return list_node_allocator::allocate(); }
	// 释放一个节点
	void put_node(iterator p) { list_node_allocator::deallocate(p); }
	// 产生一个节点(形成节点), 带有元素值
	iterator create_node(const T& value) {
		iterator p = get_node();
		construct(p.node, value);
		return p;
	}
	// 

	// 空链表初始化
	void empty_initialize() {
		node_iterator = get_node();
		node_iterator->next = node_iterator;
		node_iterator->prev = node_iterator;
	}

public:
	// 构造
	list() { empty_initialize(); }
	list(size_type n, const T& value = T()) {
	}

	// 迭代器相关
	link_type begin() { return (*node_iterator).next; }
	link_type end() { return node_iterator; }
	bool	  empty() const { return node_iterator.next == node_iterator; }
	reference font() { return *begin(); }
	reference back() { return *(--end()); }
};
} //namespace mystl