
/*
 * htl-lite - a basic data structures and algorithms.
 * Copyright (C) 2009 leon hong. All rights reserved.
 * authors:
 *   leon hong <codeblocker@gmail.com>
 */

#ifndef __HTL_ALLOC_H__
#define __HTL_ALLOC_H__

// <cstdlib>
#include <stdlib.h>
#include "htl_config.h"

__HTL_BEGIN_NAMESPACE

class allocator {

public:
    static void* allocate(size_t n) {
        void* result = malloc(n);
        if (!result) {
            // malloc…Í«Î ß∞‹
        }
        return result;
    }

    static void deallocate(void* p, size_t/* n*/) {
        free(p);
    }

    static void* reallocate(void* p, size_t old_sz, size_t new_sz) {
        void* result = realloc(p, new_sz);
        if (!result) {
            // realloc…Í«Î ß∞‹
        }
        return result;
    }
};

template<typename T, typename Alloc>
class simple_alloc {

public:
    static T* allocate(size_t n) {
        return n == 0 ? 0 : (T*)Alloc::allocate(n*sizeof(T));
    }

    static T* allocate(void) {
        return (T*)Alloc::allocate(sizeof(T));
    }

    static void deallocate(T* p, size_t n) {
        if (n) {
            Alloc::deallocate(p, sizeof(T)*n);
        }
    }

    static void deallocate(T* p) {
        Alloc::deallocate(p, sizeof(T));
    }
};

__HTL_END_NAMESPACE

#endif
