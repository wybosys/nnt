
# import "Core.h"
# import "OAWeChat.h"
# import <Tencent/WeChat/WXApi.h>
# import <Tencent/WeChat/WXApiObject.h>
# import "App.h"
# import "OADefines.h"

WSI_BEGIN_OBJC

WSIDECL_PRIVATE_BEGIN(WeChat, WSIObject)
<WXApiDelegate>

WSIDECL_PRIVATE_IMPL(WeChat)

- (id)init {
    self = [super init];            
    return self;
}

- (void)dealloc {
    [[WSIApplication shared] disconnect:self];
    [super dealloc];
}

- (void)setAppid:(NSString*)appid {
    if ([WXApi registerApp:appid] == NO) {
        trace_msg(@"failed register wechat");
        return;
    }

    [[WSIApplication shared] connect:kSignalAppOpenUrl sel:@selector(act_openurl:) obj:self];
}

- (void)setCallback:(NSString*)callback {
    SendAuthReq* auth = [[SendAuthReq alloc] init];
    auth.scope = @"post_timeline";
    auth.state = callback;
    [WXApi sendReq:auth];
    safe_release(auth);
}

- (void)act_openurl:(WSIEventObj*)evt {
    OpenURLObject* ouo = evt.result;
    [WXApi handleOpenURL:ouo.url delegate:self];
}

- (void)onReq:(BaseReq*)req {
    
}

- (void)onResp:(BaseResp*)resp {
    if ([resp isKindOfClass:[SendMessageToWXResp class]]) {
        SendMessageToWXResp* obj = (SendMessageToWXResp*)resp;
        trace_msg(obj.errStr);
    }
}

- (void)execute_post:(WeChatPost*)post {    
    SendMessageToWXReq* req = [[SendMessageToWXReq alloc] init];
    req.text = post.content;
    req.bText = YES;
    req.scene = WXSceneSession;
    [WXApi sendReq:req];
    safe_release(req);
}

WSIDECL_PRIVATE_END

@implementation WeChat

@synthesize appid = _appid, callback = _callback;

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(WeChat);
    
    self.appid = OA_WECHAT_PARTENER;
    
    return self;
}

- (void)dealloc {
    safe_release(_appid);
    safe_release(_callback);
    
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)setAppid:(NSString *)appid {
    if ([_appid isEqualToString:appid])
        return;
    
    [WSIObject refobjCopy:&_appid ref:appid];
    
    [d_ptr setAppid:appid];
}

- (void)setCallback:(NSString *)callback {
    if ([_callback isEqualToString:callback])
        return;
    
    [WSIObject refobjCopy:&_callback ref:callback];
    
    [d_ptr setCallback:callback];
}

- (void)execute:(id)obj {
    if ([obj isKindOfClass:[WeChatPost class]])
        [d_ptr execute_post:obj];
}

@end

@implementation WeChatPost

@synthesize content = _content;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    safe_release(_content);
    [super dealloc];
}

@end

WSI_END_OBJC

WSI_BEGIN_CXX
WSI_BEGIN_NS(tencent)
WSI_BEGIN_NS(wechat)

Provider::Provider()
{
    
}

Provider::~Provider()
{
    
}

WSI_END_NS
WSI_END_NS
WSI_END_CXX
