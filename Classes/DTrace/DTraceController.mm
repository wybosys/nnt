
# import "Core.h"
# import "DTraceController.h"
# import "WSILua.h"
# import "Layout.h"
# import "App.h"
# import "DTraceLibrary.h"
# import "Console+WSI.h"

WSI_USINGCXXNAMESPACE;

WSI_BEGIN_OBJC

@interface DTraceView : WSIUIView

@property (nonatomic, readonly) WSIUITextField* input;
@property (nonatomic, readonly) WSIUITextView* output;
@property (nonatomic, readonly) UIBevelButton *run, *close;

@end

@implementation DTraceView

@synthesize input, output, run, close;

- (id)initWithZero {
    self = [super initWithZero];
    
    self.backgroundColor = [UIColor whiteColor];
    
    input = [[WSIUITextField alloc] initWithZero];
    output = [[WSIUITextView alloc] initWithZero];
    run = [[UIBevelButton alloc] initWithZero];
    close = [[UIBevelButton alloc] initWithZero];
    
    run.text = @"▶";
    close.text = @"▲";
    
    input.borderStyle = UITextBorderStyleRoundedRect;
    input.clearsOnBeginEditing = NO;
    output.editable = NO;
    
    [self addSubview:input];
    [self addSubview:output];
    [self addSubview:run];
    [self addSubview:close];
    
    return self;
}

- (void)dealloc {
    safe_release(input);
    safe_release(output);
    safe_release(run);
    safe_release(close);
    
    [super dealloc];
}

- (void)layoutSubviews {
    CGRectLayoutVBox lyt(self.bounds, 2);
    CGRectLayoutLinear lnr(lyt);
    lnr << (::wsi::flex)1 << (pixel)30;
    
    output.frame = lyt << lnr;
    
    CGRectLayoutHBox lyt_cmd(lyt << lnr);
    CGRectLayoutLinear lnr_cmd(lyt_cmd);
    lnr_cmd << (flex)1 << (pixel)30 << (pixel)lyt_cmd.get_rc().size.height;
    
    input.frame = lyt_cmd << lnr_cmd;
    run.frame = lyt_cmd << lnr_cmd;
    close.frame = lyt_cmd << lnr_cmd;
}

@end

@interface DTraceController ()

@property (nonatomic, retain) WSILua* lua;

@end

@implementation DTraceController

@synthesize viewForSwitch;
@synthesize lua;
@synthesize showLogo;

- (id)init {
    self = [super init];
    
    lua = [[WSILua alloc] init];
    showLogo = YES;
    
    // register library.
    wluaopen_dtrace(lua.processor);
    wluaopen_dtrace_objc(lua.processor);
    
    return self;
}

- (void)dealloc {
    zero_release(lua);
    
    // break.
    [[WSIConsole shared] disconnect:self];
    
    [super dealloc];
}

- (void)loadView {
    DTraceView* view = [[DTraceView alloc] initWithZero];
    self.view = view;
    [view release];
}

- (void)viewIsLoading {
    DTraceView* view = (DTraceView*)self.view;
    
    // connect.
    [view.run connect:kSignalButtonClicked sel:@selector(act_run) obj:self];
    [view.close connect:kSignalButtonClicked sel:@selector(hide) obj:self];
    [view.input connect:kSignalEditingReturn sel:@selector(act_return) obj:self];
    
    // for echo.
    [[WSIConsole shared] connect:kSignalPrint sel:@selector(act_echo:) obj:self];
}

- (void)act_echo:(WSIEventObj*)evt {
    NSString* str = evt.result;
    [self performSelectorOnMainThread:@selector(do_echo:) withObject:str waitUntilDone:NO];
}

- (void)do_echo:(NSString*)str {
    DTraceView* view = (DTraceView*)self.view;
    [view.output appendLine:str];
    [view.output scrollToEnd];
}

- (void)act_return {
    [self act_run];
}

- (void)show {    
    // hide switch.
    self.viewForSwitch.hidden = YES;
    
    // root.
    UIView* root = [WSIApplication shared].window.rootViewController.view;
    
    // show self.
    CGRect rc = root.bounds;
    rc.size.height /= 2;
    self.view.frame = rc;

    // add.
    [root addSubview:self.view];
    
    [self retain];
}

- (void)hide {
    if (showLogo) {
        // show switch.
        self.viewForSwitch.hidden = NO;
    }
    
    // remove.
    [self.view removeFromSuperview];
    
    // release.
    [self release];
}

- (void)act_run {
    DTraceView* view = (DTraceView*)self.view;
    NSString* express = view.input.text;
    if ([express notEmpty] == false)
        return;
    
    if ([lua executeUTF8String:express.UTF8String]) {
        trace_msg(@"OK");
    } else {
        trace_msg(@"ERROR");
    }
}

+ (DTraceController*)shared {
    static DTraceController* __gs_ctlr = nil;
    WSI_SYNCHRONIZED(self)
    if (__gs_ctlr == nil)
        __gs_ctlr = [[DTraceController alloc] init];
    WSI_SYNCHRONIZED_END
    return __gs_ctlr;
}

- (void)clear {
    DTraceView* view = (DTraceView*)self.view;
    view.output.text = nil;
}

@end

WSI_END_OBJC