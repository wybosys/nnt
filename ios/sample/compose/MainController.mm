
# include "Foundation+NNT.h"
# include "MainController.h"
# include "UIEmailController.h"
# include "UISMSController.h"

NNTAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::White());
    
    btn_sms.set_text(@"SMS");
    btn_email.set_text(@"EMAIL");
    
    add_sub(btn_sms);
    add_sub(btn_email);
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (pixel)50 << (flex)1;
    
    lyt << lnr;
    CGRectLayoutHBox lytb(lyt << lnr);
    CGRectLayoutLinear lnrb(lytb);
    lnrb << (flex)1 << (flex)1;
    
    btn_sms.set_frame(lytb << lnrb);
    btn_email.set_frame(lytb << lnrb);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    view().btn_sms.connect(kSignalButtonClicked, _action(MainController::act_sms), this);
    view().btn_email.connect(kSignalButtonClicked, _action(MainController::act_email), this);
}

void MainController::act_sms()
{
    ui::SMSController sms;
    sms.add(@"13564918627");
    sms.set(@"LIBWSI TEST SMS.");
    sms.execute();
}

void MainController::act_email()
{
    ui::EmailController email;
    email.to(@"wybosys@gmail.com");
    email.set_body(@"Hello, WSI!");
    email.execute();
}

NNTAPP_END