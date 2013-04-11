
# include "Core.h"
# include "CmdArguments.h"

NNT_BEGIN_CXX

CmdArguments::CmdArguments(int argc /* = 0 */, char* argv[] /* = NULL */)
{
    set(argc, argv);
}

void CmdArguments::clear()
{
    cmd.clear();
    arguments.clear();
}

void CmdArguments::set(int argc, char* argv[])
{
    clear();

    if (argc)
        cmd = argv[0];

    for (int i = 1; i < argc; ++i)
        arguments.push_back(argv[i]);
}

usize CmdArguments::size() const
{
    return arguments.size();
}

core::string& CmdArguments::operator [] (int idx)
{
    return arguments[idx];
}

NNT_END_CXX
