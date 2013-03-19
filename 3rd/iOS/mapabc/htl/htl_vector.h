
/*
 * htl-lite - a basic data structures and algorithms.
 * Copyright (C) 2009 leon hong. All rights reserved.
 * authors:
 *   leon hong <codeblocker@gmail.com>
 */

#ifndef __HTL_VECTOR_H__
#define __HTL_VECTOR_H__

#include "htl_alloc.h"
#include "htl_uninitialized.h"
#include "htl_algo.h"

__HTL_BEGIN_NAMESPACE

template<class T, class Alloc = allocator>
class vector {
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
protected:
    typedef  simple_alloc<T, Alloc> data_allocator;
    iterator start;
    iterator finish;
    iterator end_of_storage;

    void fill_initalize(size_type n, const value_type& value) {
        start = allocate_and_fill(n, value);
        finish = start + n;
        end_of_storage = finish;
    }

    iterator allocate_and_fill(size_type n, const value_type& value) {
        iterator result = data_allocator::allocate(n);
        uninitalized_fill_n(result, n, value);
        return result;
    }

    void deallocate() {
        if (start) {
            data_allocator::deallocate(start, end_of_storage - start);
        }
    }

    template<class ForwardIterator>
    iterator allocate_and_copy(size_type n, ForwardIterator first, ForwardIterator last) {
        iterator result = data_allocator::allocate(n);
        uninitalized_copy(first, last, result);
        return result;
    }
public:
    template<class Type>
    iterator insert(iterator __position, const Type& x) {
      difference_type __n = __position - begin();
      if (finish != end_of_storage && __position == end())
        *finish++ = x;
      else
        insert_aux(__position, x);
      return begin() + __n;
    }
    
    iterator begin() const { return start; }
    iterator end() const { return finish; }
    size_type size() const { return size_type(end() - begin()); }
    size_type capacity()  { return size_type(end_of_storage - begin()); }
    bool empty() const { return begin() == end(); }
    reference operator[](size_type n) { return *(begin() + n); }
    const_reference operator[](size_type n) const { return *(begin() + n); }

  void range_check(size_type __n) const {
    if (__n >= this->size())// 越界
    	int iError = -1;
      //__stl_throw_range_error("vector<bool>");
  }

  reference at(size_type __n)
    { range_check(__n); return (*this)[__n]; }
  const_reference at(size_type __n) const
    { range_check(__n); return (*this)[__n]; }

  
    vector() : start(0), finish(0), end_of_storage(0) {}

    vector(size_type n, const T& value) {
        fill_initalize(n, value);
    }

    vector(int n, const T& value) {
        fill_initalize(n, value);
    }

    vector(long n, const T& value) {
        fill_initalize(n, value);
    }

    explicit vector(size_type n) {
        fill_initalize(n, T());
    }

    ~vector() {
        destory(start, finish);
        deallocate();
    }

    reference front() { return *begin(); }

    reference back() { return *(end() - 1); }

    void push_back(const value_type& x) {
        if (finish != end_of_storage) {
            construct(finish, x);
            ++finish;
        }
        else
            insert_aux(end(), x);
    }

    void pop_back() {
        --finish;
        destory(finish);
    }
    void clear() { erase(begin(), end()); }
    iterator erase(iterator first, iterator last) {
        iterator it = copy(last, finish, first);
        destory(it, finish);
        finish = finish - (last - first);
        return first;
    }

    iterator erase(iterator pos) {
        if (pos + 1 != end())
            copy(pos + 1, finish, pos);
        --finish;
        destory(finish);
        return pos;
    }

    void insert(iterator pos, size_type n, const T& x);
    
    void resize(size_type __new_size, const T& x = T()) {
      if (__new_size < size()) 
        erase(begin() + difference_type(__new_size), end());
      else
        insert(end(), __new_size - size(), x);
    }    

	vector<T, Alloc>& operator=(const vector<T, Alloc>& x);
    void reserve(size_type n);

    void swap(vector<T, Alloc>& x) {
        __HTL::swap(start, x.start);
        __HTL::swap(finish, x.finish);
        __HTL::swap(end_of_storage, x.end_of_storage);
    }
private:
    void insert_aux(iterator pos, const T& x);
};


