
# include "Foundation+NNT.h"
# include "MainController.h"
# include "ColorPalette.h"

NNTAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::Orange());
    
    add_sub(grid);
    
    grid.set_rows(4);
    grid.set_cols(4);
    
    ui::Label* lbl = ui::Label::New();
    lbl->set_text(@"LABEL 1");
    grid.add(lbl, 0, 0);
    lbl->Release();
    
    lbl = ui::Label::New();
    lbl->set_text(@"LABEL 2");
    grid.add(lbl, 1, 1);
    lbl->Release();
    
    lbl = ui::Label::New();
    lbl->set_text(@"LABEL 3");
    grid.add(lbl, 2, 2);
    lbl->Release();
    
    lbl = ui::Label::New();
    lbl->set_text(@"LABEL 4");
    grid.add(lbl, 3, 3);
    lbl->Release();
    
    ui::BevelButton* btn = ui::BevelButton::New();
    btn->set_text(@"CLICK");
    grid.add(btn, 0, 3);
    btn->connect(kSignalButtonClicked, _action(_class::act_click), this);
    btn->Release();
    
    cg::MutableLineStyle ls;
    ls.set_color(cg::Color::White());
    grid.set_rowline(ls);
}

static int __gs_index = 0;
core::ColorWheel __gs_cw;

void MainView::act_click()
{
    ui::Label lbl(grid.object_at(__gs_index, __gs_index));
    lbl.set_background(ui::Color::RGB(__gs_cw.next()));
    
    ++__gs_index;
    if (__gs_index >= 4)
        __gs_index = 0;
}

void MainView::layout_subviews()
{
    grid.set_frame(bounds());
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    
}

NNTAPP_END
