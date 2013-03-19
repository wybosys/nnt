
# import "Foundation+NNT.h"
# import "MainController.h"

# import "Context.h"
# import "Server.h"

# import "OAOpenID.h"
# import "OASINA.h"
# import "OATencent.h"
# import "OARenren.h"
# import "OANetease.h"
# import "OAKaixin.h"
# import "OARenren.h"
# import "OASohu.h"
# import "OATencentOS.h"
# import "OADouban.h"

NNTAPP_BEGIN_OBJC

static OASina *sina = nil;
static OATencent *tencent = nil;
static OANetease *net = nil;
static WSIUITextView *text = nil;
static OAKaixin *kaixin = nil;
static OARenRen *renren = nil;
static OASohu *sohu = nil;
static OATencentOS* tencentos = nil;
static OADouban *douban = nil;

@implementation MainView

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    using namespace wsi;
    
    self.backgroundColor = [UIColor whiteColor];
    
    CGRectLayoutVBox lyt(frame);
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1
    << (pixel)50
    << (pixel)50
    << (pixel)50
    << (pixel)50
    << (pixel)50
    << (pixel)50
    << (pixel)50
    << (pixel)50
    << (flex)1;
        
    lyt << lnr;
    CGRectLayoutHBox lyt_sina(lyt << lnr);
    CGRectLayoutLinear lnr_sina(lyt_sina);
    lnr_sina << (flex)1 << (flex)1 << (flex)1 << (flex)1;
    
    CGRectLayoutHBox lyt_tencent(lyt << lnr);
    CGRectLayoutHBox lyt_tencentos(lyt << lnr);
    CGRectLayoutHBox lyt_rr(lyt << lnr);
    CGRectLayoutHBox lyt_netease(lyt << lnr);
    CGRectLayoutHBox lyt_kaixin(lyt << lnr);
    CGRectLayoutHBox lyt_souhu(lyt << lnr);
    CGRectLayoutHBox lyt_douban(lyt << lnr);
    
    UIBevelButton *btn = nil;
    
    // sina
    btn = [UIBevelButton button];
    [btn setTitle:@"Login SINA" forState:UIControlStateNormal];    
    btn.frame = lyt_sina << lnr_sina;
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_login_sina) obj:self];
    
    btn = [UIBevelButton button];
    [btn setTitle:@"Get Sina User Info" forState:UIControlStateNormal];    
    btn.frame = lyt_sina << lnr_sina;
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_userinfo_sina) obj:self];
    
    btn = [UIBevelButton button];
    [btn setTitle:@"sina weibo post" forState:UIControlStateNormal];
    btn.frame = lyt_sina << lnr_sina;
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_weibo_post_sina) obj:self];
    
    btn = [UIBevelButton button];
    [btn setTitle:@"sina weibo upload" forState:UIControlStateNormal];
    btn.frame = lyt_sina << lnr_sina;
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_weibo_upload_sina) obj:self];
    
    // tencent
    btn = [UIBevelButton button];
    [btn setTitle:@"login tencent" forState:UIControlStateNormal];
    btn.frame = lyt_tencent.add_fpercent(.2);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_login_tencent) obj:self];
    
    btn = [UIBevelButton button];
    [btn setTitle:@"get Tencent User Info" forState:UIControlStateNormal];
    btn.frame = lyt_tencent.add_fpercent(.2);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_userinfo_tencent) obj:self];
    
    btn = [UIBevelButton button];
    [btn setTitle:@"weibo post" forState:UIControlStateNormal];
    btn.frame = lyt_tencent.add_fpercent(.2);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_weibo_post_tencent) obj:self];
    
    btn = [UIBevelButton button];
    [btn setTitle:@"weibo show" forState:UIControlStateNormal];
    btn.frame = lyt_tencent.add_fpercent(.2);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_weibo_show_tencent) obj:self];
    
    text = [[WSIUITextView alloc] initWithZero];
    text.frame = lyt.fill();
    [self addSubview:text];
    [text release];
    
    // tencent openspace
    btn = [UIBevelButton button];
    [btn setTitle:@"login tencent openspace" forState:UIControlStateNormal];
    btn.frame = lyt_tencentos.add_fpercent(.33);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_login_tencentos) obj:self];
    
    btn = [UIBevelButton button];
    [btn setTitle:@"get Tencent User Info" forState:UIControlStateNormal];
    btn.frame = lyt_tencentos.add_fpercent(.33);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_userinfo_tencentos) obj:self];
    
    btn = [UIBevelButton button];
    [btn setTitle:@"os share" forState:UIControlStateNormal];
    btn.frame = lyt_tencentos.add_fpercent(.33);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_post_tencentos) obj:self];
    
    // renren
    btn = [UIBevelButton button];
    [btn setTitle:@"login renren" forState:UIControlStateNormal];
    btn.frame = lyt_rr.add_percent(.3);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_login_renren) obj:self];
    
    btn = [UIBevelButton button];
    [btn setTitle:@"get RenRen User Info" forState:UIControlStateNormal];
    btn.frame = lyt_rr.add_fpercent(.3);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_userinfo_renren) obj:self];
    
    btn = [UIBevelButton button];
    [btn setTitle:@"renren post" forState:UIControlStateNormal];
    btn.frame = lyt_rr.add_fpercent(.3);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_post_renren) obj:self];
    
    text = [[WSIUITextView alloc] initWithZero];
    text.frame = lyt.fill();
    [self addSubview:text];
    [text release];
    
    //netease
    btn = [UIBevelButton button];
    [btn setTitle:@"lgoin net" forState:UIControlStateNormal];
    btn.frame = lyt_netease.add_percent(.3);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_lgoin_net) obj:self];
    
    btn = [UIBevelButton button];
    [btn setTitle:@"get_info" forState:UIControlStateNormal];
    btn.frame = lyt_netease.add_fpercent(.3);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_userinfo_net) obj:self];
    
    btn = [UIBevelButton button];
    [btn setTitle:@"net post" forState:UIControlStateNormal];
    btn.frame = lyt_netease.add_fpercent(.2);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_weibo_post_net) obj:self];
    
    //kaixin
    btn = [UIBevelButton button];
    [btn setTitle:@"lg kaixin" forState:UIControlStateNormal];
    btn.frame = lyt_kaixin.add_fpercent(.3);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_lgoin_kaixin) obj:self];
    
    btn = [UIBevelButton button];
    [btn setTitle:@"get_info" forState:UIControlStateNormal];
    btn.frame = lyt_kaixin.add_fpercent(.3);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_userinfo_kaixin) obj:self];
    
    btn = [UIBevelButton button];
    [btn setTitle:@"post" forState:UIControlStateNormal];
    btn.frame = lyt_kaixin.add_fpercent(.3);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_post_kaixin) obj:self];
    
    
    text = [[WSIUITextView alloc] initWithZero];
    text.frame = lyt.fill();
    [self addSubview:text];
    [text release];
    
    //souhu
    btn = [UIBevelButton button];
    [btn setTitle:@"lgoin souhu" forState:UIControlStateNormal];
    btn.frame = lyt_souhu.add_percent(.3);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_lgoin_sohu) obj:self];
    
    btn = [UIBevelButton button];
    [btn setTitle:@"get_info" forState:UIControlStateNormal];
    btn.frame = lyt_souhu.add_fpercent(.3);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_userinfo_sohu) obj:self];
    
    btn = [UIBevelButton button];
    [btn setTitle:@"souhu post" forState:UIControlStateNormal];
    btn.frame = lyt_souhu.add_fpercent(.2);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_post_sohu) obj:self]; 
    
    //douban
    btn = [UIBevelButton button];
    [btn setTitle:@"lgoin douban" forState:UIControlStateNormal];
    btn.frame = lyt_douban.add_percent(.3);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_lgoin_douban) obj:self];
    
    btn = [UIBevelButton button];
    [btn setTitle:@"get_info" forState:UIControlStateNormal];
    btn.frame = lyt_douban.add_fpercent(.3);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_userinfo_douban) obj:self];
    
    btn = [UIBevelButton button];
    [btn setTitle:@"douban post" forState:UIControlStateNormal];
    btn.frame = lyt_douban.add_fpercent(.2);
    [self addSubview:btn];
    [btn connect:kSignalButtonClicked sel:@selector(act_post_douban) obj:self];   
    
    return self;
}

