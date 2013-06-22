
# ifndef __NNT_CUDA_DEVICE_693DC6F9D87C4321856D1832FF6CFDD6_H_INCLUDED
# define __NNT_CUDA_DEVICE_693DC6F9D87C4321856D1832FF6CFDD6_H_INCLUDED

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cuda)

NNTCLASS(Device);

NNTDECL_PRIVATE_HEAD_CXX(Device);

class Device
{
    NNTDECL_PRIVATE_CXX(Device);
    
public:
    
    Device();
    ~Device();
    
    //! @return false if current hardware not support CUDA.
    bool is_validated() const;
    
    typedef struct {} *device_t;
    device_t handler() const;
    
    //! @return singleton device.
    static Device& Current();
    
    //! @return device's count.
    static usize Count();
    
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
