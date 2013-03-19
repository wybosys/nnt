
# include "Core.h"
# include "SocketClient.h"
# include "SocketStream.h"

# include "../../contrib/ace/ACE+NNT.h"
# include <ace/Connector.h>
# include <ace/SOCK_Connector.h>
# include <ace/Asynch_Connector.h>

NNT_BEGIN_CXX

cxx::signal_t kSignalSuccess = "::nnt::success";
cxx::signal_t kSignalFailed = "::nnt::failed";

# ifdef NNT_MSVC
#   define USE_PROACTOR_MODE
# else
#   define USE_REACTOR_MODE
# endif

NNT_BEGIN_NS(cross)

// sync ace.

class _ace_connector_sync
: public ACE_SOCK_CONNECTOR
{
public:
    
    typedef ACE_SOCK_STREAM stream_type;
    
    stream_type& peer()
    {
        return peer_;        
    }
    
    stream_type const& peer() const
    {
        return peer_;
    }
    
    ace::SocketStreamSync& stream()
    {
        return peer_;
    }
    
    ace::SocketStreamSync const& stream() const
    {
        return peer_;
    }
    
protected:
    
    ace::SocketStreamSync peer_;

};

class _ace_handler_async
    : public ACE_Service_Handler
{
    typedef ACE_Service_Handler super;

public:

    _ace_handler_async()
        : _owner(NULL)
    {
        PASS;
    }

    ~_ace_handler_async()
    {
        PASS;
    }

    ace::SocketStreamAsync& stream()
    {
        return _peer;
    }

    virtual void open(ACE_HANDLE new_handle, ACE_Message_Block &message_block)
    {
        if (_peer.r()->open(*this) != 0 ||
            _peer.w()->open(*this) != 0)
        {
            trace_msg("failed to open stream on handler.");
            _owner->emit(kSignalFailed);
            return;
        }

		_peer.buffers.lock();

        // wait read message.
        if (_peer.wait_next(false) == false)
        {
            trace_msg("failed to wait stream on handler.");
			_peer.buffers.unlock();
            _owner->emit(kSignalFailed);
            return;
        }

        // post signal.
        trace_msg("success open stream.");
        _owner->emit(kSignalSuccess);
    }

    virtual void handle_read_stream(const ACE_Asynch_Read_Stream::Result &result)
    {		
        trace_msg("handle input.");

		ace::auto_protected<ace::SocketStreamAsync::buffers_type> ap(_peer.buffers);		

        if (!result.success() || result.bytes_transferred() == 0)
        {
            // free resource.
            result.message_block().release();

            trace_msg("failed to read data from handle.");
            _owner->emit(kSignalClosed);
            return;
        }

        // set new buffer size.
        _peer.buffer->set_length(result.bytes_transferred());

		// add new buffer into array.
        _peer.buffers.push(_peer.buffer);

        // need post signal.
		if (_peer.wait == false)
        {            
            //trace_msg("post bytes available signal.");
            _peer.emit(kSignalBytesAvailable, eventobj_t::Data(&_peer));
        }

# ifdef NNT_DEBUG
		trace_msg("read stream: " + core::string(_peer.buffer->c_str(), _peer.buffer->length()));
# endif

        // free resource.
        result.message_block().release();

		// unlock.
		_peer.buffers.unlock();
    }

    virtual void handle_write_stream(const ACE_Asynch_Write_Stream::Result &result)
    {
        //trace_msg("handle output.");        
        result.message_block().release();

        if (result.success() == false)
        {
            _peer.emit(kSignalClosed);
        }
    }

    virtual void handle_time_out(const ACE_Time_Value &tv, const void *act = 0)
    {
        trace_msg("handle timeout.");
        super::handle_time_out(tv, act);
    }

    virtual ace::SocketStreamAsync& peer()
    {
        return _peer;
    }

    SocketClientAsync *_owner;
    ace::SocketStreamAsync _peer;

};

