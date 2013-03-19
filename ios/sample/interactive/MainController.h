
# ifndef MAIN_CTLR
# define MAIN_CTLR

# include "JuiceCocoa++.hpp"

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
    ui::Label lbl_path;
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();

protected:
    
    void touches_begin(EventObj&);
    void touches_moved(EventObj&);
    void touches_end(EventObj&);
    void painting();
    
    cg::MutablePath path;
    
};

WSIAPP_END

# endif
