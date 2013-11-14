
# ifndef MAINCTLR
# define MAINCTLR

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
    ui::TextField inpUrl;
    ui::BevelButton btnGo;
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();
    void act_go();
    
};

NNTAPP_END

# endif
