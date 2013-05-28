
# include "Core.h"
# include "DriverIO.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(driver)

IoCode::IoCode()
: _mm(MEMORY_BUFFER), _function(0)
{
    _update();
}

IoCode::IoCode(ulong fun)
: _mm(MEMORY_BUFFER), _function(fun)
{
    _update();
}

IoCode::IoCode(ulong fun, MemoryMode mm)
: _mm(mm), _function(fun)
{
    _update();
}

IoCode::operator ulong () const
{
    return _code;
}

void IoCode::_update()
{
# ifdef NNT_MSVC

    ulong method;
    if (_mm == MEMORY_BUFFER)
        method = METHOD_BUFFERED;
    else
        method = METHOD_IN_DIRECT;

    _code = CTL_CODE(FILE_DEVICE_UNKNOWN, _function + 0x800, method, FILE_ANY_ACCESS);

# endif
}

MemoryMode IoCode::mm() const
{
    return _mm;
}

NNT_END_NS
NNT_END_CXX
