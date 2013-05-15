
# include "Core.h"
# include "klinux.h"

# ifdef NNT_KERNEL_SPACE

# ifdef NNT_LINUX

NNT_BEGIN_CXX
NNT_BEGIN_NS(lnx)

file_operations::file_operations()
    : _da(NULL)
{
    core::zero(_obj);
    
    _obj.owner = nnt_module_current();
}

file_operations::~file_operations()
{
    nnt_free(_da);
}

file_operations::operator ::file_operations* ()
{
    nnt_file_operations_tokernel(&_obj, &_da);
    return _da;
}

NNT_END_NS
NNT_END_CXX

# endif

# endif

