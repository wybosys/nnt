
# include "Core.h"
# include "DriverObject.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(driver)

Status::Status()
{

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