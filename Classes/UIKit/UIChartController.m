
# import "Core.h"
# import "UIChartController.h"
# import "CorePlot+WSI.h"

WSI_BEGIN_OBJC

@implementation UIChartController

@synthesize graph;
@synthesize dataSource, delegate;
@dynamic backgroundImage;
@synthesize frame;

- (id)init {
    self = [super init];
    
    self.dataSource = self;
    self.delegate = self;
    
    return self;
}

- (void)dealloc {
    zero_release(graph);
    [super dealloc];
}

- (void)loadView {
    UICPGraphHostingView *cpview = [[UICPGraphHostingView alloc] initWithZero];
    UICPXYGraph *cpgraph = [[UICPXYGraph alloc] initWithFrame:CGRectZero xScaleType:CPScaleTypeLinear yScaleType:CPScaleTypeLinear];
    self.view = cpview;
    self.graph = cpgraph;
    cpview.hostedGraph = cpgraph;
    [cpgraph release];
    [cpview release];
    
    //cpview.layer.sublayerTransform = CATransform3DMakeScale(1.0, -1.0, 1.0);
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self refresh];
}

- (void)clear {
    UICPGraphHostingView *cpview = (UICPGraphHostingView*)self.view;    
    UICPXYGraph *cpgraph = [[UICPXYGraph alloc] initWithFrame:CGRectZero xScaleType:CPScaleTypeLinear yScaleType:CPScaleTypeLinear];
    //cpgraph.transform = CATransform3DMakeScale(1.0, -1.0, 1.0);
    self.graph = cpgraph;    
    cpview.hostedGraph = cpgraph;
    [cpgraph release];
    
    if ([delegate respondsToSelector:@selector(chartControllerClear:)]) {
        [delegate chartControllerClear:self];
    }
}

- (void)refresh {
    [self clear];
    
    if ([dataSource respondsToSelector:@selector(chartControllerInit:)]) {
        [dataSource chartControllerInit:self];
    }
    
    if ([delegate respondsToSelector:@selector(chartControllerRefresh:)]) {
        [delegate chartControllerRefresh:self];
    }
}

- (void)setBackgroundImage:(UIImage *)__backgroundImage {
    UICPGraphHostingView *cpview = (UICPGraphHostingView*)self.view;
    if (__backgroundImage) {
        cpview.backgroundImage = __backgroundImage;
    }
}

- (UIImage*)backgroundImage {
    UICPGraphHostingView *cpview = (UICPGraphHostingView*)self.view;
    return cpview.backgroundImage;
}

- (void)setFrame:(CGRect)__frame {
    frame = __frame;
    
    UICPGraphHostingView *cpview = (UICPGraphHostingView*)self.view; 
    [cpview setFrame:__frame];
    
    if (cpview.hostedGraph) {
        [cpview.hostedGraph.plotAreaFrame setFrame:CGRectMake(0, 0, __frame.size.width, __frame.size.height)];
        [cpview.hostedGraph.plotAreaFrame setNeedsLayout];
    }
}

# pragma mark delegate.

- (void)chartControllerInit:(UIChartController*)chart {
    PASS;
}

@end

WSI_END_OBJC