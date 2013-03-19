
/*
 * htl-lite - a basic data structures and algorithms.
 * Copyright (C) 2009 leon hong. All rights reserved.
 * authors:
 *   leon hong <codeblocker@gmail.com>
 */

#ifndef __HTL_STACK_H__
#define __HTL_STACK_H__

#include "htl_deque.h"

__HTL_BEGIN_NAMESPACE

template<class T, class Sequence = deque<T> >
class stack {
    friend bool operator==(const stack&, const stack&);
    friend bool operator<(const stack&, const stack&);
protected:
    Sequence c;
public:
    typedef typename Sequence::value_type value_type;
    typedef typename Sequence::reference reference;
    typedef typename Sequence::size_type size_type;
public:
    bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }
    reference top() { return c.back(); }
    void push(const value_type& x) { c. push_back(x); }
    void pop() { c.pop_back(); }
};

template<class T, class Sequence>
bool operator==(const stack<T, Sequence>& x, const stack<T, Sequence>& y) {
    return x.c == y.c;
}

template <class T, class Sequence>
bool operator<(const stack<T, Sequence>& x, const stack<T, Sequence>& y) {
  return x.c < y.c;
}

__HTL_END_NAMESPACE

#endif
