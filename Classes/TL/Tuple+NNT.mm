
# import "Core.h"
# import "Tuple+NNT.h"
# import "../Core/coretypes.h"

# ifdef NNT_OBJC

NNT_BEGIN_OBJC

@implementation NSPair

@synthesize first, second;
@dynamic v0, v1;

- (void)dealloc {
    zero_release(first);
    zero_release(second);
    
    [super dealloc];
}

- (NSPair*)initWith:(id)__first second:(id)__second {
    self = [super init];
    self.first = __first;
    self.second = __second;
    return self;
}

+ (NSPair*)pairWith:(id)__first second:(id)__second {
    NSPair *pair = [[[NSPair alloc] initWith:__first second:__second] autorelease];
    return pair;
}

- (void)setV0:(id)__v0 {
    self.first = __v0;
}

- (id)v0 {
    return self.first;
}

- (void)setV1:(id)__v1 {
    self.second = __v1;
}

- (id)v1 {
    return self.second;
}

- (id)objectAtIndex:(uindex)idx {
    id ret = nil;
    switch (idx) {
        case 0: ret = first; break;
        case 1: ret = second; break;
    }
    return ret;
}

- (id)objectAtIndex:(uindex)idx null:(id)null {
    id ret = [self objectAtIndex:idx];
    if (ret == nil) {
        ret = null;
    }
    if ([ret isKindOfClass:[NSNull class]]) {
        ret = null;   
    }
    return ret;
}

- (NSUInteger)count {
    return 2U;
}

- (NSUInteger)countByEnumeratingWithState:(NSFastEnumerationState *)state objects:(id *)stackbuf count:(NSUInteger)len {
    NSUInteger count = 0;
    if (state->state == 0) {
        state->mutationsPtr = &state->extra[0];
    }
    if (state->state < [self count]) {
        state->itemsPtr = stackbuf;
        while ((state->state < [self count]) && (count < len)) {
            stackbuf[count] = [self objectAtIndex:count];
            ++state->state;
            ++count;
        }
    } else {
        count = 0;
    }
    return count;
}

//! coretype.
- (uint)coreType {
    return CoreTypePair;
}

@end

@implementation NSTuple3

@synthesize v2;

- (NSTuple3*)initWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 {
    self = [super init];
    self.v0 = _v0;
    self.v1 = _v1;
    self.v2 = _v2;
    return self;
}

+ (NSTuple3*)tupleWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 {
    return [[[NSTuple3 alloc] initWith:_v0 v1:_v1 v2:_v2] autorelease];
}

- (void)dealloc {
    zero_release(v2);
    
    [super dealloc];
}

- (id)objectAtIndex:(uindex)idx {
    id ret = nil;
    switch (idx) {
        case 0: ret = first; break;
        case 1: ret = second; break;
        case 2: ret = v2; break;
    }
    return ret;
}

- (NSUInteger)count {
    return 3U;
}

@end

@implementation NSTuple4

@synthesize v3;

- (NSTuple4*)initWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 {
    self = [super init];
    self.v0 = _v0;
    self.v1 = _v1;
    self.v2 = _v2;
    self.v3 = _v3;
    return self;
}

+ (NSTuple4*)tupleWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 {
    return [[[NSTuple4 alloc] initWith:_v0 v1:_v1 v2:_v2 v3:_v3] autorelease];
}

- (void)dealloc {
    zero_release(v3);
    
    [super dealloc];
}

- (id)objectAtIndex:(uindex)idx {
    id ret = nil;
    switch (idx) {
        case 0: ret = first; break;
        case 1: ret = second; break;
        case 2: ret = v2; break;
        case 3: ret = v3; break;
    }
    return ret;
}

- (NSUInteger)count {
    return 4U;
}

@end

@implementation NSTuple5

@synthesize v4;

- (NSTuple5*)initWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 v4:(id)_v4 {
    self = [super init];
    self.v0 = _v0;
    self.v1 = _v1;
    self.v2 = _v2;
    self.v3 = _v3;
    self.v4 = _v4;
    return self;
}

