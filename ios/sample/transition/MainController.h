
# ifndef MAIN_CTLR
# define MAIN_CTLR

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    ui::BevelButton btn_a;
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    void view_loaded();
    void act_a();
};

NNTAPP_END

# endif
