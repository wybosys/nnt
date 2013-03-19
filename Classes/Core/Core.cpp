
# include "Core.h"

# ifdef WSI_MSVC

#  include <direct.h>
#  include "../msvc/classes/MSVC+WSI.h"

# endif

WSI_BEGIN_CXX

static WSI __gs_wsiobject;
bool WSI::IsRunning = false;

void WSI::Init()
{
    if (WSI::IsRunning == true)
        return;

	trace_msg("WSI[CXX] Toolkit.");
    
    WSI::IsRunning = true;
    
    char* path = (char*)malloc(1024);
	trace_msg(::getcwd(path, 1024));
    free(path);

# ifdef WSI_MSVC

    msvc::Init();

# endif

}

void WSI::Fini()
{
    WSI::IsRunning = false;
    
	trace_msg("WSI[CXX] Toolkit End.");
}

WSI_END_CXX

WSI_BEGIN_C

ulong timestamp()
{
    return (ulong)time(NULL);
}

# ifdef WSI_MSVC

void sleep_second(ulonglong d)
{
	::Sleep((DWORD)(d * 1e3));
}

void sleep_millisecond(ulonglong d)
{
	::Sleep((DWORD)d);
}

/*void sleep_microsecond(ulonglong d)
{

}
*/

/*void sleep_nanosecond(ulonglong d)
{

}
*/

# else

void sleep_second(ulonglong d)
{
    ::sleep(d);
}

void sleep_millisecond(ulonglong d)
{
    ::usleep(d * 1e3);
}

void sleep_microsecond(ulonglong d)
{
    ::usleep(d);
}

void sleep_nanosecond(ulonglong d)
{
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = d;
    ::nanosleep(&ts, NULL);
}

# endif

char const* WSIVersion()
{
    return WSI_VERSION_STR;
}

WSI_END_C
