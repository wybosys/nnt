
# include "wae.h"
# include "WaeController.h"
# include "QzEffect.h"

WAE_BEGIN_NS(guide)

SummaryView::SummaryView()
{
    btn_title.set_text(ui::Color::Black());
    
    add_sub(btn_title);
    add_sub(txt_summary);
    
    txt_summary.set_readonly();
}

void SummaryView::layout_subviews()
{
    layout::vbox lyt(bounds());
    layout::linear lnr(lyt);
    lnr << (flex)1 << (pixel)50 << (flex)1;
    
    lyt << lnr;
    
    btn_title.set_frame(lyt << lnr);
    txt_summary.set_frame(lyt << lnr);
}

SummaryController::SummaryController()
{
    
}

void SummaryController::view_loaded()
{
    view().btn_title.connect(kSignalButtonClicked, _action(_class::act_execute), this);
}

void SummaryController::set_title(ns::String const& str)
{
    view().btn_title.set_text(str);
}

void SummaryController::set_summary(ns::String const& str)
{
    view().txt_summary.set_text(str);
}

void SummaryController::set_work(work_type const& wk)
{
    _work = wk;
    view().btn_title.set_enable(_work);
}

class WorkDesk
: public ui::Desktop
{
public:
    
    WorkDesk()
    {
        cg::Shadow().apply(navi.view());
        
        add_sub(navi);
        
        set_autoclose(true);
    }
    
    void layout_subviews()
    {
        layout::hbox lyt(bounds());
        layout::linear lnr(lyt);
        lnr << (flex)1 << (flex)3;
        lyt << lnr;
        navi.view().set_frame(lyt << lnr);
    }
    
    ui::NavigationController navi;
    
};

void SummaryController::act_execute()
{ 
    ui::Instance<WorkDesk> desk;
    
    {
        instance_ref<qz::effect::SlideOut> eff;
        eff->direction = qz::effect::SlideOut::RIGHT;
        desk->set_close(*eff);
    }
    
    {
        instance_ref<qz::effect::Slide> eff;
        eff->direction = qz::effect::Slide::RIGHT;
        desk->set_show(*eff);
    }
    
    ui::AnyController work((*_work)(), true);
    work.set_title(view().btn_title.title().text());
    desk->navi.push(work);
    desk->show();
}

WorkView::WorkView()
{

}

void WorkView::layout_subviews()
{
    
}

WorkController::WorkController()
{
    
}

WorkController::~WorkController()
{
    
}

void WorkController::view_loaded()
{
    
}

WAE_END_NS
