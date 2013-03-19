
# import "Core.h"
# import "User.h"
# import "NNTConfiguration.h"

NNT_BEGIN_OBJC

signal_t kSignalUserLogin = @"::nnt::context::user::login";
signal_t kSignalUserLogout = @"::nnt::context::user::logout";
signal_t kSignalUserLoginStatusChanged = @"::nnt::context::user::login::changed";

@interface User ()

@property (nonatomic, copy) NSString *identity;
@property (nonatomic) BOOL logined;
@property (nonatomic, retain) NNTConfiguration* configuration;

@end

@implementation User 

@synthesize nickname = _nickname, passwd = _passwd;
@synthesize identity = _identity, token = _token;
@synthesize logined = _logined;
@synthesize ctx = _ctx;
@synthesize configuration = _configuration;

- (id)init {
    self = [super init];
    
    self.nickname = @"";
    self.identity = @"";
    self.passwd = @"";
    self.token = @"";
    self.configuration = nil;
    
    return self;
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalUserLogin)
NNTEVENT_SIGNAL(kSignalUserLogout)
NNTEVENT_SIGNAL(kSignalUserLoginStatusChanged);
NNTEVENT_END

- (void)dealloc {
    
    zero_release(_nickname);
    zero_release(_passwd);
    zero_release(_identity);
    zero_release(_token);
    zero_release(_configuration);
    
    [super dealloc];
}

- (void)login:(NSString *)__identity {
    if (self.logined) {
        [self logout];
    }
    
    if (__identity == nil)
        return;
       
    self.identity = __identity;
    self.configuration = [User configurationOfIdentity:self.identity];
    self.logined = YES;
}

+ (NNTConfiguration*)configurationOfIdentity:(NSString*)identity {
    return [NNTConfiguration configuration:[User configurationNameOfIdentity:identity]];
}

+ (NSString*)configurationNameOfIdentity:(NSString*)identity {
    return [NSString stringWithFormat:@".wsi.%@", identity];
}

- (void)logout {
    if (NO == self.logined)
        return;
    
    self.nickname = @"";
    self.identity = @"";
    self.passwd = @"";
    self.token = @"";
    self.configuration = nil;
    self.logined = NO;
}

- (void)setLogined:(BOOL)logined {
    if (logined == _logined)
        return;
        
    _logined = logined;
    
    if (_logined)
        [self emit:kSignalUserLogin];
    else
        [self emit:kSignalUserLogout];
    
    [self emit:kSignalUserLoginStatusChanged];
}

@end

NNT_END_OBJC