+ (NSTuple5*)tupleWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 v4:(id)_v4 {
    return [[[NSTuple5 alloc] initWith:_v0 v1:_v1 v2:_v2 v3:_v3 v4:_v4] autorelease];
}

- (void)dealloc {
    zero_release(v4);
    
    [super dealloc];
}

- (id)objectAtIndex:(uindex)idx {
    id ret = nil;
    switch (idx) {
        case 0: ret = first; break;
        case 1: ret = second; break;
        case 2: ret = v2; break;
        case 3: ret = v3; break;
        case 4: ret = v4; break;
    }
    return ret;
}

- (NSUInteger)count {
    return 5U;
}

@end

@implementation NSTuple6

@synthesize v5;

- (NSTuple6*)initWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 v4:(id)_v4 v5:(id)_v5 {
    self = [super init];
    self.v0 = _v0;
    self.v1 = _v1;
    self.v2 = _v2;
    self.v3 = _v3;
    self.v4 = _v4;
    self.v5 = _v5;
    return self;
}

+ (NSTuple6*)tupleWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 v4:(id)_v4 v5:(id)_v5 {
    return [[[NSTuple6 alloc] initWith:_v0 v1:_v1 v2:_v2 v3:_v3 v4:_v4 v5:_v5] autorelease];
}

- (void)dealloc {
    zero_release(v5);
    
    [super dealloc];
}

- (id)objectAtIndex:(uindex)idx {
    id ret = nil;
    switch (idx) {
        case 0: ret = first; break;
        case 1: ret = second; break;
        case 2: ret = v2; break;
        case 3: ret = v3; break;
        case 4: ret = v4; break;
        case 5: ret = v5; break;
    }
    return ret;
}

- (NSUInteger)count {
    return 6U;
}

@end

@implementation NSTuple7

@synthesize v6;

- (NSTuple7*)initWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 v4:(id)_v4 v5:(id)_v5 v6:(id)_v6 {
    self = [super init];
    self.v0 = _v0;
    self.v1 = _v1;
    self.v2 = _v2;
    self.v3 = _v3;
    self.v4 = _v4;
    self.v5 = _v5;
    self.v6 = _v6;
    return self;
}

+ (NSTuple7*)tupleWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 v4:(id)_v4 v5:(id)_v5 v6:(id)_v6 {
    return [[[NSTuple7 alloc] initWith:_v0 v1:_v1 v2:_v2 v3:_v3 v4:_v4 v5:_v5 v6:_v6] autorelease];
}

- (void)dealloc {
    zero_release(v6);
    
    [super dealloc];
}

- (id)objectAtIndex:(uindex)idx {
    id ret = nil;
    switch (idx) {
        case 0: ret = first; break;
        case 1: ret = second; break;
        case 2: ret = v2; break;
        case 3: ret = v3; break;
        case 4: ret = v4; break;
        case 5: ret = v5; break;
        case 6: ret = v6; break;
    }
    return ret;
}

- (NSUInteger)count {
    return 7U;
}

@end

@implementation NSTuple8

@synthesize v7;

- (NSTuple8*)initWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 v4:(id)_v4 v5:(id)_v5 v6:(id)_v6 v7:(id)_v7 {
    self = [super init];
    self.v0 = _v0;
    self.v1 = _v1;
    self.v2 = _v2;
    self.v3 = _v3;
    self.v4 = _v4;
    self.v5 = _v5;
    self.v6 = _v6;
    self.v7 = _v7;
    return self;
}

+ (NSTuple8*)tupleWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 v4:(id)_v4 v5:(id)_v5 v6:(id)_v6 v7:(id)_v7 {
    return [[[NSTuple8 alloc] initWith:_v0 v1:_v1 v2:_v2 v3:_v3 v4:_v4 v5:_v5 v6:_v6 v7:_v7] autorelease];
}

- (void)dealloc {
    zero_release(v7);
    
    [super dealloc];
}

