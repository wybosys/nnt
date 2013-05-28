
# ifndef __NNT_DRIVER_IO_c6e9dc2441574ddca8c2c1e86723fc8c_H_INCLUDED
# define __NNT_DRIVER_IO_c6e9dc2441574ddca8c2c1e86723fc8c_H_INCLUDED

# include "./DriverObject.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(driver)

NNTCLASS(IoCode);

class IoCode
{
public:

    IoCode();
    IoCode(ulong fun);
    IoCode(ulong fun, MemoryMode);

    operator ulong () const;

    MemoryMode mm() const;

protected:    

    void _update();

    ulong _function;
    MemoryMode _mm;
    ulong _code;

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