//sina
- (void)act_login_sina {
    sina = [[OASina alloc] init];
    [sina retrieve];
}

- (void)act_userinfo_sina {
    OApiSinaUserinfo* api = [[OApiSinaUserinfo alloc] initWithOAuth:sina];
    api.apiType = OAuthApiTypeJSON;
    [SERV() retrieve_model:api];
    
    wsi::ns::Dictionary dict(api.result);
    
    NSString* str = [NSString stringWithFormat:@"NICKNAME: %@\n", dict[@"screen_name"]];
    str = [str stringByAppendingFormat:@"NAME: %@\n", dict[@"name"]];
    str = [str stringByAppendingFormat:@"LOC: %@\n", dict[@"location"]];
    str = [str stringByAppendingFormat:@"DESC: %@\n", dict[@"description"]];
    
    text.text = str;
    [api release];
}

- (void)act_weibo_post_sina {
    OApiSinaWeiboPost *api = [[OApiSinaWeiboPost alloc] initWithOAuth:sina];
    api.apiType = OAuthApiTypeJSON;
    api.content = @"test post message";
    [SERV() retrieve_model:api];
    [api release];
}

- (void)act_weibo_upload_sina {
    OApiSinaWeiboUpload* api = [[OApiSinaWeiboUpload alloc] initWithOAuth:sina];
    api.apiType = OAuthApiTypeJSON;
    api.content = @"test upload image";
    api.image = [WCGImage imageWithNamed:@"logo@57.png"];
    [SERV() retrieve_model:api];
    [api release];
}

