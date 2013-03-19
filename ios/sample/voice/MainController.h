
# ifndef MAIN_CTLR
# define MAIN_CTLR

# include "IFlytekVoice.h"

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
    ui::BevelButton btn_recg, btn_speak;

};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();
    
protected:
    
    void act_recg();
    void act_recg_result(EventObj&);
    void act_speak();
    void act_speak_next();
  
    iflytek::Speech _sph;
    
};

WSIAPP_END

# endif
