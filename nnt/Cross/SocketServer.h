
# ifndef __NNT_CROSS_SOCKETSERVER_D18EE2B9FC8143B1B1B0F44199704523_H_INCLUDED
# define __NNT_CROSS_SOCKETSERVER_D18EE2B9FC8143B1B1B0F44199704523_H_INCLUDED

# include "./NetAddress.h"

NNT_BEGIN_HEADER_CXX

//! while a client connect to server, of server.
NNT_EXTERN cxx::signal_t kSignalConnected;

//! while connection closed.
NNT_EXTERN cxx::signal_t kSignalDisconnected;

NNT_BEGIN_NS(cross)

NNTCLASS(SocketServer);

NNTDECL_PRIVATE_HEAD_CXX(SocketServer)

class SocketServer
: public cxx::Object<>
{
    NNTDECL_PRIVATE_CXX(SocketServer);
    typedef cxx::Object<> super;
    
public:
    SocketServer();
    ~SocketServer();
    
    NNTDECL_SIGNALS_SLOTS;
    
public:
    
    //! listen on address.
    bool listen(core::string const& addr);
    
    //! stop.
    void stop();

protected:
    
    NetAddress address;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
