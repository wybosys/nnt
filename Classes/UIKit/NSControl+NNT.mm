
# import "Core.h"
# import "NSControl+NNT.h"

NNT_BEGIN_OBJC

signal_t kSignalAction = @"::nnt::ui::action";

@implementation NSControl (NNT)

@end

@implementation _nscontrol_eventmonitor

- (void)action:(id)sender {
    [target emit:kSignalAction];
}

@end

NNT_END_OBJC