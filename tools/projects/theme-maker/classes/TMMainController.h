
# ifndef __TM_MAIN_A2214BFC841748BB86149F5F4E53D058_H_INCLUDED
# define __TM_MAIN_A2214BFC841748BB86149F5F4E53D058_H_INCLUDED

NNTAPP_BEGIN_OBJC

@interface TMMainController : NNTNSViewController {
    NSURL *load_path, *save_path;
    UITheme* theme;
}

- (void)open:(NSURL*)url;

@end

NNTAPP_END_OBJC

NNTAPP_BEGIN

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

NNTAPP_END

# endif