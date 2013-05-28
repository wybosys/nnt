
# include "../Core/Core.h"
# include "cuda.prv.h"

__global__ void impl_square(float *input, float* output)
{
    uint pos = threadIdx.x;
    output[pos] = input[pos] * input[pos];
}

NNT_BEGIN_CUDA

void square(float* input, float* output, usize count)
{
    Dimension dim;
    dim->dim = 1;
    dim->count[0] = count;
    
    Parameter in = Parameter::Input(input, NNTValueTypeFloat, count);
    Parameter out = Parameter::Output(output, NNTValueTypeFloat, count);
    
    impl_square<<<dim->dim, dim->count[0]>>>(in, out);
}

NNT_END_CUDA
