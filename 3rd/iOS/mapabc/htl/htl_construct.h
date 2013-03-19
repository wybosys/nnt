
/*
 * htl-lite - a basic data structures and algorithms.
 * Copyright (C) 2009 leon hong. All rights reserved.
 * authors:
 *   leon hong <codeblocker@gmail.com>
 */

#ifndef __HTL_CONSTRUCT__
#define __HTL_CONSTRUCT__


#ifdef ANDROID_PHONE    //cgywin±àÒë²»¹ý£¬ÆÁ±Î£¬ÀµºèÏéÐÞ¸Ä
#include <new>
#else
#include <new.h>
#endif
//#include <e32std.h>
#include "htl_config.h"

__HTL_BEGIN_NAMESPACE

template<typename T, typename VALUE>
inline void construct(T* p, const VALUE& value) {
    new (p) T(value);
}

template<typename T>
inline void destory(T* p) {
    p->~T();
}

template<typename ForwardIterator>
inline void destory(ForwardIterator first, ForwardIterator last) {
    for (; first < last; ++first)
        destory(&*first);
}

__HTL_END_NAMESPACE

#endif
