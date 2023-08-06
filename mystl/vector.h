#pragma once
#include "allocator.h"
#include "iterator.h"
#include "uninitialized.h"

namespace mystl {
template <class T, class Alloc = mystl::allocator<T>>
class vector {
public:
	// 内嵌定义
	typedef T		  value_type;
	typedef T*		  pointer;
	typedef T*		  iterator;
	typedef T&		  reference;
	typedef size_t	  size_type;
	typedef ptrdiff_t difference_type;

protected:
	// 空间配置器
	typedef Alloc data_allocator;

	iterator start;
	iterator finish;
	iterator end_of_storage;

	// 指定位置插入元素
	void insert_aux(iterator position, const T& value);

	// 释放(vector自己的成员函数，其中调用data_allocate中的deallocate)
	void deallocate() {
		if (star) {
			data_allocator::deallocate(start, end_of_storage - start);
		}
	}

	// 主要在于初始化迭代器，掉用allocte_and_fill申请空间和初始化
	void	 fill_initialize(size_type n, const T& value);
	iterator allocate_and_fill(size_type, const T& value);

public:
	// 对外接口

	// 构造函数
	vector() :
			start(0), finish(0), end_of_storage(0) {}
	vector(size_type n, const T& value) { fill_initialize(n, value); }
	vector(int n, const T& value) { fill_initialize(n, value); }
	vector(long n, const T& value) { fill_initialize(n, value); }
	vector(size_type n) { fill_initialize(n, T()); }
	// 析构函数
	~vector() {
		destory(start, finish);
		deallocate();
	}

	// 迭代器相关
	iterator begin() { return begin(); }
	iterator end() { return end(); }

	// 容量和大小
	size_type size() const { return (size_type)(end() - begin()); }
	size_type capacity() const { return (size_type)(this->end_of_storage - begin()); }

	bool empty() const { return end() == begin(); }
	reference font() { return begin(); }
	reference back() { return *(end() - 1); }

	// 插入删除
	void push_back(const T& value) {
		if(finish != end_of_storage) {
			construct(finish, value);
			finish++;
		}
		else {
			insert_aux(finish, value)
		}
	}
	void pop_back() {
		destory(--finish);
	}

	// 具体位置删除，返回删除后该位置的迭代器
	iterator erase(iterator position) {
		if(position + 1 != end()) {
			copy(position + 1, finish, position);
		}
		finish--;
		destory(finish);
		return position;
	}
	// [first, last)范围删除，返回first的迭代器
	// TODO 超出范围异常
	iterator erase(iterator first, iterator last) {
		if(first != last) {
			iterator i = copy(last, finish, first);
			destory(i, finish);
			finish = finish - last + first;
		}
		return first;
	}

	// resize 调整vector大小到n
	// 当前大小>n则多余参数被删除
	// 当前大小<n则扩容，若传入value则放入扩容后的最后一个，若没有则添加默认构造
	void resize(size_type n, const T& value) {
		if(n < size()) {
			erase(begin() + n, end());
		}
		else{
			insert(end(), n - size(), value);
		}
	}
	void resize(size_type n) {
		resize(n, T());
	}

	void clear() { erase(begin(), end()); }
};

template <class T, class Alloc>
void vector<T, Alloc>::insert_aux(iterator position, const T& value) {
	if (end_of_storage != finish) {
		//在备用空间构造一个元素，用finish前一个元素初始化(vector最后一个元素)
		construct(finish, *(finish - 1));
		finish++;
		T value_copy = value;
		copy_backward(position, finish - 2, finish - 1);
		*position = value_copy;
	} else { //没有备用空间则重新配置新空间
		const size_type old_size = size();
		// 原大小为0则配置为1，否则配置为原来的2倍
		const size_type len = old_size != 0 ? old_size * 2 : 1;

		iterator new_start = data_allocator::allocate(len);
		iterator new_finish = new_start;
		try {
			new_finish = uninitialized_copy(start, position, new_start);
			construct(new_finish, value);
			++new_finish;
			new_finish = uninitialized_copy(position, finish, new_finish);
		} catch (...) { // 捕获任意类型的异常
			// commit or rollback
			destory(new_start, new_finish);
			data_allocator::deallocate(len, new_start);
			throw;
		}
		// 释放原来的vector
		destory(begin(), end()); // destory只是调用析构函数，不释放内存，所以要使用deallocate
		deallocate(begin());

		start = new_start;
		finish = new_finish;
		end_of_storage = new_start + len;
	}
}

template <class T, class Alloc>
void vector<T, Alloc>::fill_initialize(size_type n, const T& value) {
	start = allocate_and_fill(n, value);
	finish = start + n;
	end_of_storage = finish;
}

template <class T, class Alloc>
T* vector<T, Alloc>::allocate_and_fill(size_type n, const T& value) {
	T* result = data_allocator::allocate(n);
	uninitialized_fill_n(result, n, value);
	return result;
}

} //namespace mystl