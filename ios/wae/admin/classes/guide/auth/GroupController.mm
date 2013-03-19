
# include "wae.h"
# include "GroupController.h"
# include "MaeAuth.h"

WAE_BEGIN_NS2(guide, auth)

GroupAddPanel::GroupAddPanel()
{
    btn_add.set_text(tr(@"ADD"));
    
    txt_name.set_borderstyle(UITextBorderStyleLine);
    txt_name.set_placeholder(tr(@"NAME"));
    
    txt_prefix.set_borderstyle(UITextBorderStyleLine);
    txt_prefix.set_placeholder(tr(@"PREFIX"));
    
    add_sub(txt_name);
    add_sub(txt_prefix);
    add_sub(btn_add);
}

void GroupAddPanel::layout_subviews()
{
    layout::hbox lyt(bounds(), 5);
    layout::linear lnr(lyt);
    lnr << (flex)2 << (flex)1 << (pixel)100;
    
    txt_name.set_frame(lyt << lnr);
    txt_prefix.set_frame(lyt << lnr);
    btn_add.set_frame(lyt << lnr);
}

GroupCell::GroupCell()
{
    add_sub(lbl_id);
    add_sub(lbl_name);
    add_sub(lbl_prefix);
}

void GroupCell::layout_subviews()
{
    layout::hbox lyt(bounds(), 5);
    layout::linear lnr(lyt);
    lnr << (pixel)100 << (flex)1 << (flex)1;
    
    lbl_id.set_frame(lyt << lnr);
    lbl_name.set_frame(lyt << lnr);
    lbl_prefix.set_frame(lyt << lnr);
}

void GroupCell::update()
{
    ae::model::account::Group& grp = object();
    
    lbl_id.set_text(ns::String::Value(grp.gid));
    lbl_name.set_text(grp.name);
    lbl_prefix.set_text(grp.prefix);
}

GroupView::GroupView()
{
    set_background(ui::Color::White());
    
    add_sub(tbl_all);
    add_sub(pnl_add);
}

void GroupView::layout_subviews()
{
    layout::vbox lyt(bounds(), 5);
    layout::linear lnr(lyt);
    lnr << (flex)1 << (pixel)50;
    
    tbl_all.view().set_frame(lyt << lnr);
    pnl_add.set_frame(lyt << lnr);
}

GroupController::GroupController()
{
    connect(kSignalViewAppear, _action(_class::refresh));
}

void GroupController::view_loaded()
{
    view().pnl_add.btn_add.connect(kSignalButtonClicked, _action(_class::act_add), this);
}

void GroupController::refresh()
{
    instance_ref<ae::model::auth::AllGroup> mdl;
    mdl->set_appid(context::User().identity());
    context::Serv().retrieve_async(mdl, _mdlaction(_class::mdl_all), this);
}

void GroupController::mdl_all(AnyObject& any)
{
    ae::model::auth::AllGroup& mdl = any;
    
    instance_ref<ui::TableSection> sec;
    for (uint i = 0; i < mdl.groups.size(); ++i)
    {
        ae::model::account::Group& grp = *mdl.groups[i];
        sec->add(grp);
    }
    
    view().tbl_all.clear();
    view().tbl_all.add(sec);
    view().tbl_all.reload();
}

void GroupController::act_add()
{
    ns::String name = view().pnl_add.txt_name.text();
    if (name.is_empty())
    {
        core::Confirm::warn(tr(@"name is empty"));
        return;
    }
    
    view().pnl_add.txt_name.unfocus();
    view().pnl_add.txt_prefix.unfocus();
    
    instance_ref<ae::model::auth::AddGroup> mdl;
    mdl->name = name;
    mdl->prefix = view().pnl_add.txt_prefix.text();
    mdl->set_appid(context::User().identity());
    context::Serv().retrieve_async(mdl, _mdlaction(_class::refresh), this);
}

WAE_END_NS2
