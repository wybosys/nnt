
# ifndef MAIN_CTLR
# define MAIN_CTLR

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
    ui::WebController web;
    
};

WSIDECL_PRIVATE_HEAD_CXX(MainController);

class MainController
: public ui::Controller<MainController, MainView>
{
    WSIDECL_PRIVATE_CXX(MainController);
    
public:
    
    MainController();
    ~MainController();
    
    void view_loaded();
    
};

WSIAPP_END

# endif
