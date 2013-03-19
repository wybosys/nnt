
# import "Core.h"
# import "AppStoreService.h"
# import "WSIConfiguration.h"
# import "AppInformation.h"
# import <UIKit/UIKit.h>
# import "Mach+WSI.h"
# import "Time+WSI.h"

WSI_USINGCXXNAMESPACE;

WSI_BEGIN_OBJC

NSString* kRateAppReminderAllowRemind = @"::wsi::app::service::rateapp::reminder::allow";
NSString* kRateAppReminderAllowRemindDelay = @"::wsi::app::service::rateapp::reminder::allow::delay";

# define CHECK_INTERVAL 60
# define CHECK_CPUSAGE 20
# define CHECK_COUNT 5

@interface ReminderView : UIAlertView
<UIAlertViewDelegate>

+ (ReminderView*)reminder;

@end

@implementation ReminderView

+ (ReminderView*)reminder {
    ReminderView* ret = [[ReminderView alloc] initWithTitle:_W(@"RATE")
                                                    message:_W(@"")
                                                   delegate:self
                                          cancelButtonTitle:nil
                                          otherButtonTitles:_W(@"GOTO"), _W(@"DELAY"), _W(@"NEVER"), nil];
    ret.delegate = ret;
    return [ret autorelease];
}

- (void)layoutSubviews {
    UILabel *title = nil, *msg = nil;
    UIButton *btn[3] = {0};
    for (id each in self.subviews) {
        if ([each isKindOfClass:[UIButton class]]) {
            for (uint i = 0; i < 3; ++i) {
                if (btn[i] == 0) {
                    btn[i] = (UIButton*)each;
                    break;
                }
            }
        } else if ([each isKindOfClass:[UILabel class]]) {
            if (title == nil)
                title = (UILabel*)each;
            else if (msg == nil)
                msg = (UILabel*)each;
        }
    }
    
    cg::Rect rc(self.bounds);
    rc.set_y(cg::Rect(msg.frame).lb().y);
    rc.set_height(rc.height() - rc.y());
    rc = rc.deflate(cg::pixel(5), 5, 5, 5);
    
    layout::vbox lyt(rc, 5);
    layout::linear lnr(lyt);
    lnr << (flex)1 << (flex)1 << (flex)1;
    btn[0].frame = lyt << lnr;
    btn[1].frame = lyt << lnr;
    btn[2].frame = lyt << lnr;
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    switch (buttonIndex)
    {
        case 0: {
            NSString* app = [WSIApplication shared].urlInAppStore;
            [[UIApplication sharedApplication] openURL:[NSURL URLWithString:app]];
        } break;
        case 1: {
            PASS; // delay.
        } break;
        case 2: {
            [[WSIConfiguration shared] set:kRateAppReminderAllowRemind boolValue:NO];
        } break;
    }
}

@end

WSIDECL_PRIVATE_BEGIN(RateAppReminder, NSObject)
<UIAlertViewDelegate>
{
    WSINSTimer* _timer;
}

@property (nonatomic, retain) WSINSTimer* timer;

WSIDECL_PRIVATE_IMPL(RateAppReminder)

@synthesize timer = _timer;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    safe_release(_timer);
    [super dealloc];
}

- (void)remind {
    if ([d_owner.delegate rateReminderCanRemind:d_owner])
    {
        WSINSTimer* tmr = [[WSINSTimer alloc] init];
        tmr.interval = CHECK_INTERVAL;
        [[tmr connect: ::kSignalTimerFired sel:@selector(act_remind) obj:self] backgroundThread];
        self.timer = tmr;
        [tmr start];
        safe_release(tmr);
    }
}

- (void)act_remind {
    if (cpu_usage() > CHECK_CPUSAGE) {
        return;
    }
    
    [d_owner.delegate rateReminderRemind:d_owner];
    [self.timer stop];
    self.timer = nil;
}

WSIDECL_PRIVATE_END

@implementation RateAppReminder

@synthesize delegate = _delegate;
@synthesize appurl = _appurl;

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(RateAppReminder);
    
    self.delegate = self;
    
    return self;
}

- (void)dealloc {
    safe_release(_appurl);
    
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

+ (RateAppReminder*)shared {
    static RateAppReminder* ret = nil;
    WSI_SYNCHRONIZED(self)
    if (ret == nil)
        ret = [[[self class] alloc] init];
    WSI_SYNCHRONIZED_END
    return ret;
}

+ (BOOL)AllowRemind {
    return [[WSIConfiguration shared] getBool:kRateAppReminderAllowRemind null:YES];
}

+ (BOOL)AllowRemindDelay {
    return [[WSIConfiguration shared] getBool:kRateAppReminderAllowRemindDelay null:YES];
}

- (void)remind {
    if (_appurl == nil)
        return;
    
    if ([RateAppReminder AllowRemind] == NO)
        return;
    
    [d_ptr remind];
}

- (BOOL)rateReminderCanRemind:(RateAppReminder *)reminder {
    if (bse::Application::Counter::Launch() % CHECK_COUNT == 0) {
        return [RateAppReminder AllowRemindDelay];
    }

    return NO;
}

- (void)rateReminderRemind:(RateAppReminder *)reminder {
    ReminderView* view = [ReminderView reminder];
    [view show];
}

@end

WSI_END_OBJC
