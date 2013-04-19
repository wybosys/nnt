
# include "Core.h"
# include "String+NNT.h"

# ifdef NNT_USER_SPACE

# include <stdarg.h>
# include "../Core/Boost+NNT.h"
# include <boost/lexical_cast.hpp>
# include <boost/algorithm/string.hpp>
# include <boost/algorithm/string/replace.hpp>
# include <boost/algorithm/string/split.hpp>

NNT_BEGIN_C
NNTVAR_USE(char const*) gs_byte_to_hex_str [256];
NNT_END_C

NNT_BEGIN_CXX 
NNT_BEGIN_NS(ntl)

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
        char const* s = gs_byte_to_hex_str[bytes[idx]];
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

string tostr(longlong v)
{
    return ::boost::lexical_cast<string>(v);
}

string tostr(ulonglong v)
{
    return ::boost::lexical_cast<string>(v);
}

# define STRTOVALUEIMPL(tp) \
tp ret = 0; \
try { \
	ret = ::boost::lexical_cast<tp>(str); \
} catch (...) { \
trace_msg("failed to lexical_cast " + str + " to " + NNTMACRO_TOSTR(tp) + " ."); \
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

NNT_END_NS 
NNT_END_CXX

# else

NNT_BEGIN_CXX
NNT_BEGIN_NS(ntl)

string::string()
: _need_release(false)
{
    ::RtlInitEmptyUnicodeString(&_obj, NULL, 0);
}

string::string(char const* str)
: _need_release(true)
{
    ANSI_STRING astr;
    ::RtlInitAnsiString(&astr, str);
    ::RtlAnsiStringToUnicodeString(&_obj, &astr, TRUE);
}

string::string(wchar_t const* str)
: _need_release(false)
{
    ::RtlInitUnicodeString(&_obj, str);
}

string::string(value_type const& r)
: _need_release(true)
{
    ::RtlInitEmptyUnicodeString(&_obj,
        (PWCHAR)::ExAllocatePoolWithTag(PagedPool, r.Length, (ULONG)"str0"),
        r.Length);
    ::RtlCopyUnicodeString(&_obj, &r);
}

string::string(string const& r)
: _need_release(true)
{
    ::RtlInitEmptyUnicodeString(&_obj, 
        (PWCHAR)::ExAllocatePoolWithTag(PagedPool, r->Length, (ULONG)"str0"), 
        r->Length);
    ::RtlCopyUnicodeString(&_obj, r);
}

string::~string()
{
    clear();
}

string& string::operator = (string const& r)
{
    clear();

    ::RtlInitEmptyUnicodeString(&_obj,
        (PWCHAR)::ExAllocatePoolWithTag(PagedPool, r->Length, (ULONG)"str0"),
        r->Length);
    ::RtlCopyUnicodeString(&_obj, r);
    _need_release = true;

    return *this;
}

string string::operator + (string const& r) const
{
    string ret = *this;
    return ret += r;
}

string& string::operator += (string const& r)
{
    UNICODE_STRING str = {0};
    str.Length = str.MaximumLength = _obj.Length + r->Length;
    str.Buffer = (PWCHAR)::ExAllocatePoolWithTag(PagedPool, str.MaximumLength, (ULONG)"str0");

    if (_obj.Length)
        ::RtlCopyMemory(str.Buffer, _obj.Buffer, _obj.Length);
    if (r->Length)
        ::RtlCopyMemory((byte*)str.Buffer + _obj.Length, r->Buffer, r->Length);

    // clear current memory.
    clear();

    // set.
    _obj = str;
    _need_release = true;

    return *this;
}

void string::clear()
{
    if (_need_release)
    {
        ::RtlFreeUnicodeString(&_obj);
        _need_release = false;        
    }

    _obj.Length = 0;
}

bool string::operator == (string const& r) const
{
    return ::RtlEqualUnicodeString(*this, r, TRUE) != 0;
}

bool string::operator != (string const& r) const
{
    return !(*this == r);
}

bool string::is_equal(string const& r, bool casesens) const
{
    return ::RtlEqualUnicodeString(*this, r, casesens) != 0;
}

bool string::is_empty() const
{
    return _obj.Length == 0;
}

usize string::length() const
{
    return _obj.Length;
}

NNT_END_NS
NNT_END_CXX

# endif
