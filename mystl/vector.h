#pragma once
#include "allocator.h"
#include "iterator.h"
#include "uninitialized.h"


namespace mystl
{
    template <class T, class Alloc = mystl::allocator<T>>
    class vector {
    public:

        // 内嵌定义
        typedef T           value_type;
        typedef T*          pointer;
        typedef T*          iterator;
        typedef T&          reference;
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;

    protected:

        // 空间配置器
        typedef Alloc data_allocator;
        iterator start;
        iterator finish;
        iterator end_of_storage;

        // 指定位置插入元素
        void insert_aux(iterator position, const T& value);

        // 释放
        void deallocator();

        // 主要在于初始化迭代器，掉用allocte_and_fill申请空间和初始化
        void fill_initialize(size_type n, const T& value);
        iterator allocate_and_fill(size_type, const T& value);

    public:

        // 对外接口

    };

    template <class T, class Alloc>
    void vector<T, Alloc>::insert_aux(iterator position, const T& value)
    {
        if(star != finish) 
        {
            
        }
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::fill_initialize(size_type n, const T& value)
    {
        start = allocate_and_fill(n, value);
        finish = start + n;
        end_of_storage = finish;
    }

    template <class T, class Alloc>
    T* vector<T, Alloc>::allocate_and_fill(size_type n, const T& value)
    {
        T* result = data_allocator::allocate(n);
        uninitialized_fill_n(result, n, value);
        return result;
    }
    

}