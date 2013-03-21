
# include "Core.h"
# include "ExceptionProcess.h"
# include <DbgHelp.h>
# pragma comment (lib, "DbgHelp.lib")

NNT_BEGIN_CXX
NNT_BEGIN_NS(msvc)

core::string ExceptionProcess::Path = "DumpFile.dmp";

ExceptionProcess::ExceptionProcess()
{
    ::SetUnhandledExceptionFilter(ExceptionProcess::HandleUnknownException);
}

ExceptionProcess::~ExceptionProcess()
{

}

LONG ExceptionProcess::HandleUnknownException(struct _EXCEPTION_POINTERS* _exceptionpoints)
{
    HANDLE hd = ::CreateFileA(
        Path.c_str(),
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
        );

    MINIDUMP_EXCEPTION_INFORMATION expinfo;
    expinfo.ExceptionPointers = _exceptionpoints;
    expinfo.ThreadId = ::GetCurrentThreadId();
    expinfo.ClientPointers = TRUE;
    ::MiniDumpWriteDump(
        ::GetCurrentProcess(),
        ::GetCurrentProcessId(),
        hd,
        MiniDumpNormal,
        &expinfo,
        NULL,
        NULL
        );

    ::CloseHandle(hd);

    return EXCEPTION_EXECUTE_HANDLER;
}

NNT_END_NS
NNT_END_CXX
