
# include "Core.h"
# include "SocketStream.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(cross)

SocketStream::SocketStream(void* r, void* w)
: reader(r), writer(w), wait(true)
{
    PASS;
}

SocketStream::~SocketStream()
{
    PASS;
}

bool SocketStream::write(core::data const& d)
{
    trace_msg("write data into air.");
    return true;
}

bool SocketStream::read(core::data&)
{
    trace_msg("read data from air.");
    return true;
}

bool SocketStream::read(core::data&, core::Timeout const& tm)
{
    trace_msg("read data from air.");
    return true;
}

bool SocketStream::read_all(core::data& da, core::Timeout const& tm)
{
    uint framelen = da.length();
    
    if (read(da, tm))
    {
        uint lst_reader = da.length();
    
        if (framelen == lst_reader)
        {
            core::data tmp(framelen);        
            
            while (framelen == lst_reader)
            {            
                tmp.set_length(framelen);
                
                if (read(tmp, tm))
                {
                    da.append(tmp);
                }
                else
                {
					trace_msg("failed to read next fragment data.");
                    return false;
                }
                
                lst_reader = tmp.length();
            }
        }

        complete();
        
        return true;
    }

    return false;
}

void SocketStream::close_read()
{
	PASS;
}

void SocketStream::close_write()
{
	PASS;
}

void SocketStream::close()
{
	this->close_read();
	this->close_write();
}

void SocketStream::complete()
{
    PASS;
}

NetAddress SocketStream::remote_address() const
{
    NetAddress addr;
    return addr;
}

SocketStream null_stream;

NNT_END_NS
NNT_END_CXX