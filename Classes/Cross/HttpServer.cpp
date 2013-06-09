
# include "Core.h"
# include "HttpServer.h"
# include "../Core/App.h"
# include "../../contrib/mongoose/mongoose.h"
# include "../Script/PythonWebServer.h"
# include "../Parser/HttpParser.h"
# include "../Script/Python+NNT.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(cross)

HttpConfig::HttpConfig()
{
    document = Environment::workingDirectory() + "/htdocs";
}

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

void HttpConnection::update()
{
    use<mg_request_info> req = request;
    
    // get http info.
    uri = req->uri;
    method = req->request_method;
    version = req->http_version;
    
    // get header fields.
    headers.clear();
    for (int i = 0; i < req->num_headers; ++i)
    {
        mg_request_info::mg_header const& hdr = req->http_headers[i];
        headers.insert(core::make_pair<core::string, core::string>(hdr.name, hdr.value));
    }
}

NNTDECL_PRIVATE_BEGIN(HttpServer)

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
    
    // create http object.
    use<HttpServer> serv = req->user_data;
    HttpConnection http;
    http.connection = cnt;
    http.request = req;
    http.server = serv;
    http.update();
    
    // dispatch.
    core::string const& req_file = http.uri.filename();
    static const core::regex re_python("^\\S+.py$");
    if (re_python.match(req_file))
    {
        python::FileRequest pyreq;
        pyreq.uri = serv->config.document + http.uri;
        pyreq.method = http.method;
        if (pyreq.process())
        {
            parser::Http11Response resp;
            resp.data.append(pyreq.stream);
            http.write(resp.full());
        }
    }
    
    // send signal.
    serv->emit(kSignalNewConnection, eventobj_t::Data(&http));
    
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

NNTDECL_PRIVATE_END

HttpServer::HttpServer()
{
    NNTDECL_PRIVATE_CONSTRUCT(HttpServer);

    // use python as default script interpreter.
    script::UsePython();
}

HttpServer::~HttpServer()
{
    NNTDECL_PRIVATE_DESTROY();
}

NNTDECL_SIGNALS_BEGIN(HttpServer, super)
NNT_SIGNAL(kSignalNewConnection)
NNTDECL_SIGNALS_END

bool HttpServer::start()
{
    return d_ptr->start();
}

void HttpServer::stop()
{
    d_ptr->stop();
}

NNT_END_NS
NNT_END_CXX
