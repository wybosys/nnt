
/*
 * htl-lite - a basic data structures and algorithms.
 * Copyright (C) 2009 leon hong. All rights reserved.
 * authors:
 *   leon hong <codeblocker@gmail.com>
 */

#ifndef __HTL_CONFIG_H__
#define __HTL_CONFIG_H__


#define __HTL_BEGIN_NAMESPACE namespace htl {
#define __HTL_END_NAMESPACE }

#define __HTL htl


# ifdef __STL_USE_EXCEPTIONS
#   define __STL_TRY try
#   define __STL_CATCH_ALL catch(...)
#   define __STL_THROW(x) throw x
#   define __STL_RETHROW throw
#   define __STL_NOTHROW throw()
#   define __STL_UNWIND(action) catch(...) { action; throw; }
# else
#   define __STL_TRY 
#   define __STL_CATCH_ALL if (false)
#   define __STL_THROW(x) 
#   define __STL_RETHROW 
#   define __STL_NOTHROW 
#   define __STL_UNWIND(action) 
# endif

#endif
