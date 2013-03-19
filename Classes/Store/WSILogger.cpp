
# include "Core.h"
# include "NNTLogger.h"
# include "../Core/Time+NNT.h"

# define LOG4CPP_FIX_ERROR_COLLISION
# include <log4cpp/Category.hh>
# include <log4cpp/OstreamAppender.hh>
# include <log4cpp/BasicLayout.hh>
# include <log4cpp/PatternLayout.hh>
# include <log4cpp/Priority.hh>
# include <fstream>

NNT_BEGIN_CXX 
NNT_BEGIN_NS(store)

NNTDECL_PRIVATE_BEGIN_CXX(Logger)

void init()
{
    appender = NULL;
    category = &log4cpp::Category::getRoot();    
    
    // set.
    category->setPriority(NNTDEBUG_EXPRESS(log4cpp::Priority::DEBUG)
                          NNTRELEASE_EXPRESS(log4cpp::Priority::NOTICE));
}

void dealloc()
{
    this->close();
}

bool open(core::string const& file)
{
    this->close();
    
    fd.open(file.c_str(), ::std::ios_base::app | ::std::ios_base::out);
    if (!fd.is_open())
        return false;
    
    // open.
    appender = new log4cpp::OstreamAppender(file.c_str(), &fd);        
    log4cpp::PatternLayout* layout = new log4cpp::PatternLayout;
    layout->setConversionPattern("%d: %p %c %x: %m%n");
    appender->setLayout(layout);
    category->addAppender(appender);
    
    return true;
}

bool resume()
{
    return appender->reopen();
}

void suspend()
{
    appender->close();
}

void close()
{
    if (appender == NULL)
        return;
    appender->close();
    category->removeAppender(appender);
    appender = NULL;
    fd.close();
}

log4cpp::OstreamAppender* appender;
log4cpp::Category* category;
std::ofstream fd;

NNTDECL_PRIVATE_END_CXX

Logger::Logger()
{
    NNTDECL_PRIVATE_CONSTRUCT(Logger);
}

Logger::~Logger()
{
    NNTDECL_PRIVATE_DESTROY();
}

bool Logger::open(const core::string &file)
{
    return d_ptr->open(file);
}

void Logger::close()
{
    d_ptr->close();
}

void Logger::suspend()
{
    d_ptr->suspend();
}

bool Logger::resume()
{
    return d_ptr->resume();
}

void Logger::warn(const core::string & msg)
{
    d_ptr->category->warn(msg);
}

void Logger::error(const core::string & msg)
{
    d_ptr->category->error(msg);
}

void Logger::info(const core::string & msg)
{
    d_ptr->category->info(msg);
}

void Logger::fatal(const core::string & msg)
{
    d_ptr->category->fatal(msg);
}

void Logger::notice(const core::string & msg)
{
    d_ptr->category->notice(msg);
}

bool DMYLogger::open(core::string const& dir, core::string const& ext, core::string const& prefix)
{
    core::Time time;
    time.local_time();
    time.set_format("%d-%m-%Y");
    core::string file = dir + prefix + time.to_string() + ext;
    return Logger::open(file);
}

NNT_END_NS 
NNT_END_CXX
