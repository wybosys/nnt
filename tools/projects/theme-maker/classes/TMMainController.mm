
# import <wsi/WSIFoundation.h>
# import "TMMainController.h"
# import "TMColorController.h"
# import "TMRAWController.h"
# import "TMImageController.h"
# import "TMGradientController.h"

WSIAPP_BEGIN_OBJC

using namespace ::wsi;
using namespace ::wsi::ui;

@interface TMMainView : WSINSView {
   
    
    ListView<> *lst_avail;        
    TabView<> *tab_obj;
}

@property (nonatomic, readonly) PushButton *btn_open, *btn_new, *btn_save, *btn_reveal;
@property (nonatomic, readonly) PushButton *btn_add, *btn_del, *btn_modify;
@property (nonatomic, readonly) TextField<> *txt_path, *txt_key;
@property (nonatomic, readonly) ListView<> *lst_avail; 
@property (nonatomic, readonly) TabView<> *tab_obj;

@end

@implementation TMMainView

@synthesize btn_open, btn_new, btn_save, btn_reveal;
@synthesize btn_add, btn_del, btn_modify;
@synthesize txt_path, txt_key;
@synthesize lst_avail;
@synthesize tab_obj;

- (id)initWithZero {
    self = [super initWithZero];
    
    btn_open = new PushButton;
    btn_new = new PushButton;
    btn_save = new PushButton;
    btn_reveal = new PushButton;
    btn_add = new PushButton;
    btn_del = new PushButton;
    btn_modify = new PushButton;
    txt_path = new TextField<>;
    txt_key = new TextField<>;
    lst_avail = new ListView<>;
    tab_obj = new TabView<>;
    
    btn_open->set_title(@"OPEN");
    btn_new->set_title(@"NEW");
    btn_save->set_title(@"SAVE");
    btn_reveal->set_title(@"REVEAL");
    btn_add->set_title(@"ADD");
    btn_del->set_title(@"DEL");
    btn_modify->set_title(@"MODIFY");
    
    lst_avail->add_col(@"KEY");
    
    wsi::ns::MutableArray tabs;
    TMImageController* ctlr_image = [[TMImageController alloc] init];
    TMGradientController* ctlr_grad = [[TMGradientController alloc] init];
    TMColorController* ctlr_color = [[TMColorController alloc] init];
    TMRawController* ctlr_raw = [[TMRawController alloc] init];
    tabs << ctlr_image << ctlr_grad << ctlr_color << ctlr_raw;
    [ctlr_image release];
    [ctlr_grad release];
    [ctlr_color release];
    [ctlr_raw release];
    tab_obj->set_controllers(tabs);
    
    [self addSubview:*btn_open];
    [self addSubview:*btn_new];
    [self addSubview:*btn_save];
    [self addSubview:*btn_reveal];
    [self addSubview:*btn_add];
    [self addSubview:*btn_del];
    [self addSubview:*btn_modify];
    [self addSubview:*txt_path];
    [self addSubview:*txt_key];
    [self addSubview:*lst_avail];
    [self addSubview:*tab_obj];
        
    return self;
}

- (void)dealloc {
    delete btn_open; 
    delete btn_new; 
    delete btn_save;
    delete btn_reveal;
    delete btn_add;
    delete btn_del;
    delete btn_modify;
    delete txt_path;
    delete txt_key;
    delete lst_avail;
    delete tab_obj;
    [super dealloc];
}

