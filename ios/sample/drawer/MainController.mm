
# include "WSIFoundation.h"
# include "MainController.h"

WSIAPP_BEGIN

Drawer::Drawer()
{
    hide.set_text(@"CLOSE");
    add_sub(hide);
    hide.connect(kSignalButtonClicked, _action(Drawer::act_close), this);
    
    set_background(ui::Color::White());
}

void Drawer::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (flex)1 << (flex)1;
    lyt << lnr;
    CGRectLayoutHBox lyth(lyt << lnr);
    CGRectLayoutLinear lnrh(lyth);
    lnrh << (flex)1 << (flex)1 << (flex)1;
    lyth << lnrh;
    hide.set_frame(lyth << lnrh);
}

void Drawer::act_close()
{
    close();
}

MainView::MainView()
{
    left.set_text(@"L");
    right.set_text(@"R");
    top.set_text(@"T");
    bottom.set_text(@"B");
    
    add_sub(left);
    add_sub(right);
    add_sub(top);
    add_sub(bottom);
    
    set_background(ui::Color::Gray());
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds(), 5);
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (flex)1 << (flex)1 << (flex)1 << (flex)1 << (flex)1;
    lyt << lnr;
    left.set_frame(lyt << lnr);
    right.set_frame(lyt << lnr);
    top.set_frame(lyt << lnr);
    bottom.set_frame(lyt << lnr);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    view().left.connect(kSignalButtonClicked, _action(_class::act_left), this);
    view().right.connect(kSignalButtonClicked, _action(_class::act_right), this);
    view().top.connect(kSignalButtonClicked, _action(_class::act_top), this);
    view().bottom.connect(kSignalButtonClicked, _action(_class::act_bottom), this);
    
    view().drawer.set_length(100);
    connect(kSignalOrientationChanged, _action(Drawer::act_close), view().drawer);
}

void MainController::act_left()
{
    view().drawer.close(ui::nonanimate);
    view().drawer.set_position(CGRectPositionTypeLeft);
    view().drawer.open(view());
}

void MainController::act_right()
{
    view().drawer.close(ui::nonanimate);
    view().drawer.set_position(CGRectPositionTypeRight);
    view().drawer.open(view());
}

void MainController::act_top()
{
    view().drawer.close(ui::nonanimate);
    view().drawer.set_position(CGRectPositionTypeTop);
    view().drawer.open(view());
}

void MainController::act_bottom()
{
    view().drawer.close(ui::nonanimate);
    view().drawer.set_position(CGRectPositionTypeBottom);
    view().drawer.open(view());
}

WSIAPP_END