//tencent
- (void)act_login_tencent {
    
    tencent = [[OATencent alloc] init];
    //tencent.callback = @"oauth://wsi.test.openapi";
    [tencent retrieve];
}

- (void)act_userinfo_tencent {
    
    OApiTencentUserInfo *api = [[OApiTencentUserInfo alloc] initWithOAuth:tencent];
    api.apiType = OAuthApiTypeJSON;
    [SERV() retrieve_model:api];
    
    wsi::ns::Dictionary dict(api.result);
    
    [api release];
}

- (void)act_weibo_post_tencent {
    
    //    tencent = [[OATencent alloc] init];
    OApiTencentWeiboPost *api = [[OApiTencentWeiboPost alloc] initWithOAuth:tencent];
    api.apiType = OAuthApiTypeJSON;
    api.content = @"test";
    api.clientip = @"127.0.0.1";
    
    //    api.jing = @"121.525673";
    //    api.wei = @"31.217716";
    //    
    [SERV() retrieve_model:api];
    
    wsi::ns::Dictionary dict(api.result);
    [api release];
}

- (void)act_weibo_show_tencent {
    
    //    tencent = [[OATencent alloc] init];
    OApiTencentWeiboShow *api = [[OApiTencentWeiboShow alloc] initWithOAuth:tencent];
    api.apiType = OAuthApiTypeJSON;
    api.id = @"41177002056870";
    [SERV() retrieve_model:api];
    wsi::ns::Dictionary dict(api.result);
    [api release];
}

//tencent os
- (void)act_login_tencentos {    
    tencentos = [[OATencentOS alloc] init];
    [tencentos retrieve];
}

- (void)act_userinfo_tencentos {
    OApiQQOSUserInfo *api = [[OApiQQOSUserInfo alloc] initWithOAuth:tencentos];
    [SERV() retrieve_model:api];
    [api release];
}

- (void)act_post_tencentos {
    OApiQQOSAddShare* api = [[OApiQQOSAddShare alloc] initWithOAuth:tencentos];
    api.title = @"test";
    api.reference = @"http://www.wybosys.com/";
    api.content = @"test";
    [SERV() retrieve_model:api];
    [api release];
}

//renren
- (void)act_login_renren {
    
    renren = [[OARenRen alloc] init];
    [renren retrieve];
}

