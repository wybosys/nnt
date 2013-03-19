
# include "WSIFoundation.h"
# include "MainController.h"
# include "ColorPalette.h"

WSIAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::White());
    
    add_sub(btn_center);
    add_sub(ring);
    
    btn_center.set_text(@"CENTER");
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds());
    layout::linear lnr(lyt);
    lnr << (flex)1;
    
    ring.set_frame(lyt << lnr);
    
    {
        layout::vbox lyt(bounds());
        layout::linear lnr(lyt);
        lnr << (flex)1 << (flex)1 << (flex)1;
        lyt << lnr;
        layout::hbox lyth(lyt << lnr);
        layout::linear lnrh(lyth);
        lnrh << (flex)1 << (flex)1 << (flex)1;
        lyth << lnrh;
        btn_center.set_frame(lyth << lnrh);
    }
}

MainController::MainController()
{
    
}

core::ColorWheel cw;
int pos = 100, len = 20, step = 5, count = 1;

void MainController::view_loaded()
{
    // add ring.
    ui::AnnualRingSingle ring(view().ring.add(len, pos));
    ring.set_ring(ui::Color::RGB(cw.next()));
    
    // add item.
    for (uint j = 0; j < count; ++j)
    {
        ui::Itemlize<ui::BevelButton> item;
        item.set_size(cg::Size(50, 20));
        item.content.set_text(@"ITEM");
        item.set_removable(ui::hold);
        ring.add(item);
        item->set_interaction(true);
        item->connect(kSignalButtonClicked, _action(_class::act_click), this);
        
        cg::Shadow sd;
        sd.set_offset(cg::Point(-1, -1));
        sd.set_radius(5);
        sd.set_side(SideTypeInner);
        ring.set_ring(sd);
    }
    
    // next.
    len += step;
    pos += len;
    ++count;
}

void MainController::act_click()
{
    // add ring.
    ui::AnnualRingSingle ring(view().ring.add(len, pos));
    ring.set_ring(ui::Color::RGB(cw.next()));
    
    // add item.
    for (uint j = 0; j < count; ++j)
    {
        ui::Itemlize<ui::BevelButton> item;
        item.set_size(cg::Size(50, 20));
        item.content.set_text(@"ITEM");
        item.set_removable(ui::hold);
        ring.add(item);
        item->set_interaction(true);
        item->connect(kSignalButtonClicked, _action(_class::act_click), this);
        
        cg::Shadow sd;
        sd.set_offset(cg::Point(-1, -1));
        sd.set_radius(5);
        sd.set_side(SideTypeInner);
        ring.set_ring(sd);
    }
    
    // next.
    len += step;
    pos += len;
    ++count;
}

WSIAPP_END
