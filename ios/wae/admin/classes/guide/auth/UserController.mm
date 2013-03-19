
# include "wae.h"
# include "UserController.h"
# include "MaeAuth.h"
# include "UserModifyController.h"

WAE_BEGIN_NS2(guide, auth)

UserAddPanel::UserAddPanel()
{
    btn_group.set_text(tr(@"GROUP"));
    btn_add.set_text(tr(@"ADD"));
    
    txt_name.set_borderstyle(UITextBorderStyleLine);
    txt_prefix.set_borderstyle(UITextBorderStyleLine);
    
    txt_name.set_placeholder(tr(@"NAME"));
    txt_prefix.set_placeholder(tr(@"PREFIX"));
    
    add_sub(txt_name);
    add_sub(txt_prefix);
    add_sub(btn_group);
    add_sub(btn_add);
}

void UserAddPanel::layout_subviews()
{
    layout::hbox lyt(bounds(), 5);
    layout::linear lnr(lyt);
    lnr << (flex)2 << (flex)1 << (pixel)100 << (pixel)100;
    
    txt_name.set_frame(lyt << lnr);
    txt_prefix.set_frame(lyt << lnr);
    btn_group.set_frame(lyt << lnr);
    btn_add.set_frame(lyt << lnr);
}

UserCell::UserCell()
{
    set_accessory(UITableViewCellAccessoryDisclosureIndicator);
    
    add_sub(lbl_id);
    add_sub(lbl_name);
    add_sub(lbl_group);
    add_sub(lbl_prefix);
}

void UserCell::layout_subviews()
{
    layout::hbox lyt(bounds(), 5);
    layout::linear lnr(lyt);
    lnr << (pixel)100 << (flex)2 << (flex)1 << (flex)1;
    
    lbl_id.set_frame(lyt << lnr);
    lbl_name.set_frame(lyt << lnr);
    lbl_group.set_frame(lyt << lnr);
    lbl_prefix.set_frame(lyt << lnr);
}

void UserCell::update()
{
    ae::model::account::User& usr = object();
    
    lbl_id.set_text(ns::String::Value(usr.uid));
    lbl_name.set_text(usr.name);
    
    // find group.
    ae::model::auth::FindGroup find;
    find.gid = usr.gid;
    context::Serv().retrieve(find);
    lbl_group.set_text(find.group->name);
    
    // show prefix.
    if (usr.prefix.not_empty())
        lbl_prefix.set_text(usr.prefix);
    else if (find.group->prefix.not_empty())
        lbl_prefix.set_text(find.group->prefix);
    else
        lbl_prefix.set_text(@"");
}

void UserCell::selected()
{
    ae::model::account::User& usr = object();
    ui::Instance<UserModifyController> ctlr;
    ctlr->user = &usr;
    owner()->navigation().push(*ctlr);
}

UserView::UserView()
{
    set_background(ui::Color::White());
    
    add_sub(tbl_all);
    add_sub(pnl_add);
}

void UserView::layout_subviews()
{
    layout::vbox lyt(bounds(), 5);
    layout::linear lnr(lyt);
    lnr << (flex)1 << (pixel)50;
    
    tbl_all.view().set_frame(lyt << lnr);
    pnl_add.set_frame(lyt << lnr);
}

UserController::UserController()
{
    connect(kSignalViewAppear, _action(_class::refresh));
}

UserController::~UserController()
{
    
}

void UserController::view_loaded()
{
    view().pnl_add.btn_group.connect(kSignalButtonClicked, _action(_class::act_group_select), this);
    view().pnl_add.btn_add.connect(kSignalButtonClicked, _action(_class::act_add), this);
    
    view().tbl_all.set_navigation(navigation());
}

void UserController::refresh()
{
    instance_ref<ae::model::auth::AllUser> mdl;
    mdl->set_appid(context::User().identity());
    context::Serv().retrieve_async(mdl, _mdlaction(_class::mdl_all), this);
}

void UserController::mdl_all(AnyObject& any)
{
    ae::model::auth::AllUser& mdl = any;
    
    instance_ref<ui::TableSection> sec;
    for (uint i = 0; i < mdl.users.size(); ++i)
    {
        ae::model::account::User& usr = *mdl.users[i];
        sec->add(usr);
    }
    
    view().tbl_all.clear();
    view().tbl_all.add(sec);
    view().tbl_all.reload();
}

void UserController::act_group_select()
{
    view().pnl_add.txt_name.unfocus();
    instance_ref<ae::model::auth::AllGroup> mdl;
    mdl->set_update(true);
    mdl->set_appid(context::User().identity());
    context::Serv().retrieve_async(mdl, _mdlaction(_class::mdl_group_select), this);
}

class SelectGroupCell
: public ui::TableCell<SelectGroupCell>
{
public:
    
    void update()
    {
        ae::model::account::Group& grp = object();
        text().set_text(grp.name);
    }
    
};

class SelectGroupTable
: public ui::PlainTable<SelectGroupTable, SelectGroupCell>
{
public:
    
    SelectGroupTable()
    {
        view().set_background(ui::Color::White());
    }
    
};

void UserController::mdl_group_select(AnyObject& obj)
{
    ae::model::auth::AllGroup& mdl = obj;
    
    ui::Instance<ui::Popover<SelectGroupTable> > popr;
    popr->set_direction(UIPopoverArrowDirectionDown);
    popr->present(view().pnl_add.btn_group.frame(), view().pnl_add);
    
    // fill group.
    instance_ref<ui::TableSection> sec;
    for (uint i = 0; i < mdl.groups.size(); ++i)
    {
        ae::model::account::Group& grp = *mdl.groups[i];
        sec->add(grp).connect(kSignalSelected, _action(_class::act_group_selected), this);
    }
    
    popr->content.add(sec);
    popr->content.reload();
}

void UserController::act_group_selected(EventObj& evt)
{
    ui::TableCellObject& obj = evt.sender();
    ae::model::account::Group& grp = obj;
    view().pnl_add.btn_group.set_text(grp.name);
    view().pnl_add.store().set("selected", &grp);
}

void UserController::act_add()
{
    ns::String name = view().pnl_add.txt_name.text();
    if (name.is_empty())
    {
        core::Confirm::warn(tr(@"name is null"));
        return;
    }
    
    view().pnl_add.txt_name.unfocus();
    view().pnl_add.txt_prefix.unfocus();
    
    instance_ref<ae::model::auth::AddUser> mdl;
    mdl->set_appid(context::User().identity());
    mdl->name = name;
    mdl->prefix = view().pnl_add.txt_prefix.text();
    ae::model::account::Group* grp = (ae::model::account::Group*)view().pnl_add.store().find("selected");
    if (grp != NULL)
        mdl->gid = grp->gid;
    context::Serv().retrieve_async(mdl, _mdlaction(_class::refresh), this);
}

WAE_END_NS2
