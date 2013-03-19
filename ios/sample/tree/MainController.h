
# ifndef __MAIN_CTLR_8EE525644C764669A9591F98FA91380B_H_INCLUDED
# define __MAIN_CTLR_8EE525644C764669A9591F98FA91380B_H_INCLUDED

# include "UITableTreeViewController.h"

NNTAPP_BEGIN

class Cell
: public ui::TableCell<Cell>
{
public:
    Cell();
    
    void layout_subviews();
    void update();
};

class Table
: public ui::TableTreeController
{
public:
    Table();
    
    virtual cell_type makecell(IndexPath const&) const;
    virtual cell_type makegroupcell(IndexPath const&) const;
    
};

class GroupCell
: public ui::TableGroupCell<GroupCell, Table>
{
    typedef ui::TableGroupCell<GroupCell, Table> super;
    
public:
    GroupCell();
    void layout_subviews();
    void update();
    void did_expanded();
    void did_collapsed();
};

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    
    Table tree;
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