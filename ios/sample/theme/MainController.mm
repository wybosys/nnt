
# include "WSIFoundation.h"
# include "MainController.h"

WSIAPP_BEGIN

MainView::MainView()
{
    logo.set_frame(cg::Rect(cg::Size(128, 129)));
    add_sub(logo);
}

void MainView::layout_subviews()
{
    logo.move_center(bounds().center());
}

void MainView::theme(ui::Theme const& theme)
{
    set_background(theme.instance("main.background.color"));
    logo.set_image(theme.instance("logo"));
}

MainController::MainController()
{
    set_title(@"THEME");
    set_orientation(UIOrientationEnableAll);
    connect(kSignalViewAppear, _action(_class::act_appear), this);
}

void MainController::act_appear()
{
    ui::BarButtonItem black(@"BLACK", UIBarButtonItemStyleBordered);
    ui::BarButtonItem orange(@"ORANGE", UIBarButtonItemStyleBordered);
    
    black.connect(kSignalButtonClicked, _action(_class::act_black), this);
    orange.connect(kSignalButtonClicked, _action(_class::act_orange), this);
    
    ns::MutableArray arr;
    arr << black << orange;
    
    navigation().topbar().set_rightitems(arr);
}

void MainController::view_loaded()
{
    PASS;
}

void MainController::act_black()
{
    LoadTheme(@"black.theme");
}

void MainController::act_orange()
{
    LoadTheme(@"orange.theme");
}

void MainController::theme(ui::Theme const& theme)
{
    navigation().topbar().set_tint(theme.instance("navi.background.color"));
}

WSIAPP_END
