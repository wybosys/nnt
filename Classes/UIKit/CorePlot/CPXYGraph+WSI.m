
# import "Core.h"
# import "CorePlot+WSI.h"

WSI_BEGIN

@implementation CPXYGraph (WSI)

@end

@interface UICPXYGraphPrivate : NSObject {
    UICPXYGraph *d_owner;
}

@property (nonatomic, assign) UICPXYGraph *d_owner;

- (void)init_view;

@end

@implementation UICPXYGraphPrivate 

@synthesize d_owner;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (void)init_view {
    //d_owner.backgroundColor = [UIColor redColor].CGColor;
}

# pragma mark -
# pragma mark tap gesture

- (void)handleTap:(UITapGestureRecognizer *)sender {
    
}

@end

@implementation UICPXYGraph

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(UICPXYGraph);    
    
    [d_ptr init_view];
    
    return self;
}

- (void)dealloc {
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (id)initWithFrame:(CGRect)newFrame xScaleType:(CPScaleType)newXScaleType yScaleType:(CPScaleType)newYScaleType {
    self = [super initWithFrame:newFrame xScaleType:newXScaleType yScaleType:newYScaleType];  
    if (self) {
        WSIDECL_PRIVATE_INIT(UICPXYGraph);
        [d_ptr init_view];
    }
    return self;
}

@end

WSI_END