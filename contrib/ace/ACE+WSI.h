
# ifndef __WSI_ACE_8F20E046D78F4D1389474C889A208C3E_H_INCLUDED
# define __WSI_ACE_8F20E046D78F4D1389474C889A208C3E_H_INCLUDED

# include <boost/shared_ptr.hpp>

# include <ace/ACE.h>
# include <ace/Synch.h>
# include <ace/Synch_Traits.h>
# include <ace/Asynch_IO.h>
# include <ace/INET_Addr.h>
# include <ace/Task.h>
# include <ace/Reactor.h>
# include <ace/Proactor.h>
# include <ace/Svc_Handler.h>
# include <ace/SOCK_Stream.h>
# include <ace/Mutex.h>
# include <ace/Semaphore.h>

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ace)

template <typename RT, typename LT>
RT type_cast(LT const& l);

typedef ::boost::shared_ptr<ACE_Time_Value> ACE_Time_Value_Shared;

WSI_END_NS
WSI_END_HEADER_CXX

# include "../../Classes/Core/Time+WSI.h"
# include "../../Classes/Cross/NetAddress.h"
# include "../../Classes/Cross/SocketStream.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ace)

template <>
inline_impl ACE_INET_Addr type_cast<ACE_INET_Addr, cross::NetAddress>(cross::NetAddress const& addr)
{
    switch (addr.addr_type)
    {
        default: break;
        case cross::NetAddress::ADDRESS_IPV4:
        {
            return ACE_INET_Addr(addr.port, addr.address.c_str(), PF_INET);
        } break;
        case cross::NetAddress::ADDRESS_IPV6:
        {
            return ACE_INET_Addr(addr.port, addr.address.c_str(), PF_INET6);
        } break;
        case cross::NetAddress::ADDRESS_NAME:
        {
            return ACE_INET_Addr(addr.port, addr.address.c_str());
        } break;
        case cross::NetAddress::ADDRESS_ANY:
        {
            return ACE_INET_Addr(addr.port);
        } break;
    }

    return ACE_INET_Addr(addr.port, addr.address.c_str(), PF_INET);
}

template <>
inline_impl cross::NetAddress type_cast<cross::NetAddress, ACE_INET_Addr>(ACE_INET_Addr const& addr)
{
    return cross::NetAddress(addr.get_ip_address(), addr.get_port_number());
}

template <>
inline_impl ACE_Time_Value_Shared type_cast<ACE_Time_Value_Shared, core::Timeout>(core::Timeout const& tm)
{
    if (tm.infinate())
        return ACE_Time_Value_Shared();
    long mill = tm.millisecond();
    ACE_Time_Value_Shared ret(new ACE_Time_Value);
    ret->set_msec(mill);
    return ret;
}

template <>
inline_impl ACE_Time_Value type_cast<ACE_Time_Value, core::Timeout>(core::Timeout const& tm)
{
    long mill = tm.millisecond();
    ACE_Time_Value ret;
    ret.set_msec(mill);
    return ret;
}

template <typename T>
class Criticalize
	: public T
{
public:

	Criticalize()
	{
	}

	void lock()
	{
		_cri.acquire();
	}

	void unlock()
	{
		_cri.release();
	}

	bool try_lock()
	{
		return -1 != _cri.tryacquire();
	}

	void acquire()
	{
		_mtx.acquire();
	}

	void release()
	{
		_mtx.release();
	}

	void try_acquire()
	{
		return -1 != _mtx.tryacquire();
	}

protected:

	ACE_Mutex _mtx;
	ACE_Semaphore _cri;

};

template <typename T>
class auto_protected
{
public:

	auto_protected(T& obj)
		: object(obj)
	{
		object.acquire();
	}

	~auto_protected()
	{
		object.release();
	}

	T& object;

};

class SocketStreamSync
: public cross::SocketStream
{
public:
    
    SocketStreamSync();    
    ~SocketStreamSync();
    
    typedef ACE_SOCK_Stream PEER_STREAM;
    typedef PEER_STREAM::PEER_ADDR PEER_ADDR;
    
    //! reader.
    ACE_SOCK_Stream* r()
    {
        return (ACE_SOCK_Stream*)reader;
    }
    
    //! writer.
    ACE_SOCK_Stream* w()
    {
        return (ACE_SOCK_Stream*)writer;
    }        
    
    //! write data.
    virtual bool write(core::data const& d);
    
    //! read data.
    virtual bool read(core::data& d);
    virtual bool read(core::data&, core::Timeout const& tm);
    
    //! close.
	virtual void close_read();        
	virtual void close_write();	
	virtual void close();
    
    //! get remote address.
    virtual cross::NetAddress remote_address() const;
    
    //! operator.
    operator ACE_SOCK_Stream& ()
    {
        return _stm;
    }
    
    operator ACE_SOCK_Stream const& () const
    {
        return _stm;
    }
    
    ACE_HANDLE get_handle() const
    {
        return _stm.get_handle();
    }
    
    void set_handle(ACE_HANDLE hdl)
    {
        _stm.set_handle(hdl);
    }
    
protected:
    
    ACE_SOCK_Stream _stm;
    
    WSIDECL_SIGNALS_SLOTS;
};

class SocketStreamAsync
: public cross::SocketStream
{
public:
    
    //! async stream impl in ace.
    SocketStreamAsync();
    virtual ~SocketStreamAsync();
    
    typedef ACE_SOCK_Stream PEER_STREAM;
    typedef PEER_STREAM::PEER_ADDR PEER_ADDR;
    
    //! reader.
    ACE_Asynch_Read_Stream* r()
    {
        return (ACE_Asynch_Read_Stream*)reader;
    }
    
    //! writer.
    ACE_Asynch_Write_Stream* w()
    {
        return (ACE_Asynch_Write_Stream*)writer;
    }    

    //! read data.
    virtual bool read(core::data& d);
    virtual bool read(core::data&, core::Timeout const& tm);
	virtual void complete();
    
    //! write data.
    virtual bool write(core::data const& d);

    //! wait for data.
    virtual bool wait_next(bool _wait = true);

    //! data buffer.
    core::framedata* buffer;

    //! store all buffers.
	typedef Criticalize< core::stack<core::framedata*> > buffers_type;
    buffers_type buffers;

    //! frame len.
    usize frame_length;

protected:

    bool _do_read(core::data&);

    WSIDECL_SIGNALS_SLOTS;

};

class ReactorTask
	: public ACE_Task<ACE_NULL_SYNCH>
{
public:

	ReactorTask();
	virtual ~ReactorTask();

	virtual int open();
	virtual int close();
	virtual int svc();

    static void RunLoop();

protected:

	typedef core::vector<ACE_thread_t> threads_type;
	threads_type _threads;

};

class ProactorTask
    : public ACE_Task<ACE_NULL_SYNCH>
{
public:

    ProactorTask();
    virtual ~ProactorTask();

    virtual int open();
    virtual int close();
    virtual int svc();

    static void RunLoop();

protected:

    typedef core::vector<ACE_thread_t> threads_type;
    threads_type _threads;
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif