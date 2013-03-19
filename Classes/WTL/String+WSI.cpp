
# include "Core.h"
# include "String+WSI.h"
# include "../Core/WSIChar.h"
# include <stdarg.h>
# include "../Core/Boost+WSI.h"
# include <boost/lexical_cast.hpp>
# include <boost/algorithm/string.hpp>
# include <boost/algorithm/string/replace.hpp>
# include <boost/algorithm/string/split.hpp>

WSI_BEGIN_CXX 
WSI_BEGIN_NS(wtl)

string format(char const* fmt, ...)
{
    usize lenfmt = strlen(fmt) << 1;
    char* buf = (char*)malloc(lenfmt);
    va_list va;
    va_start(va, fmt);
    int len = vsprintf(buf, fmt, va);
    va_end(va);
    
    string ret(buf, len);
    return ret;
}

string hex_cast(byte const* bytes, usize len)
{
    string str;
    str.resize(len << 1);;
    
    uindex idx, jdx;
    for (idx = 0, jdx = 0; idx < len; ++idx, ++jdx)
    {
        char const* s = __gs_byte_to_hex_str[bytes[idx]];
        str[jdx] = s[0];
        str[++jdx] = s[1];
    }
    
    return str;
}

bool hex_cast(string const& str, byte** bytes, usize* len)
{   
    if (str.size() % 2)
        return false;
    
    *len = str.size() / 2;
    *bytes = (byte*)malloc(*len);
    
    byte* ptr = *bytes;
    for (string::const_iterator each = str.begin();
         each != str.end();
         ++each)
    {
        *ptr = MAP_ASCII_BINARY[*each++];
        *ptr = b8_make(*ptr, MAP_ASCII_BINARY[*each]);
        ++ptr;
    }
    
    return true;
}

int hex2int(string const& str)
{
    int ret = 0;
    int off = 0;
    for (string::const_reverse_iterator each = str.rbegin();
         each != str.rend();
         ++each)
    {
        char const c = MAP_ASCII_BINARY_XID[*each];
        if (c == -1)
            break;
        ret |= c << off;
        off += 4;
    }
    return ret;
}

long hex2long(string const& str)
{
    long ret = 0;
    long off = 0;
    for (string::const_reverse_iterator each = str.rbegin();
         each != str.rend();
         ++each)
    {
        long c = MAP_ASCII_BINARY_XID[*each];
        if (c == -1)
            break;
        ret |= c << off;
        off += 4;
    }
    return ret;
}

longlong hex2longlong(string const& str)
{
    longlong ret = 0;
    longlong off = 0;
    for (string::const_reverse_iterator each = str.rbegin();
         each != str.rend();
         ++each)
    {
        longlong c = MAP_ASCII_BINARY_XID[*each];
        if (c == -1)
            break;
        ret |= c << off;
        off += 4;
    }
    return ret;
}

string tostr(int v)
{
    return ::boost::lexical_cast<string>(v);
}

string tostr(uint v)
{
    return ::boost::lexical_cast<string>(v);
}

string tostr(float v)
{
    return ::boost::lexical_cast<string>(v);
}

string tostr(double v)
{
    return ::boost::lexical_cast<string>(v);
}

string tostr(short v)
{
    return ::boost::lexical_cast<string>(v);
}

string tostr(ushort v)
{
    return ::boost::lexical_cast<string>(v);
}

string tostr(long v)
{
    return ::boost::lexical_cast<string>(v);
}

string tostr(ulong v)
{
    return ::boost::lexical_cast<string>(v);
}

# define STRTOVALUEIMPL(tp) \
tp ret = 0; \
try { \
	ret = ::boost::lexical_cast<tp>(str); \
} catch (...) { \
trace_msg("failed to lexical_cast " + str + " to " + WSIMACRO_TOSTR(tp) + " ."); \
} \
return ret;

bool tobool(string const& str)
{
    STRTOVALUEIMPL(bool);
}

int toint(string const& str)
{
	STRTOVALUEIMPL(int);
}

uint touint(string const& str)
{
	STRTOVALUEIMPL(uint);
}

short toshort(string const& str)
{
	STRTOVALUEIMPL(short);
}

ushort toushort(string const& str)
{
	STRTOVALUEIMPL(ushort);
}

long tolong(string const& str)
{
	STRTOVALUEIMPL(long);
}

ulong toulong(string const& str)
{
	STRTOVALUEIMPL(ulong);
}

float tofloat(string const& str)
{
	STRTOVALUEIMPL(float);
}

double todouble(string const& str)
{
	STRTOVALUEIMPL(double);
}

real toreal(string const& str)
{
	STRTOVALUEIMPL(real);
}

void split(string const& str, string const& by, ::std::vector<string>& res, bool compress)
{
    ::boost::split(res, str, ::boost::is_any_of(by), TRIEXP(compress, ::boost::token_compress_on, ::boost::token_compress_off));
}

void split(string const& str, string const& by, ::std::deque<string>& res, bool compress)
{
    ::boost::split(res, str, ::boost::is_any_of(by), TRIEXP(compress, ::boost::token_compress_on, ::boost::token_compress_off));
}

string replace(string const& str, string const& from, string const& to)
{
    string ret = str;
    ::boost::replace_all(ret, from, to);
    return ret;
}

string& replace_of(string& str, string const& from, string const& to)
{
    ::boost::replace_all(str, from, to);
    return str;
}

WSI_END_NS 
WSI_END_CXX