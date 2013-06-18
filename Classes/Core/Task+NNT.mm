
# import "Core.h"
# import "Task+NNT.h"

NNT_USINGCXXNAMESPACE;

NNT_BEGIN_OBJC

@implementation NNTCondition

- (id)init {
    self = [super init];
    
    _obj = new core::Condition;
    
    return self;
}

- (void)dealloc {
    safe_delete<core::Condition>(_obj);

    [super dealloc];
}

- (void)wait {
    use<core::Condition>(_obj)->wait();
}

- (void)signal {
    use<core::Condition>(_obj)->signal();
}

@end

NNT_END_OBJC
