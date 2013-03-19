
# include "Core.h"
# include "SocketServer.h"
# include "SocketStream.h"

# include "../../contrib/ace/ACE+NNT.h"
# include <ace/Proactor.h>
# include <ace/Asynch_Acceptor.h>
# include <ace/POSIX_Proactor.h>
# include <ace/Reactor.h>
# include <ace/Acceptor.h>
# include <ace/SOCK_Acceptor.h>

NNT_BEGIN_CXX 

signal_t kSignalConnected = "::nnt::cross::connected";
signal_t kSignalDisconnected = "::nnt::cross::disconnected";
signal_t kSignalBytesAvailable = "::nnt::cross::bytes";
signal_t kSignalClosed = "::nnt::cross::closed";

NNT_BEGIN_NS(cross)

# define USE_REACTOR
//# define USE_PROACTOR

class _ace_proactor_service
: public ACE_Service_Handler
{
    
public:
    _ace_proactor_service();
    virtual ~_ace_proactor_service();
    
public:
    
    virtual void open (ACE_HANDLE new_handle, ACE_Message_Block &message_block);
    virtual void addresses (const ACE_INET_Addr &remote_address, const ACE_INET_Addr &local_address);
    
    virtual void handle_time_out (const ACE_Time_Value &tv, const void *act);    
    virtual void handle_read_stream (const ACE_Asynch_Read_Stream::Result &result);
    virtual void handle_write_stream (const ACE_Asynch_Write_Stream::Result &result);
    
public:

    SocketServer* server;
    
protected:
    
    ace::SocketStreamAsync stm;
    
};

_ace_proactor_service::_ace_proactor_service()
: server(NULL)
{
    PASS;
}

_ace_proactor_service::~_ace_proactor_service()
{
    PASS;
}

void _ace_proactor_service::open(ACE_HANDLE new_handle, ACE_Message_Block &message_block)
{    
    ACE_SOCK_Stream peer(new_handle);
    int bufsiz = ACE_DEFAULT_MAX_SOCKET_BUFSIZ; 
    peer.set_option(SOL_SOCKET, SO_SNDBUF, &bufsiz, sizeof bufsiz);
    
    // prepare stream.
    if (-1 == this->stm.r()->open(*this, new_handle, 0, this->proactor()))
    {
        trace_msg("failed to open reader on it.");
        return;
    }
    
    if (-1 == this->stm.w()->open(*this, new_handle, 0, this->proactor()))
    {
        trace_msg("failed to open writer on it.");
        return;
    }    
            
    // init read.
    ACE_Message_Block* mb;
    ACE_NEW(mb, ACE_Message_Block(1));
    if (-1 == this->stm.r()->read(*mb, 1))
    {
        trace_msg("failed to read init data.");
        safe_delete(mb);
    }
    
    // signal.
    this->server->emit(kSignalConnected, eventobj_t::Data(&this->stm));    
}

void _ace_proactor_service::addresses (const ACE_INET_Addr &remote_address, const ACE_INET_Addr &local_address)
{
    NetAddress addr_client_wsi = ace::type_cast<NetAddress>(remote_address);
    NetAddress addr_host_wsi = ace::type_cast<NetAddress>(local_address);
    
# ifdef NNT_DEBUG
    std::cout << "get a new connect from " << addr_client_wsi.to_string() << " to " << addr_host_wsi.to_string() << std::endl;
# endif
    
    std::cout << "thread: " << ACE_Proactor::instance()->number_of_threads() << std::endl;
}

void _ace_proactor_service::handle_time_out (const ACE_Time_Value &tv, const void *act)
{
    trace_msg("handle timeout");   
}

void _ace_proactor_service::handle_read_stream (const ACE_Asynch_Read_Stream::Result &result)
{
    trace_msg("handle read");
}

void _ace_proactor_service::handle_write_stream (const ACE_Asynch_Write_Stream::Result &result)
{
    trace_msg("handle write");
}

