
# include "Core.h"
# include "OCLDevice.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(opencl)

# ifdef NNT_OPENCL

NNTDECL_PRIVATE_BEGIN_CXX(Device)

void init()
{
# ifdef NNT_MACH
    
    queue = gcl_create_dispatch_queue(CL_DEVICE_TYPE_GPU, NULL);
    if (queue == NULL)
        queue = gcl_create_dispatch_queue(CL_DEVICE_TYPE_CPU, NULL);
    gpu = gcl_get_device_id_with_dispatch_queue(queue);
    
# endif
}

void dealloc()
{
# ifdef NNT_MACH
    
    dispatch_release(queue);
    
# endif
}

# ifdef NNT_MACH

dispatch_queue_t queue;
cl_device_id gpu;

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

Device::device_t Device::handle() const
{
# ifdef NNT_MACH
    return (device_t)&d_ptr->gpu;
# endif
    
    return NULL;
}

# endif

NNT_END_NS
NNT_END_CXX
