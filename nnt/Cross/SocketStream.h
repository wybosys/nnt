
# ifndef __NNT_CROSS_SOCKETSTREAM_23D3050063BE451EA7DD73941EDB5103_H_INCLUDED
# define __NNT_CROSS_SOCKETSTREAM_23D3050063BE451EA7DD73941EDB5103_H_INCLUDED

# include "../Core/NetAddress.h"
# include "../Core/Time+NNT.h"

NNT_BEGIN_HEADER_CXX

//! while stream receive bytes.
NNT_EXTERN cxx::signal_t kSignalBytesAvailable;

//! while stream close.
NNT_EXTERN cxx::signal_t kSignalClosed;

NNT_BEGIN_NS(cross)

NNTCLASS(SocketStream);

class SocketStream
: public cxx::Object<>
{
public:

    SocketStream(void* r = NULL, void* w = NULL);
    virtual ~SocketStream();
    
    //! write data until full.
    virtual bool write(core::data const&);
    
    //! read data until full.
    virtual bool read(core::data&);
    
    //! read data with timeout.
    virtual bool read(core::data&, core::Timeout const& tm);
    
    //! read all.
    virtual bool read_all(core::data&, core::Timeout const&);
    
    //! close write.
	virtual void close_write();
    
    //! close read.
	virtual void close_read();
    
    //! close all.
	virtual void close();

    //! complete.
    virtual void complete();
    
    //! get remove address.
    virtual core::NetAddress remote_address() const;
    
public:
    
    //! reader handle.
    void* reader;
    
    //! writer handle.
    void* writer;
    
    //! wait mode.
    bool wait;
    
};

NNT_EXTERN SocketStream null_stream;

inline_impl SocketStream& operator << (SocketStream& stm, char const* str)
{
    stm.write(core::type_cast<core::data>(str));
    return stm;
}

inline_impl SocketStream& operator >> (SocketStream& stm, core::data& da)
{
    stm.read(da);
    return stm;
}

NNT_END_NS
NNT_END_HEADER_CXX

# endif