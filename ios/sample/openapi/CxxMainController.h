
# ifndef __CXXMAIN_CTLR_76B1007F20A14209B9B4A9BC1000F714_H_INCLUDED
# define __CXXMAIN_CTLR_76B1007F20A14209B9B4A9BC1000F714_H_INCLUDED

# include "OASINA.h"
# include "OANetease.h"
# include "OATencentOS.h"
# include "OATaobao.h"
# include "OAAlipay.h"
# include "OAKaixin.h"
# include "OARenren.h"
# include "OAWeChat.h"

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
    ui::TextField txt_post;
    ui::BevelButton btn_auth, btn_info, btn_post, btn_postimg;
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();    
    void view_loaded();
    
protected:
    
    void act_auth();
    void act_info();
    void act_post();
    void act_postimg();
    
    void act_auth_sina();
    void act_authsuc_sina();
    void act_info_sina();
    void act_post_sina();
    void act_postimg_sina();
    
    void act_auth_tencent();
    void act_authsuc_tencent();
    void act_info_tencent();
    void act_post_tencent();
    void act_postimg_tencent();
    
    void act_auth_netease();
    void act_authsuc_netease();
    void act_info_netease();
    void act_post_netease();
    void act_postimg_netease();
    
    void act_auth_taobao();
    void act_authsuc_taobao();
    void act_info_taobao();
    
    void act_auth_alipay();
    void act_authsuc_alipay();
    void act_info_alipay();
    
    void act_auth_kaixin();
    void act_authsuc_kaixin();
    void act_info_kaixin();
    void act_post_kaixin();
    
    void act_auth_renren();
    void act_authsuc_renren();
    void act_info_renren();
    void act_post_renren();
    
    void act_post_wechat();
    
    sina::Provider _sina;  
    netease::Provider _netease;
    tencent::opensns::Provider _tencent;
    taobao::Provider _taobao;
    alipay::Provider _alipay;
    kaixin::Provider _kaixin;
    renren::Provider _renren;
    tencent::wechat::Provider _wechat;
    
};

WSIAPP_END

# endif