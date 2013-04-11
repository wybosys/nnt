
# include "Core.h"

# ifdef NNT_MSVC

#  include <time.h>
#  include <direct.h>
#  include "../msvc/classes/MSVC+NNT.h"

# endif

NNT_BEGIN_CXX

static NNT __gs_nntobject;
bool NNT::IsRunning = false;

void NNT::Init()
{
    if (NNT::IsRunning == true)
        return;

	trace_msg("NNT[CXX] Toolkit.");
    
    NNT::IsRunning = true;
    
    char* path = (char*)malloc(1024);
	trace_msg(::getcwd(path, 1024));
    free(path);

# ifdef NNT_MSVC

    msvc::Init();

# endif

}

void NNT::Fini()
{
    NNT::IsRunning = false;
    
	trace_msg("NNT[CXX] Toolkit End.");
}

NNT_END_CXX

NNT_BEGIN_C

ulong timestamp()
{
    return (ulong)time(NULL);
}

# ifdef NNT_MSVC

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

char const* NNTVersion()
{
    return NNT_VERSION_STR;
}

NNT_END_C
