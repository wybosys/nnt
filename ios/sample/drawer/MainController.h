
# ifndef __MAIN_CTLR_D7D663E1BC6C4FE682B5949980975CF0_H_INCLUDED
# define __MAIN_CTLR_D7D663E1BC6C4FE682B5949980975CF0_H_INCLUDED

NNTAPP_BEGIN

class Drawer
: public ui::Drawer
{
public:
    
    Drawer();    
    void layout_subviews();
    void act_close();
    
    ui::BevelButton hide;
};

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    
    Drawer drawer;
    ui::BevelButton left, right, top, bottom;
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    MainController();
    void view_loaded();
    
    void act_left();
    void act_right();
    void act_top();
    void act_bottom();
        
};

NNTAPP_END

# endif
