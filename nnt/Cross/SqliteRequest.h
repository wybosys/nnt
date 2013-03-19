
# ifndef __NNT_CROSS_SQLITEREQUEST_4DCF3D599EC7490F835FD69AF828E379_H_INCLUDED
# define __NNT_CROSS_SQLITEREQUEST_4DCF3D599EC7490F835FD69AF828E379_H_INCLUDED

# include "NullRpc.h"

# ifdef NNT_OBJC

# include "Directory+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface SqliteRequest : NullRpc {
    NNTDirectoryType _directoryType;
}

@property (nonatomic, assign) NNTDirectoryType directoryType;

@end

@interface AbsSqliteRequest : SqliteRequest

@end

@interface WritableSqliteRequest : SqliteRequest

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cross)

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

NNT_END_NS
NNT_END_HEADER_CXX

# endif // objc-cxx

# endif // objc

# endif
