
# include "WSIFoundation.h"
# include "MainController.h"
# include "AlphabetFlow.h"

WSIAPP_BEGIN

using namespace ::wsi;

ns::AlphabetFlow af;

Cell::Cell()
{    
    add_sub(img);
    img.set_image(wsi::ui::Image(@"logo@57.png"));
    set_background(cg::Gradient(cg::Color::White(), cg::Color::Black(), 0, 4, M_PI_2));
}

Cell::~Cell()
{
    trace_msg(@"delete a cell.");
}

void Cell::layout_subviews()
{
    wsi::CGRectLayoutHBox lyt(bounds());
    wsi::CGRectLayoutLinear lnr(lyt);
    lnr << (wsi::flex)1 << (wsi::pixel)bounds().size.height;
    lyt << lnr;
    img.set_frame(lyt << lnr);
}

void Cell::update()
{
    ns::String var = (id)object();
    this->text().set_text(var);
    str = var;
}

Table::Table()
{
    top.set_background(wsi::ui::Color::Red());
    bottom.set_background(wsi::ui::Color::Blue());
    
    top.normal_text().set_text(@"TOP HEADER");
    top.action_text().set_text(@"TOP ACTION HEADER");
    bottom.normal_text().set_text(@"BOTTOM HEADER");
    bottom.action_text().set_text(@"BOTTOM ACTION HEADER");
    
    view().set_topheader(top);
    view().set_bottomheader(bottom);
    
    wsi::ui::TableSection* sec = new wsi::ui::TableSection;
    sec->header = @"MAIN";
    add(sec);
    sec->drop();
    
    for (uint i = 0; i < 6; ++i) 
    {
        if (i < 3)
            sec->add(af.next()).editable = true;
        else
            sec->add(af.next()).editable = false;
    }
}

::wsi::Object* Table::makecell(IndexPath const& idx) const
{
    Cell* cell = Cell::New();
    return cell;
}

MainView::MainView()
{
    add_sub(tab);
}

void MainView::layout_subviews()
{
    tab.view().set_frame(bounds());
}

void MainController::view_loaded()
{
    view().tab.connect(kSignalSelectChanged, _action(MainController::act_selected), this);
    view().tab.connect(kSignalItemRemoved, _action(MainController::act_removed), this);
    view().tab.top.connect(kSignalAction, _action(MainController::act_top), this);
    view().tab.bottom.connect(kSignalAction, _action(MainController::act_bottom), this);
}

void MainController::act_selected(wsi::EventObj& evt)
{
    //Cell* cell = (Cell*)evt.result();
    Table::IndexPath idx((id)evt.data());
    trace_int(idx.row());
    trace_int(idx.section());
    
    view().tab.view().set_editable(!view().tab.view().is_editable());
}

void MainController::act_removed(wsi::EventObj& evt)
{
    Cell* cell = (Cell*)evt.result();
    trace_msg(cell->str);
    
    view().tab.view().set_editable(!view().tab.view().is_editable());
}

void MainController::act_top(wsi::EventObj &)
{
    trace_msg(@"TOP REFRESH");
}

void MainController::act_bottom(wsi::EventObj &)
{
    trace_msg(@"BOTTOM REFRESH");
    
    wsi::ui::TableSection* sec = new wsi::ui::TableSection;
    sec->header = @"ADD";
    for (uint i = 0; i < 12; ++i)
        sec->add(af.next());
    view().tab.add(sec);
    sec->drop();
    view().tab.reload();
}

WSIAPP_END