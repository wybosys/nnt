
# ifndef __MAIN_CTLR_9A2CD28DFD4B4D0889C9F5CE3D51F000_H_INCLUDED
# define __MAIN_CTLR_9A2CD28DFD4B4D0889C9F5CE3D51F000_H_INCLUDED

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    
    ui::BevelButton simple, lines, progress;
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    MainController();
    void view_loaded();

protected:
    void act_simple();
    void act_lines();
    void act_progress();
    void act_progress_end();
};

WSIAPP_END

# endif
