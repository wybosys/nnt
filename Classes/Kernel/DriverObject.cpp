
# include "Core.h"
# include "DriverObject.h"

# ifdef NNT_MSVC
#   ifdef NNT_USER_SPACE
#     pragma warning (push)
#     pragma warning (disable: 4005)
#     include <ntstatus.h>
#     pragma warning (pop)
#   endif
#   ifndef NTSTATUS
typedef LONG NTSTATUS;
#   endif
# endif

NNT_BEGIN_CXX
NNT_BEGIN_NS(driver)

Status::Status()
{
# ifdef NNT_MSVC

    _val = STATUS_NOT_FOUND;

# endif
}

Status::~Status()
{

}

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

void Status::success()
{
    _val =
        NNT_MSVC_EXPRESS(STATUS_SUCCESS)
        NNT_GCC_EXPRESS(0)
        ;
}

Memory::Memory(void* ptr, usize len)
: _ptr(ptr), _len(len)
{

}

Memory::~Memory()
{

}

bool Memory::is_readable(ubyte align) const
{
    bool ret = true;

# ifdef NNT_MSVC

# ifdef NNT_KERNEL_SPACE

    __try
    {
        ::ProbeForRead(_ptr, _len, align);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        ret = false;
    }

# endif

# endif

    return ret;
}

bool Memory::is_writable(ubyte align) const
{
    bool ret = true;

# ifdef NNT_MSVC

# ifdef NNT_KERNEL_SPACE

    __try
    {
        ::ProbeForWrite(_ptr, _len, align);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        ret = false;
    }

# endif

# endif

    return ret;
}

Object::Object()
{

}

Object::~Object()
{

}

NNT_END_NS
NNT_END_CXX
