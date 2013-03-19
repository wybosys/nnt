
# ifndef __WAE_ADMIN_LOGIN_C374796486264021BDE26CFCCFFB5BA8_H_INCLUDED
# define __WAE_ADMIN_LOGIN_C374796486264021BDE26CFCCFFB5BA8_H_INCLUDED

WAE_BEGIN

class LoginView
: public ui::View<LoginView>
{
public:
    
    LoginView();
    void layout_subviews();
    
    ui::ImageView logo;
    ui::Label lbl_user, lbl_passwd;
    ui::TextField txt_user;
    ui::SecureTextField txt_passwd;
    ui::BevelButton btn_login;
    
};

class LoginController
: public ui::Controller<LoginController, LoginView>
{
public:
    
    LoginController();    
    void view_loaded();
    
protected:
    
    void act_login();
    void mdl_login(AnyObject&);
    
};

WAE_END

# endif
