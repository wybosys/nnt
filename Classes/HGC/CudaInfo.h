
# ifndef __NNT_CUDA_INFO_77929BED156040BD9F1251ABDA2D4097_H_INCLUDED
# define __NNT_CUDA_INFO_77929BED156040BD9F1251ABDA2D4097_H_INCLUDED

# include "./CudaDevice.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cuda)

NNTDECL_PRIVATE_HEAD_CXX(Info);

class Info
{
    NNTDECL_PRIVATE_CXX(Info);
    
public:
    
    Info();
    Info(Device const&);
    ~Info();
    
    //! some infos.
    int version() const;
    core::string name() const;
    usize total_memory() const;
    usize processor_count() const;
    
    //! get binded device.
    Device const& device() const;
    
protected:
    
    Device const& _dev;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
