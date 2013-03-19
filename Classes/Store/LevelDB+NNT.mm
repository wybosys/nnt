
# import "Core.h"
# import "LevelDB+NNT.h"
# import "../../3rd/leveldb/db.h"

NNT_BEGIN_OBJC

@interface NNTLevelDBPrivate : NSObject {
    leveldb::DB *db;
}

@property (nonatomic, assign) NNTLevelDB *d_owner;
@property (nonatomic, assign) leveldb::DB *db;

- (leveldb::DB**)ppdb;
- (void)close;

@end

@implementation NNTLevelDBPrivate

@synthesize d_owner;
@synthesize db;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    safe_delete(db);
    [super dealloc];
}

- (void)close {
    safe_delete(db);
    db = NULL;
}

- (leveldb::DB**)ppdb {
    return &db;
}

@end

@implementation NNTLevelDB

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(NNTLevelDB);
    return self;
}

- (id)initWith:(NSString *)path type:(NNTDirectoryType)type {
    self = [self init];
    if (NO == [self openDbWith:path type:type]) {
        [self release];
        return nil;
    }
    return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (BOOL)openDbWithUrl:(NSURL *)url {
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status sta = leveldb::DB::Open(options, 
                                            [[url relativePath] UTF8String],
                                            d_ptr.ppdb);
    return sta.ok();
}

- (BOOL)put:(NSData*)data key:(NSData*)key {
    leveldb::Slice sk((char const*)[key bytes], [key length]);
    leveldb::Slice sv((char const*)[data bytes], [data length]);
    leveldb::Status sta = d_ptr.db->Put(leveldb::WriteOptions(), sk, sv);
    return sta.ok();
}

- (BOOL)put_raw:(void *)data dlen:(uint)dlen key:(void *)key klen:(uint)klen {
    leveldb::Slice sk((char const*)key, klen);
    leveldb::Slice sv((char const*)data, dlen);
    leveldb::Status sta = d_ptr.db->Put(leveldb::WriteOptions(), sk, sv);
    return sta.ok();
}

- (BOOL)over:(NSData*)data key:(NSData*)key {
    leveldb::Slice sk((char const*)[key bytes], [key length]);
    leveldb::Slice sv((char const*)[data bytes], [data length]);
    leveldb::Status sta = d_ptr.db->Put(leveldb::WriteOptions(), sk, sv);
    return sta.ok();
}

- (BOOL)over_raw:(void *)data dlen:(uint)dlen key:(void *)key klen:(uint)klen {
    leveldb::Slice sk((char const*)key, klen);
    leveldb::Slice sv((char const*)data, dlen);
    leveldb::Status sta = d_ptr.db->Put(leveldb::WriteOptions(), sk, sv);
    return sta.ok();
}

- (NSArray*)get:(NSData*)key {
    leveldb::Slice sk((char const*)[key bytes], [key length]);
    std::string val;
    leveldb::Status sta = d_ptr.db->Get(leveldb::ReadOptions(), sk, &val);
    if (sta.ok()) {
        NSMutableArray *arr = [NSMutableArray array];
        NSData *data = [NSData dataWithBytes:val.c_str() length:val.size()];
        [arr addObject:data];
        return arr;
    }
    return nil;
}

- (NSArray*)get_raw:(void*)key len:(uint)len {
    leveldb::Slice sk((char const*)key, len);
    std::string val;
    leveldb::Status sta = d_ptr.db->Get(leveldb::ReadOptions(), sk, &val);
    if (sta.ok()) {
        NSMutableArray *arr = [NSMutableArray array];
        NSData *data = [NSData dataWithBytes:val.c_str() length:val.size()];
        [arr addObject:data];
        return arr;
    }
    return nil;
}

- (uint)get:(void*)key klen:(uint)klen data:(void*)data dlen:(uint)dlen {
    leveldb::Slice sk((char const*)key, klen);
    std::string val;
    leveldb::Status sta = d_ptr.db->Get(leveldb::ReadOptions(), sk, &val);
    if (sta.ok()) {
        memcpy(data, val.c_str(), MIN(val.size(), dlen));
        return (uint)val.size();
    }
    return 0;
}

- (bool)get:(void*)key klen:(uint)klen pdata:(void**)data pdlen:(uint*)pdlen {
    leveldb::Slice sk((char const*)key, klen);
    std::string val;
    leveldb::Status sta = d_ptr.db->Get(leveldb::ReadOptions(), sk, &val);
    if (sta.ok()) {
        *pdlen = (uint)val.size();
        *data = malloc(*pdlen);
        memcpy(*data, val.c_str(), *pdlen);
        return true;
    }
    return false;
}

- (void)close {
    [d_ptr close];
}

@end

NNT_END_OBJC