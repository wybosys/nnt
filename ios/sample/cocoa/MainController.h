
# ifndef __MAIN_CTLR_46468BC159924C40A9241DF6A5405A99_H_INCLUDED
# define __MAIN_CTLR_46468BC159924C40A9241DF6A5405A99_H_INCLUDED

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    void draw(CGContextRef, CGRect const&);
    
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
