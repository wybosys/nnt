
# include "Core.h"
# include "CmdArguments.h"
# include <boost/algorithm/string.hpp>

NNT_BEGIN_CXX
NNT_BEGIN_NS(cmd)

Arguments::Arguments(int argc /* = 0 */, char* argv[] /* = NULL */)
{
    set(argc, argv);
}

Arguments::Arguments(core::string const& str)
{
    set(str);
}

Arguments::~Arguments()
{
    
}

void Arguments::clear()
{
    cmd.clear();
    arguments.clear();
}

void Arguments::set(int argc, char* argv[])
{
    clear();

    if (argc)
        cmd = argv[0];

    for (int i = 1; i < argc; ++i)
        arguments.push_back(argv[i]);
}

void Arguments::set(core::string const& str)
{
    clear();
    
    cmd = str;
    
    using namespace ::boost::algorithm;
    
    split< ::std::vector<core::string> >(arguments, str, is_any_of(" "));
}

usize Arguments::size() const
{
    return arguments.size();
}

core::string& Arguments::operator [] (int idx)
{
    return arguments[idx];
}

NNT_END_NS
NNT_END_CXX
