
# include "WSIFoundation.h"
# include "MainController.h"
# include "iOSPrinter.h"
# include "TextRender.h"
# include "TextFormatter.h"

WSIAPP_BEGIN

MainView::MainView()
{
    add_sub(input);
    add_sub(print);
    
    print.set_text(@"PRINT");
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds(), 5);
    layout::linear lnr(lyt);
    lnr << (flex)1 << (pixel)50;
    input.set_frame(lyt << lnr);
    print.set_frame(lyt << lnr);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    view().print.connect(kSignalButtonClicked, _action(_class::act_print), this);
}

void MainController::act_print()
{    
    if (view().input.text().is_empty())
    {
        core::Confirm::info(@"INPUT is empty !");
        return;
    }
    
    driver::print::ns::Printer printer;
    instance_ref<driver::print::ns::PageRender> render;
    printer.set_render(render);
    
    instance_ref<TextFormatter> fmt;
    fmt->set_text(view().input.text());
    fmt->set_font(ui::Font::System(20));
    fmt->set_color(ui::Color::Black());
    fmt->set_startpage(0);
    fmt->set_contentedge(cg::Insets(24, 24, 24, 24));
    fmt->set_maximum_content_width(6 * 24);
    render->add(*fmt);
    
    printer.execute(view().print.frame(), view());
}

WSIAPP_END
