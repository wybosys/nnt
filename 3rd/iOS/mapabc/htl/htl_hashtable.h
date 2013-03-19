
/*
 * htl-lite - a basic data structures and algorithms.
 * Copyright (C) 2009 leon hong. All rights reserved.
 * authors:
 *   leon hong <codeblocker@gmail.com>
 */

#ifndef __HTL_HASHTABLE_H__
#define __HTL_HASHTABLE_H__

#include "htl_config.h"
#include "htl_vector.h"
#include "htl_pair.h"
#include "htl_hash_fun.h"

__HTL_BEGIN_NAMESPACE

template<class value>
struct hashtable_node {
    hashtable_node* next;
    value val;
};

template<class Value, class Key, class HashFcn,
        class ExtractKey, class EqualKey, class Alloc>
class hashtable;

template<class Value, class Key, class HashFcn,
        class ExtractKey, class EqualKey, class Alloc>
struct hashtable_iterator {
    typedef hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> _Hashtable;
    typedef hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> iterator;
    typedef hashtable_node<Value> node;

    typedef forward_iterator_tag iterator_category;
    typedef Value value_type;
    typedef ptrdiff_t difference_type;
    typedef Value* pointer;
    typedef Value& reference;
    typedef size_t size_type;

    node* cur;
    _Hashtable* ht;
    hashtable_iterator(node* n, _Hashtable* tab) : cur(n), ht(tab) {}
    hashtable_iterator() {}
    reference operator*() const { return cur->val; }
    pointer operator->() const { return &(operator*()); }
    iterator& operator++();
    iterator operator++(int);
    bool operator==(const iterator& it) const { return cur == it.cur; }
    bool operator!=(const iterator& it) const { return cur != it.cur; }
};

template<class Value, class Key, class HashFcn,
        class ExtractKey, class EqualKey, class Alloc>
typename hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::iterator&
hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::operator++() {
    node* old = cur;
    cur = cur->next;
    if (!cur) {
        size_type bucket = ht->bkt_num(old->val);
        while (!cur && ++bucket < ht->buckets.size())
            cur = ht->buckets[bucket];
    }
    return *this;
}

template<class Value, class Key, class HashFcn,
        class ExtractKey, class EqualKey, class Alloc>
typename hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::iterator
hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::operator++(int) {
    iterator tmp = *this;
    ++*this;
    return tmp;
}

static const int stl_num_primes = 28;
static const unsigned long stl_prime_list[stl_num_primes] =
{
  53,         97,           193,         389,       769,
  1543,       3079,         6151,        12289,     24593,
  49157,      98317,        196613,      393241,    786433,
  1572869,    3145739,      6291469,     12582917,  25165843,
  50331653,   100663319,    201326611,   402653189, 805306457,
  1610612741, 3221225473ul, 4294967291ul
};

inline unsigned long stl_next_prime(unsigned long n) {
    const unsigned long* first = stl_prime_list;
    const unsigned long* last = stl_prime_list + stl_num_primes;
    const unsigned long* pos = lower_bound(first, last, n);
    return pos == last ? *(last - 1) : *pos;
}

template<class Value, class Key, class HashFcn,
        class ExtractKey, class EqualKey, class Alloc = allocator>
class hashtable {
public:
    typedef HashFcn hasher;
    typedef EqualKey key_equal;
    typedef Key key_type;
    typedef hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> iterator;

    typedef forward_iterator_tag iterator_category;
    typedef Value value_type;
    typedef ptrdiff_t difference_type;
    typedef Value* pointer;
    typedef Value& reference;
    typedef size_t size_type;
    friend struct hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>;
private:
    hasher hash;
    key_equal equals;
    ExtractKey get_key;

    typedef hashtable_node<Value> node;
    typedef simple_alloc<node, Alloc> node_allocator;

    vector<node*, Alloc> buckets;
    size_type num_elements;
public:
    size_type bucket_count() const { return buckets.size(); }
    size_type size() const { return num_elements; }
    bool empty() const { return size() == 0; }
    size_type next_size(size_type n) const { return stl_next_prime(n); }
    hasher hash_funct() const { return hash; }
    key_equal key_eq() const { return equals; }
    size_type bkt_num(const value_type& obj, size_type n)  {
        return bkt_num_key(get_key(obj), n);
    }

    size_type bkt_num_key(const key_type& key)  {
        return bkt_num_key(key, buckets.size());
    }

    size_type bkt_num(const value_type& obj)  {
        return bkt_num_key(get_key(obj));
    }

    size_type bkt_num_key(const key_type& key, size_type n) {
        return hash(key) % n;
    }

    size_type max_bucket_count() const { return stl_prime_list[stl_num_primes - 1]; }
protected:
    node* new_node(const value_type& obj) {
        node*n = node_allocator::allocate();
        n->next = 0;
        construct(&n->val, obj);
        return n;
    }

