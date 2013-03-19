
# include "Core.h"
# include "Regex+WSI.h"

# include "../Core/Boost+WSI.h"
# include <boost/regex.hpp>

WSI_BEGIN_CXX
WSI_BEGIN_NS(wtl)
 
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
    int old = result.size();
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

WSI_END_NS
WSI_END_CXX
