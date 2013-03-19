
# include "Foundation+NNT.h"
# include "MainController.h"

NNTAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::White());
    
    suggest.set_background(ui::Color::Green());
    history.set_background(ui::Color::Blue());
    
    add_sub(suggest);
    add_sub(history);
    
    suggest.items.push_back(@"A");
    suggest.items.push_back(@"B");
    suggest.items.push_back(@"C");
    suggest.items.push_back(@"D");
    suggest.reload();
    
    history.set_identity(@"history");
    history.set_limit(3);
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds(), 5);
    CGRectLayoutLinear lnr(lyt);
    lnr << (pixel)50 << (pixel)50 << (flex)1;
    
    suggest.set_frame(lyt << lnr);
    history.set_frame(lyt << lnr);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    
}

NNTAPP_END