
# import "Foundation+NNT.h"
# import "Bar2D.h"

WSI_BEGIN_OBJC

@implementation Bar2D

- (id)init {
    self = [super init];
    self.title = @"2D Bar";
    self.titleImage = [WSIUIImage imageNamed:@"logo@57.png"];
    
    return self;
}

- (void)viewIsLoading {
    self.view.backgroundColor = [UIColor whiteColor];
}

- (void)chartControllerInit:(UIChartController*)chart {
    
}

@end

WSI_END_OBJC