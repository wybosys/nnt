
# include "Core.h"
# include "Directory+NNT.h"
# include "Boost+NNT.h"
# include <boost/tokenizer.hpp>
# include <sys/stat.h>

NNT_BEGIN_CXX 
NNT_BEGIN_NS(core)

core::string dot(core::string const& path) 
{
    using namespace ::boost;
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    char_separator<char> sep("/\\");
    tokenizer tok(path, sep);
    core::string ret;
    tokenizer::const_iterator each = tok.begin();
    while (each != tok.end())
    {
        core::string sep = *each++;
        ret += sep + "/";
    }
    if (*path.begin() == '/' || *path.begin() == '\\')
        ret = '/' + ret;
    return ret;
}

core::string dotdot(core::string const& path)
{
    using namespace ::boost;
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    char_separator<char> sep("/\\");
    tokenizer tok(path, sep);
    core::string ret;
    tokenizer::const_iterator each = tok.begin();
    if (each != tok.end())
    {
        tokenizer::const_iterator off = tok.begin();
        ++off;
        while (off != tok.end())
        {
            core::string sep = *each++;
            ret += sep + "/";
            ++off;
        }
    }
    if (*path.begin() == '/' || *path.begin() == '\\')
        ret = '/' + ret;
    return ret;
}

bool mkdir(core::string const& path)
{    
# ifdef NNT_MSVC
	return ::CreateDirectoryA(path.c_str(), NULL) == TRUE;
# else
    int sta = ::mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    return sta == 0;
# endif
}

bool mkdirs(core::string const& path)
{
    using namespace ::boost;
    typedef ::boost::tokenizer<boost::char_separator<char> > tokenizer;
    
    char_separator<char> sep("/\\");
    tokenizer tok(path, sep);
    core::string dir;
    if (*path.begin() == '/' || *path.begin() == '\\')
        dir = '/';
    
    int sta;
    for (tokenizer::const_iterator each = tok.begin();
         each != tok.end();
         ++each)
    {
        dir += *each + "/";

# ifdef NNT_MSVC
		sta = ::CreateDirectoryA(dir.c_str(), NULL) == TRUE;
# else
        sta = ::mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
# endif
    }
    
    return sta == 0;
}

NNT_END_NS 
NNT_END_CXX