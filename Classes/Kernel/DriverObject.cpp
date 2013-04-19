
# include "Core.h"
# include "DriverObject.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(driver)

bool Status::Success(int code)
{
# ifdef NNT_MSVC
#   ifdef NNT_KERNEL_SPACE
      return NT_SUCCESS(code);
#   else
    return SUCCEEDED(code);
#   endif
# endif
}

bool Status::Failed(int code)
{
    return !Success(code);
}

NNT_END_NS
NNT_END_CXX