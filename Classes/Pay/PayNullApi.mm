
# import "Core.h"
# import "PayNullApi.h"

WSI_BEGIN_OBJC

signal_t kSignalPayReceive = @"::wsi::pay::receive";
signal_t kSignalPaySuccess = @"::wsi::pay::success";
signal_t kSignalPayFailed = @"::wsi::pay::failed";
signal_t kSignalPaying = @"::wsi::pay::doing";
signal_t kSignalPayRestore = @"::wsi::pay::restore";

@implementation PayNullApi

@synthesize requestData = _requestData;

- (void)dealloc {
    safe_release(_requestData);
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalPayReceive)
WSIEVENT_SIGNAL(kSignalPaySuccess)
WSIEVENT_SIGNAL(kSignalPayFailed)
WSIEVENT_END

+ (NSString*)identity {
    return nil;
}

- (BOOL)send:(id)data {
    self.requestData = data;
    return NO;
}

@end

WSI_END_OBJC
