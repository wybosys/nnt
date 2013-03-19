
# import "Core.h"
# import "User.h"
# import "WSIConfiguration.h"

WSI_BEGIN_OBJC

signal_t kSignalUserLogin = @"::wsi::context::user::login";
signal_t kSignalUserLogout = @"::wsi::context::user::logout";
signal_t kSignalUserLoginStatusChanged = @"::wsi::context::user::login::changed";

@interface User ()

@property (nonatomic, copy) NSString *identity;
@property (nonatomic) BOOL logined;
@property (nonatomic, retain) WSIConfiguration* configuration;

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

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalUserLogin)
WSIEVENT_SIGNAL(kSignalUserLogout)
WSIEVENT_SIGNAL(kSignalUserLoginStatusChanged);
WSIEVENT_END

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

+ (WSIConfiguration*)configurationOfIdentity:(NSString*)identity {
    return [WSIConfiguration configuration:[User configurationNameOfIdentity:identity]];
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

WSI_END_OBJC