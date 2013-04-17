
# include "Core.h"
# include "Regex+NNT.h"

# include "../Core/Boost+NNT.h"
# include <boost/regex.hpp>

NNT_BEGIN_CXX
NNT_BEGIN_NS(ntl)
 
bool regex_match(string const& re, string const& str)
{
    ::boost::regex expr(re);
    return ::boost::regex_match(str.begin(), str.end(), expr);
}

bool regex_grep(string const& re, string const& str, regex_matched_t& result)
{
    ::boost::regex expr(re);
    ::boost::smatch what;
    bool suc = 
    ::boost::regex_match(str, what, expr, ::boost::match_extra);
    if (suc == false)
        return false;
    for (uint i = 0; i < what.size(); ++i)
    {
        core::string const& capture = what[i].str();
        result.push_back(capture);
    }
    return true;
}

bool regex_capture(string const& re, string const& str, regex_captured_t& result)
{
    int old = (int)result.size();
    ::boost::regex expr(re);
    ::boost::sregex_iterator iter(str.begin(), str.end(), expr), end;
    for (; iter != end; ++iter)
    {
        regex_matched_t matched;
        
        usize const sz = iter->size();
        for (uint i = 0; i < sz; ++i)
        {            
            matched.push_back((*iter)[i]);
        }
        
        result.push_back(matched);
    }
    return (result.size() - old) != 0;
}

core::string regex_replace(string const& re, string const& replace, string const& str)
{
    ::boost::regex expr(re);
    return ::boost::regex_replace(str, expr, replace);
}

regex::regex(string const& str)
{
    _re = new ::boost::regex(str);
}

regex::~regex()
{
    delete (::boost::regex*)_re;
}

bool regex::grep(string const& str, vector<string>& result) const
{
    ::boost::smatch what;
    bool suc = ::boost::regex_match(str, what, *(::boost::regex*)_re, ::boost::match_extra);
    if (suc == false)
        return false;
    for (uint i = 0; i < what.size(); ++i)
    {
        core::string const& str = what[i].str();
        result.push_back(str);
    }
    return true;
}

vector<string> regex::grep(string const& str) const
{
    vector<string> ret;
    this->grep(str, ret);
    return ret;
}

void regex::capture(string const& str, regex_captured_t& result) const
{
    ::boost::sregex_iterator iter(str.begin(), str.end(), *(::boost::regex*)_re),
    end;
    for (; iter != end; ++iter)
    {
        regex_matched_t matched;
        
        usize const sz = iter->size();
        for (uint i = 0; i < sz; ++i)
        {            
            matched.push_back((*iter)[i]);
        }
        
        result.push_back(matched);
    }
}

regex_captured_t regex::capture(string const& str) const
{
    regex_captured_t ret;
    this->capture(str, ret);
    return ret;
}

core::string regex::replace(string const& fmt, string const& str) const
{
    return ::boost::regex_replace(str, *(::boost::regex*)_re, fmt);
}

NNT_END_NS
NNT_END_CXX
