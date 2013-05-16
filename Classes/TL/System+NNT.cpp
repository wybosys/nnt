
# include "Core.h"
# include "System+NNT.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(ntl)
NNT_BEGIN_NS(sys)

# ifdef NNT_KERNEL_SPACE

IrqLevel::IrqLevel()
{
    _next = current = Current();
}

ubyte IrqLevel::Current()
{
# ifdef NNT_WINDOWS
    return KeGetCurrentIrql();
# endif
}

void IrqLevel::raise(ubyte tgt)
{
    if (tgt <= current)
        return;

# ifdef NNT_WINDOWS
    KeRaiseIrql(tgt, &current);
# endif

    _next = tgt;
}

void IrqLevel::back()
{
    if (_next == current)
        return;

# ifdef NNT_WINDOWS
    KeLowerIrql(current);
# endif

    _next = current;
}

void IrqLevel::higher()
{
# ifdef NNT_WINDOWS
    raise(DISPATCH_LEVEL);
# endif
}

# endif

NNT_END_NS
NNT_END_NS
NNT_END_CXX
