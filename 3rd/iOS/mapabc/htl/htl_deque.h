
/*
 * htl-lite - a basic data structures and algorithms.
 * Copyright (C) 2009 leon hong. All rights reserved.
 * authors:
 *   leon hong <codeblocker@gmail.com>
 */

#include "htl_iterator.h"
#include "htl_alloc.h"
#include "htl_uninitialized.h"
#include "htl_config.h"

#ifndef __HTL_DEQUE_H__
#define __HTL_DEQUE_H__

inline size_t __deque_buf_size(size_t n, size_t sz) {
    return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
}
__HTL_BEGIN_NAMESPACE
template<class T, class Ref, class Ptr, size_t BufSize>
struct deque_iterator {
    typedef deque_iterator<T, T&, T*, BufSize> iterator;
    typedef deque_iterator<T, const T&, const T*, BufSize> const_iterator;

    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef Ptr pointer;
    typedef Ref reference;

    typedef size_t size_type;
    typedef T** map_pointer;
    typedef deque_iterator<T, Ref, Ptr, BufSize> self;

    T* cur;
    T* first;
    T* last;
    map_pointer node;

    // construct
    deque_iterator() : cur(0), first(0), last(0), node(0){}
    deque_iterator(const iterator& x)
    : cur(x.cur), first(x.first), last(x.last), node(x.node) {}
    deque_iterator(T* x, map_pointer y)
    : cur(x), first(*y), last(*y + difference_type(buffer_size())), node(y) {}

    static size_t buffer_size() {
        return __deque_buf_size(BufSize, sizeof(T));
    }

    void set_node(map_pointer new_node) {
        node = new_node;
        first = *new_node;
        last = first + difference_type(buffer_size());
    }

    reference operator*() const { return *cur; }
    pointer operator->() const { return &(operator*()); }

    difference_type operator-(const self& x) const {
        return difference_type(buffer_size())*(node - x.node - 1) +
            (cur - first) + (x.last - x.cur);
    }

    self& operator++() {
        ++cur;
        if (cur == last) {
            set_node(node + 1);
            cur = first;
        }
        return *this;
    }

    self operator++(int) {
        self tmp = *this;
        ++*this;
        return tmp;
    }

    self operator--() {
        if (cur == first) {
            set_node(node - 1);
            cur = last;
        }
        --cur;
        return *this;
    }

    self operator--(int) {
        self tmp = *this;
        --*this;
        return tmp;
    }

    self& operator+=(difference_type n) {
        difference_type offset = (cur - first) + n;
        if (offset >= 0 && offset < difference_type(buffer_size()))
            cur += n;
        else {
            difference_type node_offset =
            offset > 0 ? offset / difference_type(buffer_size())
            : -difference_type((-offset - 1) / buffer_size()) - 1;

            set_node(node + node_offset);
            cur = first + (offset - node_offset * difference_type(buffer_size()));
        }
        return *this;
    }

    self operator+(difference_type n) const{
        self tmp = *this;
        return tmp += n;
    }

    self operator-=(difference_type n) {
        return *this += -n;
    }

    self operator-(difference_type n) const{
        self tmp = *this;
        return tmp -= n;
    }

    reference operator[](difference_type n) const { return *(*this + n); }
    bool operator==(const self& x) const { return x.cur == cur; }
    bool operator!=(const self& x) const { return !(*this == x); }
    bool operator<(const self& x) const {
        return (node == x.node) ? (cur < x.cur) : (node < x. node);
    }
};

template<class T, class Alloc = allocator, size_t BufSize = 0>
class deque {
public:
    typedef deque_iterator<T, T&, T*, BufSize> iterator;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;

    typedef size_t size_type;
    typedef pointer* map_pointer;
protected:
    iterator start;
    iterator finish;
    map_pointer map;
    size_type map_size;

