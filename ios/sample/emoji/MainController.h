
# ifndef ____MAIN_CTLR_85E2A00C5AA644F68C1ACE953B10AF99_H_INCLUDED
# define ____MAIN_CTLR_85E2A00C5AA644F68C1ACE953B10AF99_H_INCLUDED

# include "UIEmojiPickerController.h"

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    
    ui::EmojiPickerController emoji;
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    MainController();
    void view_loaded();
    
private:
    void act_click(EventObj& evt);
};

NNTAPP_END

# endif