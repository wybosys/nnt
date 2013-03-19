
# ifndef MAIN_CTLR
# define MAIN_CTLR

NNTAPP_BEGIN

class BackView
: public ui::View<BackView>
{
public:
    BackView();
    void layout_subviews() {}
};

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    
    ui::PageControl page;
    BackView page_back;
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    MainController();
    void view_loaded();
};

NNTAPP_END

# endif