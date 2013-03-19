
# import "Core.h"
# import "DBMSqlAbstract.h"

WSI_BEGIN_OBJC

@implementation DBMSqlParam

@synthesize pos, value, type, name;

- (id)init {
    self = [super init];
    
    pos = -1;
    
    return self;
}

- (void)dealloc {
    zero_release(value);
    zero_release(name);
    
    [super dealloc];
}

+ (id)paramWith:(id)value type:(WSIValueType)type pos:(uint)pos {
    DBMSqlParam* ret = [[DBMSqlParam alloc] init];
    ret.pos = pos;
    ret.value = value;
    ret.type = type;
    return [ret autorelease];
}

@end

@implementation DBMSqlDatatable

@synthesize cols, rows;

- (void)dealloc {
    zero_release(cols);
    zero_release(rows);
    
    [super dealloc];
}

- (NSArray*)valueForKey:(NSString *)key {
    uindex idx = [cols indexOfObject:key];
    NSMutableArray *arr = [[[NSMutableArray alloc] initWithCapacity:[rows count]] autorelease];
    for (NSArray *row in rows) {
        [arr addObject:[row objectAtIndex:idx]];
    }
    return arr;
}

- (id)valueForKey:(NSString *)key row:(uint)row {
    uindex idx = [cols indexOfObject:key];
    NSArray *tgt = [rows objectAtIndex:row];
    return [tgt objectAtIndex:idx];
}

- (uindex)indexOfKey:(NSString *)key {
    return [cols indexOfObject:key];
}

- (NSUInteger)count {
    return [rows count];
}

@end

@implementation DBMSqlAbstract

- (DBMSqlDatatable*)exec:(NSString *)sql params:(NSArray *)param {
    return nil;
}

- (DBMSqlDatatable*)exec:(NSString *)sql {
    return [self exec:sql params:nil];
}

- (void)close {
    PASS;
}

@end

@implementation DBMSqlUrlAbstract

- (BOOL)openDbWith:(NSString *)path type:(WSIDirectoryType)type {
    //NSURL *url = WSIDirectoryCreateWithType(@"", type);
    NSURL* url = WSIFileTouchWithType(path, type);
    
    if (url == nil) {
        trace_msg(@"failed to open db at nil url");
        return NO;
    }

    /*
    url = [url URLByAppendingPathComponent:path];
    
    if (url == nil) {
        trace_msg(@"failed to open db at nil url");
        return NO;
    }
     */
    
    return [self openDbWithUrl:url];
}

- (BOOL)openDbWithUrl:(NSURL *)url {
    return NO;
}

- (id)initWith:(NSString *)path type:(WSIDirectoryType)type {
    self = [self init];
    
    if (![self openDbWith:path type:type]) {
        [self release];
        return nil;
    }
    
    return self;
}

@end

WSI_END_OBJC