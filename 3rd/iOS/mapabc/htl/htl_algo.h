
/*
 * htl-lite - a basic data structures and algorithms.
 * Copyright (C) 2009 leon hong. All rights reserved.
 * authors:
 *   leon hong <codeblocker@gmail.com>
 */

#ifndef __HTL_ALGO_H__
#define __HTL_ALGO_H__

#include "htl_config.h"
#include "htl_iterator.h"

__HTL_BEGIN_NAMESPACE

#define __STL_REQUIRES(__type_var, __concept) \
do { \
  void (*__x)( __type_var ) = __concept##_concept_specification< __type_var >\
    ::__concept##_requirement_violation; __x = __x; } while (0)


// find_first_of, with and without an explicitly supplied comparison function.
/*
template <typename _InputIter, typename _ForwardIter>
inline _InputIter find_first_of(_InputIter __first1, _InputIter __last1,
                         _ForwardIter __first2, _ForwardIter __last2)
{
  __STL_REQUIRES(_InputIter, _InputIterator);
  __STL_REQUIRES(_ForwardIter, _ForwardIterator);
  __STL_REQUIRES_BINARY_OP(_OP_EQUAL, bool, 
     typename iterator_traits<_InputIter>::value_type,
     typename iterator_traits<_ForwardIter>::value_type);

  for ( ; __first1 != __last1; ++__first1) 
    for (_ForwardIter __iter = __first2; __iter != __last2; ++__iter)
      if (*__first1 == *__iter)
        return __first1;
  return __last1;
}

template <class _InputIter, class _ForwardIter, class _BinaryPredicate>
_InputIter find_first_of(_InputIter __first1, _InputIter __last1,
                         _ForwardIter __first2, _ForwardIter __last2,
                         _BinaryPredicate __comp)
{
  __STL_REQUIRES(_InputIter, _InputIterator);
  __STL_REQUIRES(_ForwardIter, _ForwardIterator);
  __STL_BINARY_FUNCTION_CHECK(_BinaryPredicate, bool,
     typename iterator_traits<_InputIter>::value_type,
     typename iterator_traits<_ForwardIter>::value_type);

  for ( ; __first1 != __last1; ++__first1) 
    for (_ForwardIter __iter = __first2; __iter != __last2; ++__iter)
      if (__comp(*__first1, *__iter))
        return __first1;
  return __last1;
}
*/
template<typename InputIterator, typename Distance>
inline void distance(InputIterator first, InputIterator last, Distance& n) {
    for (; first != last; ++first)
        ++n;
}

template <class InputIterator, class Distance>
inline void advance(InputIterator& i, Distance n) {
    while(n--) ++i;
}

// 第一个不小于value的元素
template<class ForwardIterator, class T>
inline ForwardIterator lower_bound(ForwardIterator first,
                                   ForwardIterator last,
                                   const T& value) {
    typename iterator_traits<ForwardIterator>::difference_type len = 0;
    distance(first, last, len);
    typename iterator_traits<ForwardIterator>::difference_type half;
    ForwardIterator middle;
    while (len > 0) {
        half = len >> 1;
        middle = first;
        advance(middle, half);
        if (*middle < value) {
            first = middle;
            ++first;
            len = len - half - 1;
        }
        else {
            len = half;
        }
    }
    return first;
}

template<class T>
inline void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

__HTL_END_NAMESPACE

#endif
