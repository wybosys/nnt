
# include "Core.h"
# include "MSVC+WSI.h"
# include "ExceptionProcess.h"

WSI_BEGIN_CXX
WSI_BEGIN_NS(msvc)

void Init()
{
    static ExceptionProcess exception_process = ExceptionProcess();
}

WSI_END_NS
WSI_END_CXX
