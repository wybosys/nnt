
# include "wae.h"
# include "CounterController.h"
# include "MaeToolkit.h"

WAE_BEGIN_NS2(guide, toolkit)

CounterCell::CounterCell()
{
    add_sub(lbl_name);
    add_sub(lbl_idr);
    add_sub(lbl_counter);
}

void CounterCell::layout_subviews()
{
    layout::hbox lyt(bounds());
    layout::linear lnr(lyt);
    lnr << (flex)1 << (flex)1 << (flex)1;
    
    lbl_name.set_frame(lyt << lnr);
    lbl_idr.set_frame(lyt << lnr);
    lbl_counter.set_frame(lyt << lnr);
}

void CounterCell::update()
{
    ae::model::toolkit::Counter& obj = object();
    lbl_name.set_text(obj.name);
    lbl_idr.set_text(obj.identity);
    lbl_counter.set_text(core::tostr(obj.sum));
}

CounterDeviceCell::CounterDeviceCell()
{
    add_sub(lbl_idr);
    add_sub(lbl_dev);
    add_sub(lbl_counter);
}

void CounterDeviceCell::layout_subviews()
{
    layout::hbox lyt(bounds());
    layout::linear lnr(lyt);
    lnr << (flex)1 << (flex)2 << (flex)1;
    lbl_idr.set_frame(lyt << lnr);
    lbl_dev.set_frame(lyt << lnr);
    lbl_counter.set_frame(lyt << lnr);
}

void CounterDeviceCell::update()
{
    ae::model::toolkit::Counter& obj = object();
    lbl_idr.set_text(obj.identity);
    lbl_dev.set_text(obj.device);
    lbl_counter.set_text(core::tostr(obj.sum));
}

CounterView::CounterView()
{
    set_background(ui::Color::White());
    
    add_sub(tbl_app);
    add_sub(tbl_dev);
}

void CounterView::layout_subviews()
{
    layout::vbox lyt(bounds(), 5);
    layout::linear lnr(lyt);
    lnr << (flex)1 << (flex)1;
    
    tbl_app.view().set_frame(lyt << lnr);
    tbl_dev.view().set_frame(lyt << lnr);
}

CounterController::CounterController()
{
    connect(kSignalViewAppear, _action(_class::refresh));
}

void CounterController::view_loaded()
{
    
}

void CounterController::refresh()
{
    {
        instance_ref<ae::model::toolkit::LaunchCounter> mdl;
        mdl->set_appid(context::User().identity());
        context::Serv().retrieve_async(mdl, _mdlaction(_class::mdl_launch), this);
    }
    
    {
        instance_ref<ae::model::toolkit::LaunchDeviceCounter> mdl;
        mdl->set_appid(context::User().identity());
        context::Serv().retrieve_async(mdl, _mdlaction(_class::mdl_devicelaunch), this);
    }
}

void CounterController::mdl_launch(AnyObject& obj)
{
    ae::model::toolkit::LaunchCounter& mdl = obj;
    instance_ref<ui::TableSection> sec;
    for (uint i = 0; i < mdl.items.size(); ++i)
    {
        sec->add(*mdl.items[i]);
    }
    
    view().tbl_app.clear();
    view().tbl_app.add(sec);
    view().tbl_app.reload();
}

void CounterController::mdl_devicelaunch(AnyObject& obj)
{
    ae::model::toolkit::LaunchDeviceCounter& mdl = obj;
    instance_ref<ui::TableSection> sec;
    for (uint i = 0; i < mdl.items.size(); ++i)
    {
        sec->add(*mdl.items[i]);
    }
    
    view().tbl_dev.clear();
    view().tbl_dev.add(sec);
    view().tbl_dev.reload();
}

WAE_END_NS2
