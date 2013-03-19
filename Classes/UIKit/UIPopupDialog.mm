
# import "Core.h"
# import "UIPopupDialog.h"
# import "CoreGraphic+WSI.h"
# import "App.h"
# import "Layout.h"

WSI_BEGIN_OBJC

signal_t kSignalDialogExecute = @"::wsi::ui::dialog::execute";
signal_t kSignalDialogClose = @"::wsi::ui::dialog::close";

@interface UIPopupDialogPrivate : NSObject

@property (nonatomic, assign) UIPopupDialog* d_owner;

@end

@implementation UIPopupDialogPrivate

@synthesize d_owner;

- (void)dealloc {
    [super dealloc];
}

@end

@interface UIPopupDialog ()

- (void)__init;

@end

@implementation UIPopupDialog

@synthesize padding, margin;
@synthesize btnYes, btnNo, btnCancel;
@synthesize content;
@synthesize showClose, buttonClose;
@synthesize backgroundView;

- (id)init {
    self = [super init];
    [self __init];
    return self;
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    [self __init];
    return self;
}

- (void)__init {
    WSIDECL_PRIVATE_INIT_EX(UIPopupDialog, _d_ptr_popup);
    
    self.backgroundColor = [UIColor whiteColor];
    self.layer.shadowOpacity = .3f;
    self.padding = CGPaddingMake(.1f, .05f, .05f, .05f);
    self.margin = CGMarginMake(5, 5, 5, 5);
    self.showClose = NO;
}

- (void)dealloc {
    safe_release(btnYes);
    safe_release(btnNo);
    safe_release(btnCancel);
    safe_release(buttonClose);
    
    WSIDECL_PRIVATE_DEALLOC_EX(_d_ptr_popup);
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalIndexYes)
WSIEVENT_SIGNAL(kSignalIndexNo)
WSIEVENT_SIGNAL(kSignalDialogExecute)
WSIEVENT_SIGNAL(kSignalDialogClose)
WSIEVENT_END

- (void)setShowClose:(BOOL)enable {
    if (showClose == enable)
        return;
    showClose = enable;
    
    if (showClose) {
        if (buttonClose == nil)
            [self buttonClose];
        
        if (buttonClose == nil) {
            buttonClose = [[UIButtonClose alloc] initWithZero];
            [self addSubview:buttonClose];
            [buttonClose connect:kSignalButtonClicked sel:@selector(close) obj:self];            
        } else {
            buttonClose.hidden = NO;
        }

    } else {
        buttonClose.hidden = YES;
    }
}

- (void)drawRect:(CGRect)rect {
    [super drawRect:rect];
}

- (void)setContent:(WSIUIView *)view {
    if (content) {
        [content removeFromSuperview];
    }
    content = view;
    [self addSubview:content];
    [self layoutSubviews];
}

- (void)execute {
    if (self.superview) {        
        dthrow([NSException exceptionWithName:@"dialog" reason:@"has superview" userInfo:nil]);
        return;
    }
    
    UIView* rootView = [WSIApplication shared].window.rootViewController.view;
    CGRect rect = CGRectSetRatioPadding(rootView.bounds, self.padding);
        
    self.frame = rect;
    
    if (backgroundView == nil) {
        backgroundView = [[WSIUIView alloc] initWithFrame:rootView.bounds];
        [rootView addSubview:backgroundView];
        safe_release(backgroundView);
    } else {
        [rootView addSubview:backgroundView];
    }
    
    [rootView addSubview:self];
    
    [self emit:kSignalDialogExecute result:self];
}

- (void)close {    
    // close.
    [self emit:kSignalDialogClose result:self];
    
    [UIView beginAnimations:@"" context:nil];
    [UIView setAnimationDelegate:self];
    [UIView setAnimationDidStopSelector:@selector(act_close)];
    self.alpha = 0;
    [UIView commitAnimations];
}

- (void)act_close {
    [backgroundView removeFromSuperview];
    backgroundView = nil;
    
    [self removeFromSuperview];
}

- (void)layoutSubviews {
    CGRect rc_client = self.bounds;
    
    wsi::CGRectLayoutVBox lyt(rc_client);
    lyt.margin = self.margin;
    wsi::CGRectLayoutLinear lnr(lyt);
    lnr.add_flex(1);

    if (btnYes || btnNo || btnCancel) {
        lnr.add_pixel(30);
    }
    
    content.frame = lyt.stride_pixel(lnr.start());
    
    if (btnYes || btnNo || btnCancel) {
        wsi::CGRectLayoutHBox lyt_btns(lyt.stride_pixel(lnr.next()));
        wsi::CGRectLayoutLinear lnr_btns(lyt_btns);
        lnr_btns.add_flex(1);
        if (btnYes)
            lnr_btns.add_pixel(50);
        if (btnNo)
            lnr_btns.add_pixel(50);
        if (btnCancel)
            lnr_btns.add_pixel(50);
        lnr_btns.add_flex(1);
        
        lyt_btns.add_pixel(lnr_btns.start());
        
        if (btnYes)
            btnYes.frame = lyt_btns.add_pixel(lnr_btns.next());
        if (btnNo)
            btnNo.frame = lyt_btns.add_pixel(lnr_btns.next());
        if (btnCancel)
            btnCancel.frame = lyt_btns.add_pixel(lnr_btns.next());
    }
    
    if (buttonClose) {
        CGPoint pt = CGRectRightTop(&rc_client);
        //pt.x -= 5;
        //pt.y += 5;
        [buttonClose moveToCenter:pt];
    }
}

@end

WSI_END_OBJC