- (id)objectAtIndex:(uindex)idx {
    id ret = nil;
    switch (idx) {
        case 0: ret = first; break;
        case 1: ret = second; break;
        case 2: ret = v2; break;
        case 3: ret = v3; break;
        case 4: ret = v4; break;
        case 5: ret = v5; break;
        case 6: ret = v6; break;
        case 7: ret = v7; break;
    }
    return ret;
}

- (NSUInteger)count {
    return 8U;
}

@end

@implementation NSTuple9

@synthesize v8;

- (NSTuple9*)initWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 v4:(id)_v4 v5:(id)_v5 v6:(id)_v6 v7:(id)_v7 v8:(id)_v8 {
    self = [super init];
    self.v0 = _v0;
    self.v1 = _v1;
    self.v2 = _v2;
    self.v3 = _v3;
    self.v4 = _v4;
    self.v5 = _v5;
    self.v6 = _v6;
    self.v7 = _v7;
    self.v8 = _v8;
    return self;
}

+ (NSTuple9*)tupleWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 v4:(id)_v4 v5:(id)_v5 v6:(id)_v6 v7:(id)_v7 v8:(id)_v8 {
    return [[[NSTuple9 alloc] initWith:_v0 v1:_v1 v2:_v2 v3:_v3 v4:_v4 v5:_v5 v6:_v6 v7:_v7 v8:_v8] autorelease];
}

- (void)dealloc {
    zero_release(v8);
    
    [super dealloc];
}

- (id)objectAtIndex:(uindex)idx {
    id ret = nil;
    switch (idx) {
        case 0: ret = first; break;
        case 1: ret = second; break;
        case 2: ret = v2; break;
        case 3: ret = v3; break;
        case 4: ret = v4; break;
        case 5: ret = v5; break;
        case 6: ret = v6; break;
        case 7: ret = v7; break;
        case 8: ret = v8; break;
    }
    return ret;
}

- (NSUInteger)count {
    return 9U;
}

@end

NSObject *tuple(id v0, id v1, ...) {
    NSObject *ret = nil;
    
    va_list ap;
    va_start(ap, v1);
    NSMutableArray *store = [NSMutableArray new];
    id obj = va_arg(ap, id);
    while (obj) {
        [store addObject:obj];
        obj = va_arg(ap, id);
    }
    va_end(ap);
    
    const usize count = [store count] + 2U;
    
    switch (count) {
        case 2: ret = [NSPair pairWith:v0 second:v1]; break;
        case 3: ret = [NSTuple3 tupleWith:v0 v1:v1 v2:[store objectAtIndex:0]]; break;
        case 4: ret = [NSTuple4 tupleWith:v0 v1:v1 v2:[store objectAtIndex:0] v3:[store objectAtIndex:1]]; break;
        case 5: ret = [NSTuple5 tupleWith:v0 v1:v1 v2:[store objectAtIndex:0] v3:[store objectAtIndex:1] v4:[store objectAtIndex:2]]; break;
        case 6: ret = [NSTuple6 tupleWith:v0 v1:v1 v2:[store objectAtIndex:0] v3:[store objectAtIndex:1] v4:[store objectAtIndex:2] v5:[store objectAtIndex:3]]; break;
        case 7: ret = [NSTuple7 tupleWith:v0 v1:v1 v2:[store objectAtIndex:0] v3:[store objectAtIndex:1] v4:[store objectAtIndex:2] v5:[store objectAtIndex:3] v6:[store objectAtIndex:4]]; break;
        case 8: ret = [NSTuple8 tupleWith:v0 v1:v1 v2:[store objectAtIndex:0] v3:[store objectAtIndex:1] v4:[store objectAtIndex:2] v5:[store objectAtIndex:3] v6:[store objectAtIndex:4] v7:[store objectAtIndex:5]]; break;
        case 9: ret = [NSTuple9 tupleWith:v0 v1:v1 v2:[store objectAtIndex:0] v3:[store objectAtIndex:1] v4:[store objectAtIndex:2] v5:[store objectAtIndex:3] v6:[store objectAtIndex:4] v7:[store objectAtIndex:5] v8:[store objectAtIndex:6]]; break;
    }
    
    [store release];
    
    return ret;
}

NNT_END_OBJC

# endif