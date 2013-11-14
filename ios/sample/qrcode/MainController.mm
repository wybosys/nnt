
# include "Foundation+NNT.h"
# include "MainController.h"

NNTAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::White());
    
    img_origin.set_content(UIViewContentModeScaleAspectFill);
    img_gray.set_content(UIViewContentModeScaleAspectFill);
    
    add_sub(ctlr_reader);
    add_sub(img_origin);
    add_sub(img_gray);
    add_sub(txt_result);
    
    ctlr_reader.connect(kSignalTry, _action(_class::act_try), this);
    txt_result.set_readonly();
}

void MainView::layout_subviews()
{
    ctlr_reader.view().set_frame(bounds());
    
    CGRectLayoutVBox lyt(bounds(), 5);
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)2 << (flex)1 << (flex).5;
    lyt << lnr;
    CGRectLayoutHBox lyt_reg(lyt << lnr, 5);
    CGRectLayoutLinear lnr_reg(lyt_reg);
    lnr_reg << (flex)1 << (flex)1 << (flex)1;
    lyt_reg << lnr_reg;
    img_origin.set_frame(lyt_reg << lnr_reg);
    img_gray.set_frame(lyt_reg << lnr_reg);
    
    txt_result.set_frame(lyt << lnr);
}

void MainView::act_try(EventObj& evt)
{
    img_origin.set_image(ui::Image::Img(evt.result()));
    img_gray.set_image(ui::Image::Img((void*)evt.data()));
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    //view().ctlr_reader.set_continuable(false);
    view().ctlr_reader.connect(kSignalSuccess, _action(_class::act_success), this);
}

void MainController::act_success(EventObj& evt)
{
    ns::String str(ns::Data::Obj(evt.result()));
    view().txt_result.append(str);
    view().txt_result.scrollto_end();
}

NNTAPP_END
