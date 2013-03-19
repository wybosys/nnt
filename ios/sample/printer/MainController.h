
# ifndef MAIN_CTLR
# define MAIN_CTLR

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
    ui::TextView input;
    ui::BevelButton print;
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();
    
protected:
    
    void act_print();
    
};

WSIAPP_END

# endif