- (void)act_userinfo_renren {
    
    OApiRenRenUserInfo *api = [[OApiRenRenUserInfo alloc] initWithOAuth:renren];
    api.apiType = OAuthApiTypeJSON;
    [SERV() retrieve_model:api];
    [api release];
}

- (void)act_post_renren {
    OApiRenRenWeiboPost *api = [[OApiRenRenWeiboPost alloc] initWithOAuth:renren];
    api.apiType = OAuthApiTypeJSON;
    api.title = @"test";
    api.content = @"这是一条测试数据1121 <a target='_blank' href='http://www.163.com'>netease</a>";
    [SERV() retrieve_model:api];
    [api release];
}

//
- (void)act_lgoin_net {
    net = [[OANetease alloc] init];
    [net retrieve];
}

- (void)act_userinfo_net {
    OApiNetUserInfo *api = [[OApiNetUserInfo alloc] initWithOAuth:net];
    api.apiType = OAuthApiTypeJSON;
    [SERV() retrieve_model:api];
    wsi::ns::Dictionary dict(api.result);
}

- (void)act_weibo_post_net {
    OApiNeteaseWeiboPost *post = [[OApiNeteaseWeiboPost alloc] initWithOAuth:net];
    post.apiType = OAuthApiTypeJSON;
    post.content = @"这是一条测试数据 《《 .... 》>";
    [SERV() retrieve_model_async:post selector:@selector(done) object:self];
    [post release];
}

- (void)done {
    trace_msg(@"-----OK------");
}

//souhu
- (void)act_lgoin_sohu {
    trace_msg(@"login---souhu");
    sohu = [[OASohu alloc] init];
    [sohu retrieve];
}

- (void)act_userinfo_sohu {
    //
    //    sohu = [[OASohu alloc] init];
    OApiSohuUserInfo *api = [[OApiSohuUserInfo alloc] initWithOAuth:sohu];
    api.apiType = OAuthApiTypeJSON;
    [SERV() retrieve_model:api];
    [api release];
}

- (void)act_post_sohu {
    //    
    //    sohu = [[OASohu alloc] init];
    OApiSohuPost *api = [[OApiSohuPost alloc] initWithOAuth:sohu];
    api.apiType = OAuthApiTypeJSON;
    api.content = @"test1";
    [SERV() retrieve_model:api];
    [api release];
}

//kaixin
- (void)act_lgoin_kaixin {    
    kaixin = [[OAKaixin alloc] init];
    [kaixin retrieve]; 
}

- (void)act_userinfo_kaixin {    
    OApiKaixinUserInfo *api = [[OApiKaixinUserInfo alloc] initWithOAuth:kaixin];
    api.apiType = OAuthApiTypeJSON;
    [SERV() retrieve_model:api];
    wsi::ns::Dictionary dict(api.result);    
}

- (void)act_post_kaixin {
    OApiKaixinDiaryPost *post = [[OApiKaixinDiaryPost alloc] initWithOAuth:kaixin];
    post.apiType = OAuthApiTypeJSON;
    post.content = @"ssss";
    post.title = @"ss";
    [SERV() retrieve_model_async:post selector:@selector(doneKaixin) object:self];
    [post release];
}

- (void)doneKaixin {
    
}

//douban
- (void)act_lgoin_douban {
    douban = [[OADouban alloc] init];
    [douban retrieve];
}

- (void)act_userinfo_douban {    
    OApiDoubanUserInfo *api = [[OApiDoubanUserInfo alloc] initWithOAuth:douban];
    [SERV() retrieve_model:api];
}

- (void)act_post_douban {
    OApiDoubanDiaryPost *post = [[OApiDoubanDiaryPost alloc] initWithOAuth:douban];
    post.content = @"THIS IS TEST 这是测试";
    post.title = @"TEST 测试";
    [SERV() retrieve_model_async:post selector:@selector(doneDouban) object:self];
    [post release];
}

- (void)doneDouban {
}

@end

@implementation MainController

- (void)loadView {
    MainView* view = [[MainView alloc] initWithFrame:CGRectMake(0, 0, 768, 1024)];
    self.view = view;
    [view release];
}

@end

NNTAPP_END_OBJC