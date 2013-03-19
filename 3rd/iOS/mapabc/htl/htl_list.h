
/*
 * htl-lite - a basic data structures and algorithms.
 * Copyright (C) 2009 leon hong. All rights reserved.
 * authors:
 *   leon hong <codeblocker@gmail.com>
 */

#ifndef __HTL_LIST_H__
#define __HTL_LIST_H__

#include "htl_alloc.h"
#include "htl_algo.h"

__HTL_BEGIN_NAMESPACE

template<class T>
struct list_node {
    list_node<T>* prev;
    list_node<T>* next;
    T data;
};

template<class T, class Ref, class Ptr>
struct list_iterator {
    typedef list_iterator<T, T&, T*> iterator;
    typedef list_iterator<T, const T&, const T*> const_iterator;
    typedef list_iterator<T, Ref, Ptr> self;

    typedef bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef Ref reference;
    typedef Ptr pointer;

    typedef list_node<T>* link_type;
    typedef size_t size_type;

    link_type node;

    // construct
    list_iterator() {};
    list_iterator(link_type x) : node(x) {}
    list_iterator(const iterator& x) : node(x.node) {}

    bool operator==(const self& x) const { return node == x.node; }
    bool operator!=(const self& x) const { return node != x.node; }
    reference operator*() const { return (*node).data; }
    pointer operator->() const { return &(operator*()); }
    self& operator++() {
        node = (link_type)((*node).next);
        return *this;
    }
    self operator++(int) {
        self tmp = *this;
        ++*this;
        return tmp;
    }
    self& operator--() {
        node = (link_type)((*node).prev);
        return *this;
    }
    self operator--(int) {
        self tmp = *this;
        --*this;
        return tmp;
    }
};

template<class T, class Alloc = allocator>
class list  {
public:
    typedef list_iterator<T, T&, T*> iterator;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef const value_type* const_pointer;
    typedef const value_type& const_reference;

    typedef list_node<T>* link_type;
    typedef size_t size_type;
    typedef simple_alloc<list_node<T>, Alloc> list_node_allocator;
protected:
    link_type node;
public:
    iterator begin() { return (link_type)((*node).next); }
    iterator end() { return node; }
    reference front() { return *begin(); }
    reference back() { return *(end() - 1); }
    bool empty() const { return node == node.next; }
    size_type size() const {
        size_type result = 0;
        distance(begin(), end(), result);
        return result;
    }
protected:
    link_type get_node() { return list_node_allocator::allocate(); }
    void put_node(link_type p) { list_node_allocator::deallocate(p); }

    link_type create_node(const T& x) {
        link_type p = get_node();
        construct(&p->data, x);
        return p;
    }

    void destory_node(link_type p) {
        destory(&p->data);
        put_node(p);
    }
public:
    // construct
    list() { empty_initialize(); }
    ~list() {
        clear();
        put_node(node);
    }
protected:
    void empty_initialize() {
        node = get_node();
        node->next = node;
        node->prev = node;
    }
public:
    iterator insert(iterator pos, const T& x) {
        link_type tmp = create_node(x);
        tmp->next = pos.node;
        tmp->prev = pos.node->prev;
        pos.node->prev->next = tmp;
        pos.node->prev = tmp;
        return tmp;
    }

    void push_front(const T& x) {
        insert(begin(), x);
    }

    void push_back(const T& x) {
        insert(end(), x);
    }

    iterator erase(iterator pos) {
        link_type next_node = pos.node->next;
        link_type prev_node = pos.node->prev;
        prev_node->next = next_node;
        next_node->prev = prev_node;
        destory_node(pos.node);
        return iterator(next_node);
    }

    void pop_front() {
        erase(begin());
    }

    void pop_back() {
        iterator it = end();
        erase(--it);
    }

    void clear();
    void remove(const T& x);
    void unique();
};

template<class T, class Alloc>
void list<T, Alloc>::clear() {
    link_type cur = (*node).next;
    while (cur != node) {
        link_type tmp = cur;
        cur = cur->next;
        destory_node(tmp);
    }
    node->next = node;
    node->prev = node;
}

template<class T, class Alloc>
void list<T, Alloc>::remove(const T& x) {
    iterator first = begin();
    iterator last = end();
    while (first != last) {
        iterator next = first;
        ++next;
        if (*first == x) erase(first);
        first = next;
    }
}

template<class T, class Alloc>
void list<T, Alloc>::unique() {
    iterator first = begin();
    iterator last = end();
    if (first == last) return;
    iterator next = first;
    while (++next != last) {
        if (*next == *first)
            erase(next);
        else
            first = next;
        next = first;
    }
}

__HTL_END_NAMESPACE

#endif
