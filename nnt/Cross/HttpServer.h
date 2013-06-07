
# ifndef __NNT_CROSS_HTTPSERVER_3222F06EBCE74858BA42A4C7C74E1331_H_INCLUDED
# define __NNT_CROSS_HTTPSERVER_3222F06EBCE74858BA42A4C7C74E1331_H_INCLUDED

# include "../Core/NetAddress.h"
# include "../TL/URI+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cross)

NNTCLASS(HttpConfig);

class HttpConfig
{
public:

    core::NetAddress addr;

    bool is_correct() const;

};

NNTCLASS(HttpServer);
NNTCLASS(HttpConnection);

class HttpConnection
{
public:

    void* connection;
    void const* request;
    HttpServer* server;
    
    void update();

    int write(core::string const&);
    int write(core::data const&);
    int read(core::data&);
    
    core::uri uri;
    core::string method, version;
    core::map<core::string, core::string> headers;
    
};

NNTDECL_PRIVATE_HEAD_CXX(HttpServer);

class HttpServer
: public cxx::Class<cxx::Object<> >
{
    NNTDECL_PRIVATE_CXX(HttpServer);
    friend class HttpConnection;
    
public:
    
    HttpServer();
    ~HttpServer();

    bool start();
    void stop();

    //! config for httpd.    
    HttpConfig config;

    NNTDECL_SIGNALS_SLOTS;
    
};

static cxx::signal_t kSignalNewConnection = "::nnt::connection::new";

NNT_END_NS
NNT_END_HEADER_CXX

# endif
