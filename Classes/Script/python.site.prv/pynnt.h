
# ifndef __PYNNT_C9BB09EE5A44428E9098E5703E8C4EED_H_INCLUDED
# define __PYNNT_C9BB09EE5A44428E9098E5703E8C4EED_H_INCLUDED

NNT_BEGIN_HEADER_C

# include <python/Include/Python.h>

NNT_END_HEADER_C

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

NNT_EXTERN ::nnt::core::string PyNNT_ToString(PyObject* obj);
NNT_EXTERN ::nnt::core::string PyNNT_ErrorMessage();

# define pystr(str) (char*)(str)

NNT_END_HEADER_CXX

# endif

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

NNT_EXTERN NSString* PyNNT_ErrorMessage();

NNT_END_HEADER_OBJC

# endif

# endif
