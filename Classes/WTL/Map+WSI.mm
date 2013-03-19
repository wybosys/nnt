
# include "Core.h"
# include "Map+NNT.h"

NNT_BEGIN_OBJC

@implementation NSMap

@synthesize container = _map;

- (id)init {
    self = [super init];
    
    _map = new _NSMap();
    
    return self;
}

- (void)dealloc {
    safe_delete(_map);
    [super dealloc];
}

- (void)setContainer:(_NSMap *)map {
    safe_delete(_map);
    _map = map;
}

- (NSMapIterator)begin {
    return _map->begin();
}

- (NSMapIterator)end {
    return _map->end();
}

@end

@implementation NSMultiMap

@synthesize container = _map;

- (id)init {
    self = [super init];
    
    _map = new _NSMultiMap();
    
    return self;
}

- (void)dealloc {
    safe_delete(_map);
    [super dealloc];
}

- (void)setContainer:(_NSMultiMap *)map {
    safe_delete(_map);
    _map = map;
}

- (NSMultiMapIterator)begin {
    return _map->begin();
}

- (NSMultiMapIterator)end {
    return _map->end();
}

@end

NNT_END_OBJC