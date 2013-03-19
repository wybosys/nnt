
# import "Core.h"
# import "PayNullApi.h"

NNT_BEGIN_OBJC

signal_t kSignalPayReceive = @"::nnt::pay::receive";
signal_t kSignalPaySuccess = @"::nnt::pay::success";
signal_t kSignalPayFailed = @"::nnt::pay::failed";
signal_t kSignalPaying = @"::nnt::pay::doing";
signal_t kSignalPayRestore = @"::nnt::pay::restore";

@implementation PayNullApi

@synthesize requestData = _requestData;

- (void)dealloc {
    safe_release(_requestData);
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalPayReceive)
NNTEVENT_SIGNAL(kSignalPaySuccess)
NNTEVENT_SIGNAL(kSignalPayFailed)
NNTEVENT_END

+ (NSString*)identity {
    return nil;
}

- (BOOL)send:(id)data {
    self.requestData = data;
    return NO;
}

@end

NNT_END_OBJC
