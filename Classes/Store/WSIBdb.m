
# import "Core.h"
# import "WSIBdb.h"

WSI_BEGIN_HEADER_C
# include <bdb/db.h>
WSI_END_HEADER_C

WSI_BEGIN_OBJC

WSIDECL_PRIVATE_BEGIN(WSIBdb, NSObject)
{
    DB* _db;
}

@property (nonatomic, assign) DB* db;

- (void)sync;
- (void)close;
- (BOOL)open:(char const*)url;

WSIDECL_PRIVATE_IMPL(WSIBdb)

@synthesize db = _db;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    [self close];
    [super dealloc];
}

- (void)close {
    if (_db) {
        [self sync];
        _db->close(_db, 0);
        _db = nil;
    }
}

- (BOOL)open:(const char *)url {  
    [self close];        
    
    // create db
    if (db_create(&_db, NULL, 0) != 0) {
        NSLog(@"failed to create bdb.");
        return NO;
    }
    
    int ret = 0;
    
    if (d_owner.dup) {
        ret = _db->set_flags(_db, DB_DUP);
    }
    
    if (ret != 0) {
        _db->close(_db, 0);
        _db = NULL;
        return NO;
    }
    
    // open db
    ret = _db->open(_db,
                    NULL,
                    url,
                    NULL,
                    DB_BTREE,
                    (d_owner.readonly ? DB_RDONLY : DB_CREATE) | (d_owner.dup ? DB_DUP : 0),
                    0);
    
    if (ret != 0) {
        _db->close(_db, 0);
        _db = NULL;
        return NO;
    }

    return YES;
}

- (void)sync {
    _db->sync(_db, 0);
}

WSIDECL_PRIVATE_END

@implementation WSIBdb

@synthesize readonly = _readonly;
@synthesize name = _name;
@synthesize dup = _dup;

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(WSIBdb);
        
    _readonly = NO;
    _dup = NO;
    
    return self;
}

- (id)initWith:(NSString *)path type:(WSIDirectoryType)type {
    self = [self init];
    if (NO == [self openDbWith:path type:type]) {
        [self release];
        return nil;
    }
    return self;
}

