
# ifndef __WAE_AUTH_USER_CBFA46AB865A4033B52E7DDF0FAD6FF5_H_INCLUDED
# define __WAE_AUTH_USER_CBFA46AB865A4033B52E7DDF0FAD6FF5_H_INCLUDED

# include "WaeController.h"

WAE_BEGIN_NS2(guide, auth)

class UserAddPanel
: public ui::View<UserAddPanel>
{
public:
    
    UserAddPanel();
    void layout_subviews();    
    
    ui::TextField txt_name, txt_prefix;
    ui::BevelButton btn_group, btn_add;
    
};

class UserCell
: public ui::TableCell<UserCell>
{
public:
    
    UserCell();
    
    void layout_subviews();
    void update();
    void selected();
    
    ui::Label lbl_id, lbl_name, lbl_group, lbl_prefix;
};

class UserTable
: public ui::PlainTable<UserTable, UserCell>
{
public:
    
};

class UserView
: public ui::View<UserView>
{
public:
    
    UserView();
    void layout_subviews();

    UserTable tbl_all;
    UserAddPanel pnl_add;
    
};

class UserController
: public ui::Controller<UserController, UserView>,
public IWorkController
{
public:
    
    UserController();
    ~UserController();
    
    void view_loaded();
    void refresh();
    
protected:
    
    void mdl_all(AnyObject&);
    void act_group_select();
    void act_group_selected(EventObj&);
    void mdl_group_select(AnyObject&);
    void act_add();
    
};

WAE_END_NS2

# endif
