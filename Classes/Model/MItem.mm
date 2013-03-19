
# import "Core.h"
# import "MItem.h"

NNT_BEGIN_OBJC

@implementation MItem

@synthesize children = _children;

- (id)init {
    self = [super init];
    
    _children = [[NSMutableArray alloc] init];
    
    return self;
}

- (void)dealloc {
    zero_release(_children);
    
    [super dealloc];
}

- (void)insertItem:(MItem*)item atIndex:(NSUInteger)index {
    [_children insertObject:item atIndex:index];
}

- (void)addItem:(MItem*)item {
    [_children addObject:item];
}

- (NSUInteger)count {
    return [_children count];
}

- (NSUInteger)sum {
    NSUInteger ret = [_children count];
    for (MItem* each in _children) {
        ret += [each sum];
    }
    return ret;
}

- (void)clear {
    [_children removeAllObjects];
}

- (MItem*)itemAt:(NSUInteger)idx {
    return [_children objectAtIndex:idx];
}

@end

NNT_END_OBJC
