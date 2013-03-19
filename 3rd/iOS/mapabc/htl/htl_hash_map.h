
/*
 * htl-lite - a basic data structures and algorithms.
 * Copyright (C) 2009 leon hong. All rights reserved.
 * authors:
 *   leon hong <codeblocker@gmail.com>
 */

#ifndef __HTL_HASH_MAP__
#define __HTL_HASH_MAP__

#include "htl_hashtable.h"
#include "htl_functional.h"

__HTL_BEGIN_NAMESPACE

template<class Key,
         class T,
         class HashFcn = hash<T>,
         class EqualKey = equal_to<T>,
         class Alloc = allocator>
class hash_map {
private:
    typedef hashtable<pair<Key, T>, Key, HashFcn,
                    select1st<pair<Key, T> >, EqualKey, Alloc> ht;
    ht rep;
public:
    typedef typename ht::key_type key_type;
    typedef typename ht::value_type value_type;
    typedef typename ht::key_equal key_equal;
    typedef typename ht::hasher hasher;

    typedef typename ht::size_type size_type;
    typedef typename ht::iterator iterator;
    typedef typename ht::difference_type difference_type;
    typedef typename ht::reference reference;
    typedef typename ht::pointer pointer;

    hasher hash_funct() const { return rep.hash_funct(); }
    key_equal key_eq() const { return rep.key_eq(); }
public:
    hash_map() : rep(100, hasher(), key_equal()) {}
    hash_map(size_type n) : rep(n, hasher(), key_equal()) {}
public:
    size_type size() const { return rep.size(); }
    bool empty() const { return rep.empty(); }
    iterator begin() { return rep.begin(); }
    iterator end() { return rep.end(); }
    pair<iterator, bool> insert(const value_type& obj) {
        return rep.insert(obj);
    }

    pair<iterator, bool> insert_noresize(const value_type& obj) {
        return rep.insert_noresize(obj);
    }

    iterator find(const key_type& key) {
        return rep.find(key);
    }

    T& operator[](const key_type& key) {
        // 先将默认T() insert,之后返回T也就是iterator的second作为左值，hp["hello"] = 1;
        return rep.find_or_insert(value_type(key, T())).second;
    }

    size_type count(const key_type& key) {
        return rep.count(key);
    }

    pair<iterator, iterator> equal_range(const key_type& key) {
        return rep.equal_range(key);
    }

    size_type erase(const key_type& key) {
        return rep.erase(key);
    }

    void erase(iterator it) {
        return rep.erase(it);
    }
};

__HTL_END_NAMESPACE

#endif
