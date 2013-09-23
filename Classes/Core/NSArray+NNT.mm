
# import "Core.h"
# import "NSArray+NNT.h"

NNT_BEGIN_OBJC

@implementation NSArray (NNT)

- (id)first {
    return [self objectAtIndex:0 null:nil];
}

- (id)second {
    return [self objectAtIndex:1 null:nil];
}

- (id)v0 {
    return [self objectAtIndex:0 null:nil];
}

- (id)v1 {
    return [self objectAtIndex:1 null:nil];
}

- (id)v2 {
    return [self objectAtIndex:2 null:nil];
}

- (id)v3 {
    return [self objectAtIndex:3 null:nil];
}

- (id)v4 {
    return [self objectAtIndex:4 null:nil];
}

- (id)v5 {
    return [self objectAtIndex:5 null:nil];
}

- (id)v6 {
    return [self objectAtIndex:6 null:nil];
}

- (id)v7 {
    return [self objectAtIndex:7 null:nil];
}

- (id)v8 {
    return [self objectAtIndex:8 null:nil];
}

- (id)objectAtIndex:(NSUInteger)index null:(id)null {
    id ret = nil;
    if (index >= [self count]) {
        trace_msg(@"array warning: out of range.");
        dthrow_msg(@"array", @"out of range");
        ret = null;
    } else {
        ret = [self objectAtIndex:index];
    }
    if ([ret isKindOfClass:[NSNull class]]) {
        ret = null;
    }
    return ret;
}

+ (NSArray*)safeArray:(id)obj {
    if (obj == nil) {
        return [NSArray array];
    }
    if ([obj isKindOfClass:[NSArray class]])
        return obj;    
    return [NSArray arrayWithObject:obj];
}

+ (NSArray*)restrictArray:(id)obj {
    if ([obj isKindOfClass:[NSArray class]])
        return obj;
    return nil;
}

- (NSArray*)reverse {
    usize const count = [self count];
    NSMutableArray *arr = [NSMutableArray arrayWithCapacity:count];
    for (uindex i = count; i > 0; --i) {
        id obj = [self objectAtIndex:i - 1];
        [arr addObject:obj];
    }
    return arr;
}

- (NSDictionary*)asDictionary {
    NSMutableDictionary *dict = [NSMutableDictionary dictionaryWithCapacity:[self count]];
    uint idx = 0;
    for (id each in self) {
        [dict setObject:each
                 forKey:[NSString stringWithFormat:@"%d", idx++]];
    }
    return dict;
}

- (id)objectAtNextIndex:(NSUInteger)index {
    if (index + 1 < [self count])
        return [self objectAtIndex:index + 1];
    return nil;
}

- (id)objectAtPrevIndex:(NSUInteger)index {
    if (index > 0)
        return [self objectAtIndex:index - 1];
    return nil;
}

- (id)objectAtNext:(id)obj {
    NSUInteger idx = [self indexOfObject:obj];
    if (idx == NSNotFound)
        return nil;
    return [self objectAtNextIndex:idx];
}

- (id)objectAtPrev:(id)obj {
    NSUInteger idx = [self indexOfObject:obj];
    if (idx == NSNotFound)
        return nil;
    return [self objectAtPrevIndex:idx];
}

+ (NSArray*)arrayWithArrays:(NSArray *)arr, ... {
    NSArray *ret = arr;
    
    va_list args;
    va_start(args, arr);
        
    while (NSArray* tgt = (NSArray*)va_arg(args, NSArray*)) {
        ret = [ret arrayByAddingObjectsFromArray:tgt];
    }
    
    va_end(args);
    
    return ret;
}

- (uint)coreType {
    return NNTCoreTypeArray;
}

- (NSArray*)uniqueArray {
    NSMutableArray* arr = [[NSMutableArray alloc] init];
    
    for (id each in self) {
        if ([arr containsObject:each] == NO)
            [arr addObject:each];
    }
    
    return [arr autorelease];
}

@end