class _ace_proactor_acceptor
: public ACE_Asynch_Acceptor<_ace_proactor_service>
{    
    typedef ACE_Asynch_Acceptor<_ace_proactor_service> super_type;
    
public:  
    _ace_proactor_acceptor();
    virtual ~_ace_proactor_acceptor();
    
public:        
    
    virtual int validate_connection (const ACE_Asynch_Accept::Result& result,
                                     const ACE_INET_Addr &remote,
                                     const ACE_INET_Addr& local);
    
    virtual _ace_proactor_service *make_handler ();
    
public:
    bool open(NetAddress const& addr);
    
public:
    SocketServer* server;
};

_ace_proactor_acceptor::_ace_proactor_acceptor()
: server(NULL)
{
    PASS;
}

_ace_proactor_acceptor::~_ace_proactor_acceptor()
{
    PASS;
}

_ace_proactor_service* _ace_proactor_acceptor::make_handler()
{
    _ace_proactor_service* svi = new _ace_proactor_service;
    svi->server = this->server;        
    return svi;
}

int _ace_proactor_acceptor::validate_connection(const ACE_Asynch_Accept::Result &result, const ACE_INET_Addr &remote, const ACE_INET_Addr &local)
{        
    return 0;
}

bool _ace_proactor_acceptor::open(cross::NetAddress const& in_addr)
{
    ACE_INET_Addr addr = ace::type_cast<ACE_INET_Addr>(in_addr);
    bool sta = -1 != super_type::open(addr);
    if (!sta)
        return false;    
    
    this->validate_new_connection(true);
    this->pass_addresses(true);
    
    return true;
}

class _ace_svc_handler
: public ACE_Svc_Handler<ACE_SOCK_Stream, ACE_MT_SYNCH>
{
    typedef ACE_Svc_Handler<ACE_SOCK_Stream, ACE_MT_SYNCH> super;
    
public:
    _ace_svc_handler();
    ~_ace_svc_handler();
    
public:
    virtual int open (void*);
    
    virtual int handle_input (ACE_HANDLE fd);
    virtual int handle_output (ACE_HANDLE fd);
    virtual int handle_close(ACE_HANDLE,  ACE_Reactor_Mask);
    
    ACE_SOCK_Stream& peer();
    
public:    
    SocketServer* server;
    
protected:
    
    ace::SocketStreamSync stm;
    
};

_ace_svc_handler::_ace_svc_handler()
: server(NULL)
{

}

_ace_svc_handler::~_ace_svc_handler()
{
    
}

ACE_SOCK_Stream& _ace_svc_handler::peer()
{
    return stm;
}

int _ace_svc_handler::open(void *)
{
    stream_type& peer = this->peer();
    
    ACE_INET_Addr addr;
    peer.get_remote_addr(addr);
    NetAddress addr_client = ace::type_cast<NetAddress>(addr);
    peer.get_local_addr(addr);
    NetAddress addr_host = ace::type_cast<NetAddress>(addr);
    
# ifdef NNT_DEBUG
    std::cout << "get a new connect from " << addr_client.to_string() << " to " << addr_host.to_string() << std::endl;
# endif        
    
    // mask.
    this->reactor()->register_handler(peer.get_handle(), 
                                      this, 
                                      ACE_Event_Handler::READ_MASK |
									  ACE_Event_Handler::DONT_CALL
                                      );
    
    // event.
    this->server->emit(kSignalConnected, eventobj_t::Data(&this->stm));
    
    return 0;
}

int _ace_svc_handler::handle_input (ACE_HANDLE fd)
{
    trace_msg("handle input.");
    
    this->stm.emit(kSignalBytesAvailable, eventobj_t::Data(&this->stm));   
    
    if (this->stm.wait == false)
        return super::handle_input(fd);

    return 0;
}

int _ace_svc_handler::handle_output (ACE_HANDLE fd)
{
    trace_msg("handle output.");
    
    return super::handle_output(fd);    
}

