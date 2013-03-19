
# ifndef __NNT_LOGGER_0C85AC2EBB2F40DBBE639FC98B59F025_H_INCLUDED
# define __NNT_LOGGER_0C85AC2EBB2F40DBBE639FC98B59F025_H_INCLUDED

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(store)

NNTCLASS(Logger);

NNTDECL_PRIVATE_HEAD_CXX(Logger);

class Logger
{
    NNTDECL_NOCOPY(Logger);
    NNTDECL_PRIVATE_CXX(Logger);
    
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

NNTCLASS(DMYLogger);

//! day - month - year file logger.
class DMYLogger
: public Logger
{
public:

    bool open(core::string const& dir, core::string const& ext, core::string const& prefix = "");

};

NNT_END_NS 
NNT_END_HEADER_CXX

# endif