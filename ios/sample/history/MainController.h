
# ifndef __MAIN_CTLR_7C263FA01D15431BB18C1320116CEF95_H_INCLUDED
# define __MAIN_CTLR_7C263FA01D15431BB18C1320116CEF95_H_INCLUDED

NNTAPP_BEGIN

using namespace ::wsi;

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    
    ui::SuggestTextField suggest;
    ui::HistoryTextField history;
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