
/*
 * htl-lite - a basic data structures and algorithms.
 * Copyright (C) 2009 leon hong. All rights reserved.
 * authors:
 *   leon hong <codeblocker@gmail.com>
 */

#ifndef __HTL_SET___
#define __HTL_SET___

#include "htl_functional.h"
#include "htl_tree.h"

__HTL_BEGIN_NAMESPACE

template<typename Key,
         typename Compare = htl::less<Key>,
         typename Alloc = allocator,
         template<typename TreeKey,
                  typename TreeValue,
                  typename TreeKeyOfvalue,
                  typename TreeCompare,
                  typename TreeAlloc = allocator > class CONT = rb_tree>
class set {
public:
    typedef Key key_type;
    typedef Key value_type;
    typedef Compare key_compare;
    typedef Compare value_compare;
private:
    typedef rb_tree<key_type, value_type, identity<value_type>, key_compare, Alloc> rep_type;
    rep_type t;
public:
    typedef typename rep_type::iterator iterator;
    typedef typename rep_type::reference reference;
    typedef typename rep_type::pointer pointer;
    typedef typename rep_type::size_type size_type;
    typedef typename rep_type::difference_type difference_type;
public:
    set() : t(Compare()) {}

    key_compare key_comp() const {
        return t.key_comp();
    }

    iterator begin() {
        return t.begin();
    }

    iterator end() {
        return t.end();
    }

    bool empty() {
        return t.empty();
    }

    size_type size() {
        return t.size();
    }

    pair<iterator, bool> insert(const value_type& x) {
        pair<typename rep_type::iterator, bool> p = t.insert_unique(x);
        return pair<iterator, bool>(p.first, p.second);
    }

    void erase(iterator pos) {
        return t.erase(pos);
    }

    size_type erase(const Key& x) {
        return t.erase(x);
    }

    void clear() {
        return t.clear();
    }

    iterator find(const key_type& x) {
        return t.find(x);
    }

    size_type count(const key_type& x) {
        return t.count(x);
    }

    iterator lower_bound(const key_type& x) {
        return t.lower_bound(x);
    }

    iterator upper_bound(const key_type& x) {
        return t.lower_bound(x);
    }

    pair<iterator, iterator> equal_range(const key_type& x) {
        return t.equal_range(x);
    }
};

__HTL_END_NAMESPACE

#endif