class _aceasync_handler
    : public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>
{
    friend class SocketClientAsync;
    typedef ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH> super;
    
public:
   
    _aceasync_handler()
    {
        PASS;
    }
    
    ~_aceasync_handler()
    {
        PASS;
    }
    
    stream_type const& peer() const
    {
        return peer_;
    }
    
    stream_type& peer()
    {
        return peer_;
    }

	ACE_HANDLE get_handle() const
	{
		return peer().get_handle();
	}
    
    virtual int open(void* arg)
    {          
        // register event.
		int ret = this->reactor()->register_handler(get_handle(),  
			this,
			ACE_Event_Handler::READ_MASK);

		if (ret == -1)
		{
			trace_msg("socketclient: failed to register handle.");
		}

        return ret;
    }
    
    virtual int handle_input(ACE_HANDLE fd)  
    {  
        trace_msg("handle input.");

        peer_.emit(kSignalBytesAvailable, eventobj_t::Data(&peer_));   
        
		if (peer_.wait == false)
            return super::handle_input(fd);
        
        return 0;
    }  
    
    virtual int handle_output (ACE_HANDLE fd)
    {
        trace_msg("handle output.");
        return super::handle_output(fd);
    }
    
    virtual int handle_exception (ACE_HANDLE fd)
    {
        trace_msg("handle exception.");
        return super::handle_exception(fd);
    }

    virtual int handle_timeout (const ACE_Time_Value &current_time,
                                const void *act)
    {
        trace_msg("handle timeout.");
        return super::handle_timeout(current_time, act);
    }
    
    virtual int handle_close (ACE_HANDLE fd,
                              ACE_Reactor_Mask mask)
    {
        trace_msg("handle close.");
        
        peer_.emit(kSignalClosed, eventobj_t::Data(&peer_));
        
        return super::handle_close(fd, mask);
    }
    
    ace::SocketStreamSync& stream()
    {
        return peer_;
    }
        
protected:
    
    ace::SocketStreamSync peer_;
    
};

class _ace_connector_async
    : public ACE_Asynch_Connector<_ace_handler_async>
{
    typedef ACE_Asynch_Connector<_ace_handler_async> super;

public:

    _ace_connector_async()
        : _owner(NULL), _handle(NULL)
    {
        PASS;
    }

    ~_ace_connector_async()
    {
        PASS;
    }   

    int open (_ace_handler_async* hdl = NULL, bool pass_addresses = false, ACE_Proactor *proactor = 0, bool validate_new_connection = true)
    {
        _handle = hdl;
        return super::open(pass_addresses, proactor, validate_new_connection);
    }

    virtual _ace_handler_async* make_handler()
    {
        if (_handle)
            return _handle;
        _ace_handler_async* hdl = super::make_handler();
        hdl->_owner = _owner;
        return hdl;
    }

    _ace_handler_async* _handle;
    SocketClientAsync* _owner;

};

class _aceasync_connector
: public ACE_Connector<_aceasync_handler, ACE_SOCK_CONNECTOR>
{
public:

	_aceasync_connector()
	{
		PASS;
	}

	~_aceasync_connector()
	{
		PASS;
    }

};

// sync impl.

NNTDECL_PRIVATE_BEGIN_CXX(SocketClient)

void init()
{
	PASS;   
}

void dealloc()
{
	PASS;
}

_ace_connector_sync connector;

NNTDECL_PRIVATE_END_CXX

SocketClient::SocketClient()
{
    NNTDECL_PRIVATE_CONSTRUCT(SocketClient);
}

SocketClient::~SocketClient()
{
    NNTDECL_PRIVATE_DESTROY();
}

NNTDECL_SIGNALS_BEGIN(SocketClient, super)
NNT_SIGNAL(kSignalSuccess)
NNT_SIGNAL(kSignalFailed)
NNTDECL_SIGNALS_END

