
# include "Core.h"
# include "CudaInfo.h"
# include "cuda.prv.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(cuda)

NNTDECL_PRIVATE_BEGIN_CXX(Info)

void init()
{
# ifdef NNT_MACH
    
    use<CUdevice> dev = d_owner->_dev.handler();
    cuDeviceGetProperties(&devprop, dev);
    
# endif
}

void dealloc()
{
    
}

# ifdef NNT_MACH

CUdevprop devprop;

# endif

NNTDECL_PRIVATE_END_CXX

Info::Info()
: _dev(Device::Current())
{
    NNTDECL_PRIVATE_CONSTRUCT(Info);
}

Info::Info(Device const& dev)
: _dev(dev)
{
    NNTDECL_PRIVATE_CONSTRUCT(Info);
}

Info::~Info()
{
    NNTDECL_PRIVATE_DESTROY();
}

int Info::version() const
{
    int ret = -1;
    
# ifdef NNT_MACH
    
    cuDriverGetVersion(&ret);    
    
# endif
    
    return ret;
}

core::string Info::name() const
{
    core::string ret;
    
# ifdef NNT_MACH
    
    use<CUdevice> dev = _dev.handler();
    char buf[128];
    cuDeviceGetName(buf, 128, dev);
    ret = buf;
    
# endif
    
    return ret;
}

usize Info::total_memory() const
{
    usize ret = 0;
    
# ifdef NNT_MACH
    
    size_t mem;
    use<CUdevice> dev = _dev.handler();
    cuDeviceTotalMem(&mem, dev);
    ret = mem;
    
# endif
    
    return ret;
}

usize Info::processor_count() const
{
    usize ret = 0;
    
# ifdef NNT_MACH
    
    int val;
    use<CUdevice> dev = _dev.handler();
    cuDeviceGetAttribute(&val, CU_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT, dev);
    ret = val;
    
# endif
    
    return ret;
}

Device const& Info::device() const
{
    return _dev;
}

NNT_END_NS
NNT_END_CXX
