
# import "Core.h"
# import "Task+WSI.h"

WSI_USINGCXXNAMESPACE;

WSI_BEGIN_OBJC

@implementation WSICondition

- (id)init {
    self = [super init];
    
    _obj = new core::Condition;
    
    return self;
}

- (void)dealloc {
    safe_delete_type(_obj, core::Condition*);
    [super dealloc];
}

- (void)wait {
    use<core::Condition>(_obj)->wait();
}

- (void)signal {
    use<core::Condition>(_obj)->signal();
}

@end

WSI_END_OBJC
