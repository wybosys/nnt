
# import "Core.h"
# import "NSDictionary+NNT.h"

NNT_BEGIN_OBJC

@implementation NSDictionary (NNT)

+ (id)dictionaryWithKey:(id)key forObj:(id)obj {
    return [NSDictionary dictionaryWithObject:obj forKey:key];
}

- (id)objectForKey:(id)key null:(id)null {
    id ret = [self objectForKey:key];
    if ([ret isKindOfClass:[NSNull class]])
        ret = null;    
    return ret;
}

- (id)valueForKey:(NSString*)key null:(id)null {
    id ret = [self valueForKey:key];
    if ([ret isKindOfClass:[NSNull class]])
        ret = null;
    return ret;
}

- (id)valueForPath:(NSArray *)path null:(id)null {
    id ret = [self valueForPath:path];
    if (ret == nil)
        ret = null;
    if ([ret isKindOfClass:[NSNull class]])
        ret = null;
    return ret;
}

- (id)valueForPath:(NSArray *)path {
    id current = [self objectForKey:path.first];
    for (uint i = 1; i < [path count] && current; ++i) {
        id key = [path objectAtIndex:i];
        if ([current isKindOfClass:[NSDictionary class]]) {
            current = [(NSDictionary*)current objectForKey:key];
        } else if ([current isKindOfClass:[NSArray class]] && [key isKindOfClass:[NSNumber class]]) {
            current = [(NSArray*)current objectAtIndex:[(NSNumber*)key unsignedIntValue]];
        } else {
            current = nil;
        }
    }
    return current;
}

+ (NSDictionary*)restrictDictionary:(id)obj {
    if ([obj isKindOfClass:[NSDictionary class]])
        return obj;
    return nil;
}

- (NSString*)combineWithKVSep:(NSString*)kvsep andSegSep:(NSString*)segsep {
    return [self combineWithKVSep:kvsep andSegSep:segsep keysur:@"" valsur:@""];
}

- (NSString*)combineWithKVSep:(NSString*)kvsep andSegSep:(NSString*)segsep keysur:(NSString*)keysur valsur:(NSString*)valsur {
    NSMutableString *ret_str = [[NSMutableString alloc] initWithString:@""];
    bool mutli = false;
    for (NSString* key in self) {
        if (mutli) {
            [ret_str appendString:segsep];
        }
        NSString* val = [self valueForKey:key];
        [ret_str appendFormat:@"%@%@%@%@%@%@%@", keysur, key, keysur, kvsep, valsur, val, valsur];
        mutli = true;
    }
    return [ret_str autorelease];
}

- (NSString*)combineWithKVSep:(NSString*)kvsep andSegSep:(NSString*)segsep sort:(SEL)sort {
    return [self combineWithKVSep:kvsep andSegSep:segsep keysur:@"" valsur:@"" sort:sort];
}

- (NSString*)combineWithKVSep:(NSString*)kvsep andSegSep:(NSString*)segsep keysur:(NSString*)keysur valsur:(NSString*)valsur sort:(SEL)sort {
    NSMutableString *ret_str = [[NSMutableString alloc] initWithString:@""];
    bool mutli = false;
    for (NSString* key in [[self allKeys] sortedArrayUsingSelector:sort]) {
        if (mutli) {
            [ret_str appendString:segsep];
        }
        NSString* val = [self valueForKey:key];
        [ret_str appendFormat:@"%@%@%@%@%@%@%@", keysur, key, keysur, kvsep, valsur, val, valsur];
        mutli = true;
    }
    return [ret_str autorelease];
}

- (uint)coreType {
    return NNTCoreTypeDictionary;
}

- (NSArray*)pairArray {
    NSMutableArray * arr = [NSMutableArray array];
    for (id each in self) {
        NSPair* pa = [[NSPair alloc] init];
        pa.first = each;
        pa.second = [self objectForKey:each];
        [arr addObject:pa];
        [pa release];
    }
    return arr;
}

@end

NNTIMPL_CATEGORY(NSDictionary, NNT);
NNTIMPL_CATEGORY(NSMutableDictionary, NNT);

@implementation NSMutableDictionary (NNT)

- (void)setKey:(id)key forObj:(id)obj {
    [self setObject:obj forKey:key];
}

+ (NSMutableDictionary*)restrictDictionary:(id)obj {
    if ([obj isKindOfClass:[NSMutableDictionary class]])
        return obj;
    return nil;
}

@end

NNT_END_OBJC

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

Dictionary null_dictionary;

NNT_END_NS
NNT_END_HEADER_CXX
