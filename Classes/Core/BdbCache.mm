
# import "Core.h"
# import "BdbCache.h"

WSI_BEGIN_HEADER_C
# include <bdb/db.h>
WSI_END_HEADER_C

WSI_BEGIN_OBJC

@interface BdbCachePrivate : NSObject {
    BdbCache *d_owner;
    DB* db;
}

@property (nonatomic, assign) BdbCache *d_owner;
@property (nonatomic, assign) DB* db;

- (void)close_db;

@end

@implementation BdbCachePrivate

@synthesize d_owner;
@synthesize db;

- (id)init {
    self = [super init];
    
    int ret = db_create(&db, NULL, 0);
    if (ret) {
        trace_msg(@"db create failed");
    }
    
    return self;
}

- (void)dealloc {
    [self close_db];
    [super dealloc];
}

- (void)close_db {
    if (db) {
        db->close(db, 0);
        db = nil;
    }
}

@end

@implementation BdbCache

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT_EX(BdbCache, d_ptr_bdb);
    return self;
}

- (id)initWithPath:(NSString *)path type:(WSIDirectoryType)type {
    self = [super initWithPath:path type:type];
    WSIDECL_PRIVATE_INIT_EX(BdbCache, d_ptr_bdb);
    
    if (self.url) {
        NSString *path = [[self.url URLByAppendingPathComponent:@"cache.db"] path];
        int ret = d_ptr_bdb.db->open(d_ptr_bdb.db,
                                     NULL,
                                     [path cStringUsingEncoding:NSUTF8StringEncoding],
                                     NULL,
                                     DB_BTREE,
                                     DB_CREATE,
                                     0);
        if (ret) {
            trace_msg(@"database open failed");
        }
    }
    
    return self;
}

- (void)clear {
    DBC *cursor;
    DBT key, data;
    memset(&key, 0, sizeof(DBT));
    memset(&data, 0, sizeof(DBT));
    d_ptr_bdb.db->cursor(d_ptr_bdb.db, NULL, &cursor, 0);
    while (0 == (cursor->get(cursor, &key, &data, DB_NEXT))) {
        cursor->del(cursor, 0);
    }
    cursor->close(cursor);
    d_ptr_bdb.db->sync(d_ptr_bdb.db, 0);
}

- (void)dealloc {
    WSIDECL_PRIVATE_DEALLOC_EX(d_ptr_bdb);
    [super dealloc];
}

- (void)removeItem:(CacheItem *)item {
    if (item.pdata) {
        NSTuple3 *pdata = (NSTuple3*)item.pdata;
        NSString *keyname = pdata.v2;
        DBT key, data;
        memset(&key, 0, sizeof(DBT));
        memset(&data, 0, sizeof(DBT));
        NSData *d_data = [keyname dataUsingEncoding:NSUTF8StringEncoding];
        key.data = (void*)[d_data bytes];
        key.size = (u_int32_t)[d_data length];
        DBC *cursor;
        int ret = 0;
        if (0 == (ret = d_ptr_bdb.db->cursor(d_ptr_bdb.db, NULL, &cursor, 0))) {
            if (0 == (ret = cursor->get(cursor, &key, &data, DB_SET))) {
                ret = cursor->del(cursor, 0);
            }
        }
        if (ret) {
            trace_msg(@"bdb cache remove item failed");
        }
        cursor->close(cursor);
    }
    
    int ret = d_ptr_bdb.db->sync(d_ptr_bdb.db, 0);
    if (ret) {
        trace_msg(@"remove record from bdb failed");
    }

    [super removeItem:item];
}

- (BOOL)save {
    [super save];
    
    // flush to db
    int ret = d_ptr_bdb.db->sync(d_ptr_bdb.db, 0);
    if (ret) {
        trace_msg(@"bdb cache save failed");
        return NO;
    }
    return YES;
}

- (BOOL)saveItem:(NSString*)key item:(CacheItem*)item {
    BOOL suc = YES;
    NSData *data = [item toData];
    if (data) {        
        NSString *key_name = item.code;
        key_name = [NSString stringWithFormat:@"%@-%@", NSStringFromClass([item class]), key_name];
        NSData *data_key = [key_name dataUsingEncoding:NSUTF8StringEncoding];
        DBT tkey, tdata;
        memset(&tkey, 0, sizeof(DBT));
        memset(&tdata, 0, sizeof(DBT));
        tkey.data = (void*)[data_key bytes];
        tkey.size = (u_int32_t)[data_key length];
        tdata.data = (void*)[data bytes];
        tdata.size = (u_int32_t)[data length];
        int ret = d_ptr_bdb.db->put(d_ptr_bdb.db,
                                    NULL,
                                    &tkey,
                                    &tdata,
                                    DB_OVERWRITE_DUP);
        if (ret) {
            suc = NO;
            trace_msg(@"cache item save failed");
        }
    }    
    item.updated = NO;
    return suc;
}

- (BOOL)load {
    WSIMACRO_LOCKOBJ(self);
    
    [self begin_load];
    
    int ret;
    // for each data
    DBC *cursor = NULL;
    ret = d_ptr_bdb.db->cursor(d_ptr_bdb.db, NULL, &cursor, 0);
    if (ret) {
        trace_msg(@"bdb cache load failed");
        return NO;
    }
    DBT tkey, tdata;
    memset(&tkey, 0, sizeof(DBT));
    memset(&tdata, 0, sizeof(DBT));
    tdata.flags = DB_DBT_MALLOC;
    ret = cursor->get(cursor, &tkey, &tdata, DB_FIRST);
    while (ret == 0) {
        NSData *data_key = [NSData dataWithBytes:tkey.data length:tkey.size];
        NSString *keyname = [[NSString alloc] initWithData:data_key encoding:NSUTF8StringEncoding];
        
        NSArray *arr = [keyname componentsSeparatedByString:@"-"];
        if ([arr count] != 2) {
            [keyname release];
            continue;
        }
        NSString *type_name = [arr objectAtIndex:0];
        CacheItem *item = [[NSClassFromString(type_name) alloc] init];
        if (item == nil) {
            [keyname release];
            continue;
        }
        item.pending = YES;
        
        NSPointer *addr = [[NSPointer alloc] initWithAddr:tdata.data];
        NSTuple3 *pair = [NSTuple3 new];
        pair.v0 = addr;
        pair.v1 = [NSNumber numberWithLongLong:tdata.size];
        pair.v2 = keyname;
        item.pdata = pair;
        [addr release];
        [pair release];
        
        item.code = [arr objectAtIndex:1];
        
        [self addItem:item];
        //[self addItemUnsafe:item];
        
        [item release];
        
        [keyname release];
        ret = cursor->get(cursor, &tkey, &tdata, DB_NEXT);
    }
    cursor->close(cursor);
    
    [self end_load];
    return YES;
}

- (BOOL)loadItem:(CacheItem *)item {
    NSPair *pair = (NSPair*)item.pdata;
    NSData *data = [NSData dataWithBytesNoCopy:((NSPointer*)pair.first).addr length:[(NSNumber*)pair.second unsignedIntValue]];
    if (data == nil)
        return NO;
    [super loadItem:item];
    BOOL suc = [item fromData:data];
    item.updated = NO;
    return suc;
}


@end

WSI_END_OBJC