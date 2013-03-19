
# ifndef __MAIN_CTLR_A2AB77F2EFE14526B8C6C253F9F060E6_H_INCLUDED
# define __MAIN_CTLR_A2AB77F2EFE14526B8C6C253F9F060E6_H_INCLUDED

WSIAPP_BEGIN

class Cell
: public wsi::ui::TableCell<Cell>
{
public:
    Cell();
    ~Cell();
    wsi::ns::String str;
    
    void layout_subviews();
    void update();
    
protected:
    wsi::ui::ImageView img;
};

class Table
: public wsi::ui::PlainTableController
//: public wsi::ui::GroupedTableController
{
public:
    Table();
    
    virtual wsi::Object* makecell(IndexPath const&) const;
    
    wsi::ui::ActivityHeaderView top, bottom;
};

class MainView
: public wsi::ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    Table tab;    
};

class MainController
: public wsi::ui::Controller<MainController, MainView>
{
public:
    void view_loaded();
    
protected:
    void act_selected(wsi::EventObj&);
    void act_removed(wsi::EventObj&);
    
protected:
    void act_top(wsi::EventObj&);
    void act_bottom(wsi::EventObj&);
};

WSIAPP_END

# endif