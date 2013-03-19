
# import "Core.h"
# import "UISMSController.h"
# import <MessageUI/MessageUI.h>
# import "App.h"
# import "UIDevice+WSI.h"

WSI_BEGIN_OBJC

WSIDECL_PRIVATE_BEGIN(UISMSController, WSIObject) < MFMessageComposeViewControllerDelegate >

@property (nonatomic, readonly) MFMessageComposeViewController* ctlr;

WSIDECL_PRIVATE_IMPL(UISMSController)

@synthesize ctlr;

- (id)init {
    self = [super init];
    
    if ([UIDevice isIPhone] && [MFMessageComposeViewController canSendText]) {
        ctlr = [[MFMessageComposeViewController alloc] init];
        ctlr.messageComposeDelegate = self;
    }
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

// delegate.

- (void)messageComposeViewController:(MFMessageComposeViewController *)controller didFinishWithResult:(MessageComposeResult)result {        
    [ctlr dismissModalViewControllerAnimated:YES];
    [d_owner release];
}

WSIDECL_PRIVATE_END

@implementation UISMSController

@synthesize recipients = _recipients;
@synthesize body;

- (id)init {
    self = [super init];
    
    _recipients = [[NSMutableArray alloc] init];

    WSIDECL_PRIVATE_INIT(UISMSController);    
    return self;
}

- (void)dealloc {
    zero_release(_recipients);
    zero_release(body);
    
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)execute {
    if (d_ptr.ctlr == nil)
        return;
    
    [self retain];    

    d_ptr.ctlr.recipients = _recipients;
    d_ptr.ctlr.body = body;
    
    [[WSIApplication shared].window.rootViewController presentModalViewController:d_ptr.ctlr animated:YES];
}

- (void)add:(NSString*)phone {
    [_recipients addObject:phone];
}

+ (BOOL)available {
    return [UIDevice isIPhone] && [MFMessageComposeViewController canSendText];
}

@end

WSI_END_OBJC
