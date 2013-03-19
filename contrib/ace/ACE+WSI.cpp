
# include "Core.h"
# include "ACE+WSI.h"
# include "../../Classes/Core/Task+WSI.h"

# if !defined(ACE_HAS_WIN32_OVERLAPPED_IO) && !defined(ACE_HAS_AIO_CALLS)
#   error "unsupport aio handler."
# endif

WSI_BEGIN_CXX
WSI_BEGIN_NS(ace)

struct _ace_global
{
    _ace_global()
    {        
        ACE::init();                
    }
    
    ~_ace_global()
    {
        ACE::fini();
    }
};

static _ace_global _ace;

ReactorTask::ReactorTask()
{
	_threads.resize(4);
}

ReactorTask::~ReactorTask()
{
	PASS;
}

int ReactorTask::open()
{
	return this->activate(
		THR_NEW_LWP,
		_threads.size(),
		0,
		ACE_DEFAULT_THREAD_PRIORITY,  
		-1,  
		this,  
		0,  
		0,  
		0,  
		core::pointer(_threads));
}

int ReactorTask::close()
{        
	ACE_Reactor::instance()->end_event_loop();

	this->wait();
	return 0;
}
    
int ReactorTask::svc()
{
	ACE_Reactor::instance()->owner(ACE_Thread::self());
	ACE_Reactor::instance()->run_event_loop();
	return 0;
}

ProactorTask::ProactorTask()
{
    _threads.resize(4);
}

ProactorTask::~ProactorTask()
{
    PASS;
}

int ProactorTask::open()
{
    return this->activate(
        THR_NEW_LWP,
        _threads.size(),
        0,
        ACE_DEFAULT_THREAD_PRIORITY,  
        -1,  
        this,  
        0,  
        0,  
        0,  
        core::pointer(_threads));
}

int ProactorTask::close()
{        
    ACE_Proactor::instance()->end_event_loop();

    this->wait();
    return 0;
}

int ProactorTask::svc()
{
    ACE_Proactor::instance()->run_event_loop();
    return 0;
}
    
// stream sync.

SocketStreamSync::SocketStreamSync()
{
    this->reader = this->writer = &this->_stm;
}

SocketStreamSync::~SocketStreamSync()
{
    this->close();
}

bool SocketStreamSync::write(core::data const& d)
{
    int sta = this->w()->send_n(d.c_str(), d.length());
    bool suc = sta == d.length();
    
# ifdef WSI_DEBUG
    if (suc) 
	{
		trace_msg("stream send:\n" + core::type_cast<core::string>(d));
	}
    else 
	{
		trace_msg("failed to send data:\n" + core::type_cast<core::string>(d));
	}
# endif
    
    return suc;
}

bool SocketStreamSync::read(core::data& d)
{    
    int sta = this->r()->recv_n((void*)d.bytes(), d.length());
    bool suc = sta > 0;
    
	d.set_length(sta);
	this->wait = sta != 0;
    
# ifdef WSI_DEBUG
    if (suc) 
	{
		trace_msg("stream receive:\n" + core::string(d.c_str(), d.length()));
	}
    else 
	{
		trace_msg("failed to receive data.\n");
	}
# endif
    
    return suc;    
}

bool SocketStreamSync::read(core::data& d, core::Timeout const& tm)
{
    size_t readed = 0;
    this->r()->recv_n((void*)d.bytes(), d.length(), 
                      ace::type_cast<ace::ACE_Time_Value_Shared>(tm).get(),
                      &readed
                      );

    bool suc = readed > 0;

	d.set_length(readed);
	this->wait = readed != 0;
    
# ifdef WSI_DEBUG
    if (suc) 
	{
		trace_msg("stream receive:\n" + core::string(d.c_str(), d.length()));
	}
    else
	{
		trace_msg("failed to receive data.\n");
	}
# endif
    
    return suc;  
}

void SocketStreamSync::close_read()
{
    _stm.close_reader();
}

void SocketStreamSync::close_write()
{
    _stm.close_writer();
}

void SocketStreamSync::close()
{
    _stm.close_writer();
    _stm.close();
}