    void delete_node(node* p) {
        destory(&p->val);
        node_allocator::deallocate(p);
    }
public:
    hashtable(size_type n,
              const hasher& hf,
              const key_equal& eql)
    : hash(hf), equals(eql), get_key(ExtractKey()), num_elements(0) {
        initialize_buckets(n);
    }

    hashtable(size_type n,
              const HashFcn& hf,
              const EqualKey& eql,
              const ExtractKey& ext)
    : hash(hf), equals(eql), get_key(ext), num_elements(0) {
        initialize_buckets(n);
    }

    hashtable(const hashtable& ht)
    : hash(ht.hash), equals(ht.equals), get_key(ht.get_key), num_elements(0) {
        copy_from(ht);
    }

    ~hashtable() { clear(); }
    pair<iterator, bool> insert_unique(const value_type& obj) {
        resize(num_elements + 1);
        return insert_unique_noresize(obj);
    }

    iterator insert_equal(const value_type& obj) {
        resize(num_elements + 1);
        return insert_equal_noresize(obj);
    }

    void clear();

    iterator begin() {
        for (size_t i = 0; i < buckets.size(); ++i)
            if (buckets[i])
                return iterator(buckets[i], this);
        return iterator(0, this);
    }

    iterator end() {
        return iterator(0, this);
    }

    iterator find(const key_type& key) {
        size_type n = bkt_num_key(key);
        node* first;
        for (first = buckets[n]; first && !equals(get_key(first->val), key); first = first->next)
            ;
        return iterator(first, this);
    }

    size_type count(const key_type& key) {
        size_type n = bkt_num_key(key);
        size_type result = 0;
        for (node* cur = buckets[n]; cur; cur = cur->next)
            if (equals(key, get_key(cur->val)))
                ++result;
        return result;
    }

    reference find_or_insert(const value_type& obj);
    pair<iterator, iterator> equal_range(const key_type& key);
    size_type erase(const key_type& key);
    void erase(const iterator& it);
    void resize(size_type num_elememts_hint);
protected:
    void initialize_buckets(size_type n) {
        const size_type n_buckets = next_size(n);
        buckets.reserve(n_buckets);
        buckets.insert(buckets.end(), n, (node*) 0);
        num_elements = 0;
    }
    pair<iterator, bool> insert_unique_noresize(const value_type& obj);
    iterator insert_equal_noresize(const value_type& obj);
    void copy_from(const hashtable& ht);
};

template<class Value, class Key, class HashFcn,
        class ExtractKey, class EqualKey, class Alloc>
void hashtable<Value, Key, HashFcn,
        ExtractKey, EqualKey, Alloc>::erase(const iterator& it) {
    if (node* p = it.cur) {
        const size_type n = bkt_num(it->val);
        node* cur = buckets[n];
        if (cur == p) {
            node* next = cur->next;
            delete_node(cur);
            buckets[n] = next;
            --num_elements;
        }
        else {
            node* next = cur->next;
            while (next) {
                if (next == it.cur) {
                    cur->next = next->next;
                    delete_node(next);
                    --num_elements;
                    break;
                }
                else {
                    cur = next;
                    next = cur->next;
                }
            }
        }
    }
}

template<class Value, class Key, class HashFcn,
        class ExtractKey, class EqualKey, class Alloc>
typename hashtable<Value, Key, HashFcn,ExtractKey, EqualKey, Alloc>::size_type
hashtable<Value, Key, HashFcn,ExtractKey, EqualKey, Alloc>::erase(const key_type& key) {
    const size_type n = bkt_num_key(key);
    node* first = buckets[n];
    size_type erased = 0;
    if (first) {
        node* cur = first;
        node* next = cur->next;
        while (next) {
            if (equals(get_key(next->val), key)) {
                next = next->next;
                cur->next = next;
                delete_node(cur->next);
                ++erased;
                --num_elements;
            }
            else {
                cur = next;
                next = cur->next;
            }
        }
        if (equals(get_key(first->val, key))) {
            buckets[n] = first->next;
            delete_node(first);
            ++erased;
            --num_elements;
        }
    }
    return erased;
}


template<class Value, class Key, class HashFcn,
        class ExtractKey, class EqualKey, class Alloc>
pair<typename hashtable<Value, Key, HashFcn,ExtractKey, EqualKey, Alloc>::iterator,
     typename hashtable<Value, Key, HashFcn,ExtractKey, EqualKey, Alloc>::iterator>
hashtable<Value, Key, HashFcn,
        ExtractKey, EqualKey, Alloc>::equal_range(const key_type& key) {
    size_type n = bkt_num_key(key);
    for (node* first = buckets[n]; first; first = first->next) {
        if (equals(get_key(first->val), key)) {
            for (node* cur = first->next; cur; cur = cur->next)
                if (!equals(get_key(cur->val), key))
                    return pair<iterator, iterator>(iterator(first, this), iterator(cur, this));
            for (size_type m = n + 1; m < buckets.size(); ++m)
                if (buckets[m])
                    return pair<iterator, iterator>(iterator(first, this), iterator(buckets[m], this));
            // n的下一个恰好是size，直接返回end
            return pair<iterator, iterator>(iterator(first, this), end());
        }
    }
    return pair<iterator, iterator>(end(), end());
}

