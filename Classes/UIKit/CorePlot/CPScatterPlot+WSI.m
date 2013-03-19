
# import "Core.h"
# import "CorePlot+WSI.h"
# import "CPScatterPlot+WSI.h"

WSI_BEGIN_OBJC

@implementation CPScatterPlot (WSI)


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
    WSIDECL_PRIVATE_INIT(UICPScatterPlot);    
    return self;
}

- (void)dealloc {
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)renderAsVectorInContext:(CGContextRef)theContext {    
    [super renderAsVectorInContext:theContext];
}

@end

WSI_END_OBJC