
# ifndef __WSI_STORE_DBMS_5BBD27B4DB7B4D4492B1D349EF766475_H_INCLUDED
# define __WSI_STORE_DBMS_5BBD27B4DB7B4D4492B1D349EF766475_H_INCLUDED

# ifdef WSI_OBJC

# import "../Core/Directory+WSI.h"

WSI_BEGIN_HEADER_OBJC

@protocol IDBMS <NSObject>

//! close dbms.
- (void)close;

@optional

//! get err message.
- (NSString*)errmsg;

@end

@protocol IDBMSUrl <IDBMS>

- (BOOL)openDbWith:(NSString*)path type:(WSIDirectoryType)type;
- (BOOL)openDbWithUrl:(NSURL*)url;

@end

@interface DBMSAbstract : NSObject <IDBMS>
@end

WSI_END_HEADER_OBJC

# endif

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX 
WSI_BEGIN_NS(store)

class connection_info
{
public:
    
    //! url.
    core::string url;
    
    //! username.
    core::string user;
    
    //! password.
    core::string passwd;
    
    //! database.
    core::string database;
    
    //! encoding.
    core::string encoding;
    
};

WSICLASS(IDBMS);

class IDBMS
    : public RefObject
{
public:
        
    //! open with config string.
    virtual bool connect(connection_info const&) = 0;
    
    //! close database connection.
    virtual void close() = 0;
    
    //! simply the connection info to url.
    virtual core::string urlize(connection_info const&) const = 0;
    
};

class DBURL
{
public:
    
    //! address component.
    core::string address;
    
    //! port component.
    int port;
    
    //! instance component.
    core::string instance;
    
};

# define WSIDECL_DBMS_DRIVER \
static core::string identity; \
static IDBMS* dbmsInstance();

WSIAPI(IDBMS*) instanceDatabaseByIdentity(core::string const& identity);

WSI_END_NS 
WSI_END_HEADER_CXX

# endif

# endif