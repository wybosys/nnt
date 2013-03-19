
# include "wae.h"
# include "AllController.h"
# include "MaeSApi.h"

WAE_BEGIN_NS2(guide, sapi)

AllCell::AllCell()
{
    set_accessory(UITableViewCellAccessoryDisclosureIndicator);
}

void AllCell::update()
{
    ae::model::sapi::Class& cls = object();
    text().set_text(cls.name);
}

void AllCell::selected()
{
    ae::model::sapi::Class& cls = object();
    ui::Instance<MethodTable> tbl;
    tbl->cls = &cls;
    tbl->set_title(cls.name);
    owner()->navigation().push(tbl);
}

void MethodCell::update()
{
    ae::model::sapi::Method& mtd = object();
    ns::String method = mtd.name;
    method += @"(";
    for (uint i = 0; i < mtd.requires.size(); ++i)
    {
        method += mtd.requires[i] + @", ";
    }
    for (uint i = 0; i < mtd.optionals.size(); ++i)
    {
        method += @"~" + mtd.optionals[i] + @", ";
    }
    method += @")";
    text().set_text(method);
}

void MethodCell::selected()
{
    instance_ref<ae::model::sapi::FindDoc> mdl;
    mdl->set_appid(context::User().identity());
    ae::model::sapi::Method& mtd = object();
    core::reference<ae::model::sapi::Class> cls = interface_cast(owner(), MethodTable)->cls;
    mdl->method = cls->name + @"." + mtd.name;
    context::Serv().retrieve_async(mdl, _mdlaction(_class::mdl_doc), this);
}

void MethodCell::mdl_doc(AnyObject& any)
{
    ae::model::sapi::FindDoc& mdl = any;
    ui::Instance<ui::Controllerize<ui::TextView> > doc;
    doc->set_title(mdl.method);
    doc->view().set_text(mdl.doc);
    doc->view().set_readonly();
    interface_cast(owner(), MethodTable)->navigation().push(doc);
}

MethodTable::MethodTable()
{
    PASS;
}

void MethodTable::view_loaded()
{
    view().set_background(ui::Color::White());
    
    instance_ref<ui::TableSection> sec;
    core::reference<ae::model::sapi::Class> obj = cls;
    for (uint i = 0; i < obj->methods.size(); ++i)
    {
        sec->add(obj->methods[i]);
    }
    
    clear();
    add(sec);
    reload();
}

AllView::AllView()
{
    set_background(ui::Color::White());
    
    add_sub(tbl_all);
}

void AllView::layout_subviews()
{
    tbl_all.view().set_frame(bounds());
}

AllController::AllController()
{
    connect(kSignalViewAppear, _action(_class::refresh));
}

void AllController::view_loaded()
{
    view().tbl_all.set_navigation(navigation());
}

void AllController::refresh()
{
    instance_ref<ae::model::sapi::List> mdl;
    mdl->set_appid(context::User().identity());
    context::Serv().retrieve_async(mdl, _mdlaction(_class::mdl_all), this);
}

void AllController::mdl_all(AnyObject& obj)
{
    ae::model::sapi::List& mdl = obj;
    instance_ref<ui::TableSection> sec;
    for (uint i = 0; i < mdl.classes.size(); ++i)
    {
        sec->add(*mdl.classes[i]);
    }
    
    view().tbl_all.clear();
    view().tbl_all.add(sec);
    view().tbl_all.reload();
}

WAE_END_NS2
