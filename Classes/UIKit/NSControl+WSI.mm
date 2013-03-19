
# import "Core.h"
# import "NSControl+WSI.h"

WSI_BEGIN_OBJC

signal_t kSignalAction = @"::wsi::ui::action";

@implementation NSControl (WSI)

@end

@implementation _nscontrol_eventmonitor

- (void)action:(id)sender {
    [target emit:kSignalAction];
}

@end

WSI_END_OBJC