template<class Value, class Key, class HashFcn,
        class ExtractKey, class EqualKey, class Alloc>
void hashtable<Value, Key, HashFcn,
        ExtractKey, EqualKey, Alloc>::copy_from(const hashtable& ht) {
    buckets.clear();
    buckets.reserve(ht.buckets.size());
    buckets.insert(buckets.end(), ht.buckets.size(), (node*) 0);
    for (size_t i = 0; i < ht.buckets.size(); ++i) {
        if (const node* cur = ht.buckets[i]) {
            node* tmp = new_node(ht.buckets[i]->val);
            buckets[i] = tmp;
            for (node* next = cur->next; next; ) {
                tmp->next = new_node(next->val);
                tmp = tmp->next;
                next = cur->next;
                cur = next;
            }
        }
    }
    num_elements = ht.num_elements;
}

template<class Value, class Key, class HashFcn,
        class ExtractKey, class EqualKey, class Alloc>
void hashtable<Value, Key, HashFcn,
        ExtractKey, EqualKey, Alloc>::clear() {
    for (size_t i = 0; i < buckets.size(); ++i) {
        node* cur = buckets[i];
        while (cur) {
            node* next = cur->next;
            delete_node(cur);
            cur = next;
        }
        buckets[i] = 0;
    }
    num_elements = 0;
}

template<class Value, class Key, class HashFcn,
        class ExtractKey, class EqualKey, class Alloc>
typename hashtable<Value, Key, HashFcn,ExtractKey, EqualKey, Alloc>::iterator
hashtable<Value, Key, HashFcn,
        ExtractKey, EqualKey, Alloc>::insert_equal_noresize(const value_type& obj) {
    const size_type n = bkt_num(obj);
    node* first = buckets[n];
    for (node* cur = first; cur; cur = cur->next)
        if (equals(get_key(obj), get_key(cur->val))) {
            node* tmp = new_node(obj);
            tmp->next = cur->next;
            cur->next = tmp;
            ++num_elements;
            return iterator(tmp, this);
        }
    node* tmp = new_node(obj);
    tmp->next = first;
    buckets[n] = tmp;
    ++num_elements;
    return iterator(tmp, this);
}

template<class Value, class Key, class HashFcn,
        class ExtractKey, class EqualKey, class Alloc>
void hashtable<Value, Key, HashFcn,
        ExtractKey, EqualKey, Alloc>::resize(size_type num_elememts_hint) {
    const size_type old_n = buckets.size();
    if (num_elememts_hint > old_n) {
        const size_type n = next_size(num_elememts_hint);
        if (n > old_n) {
            vector<node*, Alloc> tmp(n,(node*) 0);
            for (size_type i = 0; i < old_n; ++i) {
                node* first = buckets[i];
                while(first) {
                    size_type new_bucket = bkt_num(first->val, n);
                    buckets[i] = first->next;
                    first->next = tmp[new_bucket];
                    tmp[new_bucket] = first;
                    first = buckets[i];
                }
            }
            buckets.swap(tmp);
        }
    }
}

template<class Value, class Key, class HashFcn,
        class ExtractKey, class EqualKey, class Alloc>
pair<typename hashtable<Value, Key, HashFcn,ExtractKey, EqualKey, Alloc>::iterator, bool>
hashtable<Value, Key, HashFcn,
ExtractKey, EqualKey, Alloc>::insert_unique_noresize(const value_type& obj) {
    const size_type n = bkt_num(obj);
    node* first = buckets[n];
    for (node* cur = first; cur; cur = cur->next)
        if (equals(get_key(cur->val), get_key(obj)))
            return pair<iterator, bool>(iterator(cur, this), false);
    node* tmp = new_node(obj);
    tmp->next = first;
    buckets[n] = tmp;
    ++num_elements;
    return pair<iterator, bool>(iterator(tmp, this), true);
}

template<class Value, class Key, class HashFcn,
        class ExtractKey, class EqualKey, class Alloc>
typename hashtable<Value, Key, HashFcn,ExtractKey, EqualKey, Alloc>::reference
hashtable<Value, Key, HashFcn,
ExtractKey, EqualKey, Alloc>::find_or_insert(const value_type& obj) {
    size_type n = bkt_num(obj);
    node* first = buckets[n];
    for (node* cur = first; cur; cur = cur->next)
        if (equals(get_key(obj), get_key(cur->val)))
            return cur->val;
    node* tmp = new_node(obj);
    tmp->next = first;
    buckets[n] = tmp;
    ++num_elements;
    return tmp->val;
}

__HTL_END_NAMESPACE

#endif
