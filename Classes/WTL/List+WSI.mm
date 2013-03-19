
# include "Core.h"
# include "List+WSI.h"

WSI_BEGIN_OBJC

@implementation NSList

@synthesize container = _list;

- (id)init {
    self = [super init];
    
    _list = new _NSList();
    
    return self;
}

- (void)dealloc {
    safe_delete(_list);
    [super dealloc];
}

- (void)setContainer:(_NSList *)list {
    safe_delete(_list);
    _list = list;
}

- (NSListIterator)begin {
    return _list->begin();
}

- (NSListIterator)end {
    return _list->end();
}

@end

WSI_END_OBJC