    typedef simple_alloc<value_type, Alloc> data_allocator;
    typedef simple_alloc<pointer, Alloc> map_allocator;
public:
    // construct
    deque() : start(), finish(), map(0), map_size(0) {
        create_map_and_nodes(0);
    }
    deque(int n, const value_type& value)
    : start(), finish(), map(0), map_size(0) {
        fill_initialize(n, value);
    }
    ~deque() {
        destory(start, finish);
        destory_map_and_nodes();
    }
    iterator begin() { return start; }
    iterator end() { return finish; }
    reference operator[](difference_type n) { return start[n]; }
    reference front() { return *start; }
    reference back() {
        iterator tmp = finish;
        --tmp;
        return *tmp;
        // return *(finish - 1);
    }
    size_type size() const { return finish - start; }
    size_type max_size() const { return size_type(-1); }
    bool empty() const { return start == finish; }
    static size_type buffer_size() {
    return __deque_buf_size(BufSize, sizeof(value_type));
  }
protected:
    void destory_map_and_nodes() {
        for (map_pointer cur = start.node; cur <= finish.node; ++cur)
            data_allocator::deallocate(*cur, buffer_size());
        map_allocator::deallocate(map, map_size);
    }
    void fill_initialize(size_type n, const value_type& value);
    void create_map_and_nodes(size_type num_elements);
    static size_type initial_map_size() { return 8; }
    pointer allocate_node() { return data_allocator::allocate(buffer_size()); }

    void push_back_aux(const value_type& x);
    void reserve_map_at_back(size_type nodes_to_add = 1);

    void push_front_aux(const value_type& x);
    void reserve_map_at_front(size_type nodes_to_add = 1);

    void reallocate_map(size_type nodes_to_add, bool add_at_front);

    void pop_back_aux();
    void pop_front_aux();
    void deallocate_node(pointer p) { return data_allocator::deallocate(p, buffer_size()); }

    iterator insert_aux(iterator pos, const value_type& x);
public:
    void push_back(const value_type& x) {
        if (finish.cur != finish.last - 1) {
            construct(finish.cur, x);
            ++finish.cur;
        }
        else
            push_back_aux(x);
    }

    void push_front(const value_type& x) {
        if (start.cur != start.first) {
            --start.cur;
            construct(start.cur, x);
        }
        else
            push_front_aux(x);
    }

    void pop_back() {
        if (finish.cur != finish.first) {
            --finish.cur;
            destory(finish.cur);
        }
        else
            pop_back_aux();
    }

    void pop_front() {
        if (start.cur != start.last - 1) {
            destory(start.cur);
            ++start.cur;
        }
        else
            pop_front_aux();
    }

    void clear();
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);
    iterator insert(iterator pos, const value_type& x);
};

template<class T, class Alloc, size_t BufSize>
typename deque<T, Alloc, BufSize>::iterator
deque<T, Alloc, BufSize>::insert(iterator pos, const value_type& x) {
    if (pos.cur == start.cur) {
        push_front(x);
        return start;
    }
    else if (pos.cur == finish.cur) {
        push_back(x);
        iterator tmp = finish;
        --tmp;
        return tmp;
    }
    else {
        return insert_aux(pos, x);
    }
}

template<class T, class Alloc, size_t BufSize>
typename deque<T, Alloc, BufSize>::iterator
deque<T, Alloc, BufSize>::insert_aux(iterator pos, const value_type& x) {
    difference_type index = pos - start;
    if (index < (size() >> 1)) {
        push_front(front());
        iterator front1 = start;
        ++front1;
        iterator front2 = front1;
        ++front2;
        pos = start + index;    // 此步必须有，因为start经过pish_front()已经改变
        iterator pos1 = pos;
        ++pos1;
        copy(front2, pos1, front1);
    }
    else {
        push_back(back());
        iterator back1 = finish;
        --back1;
        iterator back2 = back1;
        --back2;
        pos = finish - index;
        copy_backward(pos, back2, back1);
    }
    *pos = x;
    return pos;
}

template<class T, class Alloc, size_t BufSize>
typename deque<T, Alloc, BufSize>::iterator
deque<T, Alloc, BufSize>::erase(iterator first, iterator last) {
    if (first == start && last == finish) {
        clear();
        return finish;
    }
    else {
        difference_type n = last - first;
        difference_type elems_before = first - start;
        if (elems_before < (size() - n) / 2) {
            copy_backward(start, first, last);
            iterator new_start = start + n;
            destory(start, new_start);
            // destory(start.cur, new_start.cur);应该和上面等价
            for (map_pointer cur = start.node; cur < new_start.node; ++cur)
                data_allocator::deallocate(*cur, buffer_size());
            start = new_start;
        }
        else {
            copy(last, finish, first);
            iterator new_finish = finish - n;
            destory(new_finish, finish);
            for (map_pointer cur = new_finish.node + 1; cur <= finish.node; ++cur)
                data_allocator::deallocate(*cur, buffer_size());
            finish = new_finish;
        }
        return start + elems_before;
    }
}

