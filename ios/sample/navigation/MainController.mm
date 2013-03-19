
# import "WSIFoundation.h"
# import "MainController.h"

WSIAPP_BEGIN

MainController::MainController()
{
    push(ctlr, false);
    
    topbar().set_background(wsi::cg::Fill(wsi::cg::Image(@"navbar.png")));
    topbar().set_tint(wsi::ui::Color::Orange());
    
    ctlr.connect(kSignalViewAppear, _action(MainController::act_appear), this);
}

void MainController::act_appear()
{
    {
        ui::ClearButton btn;
        btn.roundrect();
        btn.set_image(ui::Image(@"refresh.png"));
        btn.image().set_content(UIViewContentModeScaleAspectFit);
        btn.set_frame(0, 0, topbar().height(), topbar().height());
        ui::BarButtonItem item(btn);
        item.connect(kSignalButtonClicked, _action(MainController::act_click), this);
        
        ns::MutableArray items;
        items.add(item);
        topbar().set_rightitems(items);
    }
 
    {
        ui::ClearButton btn;
        btn.roundrect();
        btn.set_image(ui::Image(@"refresh.png"));
        btn.image().set_content(UIViewContentModeScaleAspectFit);
        btn.set_frame(0, 0, topbar().height(), topbar().height());
        ui::BarButtonItem item(btn);
        item.connect(kSignalButtonClicked, _action(MainController::act_click), this);
        
        ns::MutableArray items;
        items.add(item);
        topbar().set_leftitems(items);
    }
}

void MainController::act_click()
{
    trace_msg(@"clicked");
}

WSIAPP_END