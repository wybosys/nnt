
# ifndef __NNT_CUDA_PRV_ECDBD34203F54E7A9270A040BBE7C609_H_INCLUDED
# define __NNT_CUDA_PRV_ECDBD34203F54E7A9270A040BBE7C609_H_INCLUDED

# ifdef NNT_CUDA

#   ifdef NNT_CC_CUDA

#     include "../../3rd/cuda/cuda.h"
#     include "./CudaFunction.h"

#     define NNT_BEGIN_CUDA NNT_BEGIN_HEADER_CXX NNT_BEGIN_NS(cuda)
#     define NNT_END_CUDA NNT_END_HEADER_CXX NNT_END_NS

#   elif defined(NNT_MACH)

#     include <CUDA/cuda.h>

#   endif

# endif

# endif
