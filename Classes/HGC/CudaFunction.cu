
# include "../Core/Core.h"
# include "CudaFunction.h"
# include "cuda.prv.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(cuda)

Dimension::Dimension()
{
    memset(&ndr, 0, sizeof(ndr));
}

Dimension::~Dimension()
{
    
}

Parameter::Parameter(void* o, void* b, usize sz, bool nb)
: _origin(o), _buffer(b), _sz(sz), _needback(nb)
{
    
}

Parameter::~Parameter()
{
    if (_needback)
        back();
    
    cudaFree(_buffer);
}

Parameter Parameter::Input(void* da, NNTValueType vt, usize count)
{
    usize sz = vt_sizeof(vt) * count;
    void* buf;
    cudaMalloc(&buf, sz);
    cudaMemcpy(buf, da, sz, cudaMemcpyHostToDevice);
    return Parameter(da, buf, sz, false);
}

Parameter Parameter::InputOutput(void* da, NNTValueType vt, usize count)
{
    usize sz = vt_sizeof(vt) * count;
    void* buf;
    cudaMalloc(&buf, sz);
    cudaMemcpy(buf, da, sz, cudaMemcpyHostToDevice);
    return Parameter(da, buf, sz, true);
}

Parameter Parameter::Output(void* da, NNTValueType vt, usize count)
{
    usize sz = vt_sizeof(vt) * count;
    void* buf;
    cudaMalloc(&buf, sz);
    return Parameter(da, buf, sz, true);
}

void Parameter::back()
{
    cudaMemcpy(_origin, _buffer, _sz, cudaMemcpyDeviceToHost);
}

NNT_END_NS
NNT_END_CXX
