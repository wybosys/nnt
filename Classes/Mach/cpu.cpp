
# include "Core.h"
# include "cpu.h"

NNT_BEGIN_C

void NNTAPI_ASM(cpuid)(mr_integer code, mregister* mr);

void cpuid(mr_integer code, mregister* mr)
{
    NNTAPI_ASM(cpuid)(code, mr);
}

NNT_END_C
