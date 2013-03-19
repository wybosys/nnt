
# include "Core.h"
# include "App.h"
# include "Directory+WSI.h"
# include "../Parser/CmdArguments.h"
# include "Task+WSI.h"

# ifdef WSI_MSVC
#   include <lmcons.h>
#   include <direct.h>
#   include "../msvc/classes/ExceptionProcess.h"
# endif

# ifdef WSI_UNIX
//#   include <sys/syslimits.h>
# endif

# ifndef PATHLEN
#   define PATHLEN 1024
# endif

# ifndef PATH_MAX
#   define PATH_MAX PATHLEN
# endif

WSI_BEGIN_CXX

Environment::Environment()
{
    wsi::Init();
}

Environment::~Environment()
{
    wsi::Fini();
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

WSI_BEGIN_NS(cross)

class Arguments
: public IArguments
{
public:
    
    Arguments(int argc, char* argv[])
    : argu(argc, argv)
    {
        PASS;
    }
    
    virtual int count() const
    {
        return argu.size();
    }
    
    virtual core::string& at(int idx)
    {
        return argu[idx];
    }
    
    CmdArguments argu;
    
};

Console::Console()
: _cmd(NULL)
{
    // init environment.
    Environment::getInstance();
}

Console::~Console()
{
    safe_delete_type(_cmd, Arguments*);
}

void Console::load()
{
    PASS;
}

void Console::_doload()
{
# ifdef WSI_MSVC
    __try {
# endif

    this->load();

# ifdef WSI_MSVC
    }
    __except (msvc::ExceptionProcess::HandleUnknownException(GetExceptionInformation()))
    {
        ::MessageBox(NULL, _T("Got an unhandle exception."), _T("FATAL"), MB_OK);

    }
# endif
}

static core::Condition __gs_app_wait;

void act_break(int)
{
    __gs_app_wait.signal();
}

int Console::execute(int argc, char *argv[])
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

WSI_END_NS

WSI_END_CXX
