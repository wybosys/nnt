
# include "wae.h"
# include "IndexController.h"
# include "QzEffect.h"

# include "guide/WaeController.h"
# include "guide/auth/UserController.h"
# include "guide/auth/GroupController.h"
# include "guide/toolkit/CounterController.h"
# include "guide/sapi/AllController.h"

WAE_BEGIN

signal_t kRangeActivated = @"::wae::range::activated";

class AnnualRingSingle
: public ui::AnnualRingSingle
{
public:
    
    AnnualRingSingle()
    {
        set_start(cg::Angle::Rad(-M_PI));
        set_clockwise(false);
        
        connect(kSignalItemsLayoutted, kSignalRingRotated);
    }
    
};

class AnnualRingItem
: public ui::Itemlize<ui::Label>
{
public:
    
    AnnualRingItem()
    {
        set_size(cg::Size(100, 50));
        
        register_signal(kRangeActivated);
    }
    
    wtl::function<func_new> guide, work;
    ns::String summary;

};

IndexView::IndexView()
{    
    set_background(ui::Color::White());
    
    add_sub(anl_funs);
    add_sub(btn_logout);
    
    // init annual.
    ui::Instance<AnnualRingSingle> anl_top;
    anl_top->set_length(100);
    anl_top->set_radius(200);
    anl_funs.add(anl_top);
    anl_funs.connect(kSignalItemInserted, _action(_class::act_ring_added), this);
    
    // init top ring.
    setup_top();
    
    // init ui.
    btn_logout.set_text(tr(@"LOGOUT"));
}

void IndexView::setup_top()
{
    ui::AnnualRingSingle& funtop = anl_funs.at<ui::AnnualRingSingle>(0);
    
    funtop.set_ring(ui::Color::Orange());
    funtop.connect(kSignalRingRotated, _action(_class::act_ring_rotated), this);
    
    typedef ui::Instance<AnnualRingItem> item_type;
    
    {
        item_type item;
        item->content.set_text(tr(@"WAE"));
        item->connect(kRangeActivated, _action(_class::act_ranged_wae), this);
        funtop.add(item);
    }
    
    {
        item_type item;        
        item->content.set_text(tr(@"AUTH"));
        item->connect(kRangeActivated, _action(_class::act_ranged_auth), this);
        funtop.add(item);
    }
    
    {
        item_type item;
        item->content.set_text(tr(@"SAPI"));
        item->connect(kRangeActivated, _action(_class::act_ranged_sapi), this);
        funtop.add(item);
    }
    
    {
        item_type item;
        item->content.set_text(tr(@"UTILS"));
        item->connect(kRangeActivated, _action(_class::act_ranged_utils), this);
        funtop.add(item);
    }
    
    {
        item_type item;
        item->content.set_text(tr(@"SAMPLE"));
        item->connect(kRangeActivated, _action(_class::act_ranged_sample), this);
        funtop.add(item);
    }
    
    {
        item_type item;
        item->content.set_text(tr(@"TOOLKIT"));
        item->connect(kRangeActivated, _action(_class::act_ranged_toolkit), this);
        funtop.add(item);
    }
}

void IndexView::layout_subviews()
{
    // layout annual ring.
    {
        layout::hbox lyt(bounds());
        layout::linear lnr(lyt);
        lnr << (flex)1 << (pixel)200;
        
        ctlr_guide.view().set_frame(lyt << lnr);
        anl_funs.set_frame(lyt << lnr);
        anl_funs.bring_totop();
    }
    
    // layout logout.
    {
        layout::hbox lyt(bounds());
        layout::linear lnr(lyt);
        lnr << (flex)1 << (flex)3;
        layout::vbox lyt1(lyt << lnr);
        layout::linear lnr1(lyt1);
        lnr1 << (pixel)lyt1.get_rc().size.width << (flex)1;
        btn_logout.set_frame(cg::Rect(lyt1 << lnr1).deflate(cg::ratio(.3f), .3f, .3f, .3f));
        btn_logout.bring_totop();
    }
}

