
# import "Core.h"
# import "WSITinyScheme.h"
# import "scheme.h"
# import "tinyscheme.prv.h"

WSI_BEGIN_OBJC

@interface WSITinySchemePrivate : WSIObject {
    scheme* env;
}

@property (nonatomic, assign) WSITinyScheme* d_owner;
@property (nonatomic, readonly) scheme* env;

- (void)close;

@end

@implementation WSITinySchemePrivate

@synthesize d_owner;
@synthesize env;

- (id)init {
    self = [super init];
    
    env = scheme_init_new();
    if (env) {
        scheme_load_string(env, tinyscheme_init_scm);
    }
    
    return self;
}

- (void)dealloc {
    [self close];
    [super dealloc];
}

- (void)close {
    if (env) {
        scheme_deinit(env);
        env = nil;
    }
}

@end

@implementation WSITinyScheme

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(WSITinyScheme);
    return self;
}

- (void)dealloc {
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (BOOL)executeUTF8String:(const char *)expr {
    scheme_load_string(d_ptr.env, expr);
    return TRUE;
}

# pragma mark impl.

- (BOOL)executeString:(NSString *)str {
    return [self executeUTF8String:[str UTF8String]];
}

- (NSString*)errorMessage {
    return @"";
}

@end

WSI_END_OBJC