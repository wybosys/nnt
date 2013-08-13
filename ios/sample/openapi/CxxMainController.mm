
# include "Foundation+NNT.h"
# include "CxxMainController.h"
# include "Configuration+NNT.h"
# include "UIActionSheet+NNT.h"

NNTAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::White());
        
    btn_auth.set_text(@"AUTH");
    btn_info.set_text(@"INFO");
    btn_post.set_text(@"POST");
    btn_postimg.set_text(@"POST IMAGE");
    
    txt_post.set_text(@"test from wsi " + ns::uuid_string());
    
    add_sub(btn_auth);
    add_sub(btn_info);
    add_sub(btn_post);
    add_sub(txt_post);
    add_sub(btn_postimg);
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    
    lnr << (pixel)50;
    lnr << (pixel)50;
    lnr << (pixel)50;
    lnr << (pixel)50;
    lnr << (pixel)50;
    lnr << (flex)1;
    
    btn_auth.set_frame(lyt << lnr);
    btn_info.set_frame(lyt << lnr);
    txt_post.set_frame(lyt << lnr);
    btn_post.set_frame(lyt << lnr);
    btn_postimg.set_frame(lyt << lnr);
}

MainController::MainController()
{
    set_orientation(UIOrientationEnableAll);
    
    _wechat.set_callback(@"oauth://wsi.test.openapi");
}

void MainController::view_loaded()
{
    view().btn_auth.connect(kSignalButtonClicked, _action(_class::act_auth), this);
    view().btn_info.connect(kSignalButtonClicked, _action(_class::act_info), this);
    view().btn_post.connect(kSignalButtonClicked, _action(_class::act_post), this);
    view().btn_postimg.connect(kSignalButtonClicked, _action(_class::act_postimg), this);
    
    _sina.connect(kSignalAuthorizeSuccess, _action(_class::act_authsuc_sina), this);
    _netease.connect(kSignalAuthorizeSuccess, _action(_class::act_authsuc_netease), this);
    _tencent.connect(kSignalAuthorizeSuccess, _action(_class::act_authsuc_tencent), this);
    _taobao.connect(kSignalAuthorizeSuccess, _action(_class::act_authsuc_taobao), this);
    _alipay.connect(kSignalAuthorizeSuccess, _action(_class::act_authsuc_alipay), this);
    _kaixin.connect(kSignalAuthorizeSuccess, _action(_class::act_authsuc_kaixin), this);
    _renren.connect(kSignalAuthorizeSuccess, _action(_class::act_authsuc_renren), this);
}

void MainController::act_auth()
{
    ui::ActionSheet acts;
    
    acts.add(@"SINA").connect(kSignalButtonClicked, _action(_class::act_auth_sina), this);
    acts.add(@"NETEASE").connect(kSignalButtonClicked, _action(_class::act_auth_netease), this);
    acts.add(@"TENCENT").connect(kSignalButtonClicked, _action(_class::act_auth_tencent), this);
    acts.add(@"TAOBAO").connect(kSignalButtonClicked, _action(_class::act_auth_taobao), this);
    acts.add(@"ALIPAY").connect(kSignalButtonClicked, _action(_class::act_auth_alipay), this);
    acts.add(@"KAIXIN").connect(kSignalButtonClicked, _action(_class::act_auth_kaixin), this);
    acts.add(@"RENREN").connect(kSignalButtonClicked, _action(_class::act_auth_renren), this);
    
    acts.cancel(@"CANCEL");
    acts.show(view());
}

void MainController::act_info()
{
    ui::ActionSheet acts;
    
    acts.add(@"SINA").connect(kSignalButtonClicked, _action(_class::act_info_sina), this);
    acts.add(@"NETEASE").connect(kSignalButtonClicked, _action(_class::act_info_netease), this);
    acts.add(@"TENCENT").connect(kSignalButtonClicked, _action(_class::act_info_tencent), this);
    acts.add(@"TAOBAO").connect(kSignalButtonClicked, _action(_class::act_info_taobao), this);
    acts.add(@"ALIPAY").connect(kSignalButtonClicked, _action(_class::act_info_alipay), this);
    acts.add(@"KAIXIN").connect(kSignalButtonClicked, _action(_class::act_info_kaixin), this);
    acts.add(@"RENREN").connect(kSignalButtonClicked, _action(_class::act_info_renren), this);
    
    acts.cancel(@"CANCEL");
    acts.show(view());
}

void MainController::act_post()
{
    ui::ActionSheet acts;
    
    acts.add(@"SINA").connect(kSignalButtonClicked, _action(_class::act_post_sina), this);
    acts.add(@"NETEASE").connect(kSignalButtonClicked, _action(_class::act_post_netease), this);
    acts.add(@"TENCENT").connect(kSignalButtonClicked, _action(_class::act_post_tencent), this);
    acts.add(@"KAIXIN").connect(kSignalButtonClicked, _action(_class::act_post_kaixin), this);
    acts.add(@"RENREN").connect(kSignalButtonClicked, _action(_class::act_post_renren), this);
    acts.add(@"WECHAT").connect(kSignalButtonClicked, _action(_class::act_post_wechat), this);
    
    acts.cancel(@"CANCEL");
    acts.show(view());
}

void MainController::act_postimg()
{
    ui::ActionSheet acts;
    
    acts.add(@"SINA").connect(kSignalButtonClicked, _action(_class::act_postimg_sina), this);
    acts.add(@"NETEASE").connect(kSignalButtonClicked, _action(_class::act_postimg_netease), this);
    acts.add(@"TENCENT").connect(kSignalButtonClicked, _action(_class::act_postimg_tencent), this);
    
    acts.cancel(@"CANCEL");
    acts.show(view());
}