NNTIMPL_CATEGORY(NSArray, NNT);

uint kNSMutableArrayInitCapacity = 4;

@implementation NSMutableArray (NNT)

+ (NSMutableArray*)safeArray:(id)obj {
    if (obj == nil) {
        return [NSMutableArray array];
    }
    if ([obj isKindOfClass:[NSMutableArray class]])
        return obj;
    return [NSMutableArray arrayWithObject:obj];
}

+ (NSMutableArray*)restrictArray:(id)obj {
    if ([obj isKindOfClass:[NSMutableArray class]])
        return obj;
    return nil;
}

+ (NSMutableArray*)arrayWithCapacity {
    return [NSMutableArray arrayWithCapacity:kNSMutableArrayInitCapacity];
}

- (void)swapObjectAtIndex:(NSUInteger)from ofIndex:(NSUInteger)to {
    id obj_from = [[self objectAtIndex:from] retain];
    id obj_to = [[self objectAtIndex:to] retain];
    
    [self replaceObjectAtIndex:from withObject:obj_to];
    [self replaceObjectAtIndex:to withObject:obj_from];
    
    [obj_from release];
    [obj_to release];
}

- (void)leftRotate {
    id obj = [[self objectAtIndex:0] retain];
    [self removeObjectAtIndex:0];
    [self addObject:obj];
    [obj release];
}

- (void)leftMove:(id)fill {
    if ([self count] == 0)
        return;
    [self removeObjectAtIndex:0];
    [self addObject:fill];
}

- (void)leftMove {
    [self leftMove:[NSNull null]];
}

//! right rotate.
- (void)rightRotate {
    id obj = [[self objectAtIndex:[self count] - 1] retain];
    [self removeObjectAtIndex:[self count] - 1];
    [self insertObject:obj atIndex:0];
    [obj release];
}

- (void)rightMove:(id)fill {
    if ([self count] == 0)
        return;
    [self removeObjectAtIndex:[self count] - 1];
    [self insertObject:fill atIndex:0];
}

- (void)rightMove {
    [self rightMove:[NSNull null]];
}

@end

NNTIMPL_CATEGORY(NSMutableArray, NNT);

@implementation NNTNSArray

@dynamic first, second, v0, v1, v2, v3, v4, v5, v6, v7, v8;

- (id)first {
    return [self objectAtIndex:0];
}

- (id)second {
    return [self objectAtIndex:1];
}

- (id)v0 {
    return [self objectAtIndex:0];
}

- (id)v1 {
    return [self objectAtIndex:1];
}

- (id)v2 {
    return [self objectAtIndex:2];
}

- (id)v3 {
    return [self objectAtIndex:3];
}

- (id)v4 {
    return [self objectAtIndex:4];
}

- (id)v5 {
    return [self objectAtIndex:5];
}

- (id)v6 {
    return [self objectAtIndex:6];
}

- (id)v7 {
    return [self objectAtIndex:7];
}

- (id)v8 {
    return [self objectAtIndex:8];
}

@end

@implementation NNTNSMutableArray

@dynamic first, second, v0, v1, v2, v3, v4, v5, v6, v7, v8;

- (id)first {
    return [self objectAtIndex:0];
}

- (id)second {
    return [self objectAtIndex:1];
}

- (id)v0 {
    return [self objectAtIndex:0];
}

- (id)v1 {
    return [self objectAtIndex:1];
}

- (id)v2 {
    return [self objectAtIndex:2];
}

- (id)v3 {
    return [self objectAtIndex:3];
}

- (id)v4 {
    return [self objectAtIndex:4];
}

- (id)v5 {
    return [self objectAtIndex:5];
}

- (id)v6 {
    return [self objectAtIndex:6];
}

- (id)v7 {
    return [self objectAtIndex:7];
}

- (id)v8 {
    return [self objectAtIndex:8];
}

@end

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(ns)

Array const null_array = Array();
MutableArray const null_mutablearray = MutableArray();

NNT_END_NS
NNT_END_CXX
