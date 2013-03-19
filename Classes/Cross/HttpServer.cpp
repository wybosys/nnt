
# include "Core.h"
# include "HttpServer.h"
# include "../../contrib/mongoose/mongoose.h"

WSI_BEGIN_CXX
WSI_BEGIN_NS(cross)

bool HttpConfig::is_correct() const
{
    return true;
}

int HttpConnection::write(core::string const& str)
{
    return write(core::type_cast<core::data>(str));
}

int HttpConnection::write(core::data const& da)
{
    use<mg_connection> cnt = connection;
    return mg_write(cnt, da.bytes(), da.length());
}

int HttpConnection::read(core::data& da)
{
    if (da.length())
        return 0;
    use<mg_connection> cnt = connection;
    return mg_read(cnt, da.bytes(), da.length());
}

WSIDECL_PRIVATE_BEGIN(HttpServer)

void init()
{
    mgctx = NULL;

    memset(&callback, 0, sizeof(mg_callbacks));
    callback.begin_request = self_type::begin_request;
    callback.end_request = self_type::end_request;
    callback.log_message = self_type::log_message;
    callback.init_ssl = self_type::init_ssl;
    callback.websocket_connect = self_type::websocket_connect;
    callback.websocket_ready = self_type::websocket_ready;
    callback.websocket_data = self_type::websocket_data;
    callback.open_file = self_type::open_file;
    callback.init_lua = self_type::init_lua;
    callback.upload = self_type::upload;
}

void dealloc()
{
    stop();    
}

bool start()
{
    if (d_owner->config.is_correct() == false)
        return false;

    // stop old server.
    stop();

    // create mongoose server.

    char const* options[] = {
        "listening_ports", d_owner->config.addr.addport.c_str(),
        NULL    
    };

    mgctx = mg_start(&callback, d_owner, options);

    return mgctx != NULL;
}

void stop()
{
    if (mgctx)
    {
        mg_stop(mgctx);
    }
}

static int begin_request(mg_connection* cnt)
{
    mg_request_info const* req = mg_get_request_info(cnt);
    use<HttpServer> serv = req->user_data;
    HttpConnection evt;
    evt.connection = cnt;
    evt.request = req;
    evt.server = serv;
    serv->emit(kSignalNewConnection, eventobj_t::Data(&evt));
    return 1;
}

static void end_request(mg_connection const* cnt, int reply_status_code)
{

}

static int log_message(mg_connection const* cnt, char const* message)
{
    return 1;
}

static int init_ssl(void* ssl_context)
{
    return 0;
}

static int websocket_connect(mg_connection const* cnt)
{
    return 0;
}

static void websocket_ready(mg_connection* cnt)
{

}

static int websocket_data(mg_connection* cnt)
{
    return 0;
}

static char const* open_file(mg_connection const* cnt, char const* path, size_t* data_len)
{
    return NULL;
}

static void init_lua(mg_connection* cnt, void* lua_context)
{

}

static void upload(mg_connection*, char const* file_name)
{

}

mg_callbacks callback;
mg_context* mgctx;

WSIDECL_PRIVATE_END

HttpServer::HttpServer()
{
    WSIDECL_PRIVATE_CONSTRUCT(HttpServer);
}

HttpServer::~HttpServer()
{
    WSIDECL_PRIVATE_DESTROY();
}

WSIDECL_SIGNALS_BEGIN(HttpServer, super)
WSI_SIGNAL(kSignalNewConnection)
WSIDECL_SIGNALS_END

bool HttpServer::start()
{
    return d_ptr->start();
}

void HttpServer::stop()
{
    d_ptr->stop();
}

WSI_END_NS
WSI_END_CXX
