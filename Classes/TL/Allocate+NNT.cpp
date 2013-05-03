
# include "Core.h"
# include "Allocate+NNT.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(ntl)
    
NNT_END_NS
NNT_END_CXX

NNT_BEGIN_C

# ifdef NNT_KERNEL_SPACE
    
# ifdef NNT_BSD

MALLOC_DEFINE(NNT_MP_NTLA, "ntl::alloc", "ntl::alloc");

# endif

# endif

NNT_END_C
