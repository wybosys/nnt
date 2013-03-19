
# include "Foundation+NNT.h"
# include "MainController.h"

// zlib.
# include <zlib.h>

NNTAPP_BEGIN

MainView::MainView()
{
    input.set_background(ui::Color::Gray());
    output.set_background(ui::Color::Orange());
    result.set_background(ui::Color::Green());
    
    add_sub(input);
    add_sub(output);
    add_sub(result);
    add_sub(comp);
    add_sub(uncomp);
    
    comp.set_text(@"COMP");
    uncomp.set_text(@"UNCOMP");
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds(), 5);
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (flex)1 << (flex)1 << (pixel)30 << (pixel)30;
    
    input.set_frame(lyt << lnr);
    output.set_frame(lyt << lnr);
    result.set_frame(lyt << lnr);
    comp.set_frame(lyt << lnr);
    uncomp.set_frame(lyt << lnr);
}

void MainController::view_loaded()
{
    view().set_background(ui::Color::White());
    view().comp.connect(kSignalButtonClicked, _action(_class::act_comp), this);
    view().uncomp.connect(kSignalButtonClicked, _action(_class::act_uncomp), this);
}

void MainController::act_comp()
{
    core::data da = core::type_cast<core::data>(view().input.text());
    ulong buflen = compressBound(da.length());
    core::data buf(buflen);
    if (Z_OK == compress((byte*)buf.bytes(), &buflen, (byte*)da.bytes(), da.length()))
    {
        ui::AlertView alert(@"info", @"compress", @"ok");
        alert.show();
        
        buf.set_length(buflen);
        view().output.set_text(core::present_cast<core::string>(buf));
    }
    else
    {
        ui::AlertView alert(@"info", @"failed to compress", @"ok");
        alert.show();
    }
}

void MainController::act_uncomp()
{
    core::data da = core::present_cast<core::data>(core::type_cast<core::string>(view().output.text()));   
    ulong buflen = 1024;
    core::data buf(buflen);
    if (Z_OK == uncompress((byte*)buf.bytes(), &buflen, (byte*)da.bytes(), da.length()))
    {
        ui::AlertView alert(@"info", @"uncompress", @"ok");
        alert.show();
        
        buf.set_length(buflen);
        view().result.set_text(core::type_cast<ns::String>(buf));
    }
    else
    {
        ui::AlertView alert(@"info", @"failed to uncompress", @"ok");
        alert.show();
    }
}

NNTAPP_END