
# ifndef __WAE_AUTH_MODIFY_29EBE657D78740D98593D66288004E58_H_INCLUDED
# define __WAE_AUTH_MODIFY_29EBE657D78740D98593D66288004E58_H_INCLUDED

# include "MaeAuth.h"

WAE_BEGIN_NS2(guide, auth)

class UserModifyView
: public ui::View<UserModifyView>
{
public:
    
    UserModifyView();
    void layout_subviews();
    
    ui::Label lbl_name, lbl_group, lbl_prefix, lbl_passwd;
    ui::TextField txt_name, txt_prefix, txt_passwd;
    ui::Picker pk_group;
    ui::BevelButton btn_commit;

};

class UserModifyController
: public ui::Controller<UserModifyController, UserModifyView>
{
public:
    
    UserModifyController();
    void view_loaded();
    
    ae::model::account::User* user;
    
protected:
    
    void mdl_groups(AnyObject&);
    void act_commit();
    
};

WAE_END_NS2

# endif
