
# ifndef __MAIN_CTLR_5563B72E9EEC4F5C9AC1ABC29A8EC84A_H_INCLUDED
# define __MAIN_CTLR_5563B72E9EEC4F5C9AC1ABC29A8EC84A_H_INCLUDED

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
  
    ui::BevelButton btn_save, btn_load;
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();
    
    void act_save();
    void act_load();
    
};

NNTAPP_END

# endif
