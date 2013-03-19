
# ifndef __WAE_AUTH_GROUP_D40958F9798A43E1BD1F0ADEC8AE3EA4_H_INCLUDED
# define __WAE_AUTH_GROUP_D40958F9798A43E1BD1F0ADEC8AE3EA4_H_INCLUDED

# include "WaeController.h"

WAE_BEGIN_NS2(guide, auth)

class GroupAddPanel
: public ui::View<GroupAddPanel>
{
public:
    
    GroupAddPanel();
    void layout_subviews();
    
    ui::TextField txt_name, txt_prefix;
    ui::BevelButton btn_add;
    
};

class GroupCell
: public ui::TableCell<GroupCell>
{
public:
    
    GroupCell();
    
    void layout_subviews();
    void update();
  
    ui::Label lbl_id, lbl_name, lbl_prefix;
    
};

class GroupTable
: public ui::PlainTable<GroupTable, GroupCell>
{
public:
    
};

class GroupView
: public ui::View<GroupView>
{
public:
    
    GroupView();
    void layout_subviews();
    
    GroupTable tbl_all;
    GroupAddPanel pnl_add;
    
};

class GroupController
: public ui::Controller<GroupController, GroupView>,
public IWorkController
{
public:
    
    GroupController();
    void view_loaded();
    void refresh();
    
protected:
    
    void mdl_all(AnyObject&);
    void act_add();
    
};

WAE_END_NS2

# endif
