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
class __list_iterator : public mystl::iterator<T, bidirectional_iterator_tag> {
	typedef __list_node<T>*	   link_type;
	typedef __list_iterator<T> iterator;
	typedef T				   value_type;
	typedef T*				   pointer;
	typedef T&				   reference;
	typedef size_t			   size_type;
	typedef ptrdiff_t		   deference_type;

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
	typedef __list_node<T>*	   link_type;
	typedef size_t			   size_type;
	typedef ptrdiff_t		   difference_type;

	typedef mystl::allocator<list_node> list_node_allocator;

private:
	link_type node_ptr;

protected:
	// 配置一个节点空间(只申请内存)
	link_type get_node() { return list_node_allocator::allocate(); }
	// 释放一个节点
	void put_node(link_type p) { list_node_allocator::deallocate(p); }
	// 产生一个节点(形成节点), 带有元素值
	link_type create_node(const T& value) {
		link_type p = get_node();
		try {
			construct(&p->data, value);
		} catch (...) {
			put_node(p);
		}
		return p;
	}

	void destory_node(link_type p) {
		destory(&p->data);
		put_node(p);
	}

	// 空链表初始化，自己指向自己
	void empty_initialize() {
		node_iterator = get_node();
		node_iterator->next = node_iterator;
		node_iterator->prev = node_iterator;
	}

	// 多个元素初始化
	void fill_initialize(size_type n, const T& value);

	// 将某连续范围内的元素迁移到某个位置, 将[first, last)迁移到position之前
	void transfer(iterator position, iterator first, iterator last) {
		if (position != last) {
			(*(link_type((*last.node).prev))).next = position.node;
			(*(link_type((*first.node).prev))).next = last.node;
			(*(link_type((*position.node).prev))).next = first.node;
			link_type temp = link_type((*position.node).prev);
			(*position.node).prev = (*last.node).prev;
			(*last.node).prev = (*first.node).prev;
			(*first.node).prev = temp;
		}
	}

public:
	// 构造
	list() { empty_initialize(); }
	list(size_type n) {
	}
	list(size_type n, const T& value = T()) {
	}

	// 迭代器相关
	iterator  begin() { return (*node_ptr).next; }
	iterator  end() { return node_ptr; }
	bool	  empty() const { return node_ptr.next == node_ptr; }
	reference font() { return *begin(); }
	reference back() { return *(--end()); }

	// 在position处插入一个节点
	iterator insert(iterator position, const T& value);
	// 插入一个节点，无初值
	iterator insert(iterator position) { return insert(position, T()); }
	// 插入n个节点
	iterator insert(iterator position, size_type n, const T& value);
	// 插入一段
	template <class InputIterator>
	iterator insert(iterator position, InputIterator first, InputIterator last);

	// 清除所有节点(保留了自己指向自己的节点)
	void clear();

	// 头插入、尾插入
	void push_font(const T& value) { insert(begin(), value); }
	void push_back(const T& value) { insert(end(), value); }

	// 消除一个位置元素
	iterator erase(iterator position);
	// 消除一段位置元素[first, last)
	iterator erase(iterator first, iterator last);

	// 头消除、尾消除
	void pop_font() { erase(begin()); }
	void pop_back() { erase(--end()); }

	// 将数值为value的节点删除
	void remove(const T& value);
	// 移除数值相同连续元素，连续而相同的元素将被移除一个
	void unique();

	// splice--对transfer的封装, 把x接到position前面，x必须不同于*this
	void splice(iterator position, list& x);
	// aplice--把i所指元素接到position前，position和i可以指向同一个list (对transfer的封装)
	void aplice(iterator position, list&, iterator i);
};

template <class T>
void list<T>::fill_initialize(size_type n, const T& value) {
	empty_initialize();
	try {
		insert(begin(), n, value);
	} catch (...) {
		clear();
		put_node(node_ptr);
	}
}

template <class T>
typename list<T>::iterator list<T>::insert(iterator position, const T& value) {
	link_type _node_temp = create_node(value);
	_node_temp->next = position.node;
	_node_temp->prev = position.node->prev;
	(position.node->prev)->next = _node_temp;
	position.node->prev = _node_temp;
	return _node_temp;
}

template <class T>
typename list<T>::iterator list<T>::insert(iterator position, size_type n, const T& value) {
	for (; n > 0; n--) {
		insert(position, value);
	}
	return position;
}

template <class T>
template <class InputIterator>
typename list<T>::iterator list<T>::insert(iterator position, InputIterator first, InputIterator last) {
	for (; first != last; first++) {
		insert(position, *first);
	}
	return position;
}

template <class T>
void list<T>::clear() {
	link_type cur = node_ptr->next;
	while (cur != node_ptr) {
		link_type temp = cur;
		cur = cur->next;
		destory_node(temp);
	}
	node_ptr->next = node_ptr;
	node_ptr->prev = node_ptr;
}

template <class T>
typename list<T>::iterator list<T>::erase(iterator position) {
	link_type next_node = position.node->next;
	link_type prev_node = position.node->prev;
	prev_node->next = next_node;
	next_node->prev = prev_node;
	destory_node(position);
	return iterator(next_node);
}

template <class T>
typename list<T>::iterator list<T>::erase(iterator first, iterator last) {
	for (; first != last; first++) {
		erase(first);
	}
	return last;
}

template <class T>
void list<T>::remove(const T& value) {
	iterator first = begin();
	iterator last = end();
	while (first != last) {
		iterator next = first;
		next++;
		if (*first == value) {
			erase(first);
		}
		first = next;
	}
}

template <class T>
void list<T>::unique() {
	if (empty())
		return;
	iterator first = begin();
	iterator last = end();
	iterator next = first;
	while (++next != last) { //++使得next是first的下一个节点
		if (*first == *next) {
			erase(next);
		} else {
			first = next;
		}
		next = first;
	}
}

template <class T>
void list<T>::splice(iterator position, list& x) {
	if (!x.empty()) {
		transfer(position, x.begin(), x.end());
	}
}

template <class T>
void list<T>::aplice(iterator position, list&, iterator i) {
	iterator temp = i;
	j++;
	if(position == i || position == temp) return;
	transfer(position, i, temp);
}
} //namespace mystl