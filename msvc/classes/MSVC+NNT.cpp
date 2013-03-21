
# include "Core.h"
# include "MSVC+NNT.h"
# include "ExceptionProcess.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(msvc)

void Init()
{
    static ExceptionProcess exception_process = ExceptionProcess();
}

NNT_END_NS
NNT_END_CXX