- (void)layoutSubviews {
    lb::CGRectLayoutVBox lyt(self.bounds, 5);    
        
    CGRectLayoutLinear lnr(lyt);
    lnr << (wsi::pixel)30 << (wsi::flex)1;        
    lb::CGRectLayoutVBox lyt_sel(lyt << lnr);
    CGRectLayoutHBox lyt_action(lyt << lnr);
    
    CGRectLayoutLinear lnr_sel(lyt_sel);
    lnr_sel << (wsi::flex)1;
    
    CGRectLayoutHBox lyt_open(lyt_sel << lnr_sel);    
    CGRectLayoutLinear lnr_open(lyt_open);
    lnr_open << (pixel)70 << (pixel)70 << (flex)1 << (pixel)100 << (pixel)70;;
    btn_open->set_frame(lyt_open << lnr_open);
    btn_new->set_frame(lyt_open << lnr_open);
    txt_path->set_frame(lyt_open << lnr_open);
    btn_save->set_frame(lyt_open << lnr_open);        
    btn_reveal->set_frame(lyt_open << lnr_open);
    
    CGRectLayoutLinear lnr_action(lyt_action);
    lnr_action << (wsi::flex)1 << (wsi::flex)1;
    lst_avail->set_frame(lyt_action << lnr_action);
    
    lb::CGRectLayoutVBox lyt_edit(lyt_action << lnr_action);
    CGRectLayoutLinear lnr_edit(lyt_edit);    
    lnr_edit << (wsi::pixel)30 << (wsi::pixel)5 << (wsi::pixel)40 << (wsi::pixel)5 << (wsi::flex)1;
    
    txt_key->set_frame(lyt_edit << lnr_edit << CGMarginMake(0, 0, 5, 0));
    lyt_edit << lnr_edit;
    
    CGRectLayoutHBox lyt_editbtns(lyt_edit << lnr_edit);
    lyt_edit << lnr_edit;
    lb::CGRectLayoutVBox lyt_editsel(lyt_edit << lnr_edit);
    
    CGRectLayoutLinear lnr_editbtns(lyt_editbtns);
    lnr_editbtns << (wsi::flex)1 << (wsi::pixel)70 << (wsi::flex)1 << (wsi::pixel)70 << (wsi::flex)1 << (wsi::pixel)80 << (wsi::flex)1;
    lyt_editbtns << lnr_editbtns;
    btn_add->set_frame(lyt_editbtns << lnr_editbtns);
    lyt_editbtns << lnr_editbtns;
    btn_del->set_frame(lyt_editbtns << lnr_editbtns);
    lyt_editbtns << lnr_editbtns;
    btn_modify->set_frame(lyt_editbtns << lnr_editbtns);
    
    CGRectLayoutLinear lnr_editsel(lyt_editsel);
    lnr_editsel << (wsi::flex)1;
    tab_obj->set_frame(lyt_editsel << lnr_editsel);
}

@end

@implementation TMMainController

- (void)dealloc {
    [load_path release];
    [save_path release];
    safe_release(theme);
    [super dealloc];
}

- (void)loadView {
    TMMainView* view = [[TMMainView alloc] initWithZero];
    self.view = view;
    [view release];
}

- (void)viewIsLoading {
    TMMainView* view = (TMMainView*)self.view;
    view.btn_open->connect(kSignalAction, @selector(act_open), self);
    view.btn_new->connect(kSignalAction, @selector(act_new), self);
    view.btn_save->connect(kSignalAction, @selector(act_save), self);
    view.btn_reveal->connect(kSignalAction, @selector(act_reveal), self);
    view.lst_avail->connect(kSignalSelectChanged, @selector(act_selected:), self);
    view.btn_add->connect(kSignalAction, @selector(act_add), self);
    view.btn_del->connect(kSignalAction, @selector(act_del), self);
    view.btn_modify->connect(kSignalAction, @selector(act_modify), self);
}

- (void)act_open {
    TMMainView* view = (TMMainView*)self.view;
    NSOpenPanel* panel = [NSOpenPanel openPanel];
    [panel setCanChooseFiles:YES];
    NSInteger clicked = [panel runModal];
    if (clicked == NSFileHandlingPanelOKButton) {
        [::NSObject refobjSet:&load_path ref:panel.URL];
        view.txt_path->set_value(load_path);
        [self open:load_path];
    }
}