void MainController::act_auth_sina()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::sina::data");
    if (dict.is_null())
        _sina.authorize();
}

void MainController::act_authsuc_sina()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::MutableDictionary dict;
    _sina.save(dict);
    config->set_obj(@"openapi::sina::data", dict);
}

void MainController::act_info_sina()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::sina::data");
    _sina.load(dict);
    sina::weibo::Userinfo api;
    _sina.execute(api);
}

void MainController::act_post_sina()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::sina::data");
    _sina.load(dict);
    sina::weibo::Post api;
    api.set_content(view().txt_post.text());
    _sina.execute(api);
}

void MainController::act_postimg_sina()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::sina::data");
    _sina.load(dict);
    sina::weibo::Upload api;
    api.set_content(view().txt_post.text());
    api.set_image(cg::Image(@"logo@114.png"));
    _sina.execute(api);
}

void MainController::act_auth_netease()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::netease::data");
    if (dict.is_null())
        _netease.authorize();
}

void MainController::act_authsuc_netease()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::MutableDictionary dict;
    _netease.save(dict);
    config->set_obj(@"openapi::netease::data", dict);
}

void MainController::act_info_netease()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::netease::data");
    _netease.load(dict);
    netease::weibo::Userinfo api;
    _netease.execute(api);
}

void MainController::act_post_netease()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::netease::data");
    _netease.load(dict);
    netease::weibo::Post api;
    api.set_content(view().txt_post.text());
    _netease.execute(api);
}

void MainController::act_postimg_netease()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::netease::data");
    _netease.load(dict);
    netease::weibo::Upload api;
    api.set_content(view().txt_post.text());
    api.set_image(cg::Image(@"logo@114.png"));
    _netease.execute(api);
}

void MainController::act_auth_tencent()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::tencent::data");
    if (dict.is_null())
        _tencent.authorize();
}

void MainController::act_authsuc_tencent()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::MutableDictionary dict;
    _tencent.save(dict);
    config->set_obj(@"openapi::tencent::data", dict);
}

void MainController::act_info_tencent()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::tencent::data");
    _tencent.load(dict);
    tencent::opensns::weibo::Userinfo api;
    _tencent.execute(api);
}

void MainController::act_post_tencent()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::tencent::data");
    _tencent.load(dict);
    tencent::opensns::weibo::Post api;
    api.set_title(@"wsi");
    api.set_reference(@"http://libwsi.sf.net");
    api.set_content(view().txt_post.text());
    _tencent.execute(api);
}

void MainController::act_postimg_tencent()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::tencent::data");
    _tencent.load(dict);
    tencent::opensns::weibo::Post api;
    api.set_title(@"wsi");
    api.set_reference(@"http://libwsi.sf.net");
    api.set_content(view().txt_post.text());
    api.set_image(ns::URL::String(@"https://sourceforge.net/p/libwsi//icon"));
    _tencent.execute(api);
}

void MainController::act_auth_taobao()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::taobao::data");
    if (dict.is_null())
        _taobao.authorize();
}

void MainController::act_authsuc_taobao()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::MutableDictionary dict;
    _taobao.save(dict);
    config->set_obj(@"openapi::taobao::data", dict);
}

void MainController::act_info_taobao()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::taobao::data");
    _taobao.load(dict);
    taobao::Userinfo api;
    _taobao.execute(api);
}

void MainController::act_auth_alipay()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::alipay::data");
    if (dict.is_null())
        _alipay.authorize();
}

void MainController::act_authsuc_alipay()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::MutableDictionary dict;
    _alipay.save(dict);
    config->set_obj(@"openapi::alipay::data", dict);
}

void MainController::act_info_alipay()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::alipay::data");
    _alipay.load(dict);
}

void MainController::act_auth_kaixin()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::kaixin::data");
    if (dict.is_null())
        _kaixin.authorize();
}

void MainController::act_authsuc_kaixin()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::MutableDictionary dict;
    _kaixin.save(dict);
    config->set_obj(@"openapi::kaixin::data", dict);
}

void MainController::act_info_kaixin()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::kaixin::data");
    _kaixin.load(dict);
    kaixin::sns::Userinfo api;
    _kaixin.execute(api);
}

void MainController::act_post_kaixin()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::kaixin::data");
    _kaixin.load(dict);
    kaixin::sns::Post api;
    api.set_content(view().txt_post.text());
    api.set_title(@"WSI");
    _kaixin.execute(api);
}

void MainController::act_auth_renren()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::renren::data");
    if (dict.is_null())
        _renren.authorize();
}

void MainController::act_authsuc_renren()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::MutableDictionary dict;
    _renren.save(dict);
    config->set_obj(@"openapi::renren::data", dict);
}

void MainController::act_info_renren()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::renren::data");
    _renren.load(dict);
    //renren::sns::Userinfo api;
    //renren::sns::Userinfo_2_0 api;
    renren::sns::UserLoginGet_2_0 api;
    _renren.execute(api);
    
    ns::Dictionary data(api.nsobject().result);
    
}

void MainController::act_post_renren()
{
    store::Configuration* config = &store::Configuration::shared();
    ns::Dictionary dict = config->get_obj(@"openapi::renren::data");
    _renren.load(dict);
    //renren::sns::Post api;
    renren::sns::BlogPut api;
    api.set_content(view().txt_post.text());
    api.set_title(@"WSI");
    _renren.execute(api);
}

void MainController::act_post_wechat()
{
    tencent::wechat::Post api;
    api.set_content(view().txt_post.text());
    _wechat.execute(api);
}

NNTAPP_END
