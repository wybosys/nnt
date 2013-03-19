
# import "Core.h"
# import "OALogin.h"
# import "OAuth.h"
# import "Context.h"
# import "Server.h"

NNT_BEGIN_OBJC

signal_t kSignalSuccess = @"::wsi::success";
signal_t kSignalFailed = @"::wsi::failed";

@implementation OALoginParameter

@synthesize clsAuth, clsUser;

@end

@implementation OALogin

+ (void)Login:(OALoginParameter*)param sel:(SEL)sel obj:(id)obj {
    NSObject<OAuth>* oauth = (NSObject<OAuth>*)[[param.clsAuth alloc] init];
    [oauth retrieve];
    
    //[oauth connect:kSignalAuthorizeSuccess func:__oalogin_authorize_suc];
    
    [oauth storeSet:@"::wsi::oauth::parameter" obj:param];
    [oauth storeSet:@"::wsi::oauth::action" obj:[NSObjectSel objectWithSel:sel]];
    [oauth storeSet:@"::wsi::oauth::target" obj:obj];
    
    [oauth release];
}

@end

NNT_END_OBJC