void IndexView::act_ring_rotated(EventObj& evt)
{
    ui::AnnualRingSingle& ring = evt.sender();
    
    AnnualRingItem* sel = ring.find<AnnualRingItem>(ring.start_angle() - cg::Angle(30).rad(),
                                                    ring.start_angle() + cg::Angle(30).rad());
    
    void* current = ring.attach().find("current");
    if (sel == current)
        return;
    if (sel == NULL)
        return;
    
    // init guide.
    wtl::function<func_new> fguide = sel->guide;
    if (fguide == NULL)
        fguide = guide::SummaryController::New;

    // show guide.
    void* obj_guide = (*fguide)();
    remove_sub(ctlr_guide);
    ctlr_guide.set(obj_guide);
    add_sub(ctlr_guide);
    relayout();
    
    // proc guide.
    guide::ISummaryController* ctlr_summary = interface_cast(obj_guide, guide::ISummaryController);
    ctlr_summary->set_title(sel->content.text());
    ctlr_summary->set_summary(sel->summary);
    ctlr_summary->set_work(sel->work);
    
    // set select.
    ring.attach().set("current", sel);
    (*sel).emit(kRangeActivated);
}

void IndexView::act_ring_added(EventObj& evt)
{
    ui::AnnualRingSingle& ring = evt;
    ring.add_effect(qz::effect::Fadein());
}

void IndexView::reset_top()
{
    while (anl_funs.count() > 1)
        anl_funs.remove(core::index::last(anl_funs));
}

void IndexView::act_ranged_wae()
{
    reset_top();
}

void IndexView::act_ranged_auth()
{
    reset_top();
    
    ui::Instance<AnnualRingSingle> ring;
    ring->set_length(100);
    ring->set_radius(400);
    ring->set_sweep(cg::Angle(60));
    ring->set_ring(ui::Color::Green());
    ring->connect(kSignalRingRotated, _action(_class::act_ring_rotated), this);
    
    typedef ui::Instance<AnnualRingItem> item_type;
    
    {
        item_type item;
        item->content.set_text(tr(@"USER"));
        item->summary = tr(@"auth::add::summary");
        item->work = guide::auth::UserController::New;
        ring->add(item);
    }
    
    {
        item_type item;
        item->content.set_text(tr(@"GROUP"));
        item->work = guide::auth::GroupController::New;
        ring->add(item);
    }
    
    anl_funs.add(ring);
}

void IndexView::act_ranged_sapi()
{
    reset_top();
    
    ui::Instance<AnnualRingSingle> ring;
    ring->set_length(100);
    ring->set_radius(400);
    ring->set_sweep(cg::Angle(60));
    ring->set_ring(ui::Color::Green());
    ring->connect(kSignalRingRotated, _action(_class::act_ring_rotated), this);
    
    typedef ui::Instance<AnnualRingItem> item_type;
    
    {
        item_type item;
        item->content.set_text(tr(@"ALL"));
        item->summary = tr(@"sapi::all");
        item->work = guide::sapi::AllController::New;
        ring->add(item);
    }
    
    anl_funs.add(ring);
}

void IndexView::act_ranged_utils()
{
    reset_top();
}

void IndexView::act_ranged_sample()
{
    reset_top();
}

void IndexView::act_ranged_toolkit()
{
    reset_top();
    
    ui::Instance<AnnualRingSingle> ring;
    ring->set_length(100);
    ring->set_radius(400);
    ring->set_sweep(cg::Angle(60));
    ring->set_ring(ui::Color::Green());
    ring->connect(kSignalRingRotated, _action(_class::act_ring_rotated), this);
    
    typedef ui::Instance<AnnualRingItem> item_type;
    
    {
        item_type item;
        item->content.set_text(tr(@"COUNTER"));
        item->summary = tr(@"toolkit::counter");
        item->work = guide::toolkit::CounterController::New;
        ring->add(item);
    }
        
    anl_funs.add(ring);
}

IndexController::IndexController()
{
    
}

void IndexController::view_loaded()
{
    view().btn_logout.connect(kSignalButtonClicked, _action(_class::act_logout), this);
}

void IndexController::act_logout()
{
    context::User().logout();
}

WAE_END