- (void)dealloc {
    safe_release(_name);

    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (BOOL)openDbWithUrl:(NSURL *)url {
    char const* db_url = NULL;
    if ([url scheme]) {
        db_url = [[url relativePath] UTF8String];
    } else {
        db_url = [[url absoluteString] UTF8String];
    }
    
    // set name.
    self.name = [url lastPathComponent];
    
    return [d_ptr open:db_url];
}

- (BOOL)put:(NSData*)data key:(NSData*)key {
    DBT dbkey, dbval;
    memset(&dbkey, 0, sizeof(DBT));
    memset(&dbval, 0, sizeof(DBT));
    dbkey.data = (void*)[key bytes];
    dbkey.size = (u_int32_t)[key length];
    dbval.data = (void*)[data bytes];
    dbval.size = (u_int32_t)[data length];
    int ret = d_ptr.db->put(d_ptr.db, NULL, &dbkey, &dbval, DB_OVERWRITE_DUP);
    return ret == 0;
}

- (BOOL)put_raw:(void *)data dlen:(uint)dlen key:(void *)key klen:(uint)klen {
    DBT dbkey, dbval;
    memset(&dbkey, 0, sizeof(DBT));
    memset(&dbval, 0, sizeof(DBT));
    dbkey.data = key;
    dbkey.size = klen;
    dbval.data = data;
    dbval.size = dlen;
    int ret = d_ptr.db->put(d_ptr.db, NULL, &dbkey, &dbval, DB_OVERWRITE_DUP);
    return ret == 0;
}

- (BOOL)over:(NSData*)data key:(NSData*)key {
    DBT dbkey, dbval;
    memset(&dbkey, 0, sizeof(DBT));
    memset(&dbval, 0, sizeof(DBT));
    dbkey.data = (void*)[key bytes];
    dbkey.size = (u_int32_t)[key length];
    dbval.data = (void*)[data bytes];
    dbval.size = (u_int32_t)[data length];
    int ret = d_ptr.db->put(d_ptr.db, NULL, &dbkey, &dbval, DB_OVERWRITE_DUP);
    return ret == 0;
}

- (BOOL)over_raw:(void *)data dlen:(uint)dlen key:(void *)key klen:(uint)klen {
    DBT dbkey, dbval;
    memset(&dbkey, 0, sizeof(DBT));
    memset(&dbval, 0, sizeof(DBT));
    dbkey.data = key;
    dbkey.size = klen;
    dbval.data = data;
    dbval.size = dlen;
    int ret = d_ptr.db->put(d_ptr.db, NULL, &dbkey, &dbval, DB_OVERWRITE_DUP);
    return ret == 0;
}

- (NSArray*)get:(NSData*)key {
    DBT dbkey, dbval;
    memset(&dbkey, 0, sizeof(DBT));
    memset(&dbval, 0, sizeof(DBT));
    dbkey.data = (void*)[key bytes];
    dbkey.size = (u_int32_t)[key length];
    dbval.flags = DB_DBT_MALLOC;
    
    int ret;
    
    // for each data
    DBC *cursor = NULL;
    ret = d_ptr.db->cursor(d_ptr.db, NULL, &cursor, 0);
    if (ret)
        return nil;
    ret = cursor->get(cursor, &dbkey, &dbval, DB_SET);
    if (ret == DB_NOTFOUND)
        return nil;
    
    NSMutableArray *arr = [NSMutableArray array];
    while (ret != DB_NOTFOUND) {
        NSData *data = [[NSData alloc] initWithBytes:dbval.data length:dbval.size];
        free(dbval.data);
        [arr addObject:data];
        [data release];
    
        // next record.
        memset(&dbval, 0, sizeof(DBT));
        dbval.flags = DB_DBT_MALLOC;
        
        ret = cursor->get(cursor, &dbkey, &dbval, DB_NEXT_DUP);
    }
    
    cursor->close(cursor);
    return arr;
}

- (NSArray*)get_raw:(void *)key len:(uint)len {
    DBT dbkey, dbval;
    memset(&dbkey, 0, sizeof(DBT));
    memset(&dbval, 0, sizeof(DBT));
    dbkey.data = key;
    dbkey.size = len;
    dbval.flags = DB_DBT_MALLOC;
    int ret;
    // for each data
    DBC *cursor = NULL;
    ret = d_ptr.db->cursor(d_ptr.db, NULL, &cursor, 0);
    if (ret) {
        return nil;
    }
    ret = cursor->get(cursor, &dbkey, &dbval, DB_SET);
    NSMutableArray *arr = [NSMutableArray array];
    while (ret != DB_NOTFOUND) {
        NSData *data = [[NSData alloc] initWithBytes:dbval.data length:dbval.size];
        free(dbval.data);
        [arr addObject:data];
        [data release];
        
        memset(&dbval, 0, sizeof(DBT));
        ret = cursor->get(cursor, &dbkey, &dbval, DB_NEXT_DUP);
    }
    cursor->close(cursor);
    return arr;
}

- (uint)get:(void*)key klen:(uint)klen data:(void*)data dlen:(uint)dlen {
    DBT dbkey, dbval;
    memset(&dbkey, 0, sizeof(DBT));
    memset(&dbval, 0, sizeof(DBT));
    dbkey.data = key;
    dbkey.size = klen;
    dbval.flags = DB_DBT_MALLOC;
    int ret;
    // for each data
    DBC *cursor = NULL;
    ret = d_ptr.db->cursor(d_ptr.db, NULL, &cursor, 0);
    if (ret) {
        return 0;
    }
    ret = cursor->get(cursor, &dbkey, &dbval, DB_SET);
    if (ret == DB_NOTFOUND) {
        return 0;
    }
    memcpy(data, dbval.data, MIN(dbval.size, dlen));
    free(dbval.data);
    cursor->close(cursor);
    return dbval.size;
}

- (bool)get:(void*)key klen:(uint)klen pdata:(void**)data pdlen:(uint*)pdlen {
    DBT dbkey, dbval;
    memset(&dbkey, 0, sizeof(DBT));
    memset(&dbval, 0, sizeof(DBT));
    dbkey.data = key;
    dbkey.size = klen;
    dbval.flags = DB_DBT_MALLOC;
    int ret;
    // for each data
    DBC *cursor = NULL;
    ret = d_ptr.db->cursor(d_ptr.db, NULL, &cursor, 0);
    if (ret) {
        return false;
    }
    ret = cursor->get(cursor, &dbkey, &dbval, DB_SET);
    if (ret == DB_NOTFOUND) {
        return false;
    }
    *data = dbval.data;
    *pdlen = dbval.size;
    cursor->close(cursor);
    return true;
}

- (BOOL)remove:(void*)key klen:(uint)klen {
    DBT dbkey, dbval;
    memset(&dbkey, 0, sizeof(DBT));
    memset(&dbval, 0, sizeof(DBT));
    dbkey.data = key;
    dbkey.size = klen;
    dbval.flags = DB_DBT_MALLOC;
    int ret;
    // for each data
    DBC *cursor = NULL;
    ret = d_ptr.db->cursor(d_ptr.db, NULL, &cursor, 0);
    if (ret) {
        return NO;
    }
    ret = cursor->get(cursor, &dbkey, &dbval, DB_SET);
    if (ret == DB_NOTFOUND) {
        return NO;
    }
    cursor->del(cursor, 0);
    cursor->close(cursor);
    return YES;
}

typedef bool (*BdbWalkFunc)(DBT* key, DBT* data, DBC* cursor);

static bool remove_cursor(DBT* key, DBT* data, DBC* cursor)
{
    if (cursor->del(cursor, 0) != 0) {
        trace_msg(@"fail to remove bdb cursor.");
    }
    return true;
}

- (void)clear {
    [self walkBdb:remove_cursor];
    [self sync];
}

- (void)walkBdb:(BdbWalkFunc)func {
    DBC *cursor;
    DBT key, data;
    memset(&key, 0, sizeof(DBT));
    memset(&data, 0, sizeof(DBT));
    d_ptr.db->cursor(d_ptr.db, NULL, &cursor, 0);
    while (0 == (cursor->get(cursor, &key, &data, DB_NEXT))) {
        if (false == (*func)(&key, &data, cursor)) {
            break;
        }
    }
    cursor->close(cursor);
}

- (void)walk:(DBMSNoSqlWalkFunc)func {
    DBC *cursor;
    DBT key, data;
    memset(&key, 0, sizeof(DBT));
    memset(&data, 0, sizeof(DBT));
    d_ptr.db->cursor(d_ptr.db, NULL, &cursor, 0);
    while (0 == (cursor->get(cursor, &key, &data, DB_NEXT))) {
        if (false == (*func)(key.data, key.size, data.data, data.size)) {
            break;
        }
    }
    cursor->close(cursor);
}

typedef struct {
    DBC *cursor;
    DBT key, data;
} WSIBdbIterator;

- (void*)iterator_begin {
    WSIBdbIterator *iter = (WSIBdbIterator*)malloc(sizeof(WSIBdbIterator));
    memset(iter, 0, sizeof(WSIBdbIterator));
    if (d_ptr.db->cursor(d_ptr.db, NULL, &iter->cursor, 0)) {
        free(iter);
        return 0;
    }
    void* ret = [self iterator_next:iter];
    if (ret == nil) {
        free(iter);
        return 0;
    }
    return ret;
}

- (void*)iterator_next:(void *)_iter {
    WSIBdbIterator *iter = (WSIBdbIterator*)_iter;
    if (0 == (iter->cursor->get(iter->cursor, &iter->key, &iter->data, DB_NEXT))) {
        return iter;
    }
    return 0;
}

- (void)iterator_end:(void *)iter {
    free(iter);
}

- (void)iterator_retrive:(void*)_iter key:(void**)key klen:(uint*)klen data:(void**)data dlen:(uint*)dlen {
    WSIBdbIterator* iter = (WSIBdbIterator*)_iter;
    *key = iter->key.data;
    *klen = iter->key.size;
    *data = iter->data.data;
    *dlen = iter->data.size;
}

- (void)sync {
    [d_ptr sync];
}

- (void)close {
    [d_ptr close];
}

@end

WSI_END_OBJC