bool SocketClient::connect_to(cross::NetAddress const& addr, core::Timeout const& tm)
{    
    int ret = d_ptr->connector.connect(d_ptr->connector.peer(),
                                       ace::type_cast<ACE_INET_Addr>(addr), 
                                       ace::type_cast<ace::ACE_Time_Value_Shared>(tm).get()
                                       );
    if (ret == 0)
    {
        emit(kSignalSuccess);
    }
    else
    {		
        emit(kSignalFailed);
		trace_msg("socketclient: failed to connect server.");
    }
    return ret == 0;
}

void SocketClient::close()
{
    d_ptr->connector.peer().close();
}

SocketStream& SocketClient::stream()
{
    return d_ptr->connector.stream();
}

SocketStream const& SocketClient::stream() const
{
    return d_ptr->connector.stream();
}

// async impl.

NNTDECL_PRIVATE_BEGIN_CXX(SocketClientAsync)

void init()
{
    handler = NULL;

# ifdef USE_REACTOR_MODE
    ace::ReactorTask::RunLoop();
# endif
    
# ifdef USE_PROACTOR_MODE
    connector._owner = d_owner;
    ace::ProactorTask::RunLoop();
# endif
}

void dealloc()
{
# ifdef USE_REACTOR_MODE
    connector.close();
# endif
    
# ifdef USE_PROACTOR_MODE
    connector.cancel();
# endif
}

# ifdef USE_REACTOR_MODE
_aceasync_connector connector;
_aceasync_handler *handler;
# endif

# ifdef USE_PROACTOR_MODE
_ace_connector_async connector;
_ace_handler_async *handler;
# endif

NNTDECL_PRIVATE_END_CXX

SocketClientAsync::SocketClientAsync()
{
    NNTDECL_PRIVATE_CONSTRUCT(SocketClientAsync);
}

SocketClientAsync::~SocketClientAsync()
{
    NNTDECL_PRIVATE_DESTROY();
}

NNTDECL_SIGNALS_BEGIN(SocketClientAsync, super)
NNT_SIGNAL(kSignalSuccess)
NNT_SIGNAL(kSignalFailed)
NNTDECL_SIGNALS_END

void SocketClientAsync::connect_to(cross::NetAddress const& addr, core::Timeout const& tm)
{    
    // connect.
    
# ifdef USE_REACTOR_MODE
    ACE_Synch_Options opt = ACE_Synch_Options::synch;
    if (tm.infinate())
    {
        opt.set(ACE_Synch_Options::USE_REACTOR, ACE_Time_Value::zero, 0);
    }
    else
    {
        opt.timeout(ace::type_cast<ACE_Time_Value>(tm));
    }
    
    d_ptr->handler = new _aceasync_handler;
# endif
    
# ifdef USE_PROACTOR_MODE
    d_ptr->handler = new _ace_handler_async;
    d_ptr->handler->_owner = this;
# endif

    // connect.
    
# ifdef USE_REACTOR_MODE
    int ret = d_ptr->connector.connect(d_ptr->handler,
                                       ace::type_cast<ACE_INET_Addr>(addr),
                                       opt
                                       );
# endif

# ifdef USE_PROACTOR_MODE
    int ret = d_ptr->connector.open(d_ptr->handler);
    if (ret == 0)
    {
        ret = d_ptr->connector.connect(ace::type_cast<ACE_INET_Addr>(addr));
    }
# endif

    if (ret == 0)
    {
# ifdef USE_REACTOR_MODE
        emit(kSignalSuccess);
# endif
    }
    else
    {
        emit(kSignalFailed);
		trace_msg("socketclient: failed to connect server.");
    }
}

void SocketClientAsync::close()
{
# ifdef USE_REACTOR_MODE
    d_ptr->connector.close();
# endif
    
# ifdef USE_PROACTOR_MODE
    d_ptr->connector.cancel();
# endif
}

SocketStream& SocketClientAsync::stream()
{
    return d_ptr->handler->stream();
}

SocketStream const& SocketClientAsync::stream() const
{
    return d_ptr->handler->stream();
}

NNT_END_NS
NNT_END_CXX