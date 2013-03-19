
# ifndef __WAE_MAIN_1C7FC58B71314A6FA65455533C2721F3_H_INCLUDED
# define __WAE_MAIN_1C7FC58B71314A6FA65455533C2721F3_H_INCLUDED

WAE_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    
    void layout_subviews();
        
    ui::StackControllers ctlrs;
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    
    void view_loaded();
    
protected:
    
    void act_logined();
    void act_logout();
    
};

WAE_END

# endif
