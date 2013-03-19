
# import "Core.h"
# import "V8+NNT.h"
# import "../../contrib/v8/include/v8.h"

NNT_BEGIN_OBJC

NNTDECL_PRIVATE_BEGIN(V8js, NNTObject)

NNTDECL_PRIVATE_IMPL(V8js)

NNTDECL_PRIVATE_END

@implementation V8js

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(V8js);
    
    return self;
}

- (void)dealloc {
    
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (id)executeString:(NSString *)expr {
    /*
    using namespace v8;
    
    Handle<String> str = String::New(expr.UTF8String);
    Handle<Script> scp = Script::Compile(str);
    Handle<Value> res = scp->Run();
    
     */
    
    return nil;
}

@end

NNT_END_OBJC
