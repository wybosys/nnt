
# include "Foundation+NNT.h"
# include "ImageController.h"

NNTAPP_BEGIN

ImageView::ImageView()
{
    set_background(ui::Color::White());
    
    add_sub(txt_url);
    add_sub(btn_load);
    add_sub(view_img);
    
    btn_load.set_text(@"LOAD");
}

void ImageView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (pixel)30 << (pixel)30;
    
    view_img.set_frame(lyt << lnr);
    txt_url.set_frame(lyt << lnr);
    btn_load.set_frame(lyt << lnr);
}

ImageController::ImageController()
{
    
}

void ImageController::view_loaded()
{
    view().btn_load.connect(kSignalButtonClicked, _action(_class::act_load), this);
}

void ImageController::act_load()
{
    view().view_img.load(ns::URL::String(view().txt_url.text()));
}

NNTAPP_END
