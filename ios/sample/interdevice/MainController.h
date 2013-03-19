
# ifndef MAIN_CTLR
# define MAIN_CTLR

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();

protected:
    
    void act_shaked();
    
};

NNTAPP_END

# endif
