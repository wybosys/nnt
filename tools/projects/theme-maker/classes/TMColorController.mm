
# import <nnt/Foundation+NNT.h>
# import "TMColorController.h"

NNTAPP_BEGIN_OBJC

@interface TMColorView : NNTNSView {
    NSColorPanel* pn_color;
}

@property (nonatomic, readonly) NSColorPanel* pn_color;

@end

@implementation TMColorView

@synthesize pn_color;

- (id)initWithZero {
    self = [super initWithZero];
    
    pn_color = [NSColorPanel sharedColorPanel];
    [self addSubview:pn_color.contentView];
    
    return self;
}

- (void)layoutSubviews {
    [pn_color.contentView moveToCenter:CGRectCenterPoint2(self.bounds)];
}

@end

@implementation TMColorController

- (id)init {
    self = [super init];
    self.identity = self.title = @"COLOR";
    return self;
}

- (void)loadView {
    TMColorView* view = [[TMColorView alloc] initWithZero];
    self.view = view;
    [view release];
}

- (id)dataObject {
    TMColorView* view = (TMColorView*)self.view;
    NSColor* color = view.pn_color.color;
    NgColor* colr = [NgColor colorWithComponentRed:[color redComponent]
                                               green:[color greenComponent]
                                                blue:[color blueComponent]
                                               alpha:[color alphaComponent]];
    return colr;
}

- (void)setDataObject:(NgColor*)colr {
    TMColorView* view = (TMColorView*)self.view;
    NSColor* color = [NSColor colorWithSRGBRed:[colr redComponent]
                                         green:[colr greenComponent]
                                          blue:[colr blueComponent]
                                         alpha:[colr alphaComponent]];
    view.pn_color.color = color;
}

@end

NNTAPP_END_OBJC
