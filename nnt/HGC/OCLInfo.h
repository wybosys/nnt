
# ifndef __NNT_OCL_INFO_141BDD37A5F740B789D512CAF1328F5C_H_INCLUDED
# define __NNT_OCL_INFO_141BDD37A5F740B789D512CAF1328F5C_H_INCLUDED

# include "OCLDevice.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(opencl)

NNTCLASS(Info);

class Info
{
public:
    
    Info(Device const&);
    
    core::string name() const;
    core::string vendor() const;

protected:

    Device const& _dev;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
