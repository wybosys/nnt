
# ifndef __MAIN_CTLR_348E744CC0AC49E7A73B765AEB1FDA4C_H_INCLUDED
# define __MAIN_CTLR_348E744CC0AC49E7A73B765AEB1FDA4C_H_INCLUDED

NNTAPP_BEGIN

using namespace ::wsi;

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    
    ui::BevelButton btn_present, btn_form, btn_desktop;
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    MainController();
    void view_loaded();
    
protected:
    
    void act_present();
    void act_form();
    void act_desktop();
    
};

NNTAPP_END

# endif