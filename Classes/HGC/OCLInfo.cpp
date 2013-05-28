
# include "Core.h"
# include "OCLInfo.h"
# include "opencl.prv.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(opencl)

Info::Info()
: _dev(Device::Current())
{
    
}

Info::Info(Device const& dev)
: _dev(dev)
{
    
}

core::string Info::name() const
{
# ifdef NNT_OPENCL
    
# ifdef NNT_MACH
    
    use<cl_device_id> dev = _dev.handle();
    char buf[128];
    size_t sz;
    clGetDeviceInfo(dev, CL_DEVICE_NAME, 128, buf, &sz);
    return core::string(buf, sz - 1);
    
# endif
    
# endif
    
    return core::null_string;
}

core::string Info::vendor() const
{
# ifdef NNT_OPENCL
    
# ifdef NNT_MACH
    
    use<cl_device_id> dev = _dev.handle();
    char buf[128];
    size_t sz;
    clGetDeviceInfo(dev, CL_DEVICE_VENDOR, 128, buf, &sz);
    return core::string(buf, sz - 1);
    
# endif
    
# endif
    
    return core::null_string;
}

NNT_END_NS
NNT_END_CXX
