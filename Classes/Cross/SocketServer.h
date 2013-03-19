
# ifndef __WSI_CROSS_SOCKETSERVER_D18EE2B9FC8143B1B1B0F44199704523_H_INCLUDED
# define __WSI_CROSS_SOCKETSERVER_D18EE2B9FC8143B1B1B0F44199704523_H_INCLUDED

# include "./NetAddress.h"

WSI_BEGIN_HEADER_CXX

//! while a client connect to server, of server.
WSI_EXTERN cxx::signal_t kSignalConnected;

//! while connection closed.
WSI_EXTERN cxx::signal_t kSignalDisconnected;

WSI_BEGIN_NS(cross)

WSICLASS(SocketServer);

WSIDECL_PRIVATE_HEAD_CXX(SocketServer)

class SocketServer
: public cxx::Object<>
{
    WSIDECL_PRIVATE_CXX(SocketServer);
    typedef cxx::Object<> super;
    
public:
    SocketServer();
    ~SocketServer();
    
    WSIDECL_SIGNALS_SLOTS;
    
public:
    
    //! listen on address.
    bool listen(core::string const& addr);
    
    //! stop.
    void stop();

protected:
    
    NetAddress address;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif
