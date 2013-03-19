
# import "Core.h"
# import "CorePlot+NNT.h"
# import "CPScatterPlot+NNT.h"

NNT_BEGIN_OBJC

@implementation CPScatterPlot (NNT)


@end

@interface UICPScatterPlotPrivate : NSObject {
    
    UICPScatterPlot *d_owner;
}

@property (nonatomic, assign) UICPScatterPlot *d_owner;

@end

@implementation UICPScatterPlotPrivate

@synthesize d_owner;

@end

@implementation UICPScatterPlot

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(UICPScatterPlot);    
    return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)renderAsVectorInContext:(CGContextRef)theContext {    
    [super renderAsVectorInContext:theContext];
}

@end

NNT_END_OBJC