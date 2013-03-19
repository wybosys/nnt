
# ifndef __MAIN_CTLR_D53F1C6F73EB40B183861A2A99FB1D12_H_INCLUDED
# define __MAIN_CTLR_D53F1C6F73EB40B183861A2A99FB1D12_H_INCLUDED

NNTAPP_BEGIN

using namespace ::wsi;

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    
    ui::TextField txt_config;
    ui::BevelButton btn_config;
    
protected:
    void act_config();
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    void view_loaded();

};

NNTAPP_END

# endif