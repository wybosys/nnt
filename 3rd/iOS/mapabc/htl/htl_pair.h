
/*
 * htl-lite - a basic data structures and algorithms.
 * Copyright (C) 2009 leon hong. All rights reserved.
 * authors:
 *   leon hong <codeblocker@gmail.com>
 */

#ifndef __HTL_PAIR_H__
#define __HTL_PAIR_H__

#include "htl_config.h"

__HTL_BEGIN_NAMESPACE

template<class T1, class T2>
struct pair {
    typedef T1 first_type;
    typedef T1 second_type;
    T1 first;
    T2 second;
    pair() : first(T1()), second(T2()) {}
    pair(const T1& a, const T2& b) : first(a), second(b){ }
    template<class U1, class U2>
    pair(const pair<U1, U2>& p) : first(p.first), second(p.second){}
};

template<class T1, class T2>
inline bool operator==(const pair<T1, T2>& a, const pair<T1, T2>& b) {
    return a.first == b.first && a.second == b.second;
}

template<class T1, class T2>
inline bool operator<(const pair<T1, T2>& a, const pair<T1, T2>& b) {
    return a.first < b.first || (!(b.first < a.first) && a.second < b.second);
}

template<class T1, class T2>
inline pair<T1, T2> make_pair(const T1& x, const T2& y) {
    return pair<T1, T2>(x, y);
}

}
//__HTL_END_NAMESPACE

#endif
