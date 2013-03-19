
# ifndef __MAIN_CTLR_6ACF2CE0A19C424E9691AB95AD277F73_H_INCLUDED
# define __MAIN_CTLR_6ACF2CE0A19C424E9691AB95AD277F73_H_INCLUDED

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    
    ui::SimpleView r0, r1, r2;
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