template<class T, class Alloc, size_t BufSize>
typename deque<T, Alloc, BufSize>::iterator
deque<T, Alloc, BufSize>::erase(iterator pos) {
    iterator next = pos;
    ++next;
    difference_type index = pos - start;
    if (index < (size() >> 1)) {
        copy_backward(start, pos, next);
        pop_front();
    }
    else {
        copy(next, finish, pos);
        pop_back();
    }
    return start + index;
}

template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::clear() {
    for (map_pointer cur = start.node + 1; cur < finish.node; ++cur) {
        destory(*cur, *cur + buffer_size());
        data_allocator::deallocate(*cur, buffer_size());
    }
    if (start.node != finish.node) {
        destory(start.cur, start.last);
        destory(finish.first, finish.cur);
        data_allocator::deallocate(finish.first, buffer_size());
    }
    else
        destory(start.cur, finish.cur);
    finish = start;
}

template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::pop_front_aux() {
    destory(start.cur);
    deallocate_node(start.first);
    start.set_node(start.node + 1);
    start.cur = start.first;
}

template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::pop_back_aux() {
    deallocate_node(finish.first);
    finish.set_node(finish.node - 1);
    finish.cur = finish.last - 1;
    destory(finish.cur);
}
template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::fill_initialize(size_type n, const value_type& value) {
    create_map_and_nodes(n);
    map_pointer cur;
    for (cur = start.node; cur < finish.node; ++cur)
        uninitalized_fill(*cur, *cur + buffer_size(), value);
    uninitalized_fill(finish.first, finish.cur, value);
}

template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::create_map_and_nodes(size_type num_elements) {
    size_type num_nodes = num_elements / buffer_size() + 1;
    map_size = htl_max(initial_map_size(), num_nodes + 2);
    map = map_allocator::allocate(map_size);
    map_pointer nstart = map + (map_size - num_nodes) / 2;
    map_pointer nfinish = nstart + (num_nodes - 1);
    map_pointer cur;
    for (cur = nstart; cur <= nfinish; ++cur)
        *cur = allocate_node();
    start.set_node(nstart);
    finish.set_node(nfinish);
    start.cur = start.first;
    finish.cur = finish.first + num_elements % buffer_size();
}
template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::push_back_aux(const value_type& x) {
    reserve_map_at_back();
    *(finish.node + 1) = allocate_node();
    construct(finish.cur, x);
    finish.set_node(finish.node + 1);
    finish.cur = finish.first;
}

template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::reserve_map_at_back(size_type nodes_to_add) {
    if (nodes_to_add + 1 > map_size - (finish.node - map))
        reallocate_map(nodes_to_add, false);
}

template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::push_front_aux(const value_type& x) {
    reserve_map_at_front();
    *(start.node - 1) = allocate_node();
    start.set_node(start.node - 1);
    start.cur = start.last - 1;
    construct(start.cur, x);
}

template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::reserve_map_at_front(size_type nodes_to_add) {
    if (nodes_to_add > start.node - map)
        reallocate_map(nodes_to_add, true);
}

template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::reallocate_map(size_type nodes_to_add,
                                        bool add_at_front) {
    size_type old_num_nodes = finish.node - start.node + 1;
    size_type new_num_nodes = old_num_nodes + nodes_to_add;
    map_pointer new_nstart;
    if (map_size > 2 * new_num_nodes) {
        new_nstart = map + (map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
        if (new_nstart < start.node)
            copy(start.node, finish.node + 1, new_nstart);
        else
            copy_backward(start.node, finish.node + 1, new_nstart +  old_num_nodes);
    }
    else {
        size_type new_map_size = map_size + htl_max(map_size, nodes_to_add) + 2;
        map_pointer new_map = map_allocator::allocate(new_map_size);
        new_nstart = new_map + (map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
        copy(start.node, finish.node + 1, new_map);
        map_allocator::deallocate(map, map_size);
        map = new_map;
        map_size = new_map_size;
    }
    start.set_node(new_nstart);
    finish.set_node(new_nstart + old_num_nodes - 1);
}

__HTL_END_NAMESPACE

#endif
