
# ifndef __WSI_CROSS_SQLITEREQUEST_4DCF3D599EC7490F835FD69AF828E379_H_INCLUDED
# define __WSI_CROSS_SQLITEREQUEST_4DCF3D599EC7490F835FD69AF828E379_H_INCLUDED

# include "NullRpc.h"

# ifdef WSI_OBJC

# include "Directory+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface SqliteRequest : NullRpc {
    WSIDirectoryType _directoryType;
}

@property (nonatomic, assign) WSIDirectoryType directoryType;

@end

@interface AbsSqliteRequest : SqliteRequest

@end

@interface WritableSqliteRequest : SqliteRequest

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(cross)

class SqliteRequest
: public ns::Object< ::SqliteRequest >
{
    
};

class AbsSqliteRequest
: public ns::Object< ::AbsSqliteRequest >
{
    
};

class WritableSqliteRequest
: public ns::Object< ::WritableSqliteRequest >
{
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif // objc-cxx

# endif // objc

# endif
