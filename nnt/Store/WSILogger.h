
# ifndef __WSI_LOGGER_0C85AC2EBB2F40DBBE639FC98B59F025_H_INCLUDED
# define __WSI_LOGGER_0C85AC2EBB2F40DBBE639FC98B59F025_H_INCLUDED

WSI_BEGIN_HEADER_CXX 
WSI_BEGIN_NS(store)

WSICLASS(Logger);

WSIDECL_PRIVATE_HEAD_CXX(Logger);

class Logger
{
    WSIDECL_NOCOPY(Logger);
    WSIDECL_PRIVATE_CXX(Logger);
    
public:
    
    Logger();
    ~Logger();
    
    //! open log file.
    bool open(core::string const& file);
    
    //! close.
    void close();
    
    //! suspend & resume.
    bool resume();
    void suspend();
    
public:
    
    void error(core::string const&);
    void warn(core::string const&);
    void info(core::string const&);
    void notice(core::string const&);
    void fatal(core::string const&);

};

WSICLASS(DMYLogger);

//! day - month - year file logger.
class DMYLogger
: public Logger
{
public:

    bool open(core::string const& dir, core::string const& ext, core::string const& prefix = "");

};

WSI_END_NS 
WSI_END_HEADER_CXX

# endif