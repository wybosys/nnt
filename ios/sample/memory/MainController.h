
# ifndef __MAIN_CTLR_2E9230C776544809BFC415FE7CD4BB16_H_INCLUDED
# define __MAIN_CTLR_2E9230C776544809BFC415FE7CD4BB16_H_INCLUDED

WSIAPP_BEGIN

class SubView
:  public ui::View<SubView>
{
public:
    
    SubView();
    void layout_subviews();
    
};

class SubController
: public ui::Controller<SubController, SubView>
{
public:
    
    SubController();
    void view_loaded();
    
    void imitate();
    
};

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
    SubController ctlr;
    ui::BevelButton btn_imitate, btn_view;
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();
    
    void act_imitate();
    void act_view();
};

WSIAPP_END

# endif