template <class T, class Alloc>
inline bool 
operator==(const vector<T, Alloc>& x, const vector<T, Alloc>& y)
{
	return x.size() == y.size() &&
		equal(x.begin(), x.end(), y.begin());
}

template <class T, class Alloc>
inline bool 
operator<(const vector<T, Alloc>& x, const vector<T, Alloc>& y)
{
	return lexicographical_compare(x.begin(), x.end(), 
		y.begin(), y.end());
}


#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER

template <class T, class Alloc>
inline void swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
{
	x.swap(y);
}

template <class T, class Alloc>
inline bool
operator!=(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {
	return !(x == y);
}

template <class T, class Alloc>
inline bool
operator>(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {
	return y < x;
}

template <class T, class Alloc>
inline bool
operator<=(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {
	return !(y < x);
}

template <class T, class Alloc>
inline bool
operator>=(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {
	return !(x < y);
}

#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */


template<typename T, typename Alloc>
void vector<T, Alloc>::reserve(size_type n) {
    if (capacity() < n) {
        size_type old_size = size();
        iterator tmp = allocate_and_copy(n, start, finish);
        destory(start, finish);
        data_allocator::deallocate(start, end_of_storage - start);
        start = tmp;
        finish = start + old_size;
        end_of_storage = start + n;
    }
}

template<typename T, typename Alloc>
void vector<T, Alloc>::insert_aux(iterator pos, const T& x) {
    if (finish != end_of_storage) {
        construct(finish , *(finish - 1));
        ++finish;
        T x_copy = x;
        copy_backward(pos, finish-2, finish-1);
        //construct(pos, x);
        *pos =x_copy;
    }
    else {
        const size_type old_size = size();
        const size_type len = old_size != 0 ? old_size * 2 : 1;
        iterator new_start = data_allocator::allocate(len);
        iterator new_finish = new_start;
        new_finish = uninitalized_copy(start, pos, new_start);
        construct(&*new_finish, x);
        ++new_finish;
        new_finish = uninitalized_copy(pos, finish, new_finish);
        //释放原来内存
        destory(begin(), end());
        deallocate();
        start = new_start;
        finish = new_finish;
        end_of_storage = new_start + len;
    }
}

template <class T, class Alloc>
vector<T,Alloc>& 
vector<T,Alloc>::operator=(const vector<T, Alloc>& x)
{
	if (&x != this) {
		const size_type xlen = x.size();
		if (xlen > capacity()) {
			iterator tmp = allocate_and_copy(xlen, x.begin(), x.end());
			destory(start, finish);
			//deallocate(start, end_of_storage - start);
			deallocate();
			start = tmp;
			end_of_storage = start + xlen;
		}
		else if (size() >= xlen) {
			iterator i = copy(x.begin(), x.end(), begin());
			destory(i, finish);
		}
		else {
			copy(x.begin(), x.begin() + size(), start);
			uninitalized_copy(x.begin() + size(), x.end(), finish);
			//uninitialized_copy(x.begin() + size(), x.end(), finish);
		}
		finish = start + xlen;
	}
	return *this;
}


template<typename T, typename Alloc>
void vector<T, Alloc>::insert(iterator pos, size_type n, const T& x) {
    if (n != 0) {
        if (size_type(end_of_storage - finish) >= n) {
            //T x_copy = x;
            const size_type elems_after = finish - pos;
            iterator old_finish = finish;

            if (elems_after > n) {
                uninitalized_copy(finish - n, finish, finish);
                finish = finish + n;
                copy_backward(pos, old_finish - n, old_finish);
                fill(pos, pos + n, x);
            }
            else {
                uninitalized_fill_n(finish, n - elems_after, x);
                finish += n - elems_after;
                uninitalized_copy(pos, old_finish, finish);
                finish += elems_after;
                fill(pos, old_finish, x);
            }
        }
        else {
            const size_type old_size = size();
            const size_type len = old_size + htl_max(old_size, n);
            iterator new_start = data_allocator::allocate(len);
            iterator new_finish = new_start;
            new_finish = uninitalized_copy(start, pos, new_start);
            new_finish = uninitalized_fill_n(new_finish, n, x);
            new_finish = uninitalized_copy(pos, finish, new_finish);

            destory(start, finish);
            deallocate();
            start = new_start;
            finish = new_finish;
            end_of_storage = new_start + len;
        }
    }
}

__HTL_END_NAMESPACE

#endif
