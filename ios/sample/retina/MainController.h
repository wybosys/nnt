
# ifndef __MAIN_CTLR_1BD216586EC94F2BAC7FC00BA75D0F72_H_INCLUDED
# define __MAIN_CTLR_1BD216586EC94F2BAC7FC00BA75D0F72_H_INCLUDED

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
    ui::SimpleView view;
    ui::ImageView img;
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();
    
protected:
    
    void act_view();
    
};

NNTAPP_END

# endif