int _ace_svc_handler::handle_close(ACE_HANDLE h, ACE_Reactor_Mask m)
{
    trace_msg("handle close.");
    
    this->stm.emit(kSignalClosed, eventobj_t::Data(&this->stm));
    
    return super::ACE_Event_Handler::handle_close(h, m);
}

class _ace_acceptor
: public ACE_Acceptor<_ace_svc_handler, ACE_SOCK_Acceptor>
{
    typedef ACE_Acceptor<_ace_svc_handler, ACE_SOCK_Acceptor> super;
    
public:
    typedef ACE_SOCK_Acceptor::PEER_ADDR PEER_ADDR;
    
    _ace_acceptor();
    ~_ace_acceptor();
    
public:
    bool open(NetAddress const& addr);
    
protected:
    virtual int make_svc_handler (_ace_svc_handler *&sh);
    
public:
    SocketServer* server;
};

_ace_acceptor::_ace_acceptor()
: server(NULL)
{

}

_ace_acceptor::~_ace_acceptor()
{
    
}

int _ace_acceptor::make_svc_handler (_ace_svc_handler *&sh)
{
    sh = new _ace_svc_handler();
    sh->server = this->server;
    return super::make_svc_handler(sh);
}

bool _ace_acceptor::open(NetAddress const& in_addr)
{
    ACE_INET_Addr addr = ace::type_cast<ACE_INET_Addr>(in_addr);
    bool sta = -1 != super::open(addr);
    if (!sta)
        return false;
    return true;
}

NNTDECL_PRIVATE_BEGIN_CXX(SocketServer)

class _ace_task
: public ACE_Task_Base
{
public:
    
    _ace_task()
    :server(NULL)
    {
        PASS;
    }
    
    SocketServer* server;
    
    int open()
    {
        return this->activate();
    }
    
    int close()
    {
        
# ifdef USE_PROACTOR
        ACE_Proactor::end_event_loop();
# endif
        
# ifdef USE_REACTOR
        
        acceptor.close();
        
        ACE_Reactor::end_event_loop();
# endif
        
        this->wait();
        return 0;
    }
    
    virtual int svc()
    {
        
# ifdef USE_PROACTOR
        _ace_proactor_acceptor acceptor;
        acceptor.server = server;    
        
        if (false == acceptor.open(server->address))
		{
			trace_msg("failed to listening on: " + server->address.to_string() + ".");
            return 0;        
		}
		trace_msg("listening on: " + server->address.to_string() + ".");		
        
        ACE_Proactor::run_event_loop();
# endif
        
# ifdef USE_REACTOR
        acceptor.server = server;
        
        if (false == acceptor.open(server->address))
		{
			trace_msg("failed to listening on: " + server->address.to_string() + ".");
            return 0;
		}
		trace_msg("listening on: " + server->address.to_string() + ".");
        
        ACE_Reactor::run_event_loop();
# endif
        
        return 0;
    }
    
    void stop()
    {
# ifdef USE_REACTOR
       
        acceptor.close();
        
# endif
    }
    
# ifdef USE_REACTOR
    
    _ace_acceptor acceptor;
    
# endif
};

_ace_task task;

void init()
{
    task.server = d_owner;
}

void dealloc()
{
    this->task.close();
}

bool listen()
{    
    return this->task.open() == 0;
}

void stop()
{
    this->task.stop();
}

NNTDECL_PRIVATE_END_CXX

SocketServer::SocketServer()
{
    NNTDECL_PRIVATE_CONSTRUCT(SocketServer);
}

SocketServer::~SocketServer()
{
    NNTDECL_PRIVATE_DESTROY();
}

NNTDECL_SIGNALS_BEGIN(SocketServer, super)
NNT_SIGNAL(kSignalConnected)
NNT_SIGNAL(kSignalDisconnected)
NNTDECL_SIGNALS_END

bool SocketServer::listen(const core::string &addr)
{
    bool sta = this->address.set_address(addr);
    sta &= d_ptr->listen();
    return sta;
}

void SocketServer::stop()
{
    d_ptr->stop();
}

NNT_END_NS 
NNT_END_CXX
