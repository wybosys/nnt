
# ifndef __MAIN_CTLR_2F341A18C3504D7E8FF8E44992085160_H_INCLUDED
# define __MAIN_CTLR_2F341A18C3504D7E8FF8E44992085160_H_INCLUDED

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
    ui::BevelButton alipay, bypay;
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();
    
protected:
    
    void act_alipay();
    void act_bypay();
    void mdl_bypay(AnyObject&);
    void cb_bypay_failed();
    void cb_bypay_suc();
    
};

NNTAPP_END

# endif