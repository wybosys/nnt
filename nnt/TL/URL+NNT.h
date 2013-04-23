
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

template <typename strT, typename sysT = os_type, typename spaceT = space_type>
class FileUrl
    : public Url<strT, sysT>
{
    typedef Url<strT, sysT> super;
};

template <typename strT = ntl::string, typename sysT = os_type, typename spaceT = space_type>
class DeviceUrl
    : public FileUrl <strT, sysT, spaceT>
{

};

template <typename strT>
class DeviceUrl <strT, os_windows, space_user>
    : public FileUrl<strT, os_windows, space_user>
{
    typedef FileUrl<strT, os_windows, space_user> super;

public:

    typedef typename super::string_type string_type;

    DeviceUrl(string_type const& ph)
    {
        this->scheme = "\\\\.\\";
        this->path = ph;
    }

};

template <typename strT>
class DeviceUrl <strT, os_windows, space_kernel>
    : public FileUrl<strT, os_windows, space_kernel>
{
    typedef FileUrl<strT, os_windows, space_kernel> super;

public:

    typedef typename super::string_type string_type;

    DeviceUrl(string_type const& ph = "")
    {
        this->scheme = "\\??\\";
        this->path = ph;
    }

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
