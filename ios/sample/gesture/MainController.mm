
# include "Foundation+NNT.h"
# include "MainController.h"
# include "ColorPalette.h"
# include "UIGesture+NNT.h"

NNTAPP_BEGIN

MainView::MainView()
{
    {
        ui::Instance<ui::Label> lbl;
        lbl->set_text(@"LONG");
        add_sub(*lbl);
        
        ui::gesture::LongPress ges;
        ges.connect(kSignalGestureActive, ^(NNTEventObj*) {
            trace_msg(@"long press");
        });
        lbl->set_gesture(ges);
    }
    
    {
        ui::Instance<ui::Label> lbl;
        lbl->set_text(@"TAP");
        add_sub(*lbl);
        
        ui::gesture::Tap ges;
        ges.connect(kSignalGestureActive, ^(NNTEventObj*) {
            trace_msg(@"tap");
        });
        lbl->set_gesture(ges);
    }
    
    {
        ui::Instance<ui::Label> lbl;
        lbl->set_text(@"SWIPE");
        add_sub(*lbl);
        
        {
            ui::gesture::Swipe ges;
            ges.connect(kSignalGestureActive, ^(NNTEventObj*) {
                trace_msg(@"swipe");
            });
            lbl->set_gesture(ges);
        }
        
        {
            ui::gesture::LongPress ges;
            ges.connect(kSignalGestureActive, ^(NNTEventObj*) {
                trace_msg(@"long press");
            });
            lbl->set_gesture(ges);
        }
    }
    
    {
        ui::Instance<ui::Label> lbl;
        lbl->set_text(@"PINCH");
        add_sub(*lbl);
        
        ui::gesture::Pinch ges;
        ges.connect(kSignalGestureActive, ^(NNTEventObj*) {
            trace_msg(@"pinch");
        });
        lbl->set_gesture(ges);
    }
    
    {
        ui::Instance<ui::Label> lbl;
        lbl->set_text(@"PAN");
        add_sub(*lbl);
        
        ui::gesture::Pan ges;
        ges.connect(kSignalGestureActive, ^(NNTEventObj*) {
            trace_msg(@"pan");
        });
        ges.connect(kSignalGestureChanged, ^(NNTEventObj*) {
            trace_msg(@"pan changed");
        });
        lbl->set_gesture(ges);
    }
    
    {
        ui::Instance<ui::Label> lbl;
        lbl->set_text(@"ROTATION");
        add_sub(*lbl);
        
        ui::gesture::Rotation ges;
        ges.connect(kSignalGestureActive, ^(NNTEventObj*) {
            trace_msg(@"rotate");
        });
        ges.connect(kSignalGestureChanged, ^(NNTEventObj*) {
            trace_msg(@"rotate changed");
        });
        lbl->set_gesture(ges);
    }
    
    ui::ViewsArray va = views();
    core::ColorWheel cw;
    for (uindex i = 0; i < va.arr.size(); ++i)
    {
        use<ui::Label> lbl = va[i];
        lbl->set_background(ui::Color::RGB(cw.next()));
    }
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds());
    layout::linear lnr(lyt);
    
    ui::ViewsArray va = views();
    for (uindex i = 0; i < va.arr.size(); ++i)
    {
        lnr << (flex)1;
    }
    
    for (uindex i = 0; i < va.arr.size(); ++i)
    {
        use<ui::Label> lbl = va[i];
        lbl->set_frame(lyt << lnr);
    }
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    
}

NNTAPP_END
