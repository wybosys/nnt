
# import "Core.h"
# import "DBMSNoSqlAbstract.h"

NNT_BEGIN_OBJC

@implementation DBMSNoSqlAbstract

- (BOOL)put:(NSData*)data key:(NSData*)key {
    return NO;
}

- (BOOL)over:(NSData*)data key:(NSData*)key {
    return NO;
}

- (BOOL)put_raw:(void *)data dlen:(uint)dlen key:(void *)key klen:(uint)klen {
    return NO;
}

- (BOOL)over_raw:(void *)data dlen:(uint)dlen key:(void *)key klen:(uint)klen {
    return NO;
}

- (NSArray*)get:(NSData*)key {
    return nil;
}

- (NSArray*)get_raw:(void*)key len:(uint)len {
    return nil;
}

- (uint)get:(void*)key klen:(uint)klen data:(void*)data dlen:(uint)dlen {
    return 0;
}

- (bool)get:(void*)key klen:(uint)klen pdata:(void**)data pdlen:(uint*)pdlen {
    return false;
}

- (BOOL)remove:(void*)key klen:(uint)klen {
    return NO;
}

- (BOOL)remove:(NSData*)key {
    return [self remove:(void*)[key bytes] klen:[key length]];
}

- (void)walk:(DBMSNoSqlWalkFunc)func {
    PASS;
}

- (void)sync {
    PASS;
}

- (void)close {
    PASS;
}

- (void*)iterator_begin {
    return 0;
}

- (void*)iterator_next:(void *)iter {
    return iter;
}

- (void)iterator_end:(void *)iter {
    PASS;
}

- (void)iterator_retrive:(void*)iter key:(void**)key klen:(uint*)klen data:(void**)data dlen:(uint*)dlen {
    PASS;
}

@end

@implementation DBMSNoSqlUrlAbstract

- (id)initWith:(NSString*)path type:(NNTDirectoryType)type {
    self = [self init];
    if (![self openDbWith:path type:type]) {
        [self release];
        return nil;
    }
    return self;
}

- (BOOL)openDbWith:(NSString*)path type:(NNTDirectoryType)type {
    NSURL *url = NNTDirectoryCreateWithType(@"", type);
    if (url == nil)
        return NO;
    url = [url URLByAppendingPathComponent:path];
    if (url == nil)
        return NO;
    return [self openDbWithUrl:url];
}

- (BOOL)openDbWithUrl:(NSURL*)url {
    return NO;
}

@end

NNT_END_OBJC