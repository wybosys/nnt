
# include "WSIFoundation.h"
# include "MainController.h"
# include "GameCenterService.h"
# include "AppInformation.h"
# include "ICloudService.h"

WSIAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::White());
    
    btn_show_achs.set_text(@"SHOW ACHIEVEMENTS");
    btn_show_leader.set_text(@"SHOW LEADERBOARD");
    btn_show_inapp.set_text(@"SHOW INAPP PURCHASE ITEMS");
    btn_buy_inapp.set_text(@"BUY ONE INAPP");
    
    add_sub(btn_show_achs);
    add_sub(btn_show_leader);
    add_sub(btn_show_inapp);
    add_sub(btn_buy_inapp);
    
    btn_cloud_save.set_text(@"CLOUD SAVE");
    btn_cloud_load.set_text(@"CLOUD LOAD");
    txt_cloud_input.set_borderstyle(UITextBorderStyleRoundedRect);
    
    add_sub(btn_cloud_save);
    add_sub(btn_cloud_load);
    add_sub(txt_cloud_input);
    
    add_sub(ctlr_iad);
    add_sub(ctlr_adb);
    add_sub(ctlr_dmb);
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds(), 5);
    layout::linear lnr(lyt);
    lnr << (flex)1 << (flex)1 << (flex)1 << (flex)1 << (pixel)50 << (pixel)50 << (pixel)50;
    
    btn_show_achs.set_frame(lyt << lnr);
    btn_show_leader.set_frame(lyt << lnr);
    
    layout::hbox lytinapp(lyt << lnr);
    layout::linear lnrinapp(lytinapp);
    lnrinapp << (flex)1 << (flex)1;
    btn_show_inapp.set_frame(lytinapp << lnrinapp);
    btn_buy_inapp.set_frame(lytinapp << lnrinapp);
    
    layout::hbox lytcloud(lyt << lnr, 5);
    layout::linear lnrcloud(lytcloud);
    lnrcloud << (flex)2 << (flex)1 << (flex)1;
    txt_cloud_input.set_frame(lytcloud << lnrcloud);
    btn_cloud_save.set_frame(lytcloud << lnrcloud);
    btn_cloud_load.set_frame(lytcloud << lnrcloud);
    
    ctlr_iad.view().set_frame(lyt << lnr);
    ctlr_adb.view().set_frame(lyt << lnr);
    ctlr_dmb.view().set_frame(lyt << lnr);
}

MainController::MainController()
{
    set_orientation(UIOrientationEnableAll);
}

void MainController::view_loaded()
{
    view().btn_show_achs.connect(kSignalButtonClicked, _action(_class::act_show_achs), this);
    view().btn_show_leader.connect(kSignalButtonClicked, _action(_class::act_show_leader), this);
    view().btn_show_inapp.connect(kSignalButtonClicked, _action(_class::act_show_inapp), this);
    view().btn_buy_inapp.connect(kSignalButtonClicked, _action(_class::act_inapp_buy), this).background();
    view().btn_cloud_save.connect(kSignalButtonClicked, _action(_class::act_cloud_save), this);
    view().btn_cloud_load.connect(kSignalButtonClicked, _action(_class::act_cloud_load), this);
    
    game::GameCenter& gamec = game::GameCenter::getInstance();
    
    // must call back in background thread.
    // if you don't want get the remote score from gamecenter, choose thread mode at will.
    gamec.connect(kSignalUserLogin, _action(_class::act_gamecenter_login), this).background();
}

void MainController::act_gamecenter_login()
{
    // print gamer.
    game::GameCenter& gamec = game::GameCenter::getInstance();
    trace_msg(gamec.player_nickname());
    
    // set ach.
    game::Achievement ach(@"wsi.sample.game.ach.firstgot");
    trace_float(ach.percent());
    if (!ach.completed())
    {
        ach.set_value(bse::Application::Counter::Launch() / 2);
        ach.submit();
    }
    
    // set point.
    game::Leaderboard lb(@"wsi.sample.game.point");
    game::Score sco = lb.score();
    //game::Score sco;
    trace_float(sco.value());
    sco.set_value(sco.value() + 10);
    lb.submit(sco);
}

void MainController::act_show_achs()
{
    ui::Instance<game::AchievementsController> ctlr;
    present(ctlr);
}

void MainController::act_show_leader()
{
    ui::Instance<game::LeaderboardController> ctlr;
    present(ctlr);
}

void MainController::act_show_inapp()
{
    purchase::inapp::Items inapp;
    inapp.connect(kSignalSuccess, _action(_class::act_inapp_got), this);
    inapp.set_identifier(ns::String(@"wsi.sample.game.buy.onepoint"));
    inapp.update();
}

void MainController::act_inapp_got(EventObj& evt)
{
    ns::Array items(evt.result());
    for (uint i = 0; i < items.count(); ++i)
    {
        purchase::inapp::Item item(items[i]);
        ns::String msg = item.title() + @" ";
        msg += item.description() + @" ";
        msg += item.price();
        trace_msg(msg);
    }
}

void MainController::act_inapp_buy()
{
    purchase::inapp::Items inapp(ns::String(@"wsi.sample.game.buy.onepoint"));
    inapp.fetch();
    purchase::inapp::Item item = inapp.at(0);
    purchase::inapp::Service::getInstance().add(item);
}

void MainController::act_cloud_save()
{
    ns::String str = view().txt_cloud_input.text();
    if (str.is_empty())
    {
        core::Msgbox::warn(@"please input some text.");
        return;
    }
    
    cloud::iCloud::getInstance().set(@"wsi.sample.game.cloud.text", str);
}

void MainController::act_cloud_load()
{
    ns::String str = cloud::iCloud::getInstance().to_string(@"wsi.sample.game.cloud.text");
    view().txt_cloud_input.set_text(str);
}

WSIAPP_END
