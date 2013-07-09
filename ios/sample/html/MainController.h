
# ifndef __MAIN_CTLR_84CF3BDE577245C7A2021246AA503248_H_INCLUDED
# define __MAIN_CTLR_84CF3BDE577245C7A2021246AA503248_H_INCLUDED

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    
    ui::NaviWebController web;
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    MainController();
    void view_loaded();
    
protected:
    void act_webaction(EventObj&);
    
};

NNTAPP_END

# endif