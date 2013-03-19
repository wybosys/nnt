
# import "WSIFoundation.h"
# import "MainController.h"
# import "CIFilter+WSI.h"

WSIAPP_BEGIN

MainView::MainView()
: table(NULL)
{
    name = @"lenna.bmp";    
    image.load(name);
    
    imageview.set_content(UIViewContentModeScaleAspectFit);
    imageview.set_image(image);
    //imageview.load(ns::URL(@"http://hiphotos.baidu.com/lyxsyz7964555/pic/item/0b08bf859f6510f10df4d20e.jpg"), false);

    btn_process.set_text(@"PROCESS");
    btn_process.connect(kSignalButtonClicked, _action(MainView::act_process), this);
    
    btn_reset.set_text(@"RESET");
    btn_reset.connect(kSignalButtonClicked, _action(MainView::act_reset), this);
    
    table = [[UINavigationTableViewController alloc] initWithRootTitle:@"FILTERS"];
    add_subview(table.view);
    
    // list all.
    ns::Array filters = vision::ci::Filter::SystemFilters();
    table.rootTable.datas = filters;
    table.view.backgroundColor = [UIColor whiteColor];
    [table.rootTable connect:kSignalSelectChanged action:_action(MainView::act_filter) target:this];
    
    add_sub(btn_process);
    add_sub(btn_reset);
    add_sub(imageview);
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (pixel)50 << (flex)1;
    
    imageview.set_frame(lyt << lnr);
    
    CGRectLayoutHBox hbtns(lyt << lnr);
    CGRectLayoutLinear lbtns(hbtns);
    lbtns << (flex)1 << (flex)1;
    btn_process.set_frame(hbtns << lbtns);
    btn_reset.set_frame(hbtns << lbtns);
    
    CGRectLayoutVBox hlst(lyt << lnr);
    CGRectLayoutLinear llst(hlst);
    llst << (flex)1;
    table.view.frame = hlst << llst;
}

void MainView::act_process()
{
    if ([table.visibleViewController supportStore] == NO)
        return;
    id obj = [table.visibleViewController storeFind:@"filter"];
    if (obj == nil)
        return;
    vision::ci::Filter filter(obj);
    WCGImage* img = filter.process(image);
    imageview.set_image(ui::Image(img));
}

void MainView::act_reset()
{
    image.set_null();
    image.load(name);
    imageview.set_image(image);
}

void MainView::act_filter(EventObj& evt)
{
    WSIUITableViewCell* cell = (WSIUITableViewCell*)evt.result();
    NSString* filter = cell.textLabel.text;
    WSIUITableViewController* ctlr = [[WSIUITableViewController alloc] init];   
    [ctlr connect:kSignalSelectChanged action:_action(MainView::act_value) target:this];
    ctlr.title = filter;    
    
    vision::ci::Filter obj(filter);
    [ctlr storeSet:@"filter" obj:obj];
    ctlr.datas = obj.attributes();
    
    [table pushViewController:ctlr animated:YES];
    [ctlr release];
}

void MainView::act_value(EventObj& evt)
{
    WSIUITableViewCell* cell = (WSIUITableViewCell*)evt.result();
    NSString* prop = cell.textLabel.text;
    vision::ci::Filter obj([(id)evt.sender() storeFind:@"filter"]);
    id settings = obj.instance_settings(prop);
    if (settings == nil)
        return;
    WSIUIViewController* ctlr = [[WSIUIViewController alloc] init];
    [ctlr storeSet:@"filter" obj:obj];
    ctlr.title = prop;
    ctlr.view = settings;
    ctlr.view.backgroundColor = [UIColor whiteColor];
    [table pushViewController:ctlr animated:YES];
    [ctlr release];
}

void MainController::view_loaded()
{
    
}

WSIAPP_END

WSIAPP_END_OBJC