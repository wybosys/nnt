
# ifndef __MAIN_CTLR_93BDBC98F3AD4232B8345943FA8DA21F_H_INCLUDED
# define __MAIN_CTLR_93BDBC98F3AD4232B8345943FA8DA21F_H_INCLUDED

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
    ui::PageRoller roller;
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();
    
};

WSIAPP_END

# endif