- (void)act_new {
    TMMainView* view = (TMMainView*)self.view;
    NSSavePanel* panel = [NSSavePanel savePanel];
    NSInteger clicked = [panel runModal];
    if (clicked == NSFileHandlingPanelOKButton) {
        [::NSObject refobjSet:&load_path ref:panel.URL];
        view.txt_path->set_value(load_path);
        [self open:load_path];
    }
}

- (void)act_save {
    [theme flush];
}

- (void)act_reveal {
    if (load_path isnil_)
        return;
    NSWorkspace* wk = [NSWorkspace sharedWorkspace];
    [wk selectFile:[load_path relativePath] inFileViewerRootedAtPath:[load_path relativePath]];
}

- (void)open:(NSURL*)url {
    // clear.

    safe_release(theme);
    theme = [[UITheme alloc] init];
    if (NO == [theme loadTheme:[url relativePath] type:WSIDirectoryTypeAbsolute]) {
        zero_release(theme);
        return;
    }
 
    [self refresh:YES];
}

- (void)refresh:(BOOL)r {
    TMMainView* view = (TMMainView*)self.view;

    // update list.
    ::NSArray* keys = [theme allKeys];
    view.lst_avail->set_data(keys);
    view.lst_avail->reload(r);
}

- (void)act_selected:(WSIEventObj*)evt {
    TMMainView* view = (TMMainView*)self.view;
    ListView<>* table = (ListView<>*)evt.sender;
    ::NSString* key = table->content_at(table->selected_row());
    view.txt_key->set_text(key);
    id obj = [theme instanceObjectByString:key];
    trace_msg(::wsi::tostr(object_getClassName(obj)));
    
    if ([obj isKindOfClass:[WCGImage class]]) {
        view.tab_obj->select(@"IMAGE");
        TMDataController* ctlr = (TMDataController*)view.tab_obj->selected();
        ctlr.dataObject = obj;
    } else if ([obj isKindOfClass:[::NSString class]]) {
        view.tab_obj->select(@"RAW");
        TMDataController* ctlr = (TMDataController*)view.tab_obj->selected();
        ctlr.dataObject = obj;
    } else if ([obj isKindOfClass:[WCGColor class]]) {
        view.tab_obj->select(@"COLOR");
        TMDataController* ctlr = (TMDataController*)view.tab_obj->selected();
        ctlr.dataObject = obj;
    } else {
        view.tab_obj->select(@"RAW");
        NSData* da = [theme dataForValue:key];
        ::NSString* str = [[::NSString alloc] initWithBytes:[da bytes] length:[da length] encoding:NSASCIIStringEncoding];
        TMDataController* ctlr = (TMDataController*)view.tab_obj->selected();
        ctlr.dataObject = str;
        [str release];
    }
}

- (void)act_add {
    TMMainView* view = (TMMainView*)self.view;
    ::NSString* key = view.txt_key->get_text();
    if (![key notEmpty])
        return;
    id obj = ((TMDataController*)view.tab_obj->selected()).dataObject;
    if (obj isnil_)
        return;    
    [theme storeObjectString:key obj:obj];
    [self refresh:NO];
}

- (void)act_del {
    TMMainView* view = (TMMainView*)self.view;
    ::NSString* key = view.txt_key->get_text();
    if (![key notEmpty])
        return;
    [theme removeValue:key];
    [self refresh:NO];
}

- (void)act_modify {
    TMMainView* view = (TMMainView*)self.view;
    ::NSString* key = view.txt_key->get_text();
    if (![key notEmpty])
        return;
    id obj = ((TMDataController*)view.tab_obj->selected()).dataObject;
    if (obj isnil_)
        return;    
    [theme storeObject:core::tostr(key).c_str() obj:obj];
    [self refresh:NO];
}

@end

WSIAPP_END_OBJC

WSIAPP_BEGIN

MainView::MainView()
{
    
}

void MainView::layout_subviews()
{
    
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    
}

WSIAPP_END
