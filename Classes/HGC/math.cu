
# include "../Core/Core.h"

__global__ void square(float *input, float* output)
{
    uint pos = blockIdx.x;
    output[pos] = input[pos] * input[pos];
}