
# ifndef __MAIN_CTLR_A5915098C6D24758AAEF9EC12D513F4D_H_INCLUDED
# define __MAIN_CTLR_A5915098C6D24758AAEF9EC12D513F4D_H_INCLUDED

WSIAPP_BEGIN

class LogoHeaderView
: public ui::ActivityHeaderView
{
public:
    
    LogoHeaderView();
    void layout_subviews();
    ui::ImageView logo;
    
};

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
    ui::BevelButton btn_center;
    LogoHeaderView top;
    LogoHeaderView bottom;
    
};

class MainController
: public ui::Controller<MainController, ui::Scrollable<MainView> >
{
public:
    
    MainController();
    void view_loaded();
    
    void act_top(EventObj&);
    void act_bottom(EventObj&);
    
};

WSIAPP_END

# endif