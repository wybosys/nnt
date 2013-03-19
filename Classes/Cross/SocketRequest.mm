
# import "Core.h"
# import "SocketRequest.h"

NNT_BEGIN_OBJC

@interface SocketRequestPrivate : NSObject {
    
    SocketRequest *d_owner;
    
}

@property (nonatomic, assign) SocketRequest *d_owner;

@end

@implementation SocketRequestPrivate

@synthesize d_owner;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    [super dealloc];
}

@end

@implementation SocketRequest

- (id)init {
    self = [super init];    
    NNTDECL_PRIVATE_INIT(SocketRequest);
    return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (NSObject*)call:(Model *)model withUrl:(NSURL*)url {
    [super call:model withUrl:url];
    
    NNTMACRO_LOCKOBJ(self);

    return nil;
}

- (BOOL)connect:(NSURL *)__url {
    return YES;
}

- (BOOL)is_connected {
    return YES;
}

- (void)disconnect {
    PASS;
}

@end

NNT_END_OBJC