
# ifndef __NNT_MSVC_EXCEPTIONPROCESS_8434b97299044668a4eabf931f02e67d_H_INCLUDED
# define __NNT_MSVC_EXCEPTIONPROCESS_8434b97299044668a4eabf931f02e67d_H_INCLUDED

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(msvc)

class ExceptionProcess
{
public:

    ExceptionProcess();
    ~ExceptionProcess();

    static core::string Path;

    static LONG WINAPI HandleUnknownException(struct _EXCEPTION_POINTERS*);

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
