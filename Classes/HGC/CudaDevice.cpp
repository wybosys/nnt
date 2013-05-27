
# include "Core.h"
# include "CudaDevice.h"
# include "cuda.prv.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cuda)

# ifdef NNT_CUDA

NNTDECL_PRIVATE_BEGIN_CXX(Device)

void init()
{
    inited = false;
    
# ifdef NNT_MACH
    
    inited = cuInit(0) == CUDA_SUCCESS;
    
    if (inited)
    {
        cuDeviceGet(&dev, 0);
    }
    
# endif
}

void dealloc()
{
    
}

bool inited;

# ifdef NNT_MACH

CUdevice dev;

# endif

NNTDECL_PRIVATE_END_CXX

Device::Device()
{
    NNTDECL_PRIVATE_CONSTRUCT(Device);
}

Device::~Device()
{
    NNTDECL_PRIVATE_DESTROY();
}

Device& Device::Current()
{
    static Device current = Device();
    return current;
    
}

Device::device_t Device::handler() const
{
    return (device_t)&d_ptr->dev;
}

bool Device::is_validated() const
{
    return d_ptr->inited;
}

usize Device::Count()
{
    usize ret = 0;
    
# ifdef NNT_MACH
    
    int cnt;
    cuDeviceGetCount(&cnt);
    ret = cnt;
    
# endif
    
    return ret;
}

# endif

NNT_END_NS
NNT_END_HEADER_CXX
