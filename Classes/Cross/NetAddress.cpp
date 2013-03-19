
# include "Core.h"
# include "NetAddress.h"
# include "../Core/Boost+NNT.h"
# include <boost/regex.hpp>
# include <boost/lexical_cast.hpp>

NNT_BEGIN_CXX
NNT_BEGIN_NS(cross)

NetAddress::NetAddress()
: port(0)
{
    
}

NetAddress::NetAddress(core::string const& addr)
: port(0)
{
    this->set_address(addr);
}

NetAddress::NetAddress(core::string const& addr, uint port, ADDRESS_TYPE type)
: addr_type(type),
port(0)
{
    this->address = addr;
    this->port = port;
}

NetAddress::NetAddress(uint ip, uint port)
{
    this->set_address(ip, port);
}

bool NetAddress::set_address(const core::string &url)
{
    ADDRESS_TYPE t_type;
    core::string t_addr, t_addp;
    uint t_port = 0;
    if (NetAddress::is_ipv4(url))
    {
        t_type = ADDRESS_IPV4;
        static ::boost::regex re_ipv4_capture("((?:[0-9]{1,3}\\.){3}[0-9]{1,3})(?::([0-9]{1,5}))");
        ::boost::match_results<core::string::const_iterator> wh;
        ::boost::regex_match(url.begin(), url.end(), wh, re_ipv4_capture);
        t_addr = wh[1].str();
        t_addp = wh[2].str();
        t_port = ::boost::lexical_cast<uint>(t_addp);
    } 
    else if (NetAddress::is_ipv6(url))
    {
        t_type = ADDRESS_IPV6;
        static ::boost::regex re_ipv6_capture("\\[((?<![:.\\w])(?:[A-F0-9]{1,4}:){7}[A-F0-9]{1,4}(?![:.\\w]))\\]:([0-9]{1,5})");
        ::boost::match_results<core::string::const_iterator> wh;
        ::boost::regex_match(url.begin(), url.end(), wh, re_ipv6_capture);
        t_addr = wh[1].str();
        t_addp = wh[2].str();
        t_port = ::boost::lexical_cast<uint>(t_addp);
    }
    else if (NetAddress::is_host(url))
    {
        t_type = ADDRESS_NAME;
        static ::boost::regex re_host_capture("([a-z0-9\\-._~%]+|\\[[a-z0-9\\-._~%!$&'()*+,;=:]+\\]):?([0-9]{1,5})?");
        ::boost::match_results<core::string::const_iterator> wh;
        ::boost::regex_match(url.begin(), url.end(), wh, re_host_capture);
        t_addr = wh[1].str();      
        t_addp = wh[2].str();
        if (!t_addp.empty())
            t_port = ::boost::lexical_cast<uint>(t_addp);
    }
    else if (NetAddress::is_any(url))
    {
        t_type = ADDRESS_ANY;
        static ::boost::regex re_any_capture("(\\*):?([0-9]{1,5})?");
        ::boost::match_results<core::string::const_iterator> wh;
        ::boost::regex_match(url.begin(), url.end(), wh, re_any_capture);
        t_addr.clear();
        t_addp = wh[2].str();
        if (!t_addp.empty())
            t_port = ::boost::lexical_cast<uint>(t_addp);
    }
    else
    {
        t_type = ADDRESS_UNKNOWN;
    }
    
    if (t_type != ADDRESS_UNKNOWN)
    {
        this->addr_type = t_type;
        this->address = t_addr;
        this->addport = t_addp;
        this->port = t_port;
    }
    
    return t_type != ADDRESS_UNKNOWN;
}

NetAddress& NetAddress::operator = (core::string const& str)
{
    set_address(str);
    return *this;
}

bool NetAddress::set_address(uint ip, uint port)
{
    this->addr_type = ADDRESS_IPV4;
    this->port = port;
    
    ::std::ostringstream oss;
    oss << b32_h1(ip) << "." << b32_h0(ip) << "." << b32_l1(ip) << "." << b32_l0(ip);
    this->address = oss.str();
    this->addport = ::boost::lexical_cast<core::string>(port);
    
    return true;
}

core::string NetAddress::to_string() const
{        
    if (0 == port)
        return this->address;
    
    core::string re;
    
    switch (this->addr_type)
    {
        case ADDRESS_UNKNOWN: break;
        case ADDRESS_IPV4: re = this->address + ":" + ::boost::lexical_cast<core::string>(this->port); break;
        case ADDRESS_IPV6: re = "[" + this->address + "]:" + ::boost::lexical_cast<core::string>(this->port); break;
        case ADDRESS_NAME: re = this->address + ":" + ::boost::lexical_cast<core::string>(this->port); break;
		case ADDRESS_ANY: re = "*:" +  ::boost::lexical_cast<core::string>(this->port); break;
    }
    
    return re;
}

NNT_STATIC_IMPL bool NetAddress::is_ipv4(const core::string &url)
{
    static ::boost::regex re_ipv4_match("(?:[0-9]{1,3}\\.){3}[0-9]{1,3}(?::[0-9]{1,5})");
    return ::boost::regex_match(url.begin(), url.end(), re_ipv4_match);
}

NNT_STATIC_IMPL bool NetAddress::is_ipv6(const core::string &url)
{
    static ::boost::regex re_ipv6_match("\\[(?<![:.\\w])(?:[A-F0-9]{1,4}:){7}[A-F0-9]{1,4}(?![:.\\w])\\]:[0-9]{1,5}");
    return ::boost::regex_match(url.begin(), url.end(), re_ipv6_match);
}

NNT_STATIC_IMPL bool NetAddress::is_host(const core::string &url)
{
    static ::boost::regex re_host_match("([a-z0-9\\-._~%]+|\\[[a-z0-9\\-._~%!$&'()*+,;=:]+\\])(?::([0-9]{1,5}))?");  
    return ::boost::regex_match(url.begin(), url.end(), re_host_match);
}

NNT_STATIC_IMPL bool NetAddress::is_any(const core::string &url)
{
    static ::boost::regex re_host_match("(\\*)(?::([0-9]{1,5}))?");  
    return ::boost::regex_match(url.begin(), url.end(), re_host_match);
}

NNT_END_NS
NNT_END_CXX
