
# import "Core.h"
# import "UIEmailController.h"
# import <MessageUI/MessageUI.h>

NNT_BEGIN_OBJC

NNTDECL_PRIVATE_BEGIN(UIEmailController, NNTObject) <MFMailComposeViewControllerDelegate>

@property (nonatomic, readonly) MFMailComposeViewController* ctlr;

NNTDECL_PRIVATE_IMPL(UIEmailController)

@synthesize ctlr;

- (id)init {
    self = [super init];
    
    ctlr = [[MFMailComposeViewController alloc] init];
    ctlr.mailComposeDelegate = self;
    
    return self;
}

- (void)dealloc {
    zero_release(ctlr);
    
    [super dealloc];
}

- (void)mailComposeController:(MFMailComposeViewController*)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError*)error {    
    [ctlr dismissModalViewControllerAnimated:YES];
    [d_owner release];
}

NNTDECL_PRIVATE_END

@implementation UIEmailController

@synthesize to = _to, cc = _cc, bcc = _bcc;
@synthesize body = _body, html = _html;

- (id)init {
    self = [super init];
    
    _to = [[NSMutableArray alloc] init];
    _cc = [[NSMutableArray alloc] init];
    _bcc = [[NSMutableArray alloc] init];
    
    NNTDECL_PRIVATE_INIT(UIEmailController);
    return self;
}

- (void)dealloc {
    zero_release(_to);
    zero_release(_cc);
    zero_release(_bcc);
    
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)addTo:(NSString*)addr {
    [_to addObject:addr];
}

- (void)addCc:(NSString*)addr {
    [_cc addObject:addr];
}

- (void)addBcc:(NSString*)addr {
    [_bcc addObject:addr];
}

- (void)execute {
    if (d_ptr.ctlr == nil)
        return;
    
    [self retain];
    
    d_ptr.ctlr.toRecipients = _to;
    d_ptr.ctlr.ccRecipients = _cc;
    d_ptr.ctlr.bccRecipients = _bcc;
    
    if (_html) {
        [d_ptr.ctlr setMessageBody:_html isHTML:YES];
    } else {
        [d_ptr.ctlr setMessageBody:_body isHTML:NO];
    }
    
    [[NNTApplication shared].window.rootViewController presentModalViewController:d_ptr.ctlr animated:YES];
}

@end

NNT_END_OBJC