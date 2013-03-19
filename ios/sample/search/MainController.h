
# ifndef __MAIN_CTLR_F4F0433ED9D14E9793F59D51D09838A8_H_INCLUDED
# define __MAIN_CTLR_F4F0433ED9D14E9793F59D51D09838A8_H_INCLUDED

# include "UISearchDisplayController+WSI.h"

WSIAPP_BEGIN

class SearchCell
: public ui::TableCell<SearchCell>
{
public:
    void update();
    void selected();
};

class SearchTable
: public ui::PlainTableController
{
public:
    ::wsi::Object* makecell(IndexPath const&) const;
};

class SearchDisplayer
: public ui::SearchDisplayController<
//ui::Navigatilize<SearchTable>
SearchTable
>
{
public:
    bool searchByString(ns::String const&);
};

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    
    SearchDisplayer searchctlr;
    ui::Label dock;
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
