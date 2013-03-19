
# import "Core.h"
# import "TinyScheme+NNT.h"
# import "scheme.h"
# import "tinyscheme.prv.h"

NNT_BEGIN_OBJC

@interface NNTTinySchemePrivate : NNTObject {
    scheme* env;
}

@property (nonatomic, assign) NNTTinyScheme* d_owner;
@property (nonatomic, readonly) scheme* env;

- (void)close;

@end

@implementation NNTTinySchemePrivate

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

@implementation NNTTinyScheme

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(NNTTinyScheme);
    return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC();
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

NNT_END_OBJC