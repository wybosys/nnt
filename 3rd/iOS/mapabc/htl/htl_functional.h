
/*
 * htl-lite - a basic data structures and algorithms.
 * Copyright (C) 2009 leon hong. All rights reserved.
 * authors:
 *   leon hong <codeblocker@gmail.com>
 */

#ifndef __HTL_FUNCTIONAL_H__
#define __HTL_FUNCTIONAL_H__

#include "htl_pair.h"

__HTL_BEGIN_NAMESPACE

template<class Arg, class Result>
struct unary_function {
    typedef Arg argument_type;
    typedef Result result_type;
};

template<class Arg1, class Arg2, class Result>
struct binary_function {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};

template<class T>
struct equal_to : public binary_function<T, T, bool> {
    bool operator()(const T& a, const T& b) const {
        return a == b;
    }
};

template<class T>
struct identity : public unary_function<T, T> {
    const T& operator()(const T& x) const { return x; }
};

template<class Pair>
struct select1st : public unary_function<Pair, typename Pair::first_type> {
    const typename Pair::first_type operator()(const Pair& x) const { return x.first; }
};

template<class T>
struct less : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) {
        return x < y;
    }
};

__HTL_END_NAMESPACE

#endif

