
# import "Core.h"
# import "Network.h"
# import <sys/socket.h>
# import <netinet/in.h>
# import <netinet6/in6.h>
# import <arpa/inet.h>
# import <ifaddrs.h>
# import <netdb.h>
# import <SystemConfiguration/SystemConfiguration.h>

NNT_BEGIN_OBJC

@interface NNTNetworkStatusPrivate : NSObject {
    NNTNetworkStatus *d_owner;
}

@property (nonatomic, assign) NNTNetworkStatus *d_owner;

@end

@implementation NNTNetworkStatusPrivate

@synthesize d_owner;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    [super dealloc];
}

@end

@implementation NNTNetworkStatus

@synthesize available, availableWWAN, availableEn;
@synthesize address;

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(NNTNetworkStatus);
    return self;
}

- (void)dealloc {
    zero_release(address);
    NNTDECL_PRIVATE_DEALLOC();    
    [super dealloc];
}

+ (NNTNetworkStatus*)getInstance {
    static NNTNetworkStatus* instance = nil;
    @synchronized(self) {
        if (instance == nil) {
            instance = [NNTNetworkStatus new];
        }		
    }
    return instance;
}

- (BOOL)available {
    if (self.availableEn)
        return YES;
    if (self.availableWWAN)
        return YES;
    return NO;
}

- (BOOL)availableWWAN {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_len = sizeof(struct sockaddr_in);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(IN_LINKLOCALNETNUM);
    SCNetworkReachabilityRef ref = SCNetworkReachabilityCreateWithAddress(kCFAllocatorDefault, (struct sockaddr*)&addr);
    if (ref == nil)
        return NO;
    SCNetworkReachabilityFlags flags;
    if (!SCNetworkReachabilityGetFlags(ref, &flags))
        return NO;

# ifdef NNT_TARGET_IOS
    if (MASK_CHECK(kSCNetworkReachabilityFlagsIsWWAN, flags))
        return YES;
# endif
    
# ifdef NNT_TARGET_MAC
    if (MASK_CHECK(kSCNetworkReachabilityFlagsIsLocalAddress, flags))
        return YES;
# endif
    
    return NO;
}

- (BOOL)availableEn {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_len = sizeof(struct sockaddr_in);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(IN_LINKLOCALNETNUM);
    SCNetworkReachabilityRef ref = SCNetworkReachabilityCreateWithAddress(kCFAllocatorDefault, (struct sockaddr*)&addr);
    if (ref == nil)
        return NO;
    SCNetworkReachabilityFlags flags;
    if (!SCNetworkReachabilityGetFlags(ref, &flags))
        return NO;
    if (MASK_CHECK(kSCNetworkReachabilityFlagsReachable, flags))
        return YES;
    return NO;
}

- (NSString*)address {
    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd < 0) {
        return @"";
    }
    struct sockaddr_in ss;
    memset(&ss, 0, sizeof(ss));
    ss.sin_len = sizeof(ss);
    ss.sin_family = AF_INET;
    ss.sin_addr.s_addr = htonl(INADDR_ANY);
    socklen_t len = sizeof(ss);
    if (bind(fd, (struct sockaddr const*)&ss, len) < 0) {
        close(fd);
        return @"";
    }
    if (getsockname(fd, (struct sockaddr*)&ss, &len) < 0) {
        close(fd);
        return @"";
    }
    char *str = inet_ntoa(ss.sin_addr);
    NSString *ret = [NSString stringWithUTF8String:str];
    close(fd);
    return ret;
}

@end

NNT_END_OBJC