
# include "Core.h"
# include "OCLFunction.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(opencl)

Parameter::Parameter(void* origin, void* buf, usize sz, bool back)
: _buffer(buf), _origin(origin), _size(sz), _needback(back)
{
    
}

Parameter::~Parameter()
{
# ifdef NNT_OPENCL
    
    gcl_free(_buffer);
    
# endif
}

Parameter Parameter::Input(void *in, NNTOpenCLValueType vt, uinteger cnt)
{
    usize const sz = vt_sizeof(vt) * cnt;
    void* buf = NULL;
    
# ifdef NNT_OPENCL
    
    buf = gcl_malloc(sz, in, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR);
    
# endif
    
    return Parameter(in, buf, sz);
}

Parameter Parameter::InputOutput(void *in, NNTOpenCLValueType vt, uinteger cnt)
{
    usize const sz = vt_sizeof(vt) * cnt;
    void* buf = NULL;
    
# ifdef NNT_OPENCL
    
    buf = gcl_malloc(sz, in, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR);
    
# endif
    
    return Parameter(in, buf, sz, true);
}

Parameter Parameter::Output(void *out, NNTOpenCLValueType vt, uinteger cnt)
{
    usize const sz = vt_sizeof(vt) * cnt;
    void* buf = NULL;
    
# ifdef NNT_OPENCL
    
    buf = gcl_malloc(sz, NULL, CL_MEM_READ_WRITE);
    
# endif
    
    return Parameter(out, buf, sz, true);
}

void Parameter::back()
{
    if (_needback == false)
        return;
    
# ifdef NNT_OPENCL
    
    gcl_memcpy(_origin, _buffer, _size);
    
# endif
}

Dimension::Dimension()
: dim(0)
{
    offset[0] = offset[1] = offset[2] = 0;
    count[0] = count[1] = count[2] = 0;
    
# ifdef NNT_OPENCL
    memset(&_ndr, 0, sizeof(_ndr));
# endif
}

Dimension::operator range_t () const
{
# ifdef NNT_OPENCL
    
    cl_ndrange& ndr = ntl::down_const(_ndr);
    ndr.work_dim = dim;
    ndr.global_work_offset[0] = offset[0];
    ndr.global_work_offset[1] = offset[1];
    ndr.global_work_offset[2] = offset[2];
    ndr.global_work_size[0] = count[0];
    ndr.global_work_size[1] = count[1];
    ndr.global_work_size[2] = count[2];
    
# endif
    
    return (range_t)&_ndr;
}

void Dimension::update(Function const& func)
{
# ifdef NNT_OPENCL
    
    usize wgs = func.wgs();
    _ndr.local_work_size[0] = count[0] / wgs;
    if (_ndr.local_work_size[0] == 0)
        _ndr.local_work_size[0] = 1;
    if (count[1])
    {
        _ndr.local_work_size[1] = count[1] / wgs;
        if (_ndr.local_work_size[1] == 0)
            _ndr.local_work_size[1] = 1;
    }
    if (count[2])
    {
        _ndr.local_work_size[2] = count[2] / wgs;
        if (_ndr.local_work_size[2] == 0)
            _ndr.local_work_size[2] = 1;
    }
    
# endif
}

NNT_BEGIN_HEADER_C

typedef void (^functype_2)(void const*, void*, void*);

NNT_END_HEADER_C

Function::Function(block_t block)
: _block(block), _device(Device::Current())
{

}

Function::~Function()
{

}

usize Function::wgs() const
{
    usize ret = 1;
    
# ifdef NNT_OPENCL
    
    gcl_get_kernel_block_workgroup_info(_block,
                                        CL_KERNEL_WORK_GROUP_SIZE,
                                        sizeof(ret),
                                        &ret,
                                        NULL);
    
# endif
    
    return ret;
}

void Function::invoke(Dimension const& d, Parameter& _0, Parameter& _1)
{
    functype_2 func = (functype_2)_block;

# ifdef NNT_OPENCL
    
# ifdef NNT_MACH
    
    use<dispatch_queue_t> queue = _device.queue();
    
    dispatch_sync(queue, ^{
        ntl::down_const(d).update(*this);
        cl_ndrange* ndr = (cl_ndrange*)d;
        
        func(ndr, _0, _1);
        
        _0.back(); _1.back();
    });
    
# endif
    
# endif
}

NNT_END_NS
NNT_END_CXX
