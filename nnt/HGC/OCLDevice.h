
# ifndef __NNT_OCL_DEVICE_CE0A75EFB60F4E9699515C0F18A35316_H_INCLUDED
# define __NNT_OCL_DEVICE_CE0A75EFB60F4E9699515C0F18A35316_H_INCLUDED

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(opencl)

NNTCLASS(Device);

NNTDECL_PRIVATE_HEAD_CXX(Device);

class Device
{
    NNTDECL_PRIVATE_CXX(Device);
    
public:
    
    Device();
    ~Device();
    
public:
    
    typedef struct {} *device_t;
    
    //! get device handler.
    device_t handle() const;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
