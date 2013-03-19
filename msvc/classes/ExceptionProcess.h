
# ifndef __WSI_MSVC_EXCEPTIONPROCESS_8434b97299044668a4eabf931f02e67d_H_INCLUDED
# define __WSI_MSVC_EXCEPTIONPROCESS_8434b97299044668a4eabf931f02e67d_H_INCLUDED

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(msvc)

class ExceptionProcess
{
public:

    ExceptionProcess();
    ~ExceptionProcess();

    static core::string Path;

    static LONG WINAPI HandleUnknownException(struct _EXCEPTION_POINTERS*);

};

WSI_END_NS
WSI_END_HEADER_CXX

# endif
