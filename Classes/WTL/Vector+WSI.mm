
# include "Core.h"
# include "Vector+NNT.h"

NNT_BEGIN_OBJC

@implementation NSVector

@synthesize container = _vector;

- (id)init {
    self = [super init];
    
    _vector = new _NSVector();
    
    return self;
}

- (void)dealloc {
    safe_delete(_vector);
    
    [super dealloc];
}

- (void)setContainer:(_NSVector *)vec {
    safe_delete(_vector);
    _vector = vec;
}

- (NSVectorIterator)begin {
    return _vector->begin();
}

- (NSVectorIterator)end {
    return _vector->end();
}

@end

NNT_END_OBJC