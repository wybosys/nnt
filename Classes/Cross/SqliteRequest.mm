
# import "Core.h"
# import "SqliteRequest.h"
# import "WSISqlite.h"
# import "Model.h"

WSI_BEGIN_OBJC

::wsi::ns::MutableDictionary __gs_databases;

@implementation SqliteRequest

@synthesize directoryType = _directoryType;

- (id)init {
    self = [super init];
    
    _directoryType = WSIDirectoryTypeBundle;
    
    return self;
}

- (NSObject*)call:(Model *)model withUrl:(NSURL*)url {
    [super call:model withUrl:url];
    
    WSIRPC_CALLROUND;
    
    // open database.
    WSISqlite* sqlite = nil;
    WSI_SYNCHRONIZED(self)
    sqlite = __gs_databases[url];
    if (sqlite == nil) {
        sqlite = [[WSISqlite alloc] init];
        if (NO == [sqlite openDbWith:[url relativePath] type:_directoryType]) {
            zero_release(sqlite);
        }
        else {
            __gs_databases[url] = sqlite;
        }
    }
    WSI_SYNCHRONIZED_END
    
    // end.
    if (sqlite == nil)
        return nil;
    
    NSString* method = [model get_method];
    NSArray* params = [model get_params];
    DBMSqlDatatable* dt = nil;
    if (params && params.count) {
        dt = [sqlite exec:method params:params];
    } else {
        dt = [sqlite exec:method];
    }
    
    if (dt == nil) {
        dt = [[[DBMSqlDatatable alloc] init] autorelease];
    }
     
    return dt;
}

@end

@implementation AbsSqliteRequest

- (id)init {
    self = [super init];
    
    self.directoryType = WSIDirectoryTypeAbsolute;
    
    return self;
}

@end

@implementation WritableSqliteRequest

- (id)init {
    self = [super init];
    
    self.directoryType = WSIDirectoryTypeBundleWritable;
    
    return self;
}

@end

WSI_END_OBJC
