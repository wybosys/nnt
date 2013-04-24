
# include "Core.h"
# include "ExceptionProcess.h"

# include <eh.h>
# include <Psapi.h>
# include <DbgHelp.h>
# pragma comment (lib, "Psapi.lib")
# pragma comment (lib, "DbgHelp.lib")

NNT_BEGIN_CXX
NNT_BEGIN_NS(msvc)

core::string ExceptionProcess::Path = "DumpFile.dmp";
core::string ExceptionProcess::ErrorMessage = "";

ExceptionProcess::ExceptionProcess()
{
    ::SetUnhandledExceptionFilter(ExceptionProcess::HandleUnknownException);
}

ExceptionProcess::~ExceptionProcess()
{

}

LONG ExceptionProcess::HandleUnknownException(struct _EXCEPTION_POINTERS* _exceptionpoints)
{

    // save dump file.
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

    // save message.
    ErrorMessage = ExceptionToString(_exceptionpoints);

    return EXCEPTION_EXECUTE_HANDLER;
}

static const char* opDescription( const ULONG opcode )
{
    switch( opcode ) 
    {
      case 0: return "read";
      case 1: return "write";
      case 8: return "user-mode data execution prevention (DEP) violation";
      default: return "unknown";
    }
}

static const char* seDescription( const uint& code )
{
    switch( code ) 
    {
         case EXCEPTION_ACCESS_VIOLATION:         return "EXCEPTION_ACCESS_VIOLATION"         ;
         case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:    return "EXCEPTION_ARRAY_BOUNDS_EXCEEDED"    ;
         case EXCEPTION_BREAKPOINT:               return "EXCEPTION_BREAKPOINT"               ;
         case EXCEPTION_DATATYPE_MISALIGNMENT:    return "EXCEPTION_DATATYPE_MISALIGNMENT"    ;
         case EXCEPTION_FLT_DENORMAL_OPERAND:     return "EXCEPTION_FLT_DENORMAL_OPERAND"     ;
         case EXCEPTION_FLT_DIVIDE_BY_ZERO:       return "EXCEPTION_FLT_DIVIDE_BY_ZERO"       ;
         case EXCEPTION_FLT_INEXACT_RESULT:       return "EXCEPTION_FLT_INEXACT_RESULT"       ;
         case EXCEPTION_FLT_INVALID_OPERATION:    return "EXCEPTION_FLT_INVALID_OPERATION"    ;
         case EXCEPTION_FLT_OVERFLOW:             return "EXCEPTION_FLT_OVERFLOW"             ;
         case EXCEPTION_FLT_STACK_CHECK:          return "EXCEPTION_FLT_STACK_CHECK"          ;
         case EXCEPTION_FLT_UNDERFLOW:            return "EXCEPTION_FLT_UNDERFLOW"            ;
         case EXCEPTION_ILLEGAL_INSTRUCTION:      return "EXCEPTION_ILLEGAL_INSTRUCTION"      ;
         case EXCEPTION_IN_PAGE_ERROR:            return "EXCEPTION_IN_PAGE_ERROR"            ;
         case EXCEPTION_INT_DIVIDE_BY_ZERO:       return "EXCEPTION_INT_DIVIDE_BY_ZERO"       ;
         case EXCEPTION_INT_OVERFLOW:             return "EXCEPTION_INT_OVERFLOW"             ;
         case EXCEPTION_INVALID_DISPOSITION:      return "EXCEPTION_INVALID_DISPOSITION"      ;
         case EXCEPTION_NONCONTINUABLE_EXCEPTION: return "EXCEPTION_NONCONTINUABLE_EXCEPTION" ;
         case EXCEPTION_PRIV_INSTRUCTION:         return "EXCEPTION_PRIV_INSTRUCTION"         ;
         case EXCEPTION_SINGLE_STEP:              return "EXCEPTION_SINGLE_STEP"              ;
         case EXCEPTION_STACK_OVERFLOW:           return "EXCEPTION_STACK_OVERFLOW"           ;
         default: return "UNKNOWN EXCEPTION" ;
    }
}

core::string ExceptionProcess::ExceptionToString(struct _EXCEPTION_POINTERS* ep)
{
    HMODULE hm;
    ::GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, static_cast<LPCTSTR>(ep->ExceptionRecord->ExceptionAddress), &hm);
    MODULEINFO mi;
    ::GetModuleInformation( ::GetCurrentProcess(), hm, &mi, sizeof(mi) );
    char fn[MAX_PATH];
    ::GetModuleFileNameExA( ::GetCurrentProcess(), hm, fn, MAX_PATH );

    uint code = ep->ExceptionRecord->ExceptionCode;
    std::ostringstream oss;
    oss << "SEH: " << seDescription(code) << " at address 0x" << std::hex << ep->ExceptionRecord->ExceptionAddress << std::dec 
        << " inside " << fn << " loaded at base address 0x" << std::hex << mi.lpBaseOfDll << "\n"; 

    if (code == EXCEPTION_ACCESS_VIOLATION || 
        code == EXCEPTION_IN_PAGE_ERROR )
    {
        oss << "Invalid operation: " << opDescription((ULONG)ep->ExceptionRecord->ExceptionInformation[0]) << " at address 0x" << std::hex << ep->ExceptionRecord->ExceptionInformation[1] << std::dec << "\n";
    }

    if (code == EXCEPTION_IN_PAGE_ERROR ) 
    {
        oss << "Underlying NTSTATUS code that resulted in the exception " << ep->ExceptionRecord->ExceptionInformation[2] << "\n";
    }

    return oss.str();
}

NNT_END_NS
NNT_END_CXX
