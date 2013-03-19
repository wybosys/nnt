
# ifndef __MAIN_CTLR_01B0C7A76E964C70A5D1419566FF9FEF_H_INCLUDED
# define __MAIN_CTLR_01B0C7A76E964C70A5D1419566FF9FEF_H_INCLUDED

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();    

    ui::ClearButton btn_sec;
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();

protected:
    
    void act_sec(EventObj&);
    
};

NNTAPP_END

# endif