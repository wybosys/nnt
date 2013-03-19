
# ifndef __TM_MAIN_A2214BFC841748BB86149F5F4E53D058_H_INCLUDED
# define __TM_MAIN_A2214BFC841748BB86149F5F4E53D058_H_INCLUDED

WSIAPP_BEGIN_OBJC

@interface TMMainController : WSINSViewController {
    NSURL *load_path, *save_path;
    UITheme* theme;
}

- (void)open:(NSURL*)url;

@end

WSIAPP_END_OBJC

WSIAPP_BEGIN

using namespace ::wsi;

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    
    void layout_subviews();
    
    ui::PushButton btn_open, btn_new, btn_save, btn_reveal;
    ui::PushButton btn_add, btn_del, btn_modify;
    ui::TextField txt_path, txt_key;
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