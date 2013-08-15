
# include "Core.h"
# include "App.h"
# include "Directory+NNT.h"
# include "CmdArguments.h"
# include "Task+NNT.h"

# ifdef NNT_MSVC

#   include <lmcons.h>
#   include <direct.h>
#   include "../msvc/classes/ExceptionProcess.h"

# endif

# ifdef NNT_UNIX
//#   include <sys/syslimits.h>
# endif

# ifndef PATHLEN
#   define PATHLEN 1024
# endif

# ifndef PATH_MAX
#   define PATH_MAX PATHLEN
# endif

NNT_BEGIN_CXX

Environment::Environment()
{
    ::nnt::Init();
}

Environment::~Environment()
{
    ::nnt::Fini();
}

static Environment __gs_app;

Environment* Environment::getInstance()
{
    return &__gs_app;
}

static core::string __preferred_workingdirectory;

core::string Environment::workingDirectory()
{
    if (__preferred_workingdirectory.empty() == false)
        return __preferred_workingdirectory;

    char* path = (char*)malloc(PATH_MAX);
    core::string ret = getcwd(path, PATH_MAX);
    free(path);
    ret = core::dot(ret);
    return ret;
}

void Environment::replaceWorkingDirectory(const core::string & str)
{
    __preferred_workingdirectory = str;
}

NNT_BEGIN_NS(cross)

class Arguments
: public IArguments
{
public:
    
    Arguments(int argc, char* argv[])
    : argu(argc, argv)
    {
        PASS;
    }
    
    virtual usize count() const
    {
        return argu.count();
    }
    
    virtual core::string& at(int idx)
    {
        return argu[idx];
    }
    
    cmd::Arguments argu;
    
};

Console::Console()
: _cmd(NULL)
{
    // init environment.
    Environment::getInstance();
}

Console::~Console()
{
    safe_delete<Arguments>(_cmd);
}

void Console::load()
{
    PASS;
}

void Console::_doload()
{
# ifdef NNT_MSVC
    __try {
# endif

    this->load();

# ifdef NNT_MSVC
    }
    __except (msvc::ExceptionProcess::HandleUnknownException(GetExceptionInformation()))
    {
        ::MessageBoxA(NULL, msvc::ExceptionProcess::ErrorMessage.c_str(), "FATAL", MB_OK);
    }
# endif
}

static core::Condition __gs_app_wait;

extern void act_break(int);
void act_break(int)
{
    __gs_app_wait.signal();
}

int Console::execute(int argc, char **argv)
{
    // process arguments.
    if (_cmd == NULL)
        _cmd = new Arguments(argc, argv);

    // get sig for exit.
    signal(SIGINT, act_break);

    // application load routine.
    this->_doload();

    // wait for quit.
    __gs_app_wait.wait();
    return 0;
}

IArguments* Console::arguments()
{
    return (IArguments*)_cmd;
}

NNT_END_NS // cross

NNT_END_CXX
