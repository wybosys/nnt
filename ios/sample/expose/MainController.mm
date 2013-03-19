
# include "Foundation+NNT.h"
# include "MainController.h"

NNTAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::White());
    
    add_sub(hor);
    
    hor.set_background(ui::Color::Gray());
    //hor.set_aligncenter(false);
    hor.set_deceleration_rate(0);
    hor.set_preffered_count(1.5);
    
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds());
    layout::linear lnr(lyt);
    lnr << (pixel)160 << (flex)1;
    
    hor.set_frame(lyt << lnr);
}

MainController::MainController()
{

}

void MainController::view_loaded()
{
    view().hor.set_count(3);
    
    for (uint i = 0; i < view().hor.count(); ++i)
    {
        ui::Instance<ui::ImageView> img;
        img->set_image(ui::Image(@"logo@114.png"));
        view().hor.add_item(img);
    }
    
    view().hor.relayout_items();
}

NNTAPP_END
