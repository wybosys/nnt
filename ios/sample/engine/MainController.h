
# ifndef __ENGINE_CONTROLLER_C77E1670BC954A0FB63023375935828C_H_INCLUDED
# define __ENGINE_CONTROLLER_C77E1670BC954A0FB63023375935828C_H_INCLUDED

WSIAPP_BEGIN

class ScreenManagerImpl;

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    ~MainView();
    
    void layout_subviews();
    void draw(CGContextRef, CGRect const&);
    
    ScreenManagerImpl* scrMgr;
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    MainController();
    void view_loaded();
    
    void act_clicked(EventObj&);
    
};

WSIAPP_END

# endif