
# ifndef __NNT_CROSS_SOCKCLIENT_F2A633639EE84B6EA76A5A27157D07FB_H_INCLUDED
# define __NNT_CROSS_SOCKCLIENT_F2A633639EE84B6EA76A5A27157D07FB_H_INCLUDED

# include "../Core/NetAddress.h"
# include "../Core/Time+NNT.h"
# include "SocketStream.h"

NNT_BEGIN_HEADER_CXX

//! emit while connected.
NNT_EXTERN cxx::signal_t kSignalSuccess;

//! emit while failed.
NNT_EXTERN cxx::signal_t kSignalFailed;

NNT_BEGIN_NS(cross)

NNTCLASS(SocketClient);
NNTCLASS(SocketClientAsync);

NNTDECL_PRIVATE_HEAD_CXX(SocketClient);

class SocketClient
: public cxx::Object<>
{
    typedef cxx::Object<> super;
    NNTDECL_PRIVATE_CXX(SocketClient);
    
public:
    
    NNTDECL_SIGNALS_SLOTS;
    
    SocketClient();
    ~SocketClient();
    
    //! connect to server.
    bool connect_to(core::NetAddress const& addr, core::Timeout const& = core::Timeout::Default());
    
    //! disconnect.
    void close();
    
    //! stream.
    SocketStream& stream();
    SocketStream const& stream() const;
    
};

NNTDECL_PRIVATE_HEAD_CXX(SocketClientAsync);

class SocketClientAsync
: public cxx::Object<>
{
    typedef cxx::Object<> super;
    NNTDECL_PRIVATE_CXX(SocketClientAsync);
    
public:
    
    NNTDECL_SIGNALS_SLOTS;
    
    SocketClientAsync();
    ~SocketClientAsync();
    
    //! connect to server.
    void connect_to(core::NetAddress const& addr, core::Timeout const& = core::Timeout::Default());
    
    //! disconnect.
    void close();
    
    //! stream.
    SocketStream& stream();
    SocketStream const& stream() const;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif