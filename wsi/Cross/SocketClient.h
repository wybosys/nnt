
# ifndef __WSI_CROSS_SOCKCLIENT_F2A633639EE84B6EA76A5A27157D07FB_H_INCLUDED
# define __WSI_CROSS_SOCKCLIENT_F2A633639EE84B6EA76A5A27157D07FB_H_INCLUDED

# include "NetAddress.h"
# include "../Core/Time+WSI.h"
# include "SocketStream.h"

WSI_BEGIN_HEADER_CXX

//! emit while connected.
WSI_EXTERN cxx::signal_t kSignalSuccess;

//! emit while failed.
WSI_EXTERN cxx::signal_t kSignalFailed;

WSI_BEGIN_NS(cross)

WSICLASS(SocketClient);
WSICLASS(SocketClientAsync);

WSIDECL_PRIVATE_HEAD_CXX(SocketClient);

class SocketClient
: public cxx::Object<>
{
    typedef cxx::Object<> super;
    WSIDECL_PRIVATE_CXX(SocketClient);
    
public:
    
    WSIDECL_SIGNALS_SLOTS;
    
    SocketClient();
    ~SocketClient();
    
    //! connect to server.
    bool connect_to(NetAddress const& addr, core::Timeout const& = core::Timeout::Default());
    
    //! disconnect.
    void close();
    
    //! stream.
    SocketStream& stream();
    SocketStream const& stream() const;
    
};

WSIDECL_PRIVATE_HEAD_CXX(SocketClientAsync);

class SocketClientAsync
: public cxx::Object<>
{
    typedef cxx::Object<> super;
    WSIDECL_PRIVATE_CXX(SocketClientAsync);
    
public:
    
    WSIDECL_SIGNALS_SLOTS;
    
    SocketClientAsync();
    ~SocketClientAsync();
    
    //! connect to server.
    void connect_to(NetAddress const& addr, core::Timeout const& = core::Timeout::Default());
    
    //! disconnect.
    void close();
    
    //! stream.
    SocketStream& stream();
    SocketStream const& stream() const;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif