
# ifndef __MAIN_CTLR_DEF77B6400B746FA9F8BBDCBA082986E_H_INCLUDED
# define __MAIN_CTLR_DEF77B6400B746FA9F8BBDCBA082986E_H_INCLUDED

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    
    ui::TextField si_key;
    ui::TextView si_value;
    ui::BevelButton si_set, si_get;
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    MainController();
    void view_loaded();
    
protected:
    void act_siset();
    void act_siget();
};

NNTAPP_END

# endif
