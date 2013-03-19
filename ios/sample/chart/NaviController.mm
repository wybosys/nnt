
# import "WSIFoundation.h"
# import "NaviController.h"
# import "Bar2D.h"

WSI_BEGIN_OBJC

@implementation NaviController

- (id)init {
    self = [super init];
    self.title = @"CHART";
    
    self.rows = 3;
    self.cols = 3;
    
    wsi::ns::MutableArray arr;
    Bar2D* bar = [[Bar2D alloc] init];
    arr << bar;
    safe_release(bar);
    
    self.items = arr;
    
    return self;
}

@end

WSI_END_OBJC