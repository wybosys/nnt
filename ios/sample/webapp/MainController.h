
# ifndef MAIN_CTLR
# define MAIN_CTLR

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
    ui::TextField url;
    ui::WebController web;
    
};

NNTDECL_PRIVATE_HEAD_CXX(MainController);

class MainController
: public ui::Controller<MainController, MainView>
{
    NNTDECL_PRIVATE_CXX(MainController);
    
public:
    
    MainController();
    ~MainController();
    
    void view_loaded();
    void act_goto(EventObj&);
    
    ns::String url;
    
};

NNTAPP_END

# endif
