
# ifndef __WSI_CROSS_HTTPSERVER_3222F06EBCE74858BA42A4C7C74E1331_H_INCLUDED
# define __WSI_CROSS_HTTPSERVER_3222F06EBCE74858BA42A4C7C74E1331_H_INCLUDED

# include "NetAddress.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(cross)

WSICLASS(HttpConfig);

class HttpConfig
{
public:

    NetAddress addr;

    bool is_correct() const;

};

WSICLASS(HttpServer);
WSICLASS(HttpConnection);

class HttpConnection
{
public:

    void* connection;
    void const* request;
    HttpServer* server;

    int write(core::string const&);
    int write(core::data const&);
    int read(core::data&);

};

WSIDECL_PRIVATE_HEAD_CXX(HttpServer);

class HttpServer
: public cxx::Class<cxx::Object<> >
{
    WSIDECL_PRIVATE_CXX(HttpServer);
    friend class HttpConnection;
    
public:
    
    HttpServer();
    ~HttpServer();

    bool start();
    void stop();

    //! config for httpd.    
    HttpConfig config;

    WSIDECL_SIGNALS_SLOTS;
    
};

static cxx::signal_t kSignalNewConnection = "::wsi::connection::new";

WSI_END_NS
WSI_END_HEADER_CXX

# endif
