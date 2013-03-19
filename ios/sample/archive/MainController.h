
# ifndef __MAIN_CTLR_5358A0E178EF4EC3991A6E2E575211D5_H_INCLUDED
# define __MAIN_CTLR_5358A0E178EF4EC3991A6E2E575211D5_H_INCLUDED

WSIAPP_BEGIN

using namespace ::wsi;

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    
    void layout_subviews();
    
    ui::TextField input, output, result;
    ui::BevelButton comp, uncomp;
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    void view_loaded();
    
protected:
    
    void act_comp();
    void act_uncomp();
    
};

WSIAPP_END

# endif