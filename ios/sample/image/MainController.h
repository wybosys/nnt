
# ifndef __SAMPLE_MAIN_59A720709BBC452FA61FB6665215EC50_H_INCLUDED
# define __SAMPLE_MAIN_59A720709BBC452FA61FB6665215EC50_H_INCLUDED

WSIAPP_BEGIN

using namespace ::wsi;

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    
    void layout_subviews();
    
    void act_process();
    void act_reset();
    void act_filter(EventObj&);
    void act_value(EventObj&);
    
    ui::Image image;
    ui::ImageView imageview;
    ui::BevelButton btn_process, btn_reset;
    ns::String name;
    UINavigationTableViewController* table;
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    void view_loaded();
};

WSIAPP_END

# endif