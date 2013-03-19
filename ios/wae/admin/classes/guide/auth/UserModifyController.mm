
# include "wae.h"
# include "UserModifyController.h"

WAE_BEGIN_NS2(guide, auth)

UserModifyView::UserModifyView()
{
    set_background(ui::Color::White());
    
    add_sub(lbl_name);
    add_sub(txt_name);
    
    add_sub(lbl_prefix);
    add_sub(txt_prefix);
    
    add_sub(lbl_group);
    add_sub(pk_group);
    
    add_sub(lbl_passwd);
    add_sub(txt_passwd);
    
    add_sub(btn_commit);
    
    lbl_name.set_text(tr(@"NAME"));
    lbl_prefix.set_text(tr(@"PREFIX"));
    lbl_group.set_text(tr(@"GROUP"));
    lbl_passwd.set_text(tr(@"PASSWORD"));
    btn_commit.set_text(tr(@"COMMIT"));
    
    txt_name.set_borderstyle(UITextBorderStyleLine);
    txt_passwd.set_borderstyle(UITextBorderStyleLine);
    txt_prefix.set_borderstyle(UITextBorderStyleLine);
}

void UserModifyView::layout_subviews()
{
    layout::vbox lyt_main(bounds(), 5);
    layout::linear lnr_main(lyt_main);
    lnr_main << (flex)1 << (pixel)50;
    
    {
        layout::vbox lyt(lyt_main << lnr_main);
        layout::linear lnr(lyt);
        lnr << (flex)1 << (flex)1 << (flex)2 << (flex)1;
        
        {
            layout::hbox lyth(lyt << lnr);
            layout::linear lnrh(lyth);
            lnrh << (pixel)200 << (flex)1;
            lbl_name.set_frame(lyth << lnrh);
            txt_name.set_frame(lyth << lnrh);
        }
        
        {
            layout::hbox lyth(lyt << lnr);
            layout::linear lnrh(lyth);
            lnrh << (pixel)200 << (flex)1;
            lbl_prefix.set_frame(lyth << lnrh);
            txt_prefix.set_frame(lyth << lnrh);
        }
        
        {
            layout::hbox lyth(lyt << lnr);
            layout::linear lnrh(lyth);
            lnrh << (pixel)200 << (flex)1;
            lbl_group.set_frame(lyth << lnrh);
            pk_group.set_frame(lyth << lnrh);
        }
        
        {
            layout::hbox lyth(lyt << lnr);
            layout::linear lnrh(lyth);
            lnrh << (pixel)200 << (flex)1;
            lbl_passwd.set_frame(lyth << lnrh);
            txt_passwd.set_frame(lyth << lnrh);
        }
    }
    
    {
        layout::hbox lyt(lyt_main << lnr_main);
        layout::linear lnr(lyt);
        lnr << (flex)1 << (flex)1 << (flex)1;
        lyt << lnr;
        btn_commit.set_frame(lyt << lnr);
    }
}

UserModifyController::UserModifyController()
{
    set_title(tr(@"Modify User"));
}

void UserModifyController::view_loaded()
{
    view().btn_commit.connect(kSignalButtonClicked, _action(_class::act_commit), this);
    
    view().txt_name.set_text(user->name);
    view().txt_prefix.set_text(user->prefix);
    
    // load group.
    instance_ref<ae::model::auth::AllGroup> mdl;
    mdl->set_update(true);
    mdl->set_appid(context::User().identity());
    context::Serv().retrieve_async(mdl, _mdlaction(_class::mdl_groups), this);
}

void UserModifyController::mdl_groups(AnyObject& any)
{
    view().pk_group.clear();
    
    //ae::model::auth::AllGroup& mdl = any;
}

void UserModifyController::act_commit()
{
    
}

WAE_END_NS2
