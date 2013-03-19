
WSIAPP_BEGIN

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
    
};

class App
: public Application
{
public:
    
    void load();
    MainController ctlr;
    
};

WSIAPP_END
