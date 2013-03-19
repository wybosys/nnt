
# ifndef __WSI_CROSS_NETADDRESS_C2B223FD39654F86874B8FE9765F8666_H_INCLUDED
# define __WSI_CROSS_NETADDRESS_C2B223FD39654F86874B8FE9765F8666_H_INCLUDED

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(cross)

WSICLASS(NetAddress);

class NetAddress
{
public:
    enum ADDRESS_TYPE
    {
        ADDRESS_UNKNOWN,
        ADDRESS_IPV4,
        ADDRESS_IPV6,
        ADDRESS_NAME,
        ADDRESS_ANY,
    };
    
public:
    
    NetAddress();
    NetAddress(core::string const& url);
    NetAddress(core::string const& addr, uint port, ADDRESS_TYPE = ADDRESS_IPV4);
    NetAddress(uint ip, uint port);
    
    //! set address
    //! @return false if url is in bad format.
    bool set_address(core::string const& url);
    NetAddress& operator = (core::string const&);
    
    //! set address.
    //! @param ip address as integer.
    //! @param port port.
    bool set_address(uint ip, uint port);
    
    //! to string.
    core::string to_string() const;
    
public:
    
    WSI_STATIC bool is_ipv4(core::string const& url);
    WSI_STATIC bool is_ipv6(core::string const& url);
    WSI_STATIC bool is_host(core::string const& url);
    WSI_STATIC bool is_any(core::string const& url);
        
public:
    
    core::string address, addport; //! address like ipv4, ipv6, or hostname
    uint port; //! port on address.
    ADDRESS_TYPE addr_type; //! address type.
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif