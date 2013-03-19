
# ifndef MAIN_CTLR
# define MAIN_CTLR

# include "IAdService.h"
# include "InAppPurchase.h"
# include "AdmobService.h"
# include "DomobService.h"

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
    ui::BevelButton btn_show_achs, btn_show_leader, btn_show_inapp, btn_buy_inapp, btn_cloud_save, btn_cloud_load;
    ui::TextField txt_cloud_input;
    ui::ad::iAdController ctlr_iad;
    ui::ad::AdmobController ctlr_adb;
    ui::ad::DomobController ctlr_dmb;
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();
    
protected:
    
    void act_gamecenter_login();
    void act_show_achs();
    void act_show_leader();
    void act_show_inapp();
    void act_cloud_save();
    void act_cloud_load();
    void act_inapp_got(EventObj&);
    void act_inapp_buy();
    
};

NNTAPP_END

# endif
