
# include "wae.h"
# include "LoginController.h"
# include "MaeAuth.h"

WAE_BEGIN

LoginView::LoginView()
{
    set_background(ui::Color::White());
    
    add_sub(lbl_user);
    add_sub(txt_user);
    add_sub(lbl_passwd);
    add_sub(txt_passwd);
    add_sub(btn_login);
    add_sub(logo);
    
    lbl_user.set_text(tr(@"USERNAME"));
    lbl_passwd.set_text(tr(@"PASSWORD"));
    btn_login.set_text(tr(@"LOGIN"));
    logo.set_image(ui::Image(@"wae.png"));
    logo.set_content(UIViewContentModeScaleAspectFill);
    txt_user.set_borderstyle(UITextBorderStyleRoundedRect);
    txt_passwd.set_borderstyle(UITextBorderStyleRoundedRect);
}

void LoginView::layout_subviews()
{
    // layout center.
    {
        layout::hbox lyt0(bounds());
        layout::linear lnr0(lyt0);
        lnr0 << (flex)1 << (flex)2 << (flex)1;
        lyt0 << lnr0;
        layout::vbox lyt1(lyt0 << lnr0);
        layout::linear lnr1(lyt1);
        lnr1 << (flex)2 << (flex)1 << (flex)2;
        lyt1 << lnr1;
        // center.
        layout::hbox lyt2(lyt1 << lnr1, 5);
        layout::linear lnr2(lyt2);
        lnr2 << whar(1, 1) << (flex)1;
        logo.set_frame(lyt2 << lnr2);
        // input.
        layout::vbox lyt3(lyt2 << lnr2, 5);
        layout::linear lnr3(lyt3);
        lnr3 << (flex)1 << (flex)1;
        // user.
        layout::hbox lyt4(lyt3 << lnr3, 5);
        layout::linear lnr4(lyt4);
        lnr4 << (pixel)120 << (flex)1;
        lbl_user.set_frame(lyt4 << lnr4);
        txt_user.set_frame(lyt4 << lnr4);
        // passwd.
        layout::hbox lyt5(lyt3 << lnr3, 5);
        layout::linear lnr5(lyt5);
        lnr5 << (pixel)120 << (flex)1;
        lbl_passwd.set_frame(lyt5 << lnr5);
        txt_passwd.set_frame(lyt5 << lnr5);
    }
    
    // layout login.
    {
        layout::hbox lyt0(bounds());
        layout::linear lnr0(lyt0);
        lnr0 << (flex)3 << (flex)1;
        lyt0 << lnr0;
        layout::vbox lyt1(lyt0 << lnr0);
        layout::linear lnr1(lyt1);
        lnr1 << (flex)1 << (pixel)(lyt1.get_rc().size.width);
        lyt1 << lnr1;
        btn_login.set_frame(cg::Rect(lyt1 << lnr1).deflate(cg::ratio(.3f), .3f, .3f, .3f));
    }
}

LoginController::LoginController()
{
    
}

void LoginController::view_loaded()
{
    view().btn_login.connect(kSignalButtonClicked, _action(_class::act_login), this);
    
    // recall
    view().txt_user.set_text(context::Prefs().defaults.find(@"::wae::user"));
    view().txt_passwd.set_text(context::Prefs().defaults.find(@"::wae::passwd"));
}

void LoginController::act_login()
{    
    ns::String user = view().txt_user.text();
    if (user.is_empty())
    {
        core::Confirm::info(tr(@"USERNAME is NULL."));
        return;
    }
    
    ns::String passwd = view().txt_passwd.text();
    if (passwd.is_empty())
    {
        core::Confirm::info(tr(@"PASSWD is NULL."));
        return;
    }
    
    instance_ref< ::wsi::ae::model::auth::Login> mdl;
    mdl->name = user;
    mdl->passwd = passwd;
    context::Serv().retrieve_async(mdl, _mdlaction(_class::mdl_login), this);
}

void LoginController::mdl_login(AnyObject& any)
{
    ::wsi::ae::model::auth::Login& mdl = any;
    
    context::User().login(mdl.user.appid);
    
    // remember.
    ns::String user = view().txt_user.text();
    ns::String passwd = view().txt_passwd.text();
    context::Prefs().defaults.set(@"::wae::user", user);
    context::Prefs().defaults.set(@"::wae::passwd", passwd);
}

WAE_END
