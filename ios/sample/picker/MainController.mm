
# include "WSIFoundation.h"
# include "MainController.h"

WSIAPP_BEGIN

CustomPickerItem::CustomPickerItem()
{
    add_sub(lbl);
    
    lbl.set_alignment(UITextAlignmentCenter);
    lbl.set_font(ui::Font::BoldSystem(kUIPickerControlItemFontSize));
}

void CustomPickerItem::layout_subviews()
{
    lbl.set_frame(bounds());
}

void CustomPickerItem::update()
{
    ns::String str = (id)object();
    lbl.set_text(str);
}

void CustomPickerItem::selected()
{
    ns::String str = (id)object();
    trace_msg(str);
}

MainView::MainView()
{
    set_background(ui::Color::White());
    
    add_sub(picker);
    
    picker.show_indicator(true);
    
    {
        instance_ref<ui::PickerSection> sec;
        sec->add(@"A");
        sec->add(@"B");
        sec->add(@"C");
        sec->add(@"D");
        sec->add(@"E");
        sec->add(@"F");
        picker.add(sec);
    }
    
    {
        instance_ref<ui::PickerSection> sec;
        sec->add(@"A");
        sec->add(@"B");
        sec->add(@"C");
        sec->add(@"D");
        sec->add(@"E");
        sec->add(@"F");
        picker.add(sec);
    }
    
    add_sub(drum);
    
    add_sub(date);
}

void MainView::layout_subviews()
{
    layout::vbox box(bounds(), 5);
    layout::linear lnr(box);
    lnr << (flex)1 << (flex)1 << (flex)1;
    
    picker.set_frame(box << lnr);
    drum.set_frame(box << lnr);
    date.set_frame(box << lnr);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    view().picker.connect(kSignalSelectChanged, _action(_class::act_picker_selectchanged), this);
}

void MainController::act_picker_selectchanged(EventObj& evt)
{
    ui::PickerItemObject& obj = evt.data();
    ns::String msg = @"selected ";
    msg += obj;
    trace_msg(msg);
}

WSIAPP_END
