
# include "Foundation+NNT.h"
# include "MainController.h"
# include "QuickLooker.h"

NNTAPP_BEGIN

MainView::MainView()
{
    show.set_text(@"SHOW");
    add_sub(show);
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (pixel)50 << (flex)1;
    
    lyt << lnr;
    show.set_frame(lyt << lnr);
}

MainController::MainController()
{

}

void MainController::view_loaded()
{
    view().show.connect(kSignalButtonClicked, _action(_class::act_show), this);
}

void MainController::act_show()
{
    ui::Navigatilize<sys::QuickLooker> looker;
    
    ns::MutableArray arr;
    arr << ns::URL::Bundle(@"docs.bundle/AppStore.rtf") << ns::URL::Bundle(@"docs.bundle/apple.jpg") << ns::URL::Bundle(@"docs.bundle/h2.pdf");
    looker->set_items(arr);
    looker->reload();
    
    looker->set_selection(1);
    
    present(looker);
}

NNTAPP_END
