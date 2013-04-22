
# ifndef __NNT_CORE_URL_cb223ed0a5ec48a39117c2495b066787_H_INCLUDED
# define __NNT_CORE_URL_cb223ed0a5ec48a39117c2495b066787_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ntl)

template <typename strT, typename sysT>
class Url
{
public:

    typedef strT string_type;

    string_type full() const
    {
        return scheme + path;
    }

    string_type scheme;
    string_type path;

};

template <typename strT, typename sysT = os_type>
class FileUrl
    : public Url<strT, sysT>
{

};

# ifdef NNT_KERNEL_SPACE

template <typename strT>
class FileUrl <strT, os_windows>
    : public Url<strT, os_windows>
{

    typedef Url<strT, os_windows> super;

public:

    typedef typename super::string_type string_type;

    FileUrl(string_type const& ph = "")
    {
        this->scheme = "\\??\\";
        this->path = ph;
    }

};

# endif

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