cross::NetAddress SocketStreamSync::remote_address() const
{
    ACE_INET_Addr addr;
    _stm.get_remote_addr(addr);
    cross::NetAddress addr_client = ace::type_cast<cross::NetAddress>(addr);
    return addr_client;
}

WSIDECL_SIGNALS_BEGIN(SocketStreamSync, cross::SocketStream)
WSI_SIGNAL(kSignalBytesAvailable)
WSI_SIGNAL(kSignalClosed)
WSIDECL_SIGNALS_END

// stream async.

SocketStreamAsync::SocketStreamAsync()
: buffer(NULL)
{
    reader = new ACE_Asynch_Read_Stream();
    writer = new ACE_Asynch_Write_Stream();
    frame_length = 4096;
}

SocketStreamAsync::~SocketStreamAsync()
{
    safe_delete_type(reader, ACE_Asynch_Read_Stream*);
    safe_delete_type(writer, ACE_Asynch_Write_Stream*);
    core::clear_destroy(buffers);
}

WSIDECL_SIGNALS_BEGIN(SocketStreamAsync, cross::SocketStream)
WSI_SIGNAL(kSignalBytesAvailable)
WSI_SIGNAL(kSignalClosed)
WSIDECL_SIGNALS_END

bool SocketStreamAsync::wait_next(bool _wait)
{
	this->wait = _wait;

	if (buffer != NULL)
		trace_msg("buffer is must be null");

	buffer = new core::framedata(frame_length);

    bool ret = true;
    ACE_Message_Block* mb = new ACE_Message_Block(buffer->c_str(), buffer->length());
    if (r()->read(*mb, mb->space()) != 0)
    {
        ret = false;
        mb->release();
    }

    return ret;
}

bool SocketStreamAsync::_do_read(core::data& d)
{
	if (buffers.size() == 0)
	{
		this->wait = true;

		if (buffers.try_lock())
		{
			// no deqeue wait.
			// for next read.
			wait_next(true);

			trace_msg("fetch next fragment data.");
		}
		else 
		{			
			trace_msg("fetch is during a wait.");
		}

		buffers.lock();
		buffers.unlock();
	}

	auto_protected<buffers_type> ap(buffers);

	core::framedata target(d.bytes(), d.length());
	while (buffers.size() != 0)
	{
		core::framedata* top = buffers.top();
		if (top->length() > d.length())
		{
			target.copy(top->bytes(), d.length());
			target.move(d.length());
			top->move(d.length());
			break;
		}
		else
		{
			target.copy(top->bytes(), top->length());
			target.move(top->length());
			d.set_length(top->length());
			          
			// if top is buffer.
			if (top == buffer)
			{
				buffer = NULL;
			}

			// free top.
			delete top;
			buffers.pop();			

		}
	}

	target.set_length(target.position());

# ifdef WSI_DEBUG
    if (d.length() != 0)
    {
        trace_msg("stream receive:\n" + core::string(d.c_str(), d.length()));
    }
# endif

    return d.length() != 0;
}

void SocketStreamAsync::complete()
{
	if (buffers.size() == 0)
	{
		// for next read date.
		buffers.lock();
		wait_next(false);
	}
}

bool SocketStreamAsync::read(core::data& d)
{
    bool ret = _do_read(d);
    return ret;
}

bool SocketStreamAsync::read(core::data& d, core::Timeout const& tm)
{
    bool ret = _do_read(d);
    return ret;
}

bool SocketStreamAsync::write(core::data const& d)
{
    ACE_Message_Block* block = new ACE_Message_Block(d.length());
    block->copy(d.c_str(), d.length());
    
    int sta = this->w()->write(*block, block->length());

    if (sta == 0) 
	{
		trace_msg("stream send:\n" + core::type_cast<core::string>(d));
	}
    else 
	{
        trace_msg("failed to send data:\n" + core::type_cast<core::string>(d));        
        block->release();
	}   

    return sta == 0;
}

void ReactorTask::RunLoop()
{
    static ReactorTask task;
	static bool task_run = false;
	if (task_run)
		return;
	task_run = true;

	task.open();
}

void ProactorTask::RunLoop()
{
    static ProactorTask task;
    static bool task_run = false;
    if (task_run)        
        return;
    task_run = true;

    task.open();
}

WSI_END_NS
WSI_END_CXX