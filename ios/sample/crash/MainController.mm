
# include "Foundation+NNT.h"
# include "MainController.h"

NNTAPP_BEGIN

MainView::MainView()
{
    crash.set_text(@"CRASH");
    add_sub(crash);
    
    crash.connect(kSignalButtonClicked, ^(NNTEventObj *) {
        NSObject* obj = [[NSObject alloc] init];
        [obj crash];
        safe_release(obj);
    });
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds());
    layout::linear lnr(lyt);
    lnr << (flex)1 << (flex)1 << (flex)1;
    lyt << lnr;
    crash.set_frame(lyt << lnr);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{

}

NNTAPP_END
