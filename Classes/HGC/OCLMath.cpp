
# include "Core.h"
# include "OCLMath.h"
# include "OCLFunction.h"

# ifdef NNT_OPENCL

# include "math.cl.h"

# endif

NNT_BEGIN_CXX
NNT_BEGIN_NS(opencl)

void square(void* input, void* output, NNTOpenCLValueType vt, uinteger cnt)
{
    Function func((Function::block_t)square_kernel);
    Parameter in = Parameter::Input(input, vt, cnt);
    Parameter out = Parameter::Output(output, vt, cnt);
    
    Dimension d;
    d.dim = 1;
    d.count[0] = cnt;

    func.invoke(d, in, out);
}

NNT_END_NS
NNT_END_CXX
