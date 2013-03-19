
# import "Core.h"
# import "V8+WSI.h"
# import "../../contrib/v8/include/v8.h"

WSI_BEGIN_OBJC

WSIDECL_PRIVATE_BEGIN(V8js, WSIObject)

WSIDECL_PRIVATE_IMPL(V8js)

WSIDECL_PRIVATE_END

@implementation V8js

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(V8js);
    
    return self;
}

- (void)dealloc {
    
    WSIDECL_PRIVATE_DEALLOC();
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

WSI_END_OBJC
