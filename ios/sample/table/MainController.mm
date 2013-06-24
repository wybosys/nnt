
# include "Foundation+NNT.h"
# include "MainController.h"
# include "AlphabetFlow.h"

NNTAPP_BEGIN

ns::AlphabetFlow af;

Cell::Cell()
{    
    add_sub(img);
    img.set_image(ui::Image(@"logo@57.png"));
    set_background(cg::Gradient(cg::Color::White(), cg::Color::Black(), 0, 4, M_PI_2));
}

Cell::~Cell()
{
    trace_msg(@"delete a cell.");
}

void Cell::layout_subviews()
{
    CGRectLayoutHBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (pixel)bounds().size.height;
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
    top.set_background(ui::Color::Red());
    bottom.set_background(ui::Color::Blue());
    
    top.normal_text().set_text(@"TOP HEADER");
    top.action_text().set_text(@"TOP ACTION HEADER");
    bottom.normal_text().set_text(@"BOTTOM HEADER");
    bottom.action_text().set_text(@"BOTTOM ACTION HEADER");
    
    view().set_topheader(top);
    view().set_bottomheader(bottom);
    
    ui::TableSection* sec = new ui::TableSection;
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

::nnt::Object* Table::makecell(IndexPath const& idx) const
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

void MainController::act_selected(EventObj& evt)
{
    //Cell* cell = (Cell*)evt.result();
    Table::IndexPath idx((id)evt.data());
    trace_int(idx.row());
    trace_int(idx.section());
    
    view().tab.view().set_editable(!view().tab.view().is_editable());
}

void MainController::act_removed(EventObj& evt)
{
    Cell* cell = (Cell*)evt.result();
    trace_msg(cell->str);
    
    view().tab.view().set_editable(!view().tab.view().is_editable());
}

void MainController::act_top(EventObj &)
{
    trace_msg(@"TOP REFRESH");
}

void MainController::act_bottom(EventObj &)
{
    trace_msg(@"BOTTOM REFRESH");
    
    ui::TableSection* sec = new ui::TableSection;
    sec->header = @"ADD";
    for (uint i = 0; i < 12; ++i)
        sec->add(af.next());
    view().tab.add(sec);
    sec->drop();
    view().tab.reload();
}

NNTAPP_END