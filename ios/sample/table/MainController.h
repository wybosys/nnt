
# ifndef __MAIN_CTLR_A2AB77F2EFE14526B8C6C253F9F060E6_H_INCLUDED
# define __MAIN_CTLR_A2AB77F2EFE14526B8C6C253F9F060E6_H_INCLUDED

NNTAPP_BEGIN

class Cell
: public ui::TableCell<Cell>
{
public:
    Cell();
    ~Cell();
    
    ns::String str;
    
    void layout_subviews();
    void update();
    
protected:
    
    ui::ImageView img;
    
};

class Table
: public ui::PlainTableController
//: public wsi::ui::GroupedTableController
{
public:
    Table();
    
    virtual ::nnt::Object* makecell(IndexPath const&) const;
    
    ui::ActivityHeaderView top, bottom;
};

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    Table tab;    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    void view_loaded();
    
protected:
    void act_selected(EventObj&);
    void act_removed(EventObj&);
    
protected:
    void act_top(EventObj&);
    void act_bottom(EventObj&);
};

NNTAPP_END

# endif