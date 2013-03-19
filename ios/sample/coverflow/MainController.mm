
# import "WSIFoundation.h"
# import "MainController.h"
# import "Math+WSI.h"

WSI_USINGCXXNAMESPACE;

WSI_BEGIN_OBJC

real itemFractionReflection = kCoverFlowItemFractionReflection;

@interface MainView : WSIUIView {
    UISliderTitleValue *slider_slant, *slider_zpos, *slider_angle, *slider_scale, *slider_coverspace, *slider_centeroffset, *slider_reflection, *slider_padtop;
}

@property (nonatomic, assign) UIView* main;
@property (nonatomic, assign) MainController* ctlr;

- (void)create;

@end

@implementation MainView

@synthesize main;
@synthesize ctlr;

- (id)initWithZero {
    self = [super initWithZero];
    self.backgroundColor = [UIColor whiteColor];
    return self;
}

- (void)create {
    slider_slant = [[UISliderTitleValueReset alloc] initWithZero];
    slider_slant.title.text = @"slant";
    slider_slant.maximumValue = 0.01;
    slider_slant.minimumValue = -0.01;
    slider_slant.currentValue = ctlr.coverflow.coverSlant;
    [slider_slant connect:kSignalValueChanged sel:@selector(slant_changed) obj:self];
    [self addSubview:slider_slant];
    
    slider_zpos = [[UISliderTitleValueReset alloc] initWithZero];
    slider_zpos.title.text = @"zpos";
    slider_zpos.maximumValue = 100;
    slider_zpos.minimumValue = -200;
    slider_zpos.currentValue = ctlr.coverflow.coverZPosition;
    [slider_zpos connect:kSignalValueChanged sel:@selector(zpos_changed) obj:self];
    [self addSubview:slider_zpos];
    
    slider_angle = [[UISliderTitleValueReset alloc] initWithZero];
    slider_angle.title.text = @"angle";
    slider_angle.maximumValue = ANGLE2RAD(90);
    slider_angle.minimumValue = -ANGLE2RAD(90);
    slider_angle.currentValue = ctlr.coverflow.coverAngle;
    [slider_angle connect:kSignalValueChanged sel:@selector(angle_changed) obj:self];
    [self addSubview:slider_angle];
    
    slider_scale = [[UISliderTitleValueReset alloc] initWithZero];
    slider_scale.title.text = @"scale";
    slider_scale.maximumValue = 2.f;
    slider_scale.minimumValue = 0.f;
    slider_scale.currentValue = ctlr.coverflow.coverScale;
    [slider_scale connect:kSignalValueChanged sel:@selector(scale_changed) obj:self];    
    [self addSubview:slider_scale];
    
    slider_coverspace = [[UISliderTitleValueReset alloc] initWithZero];
    slider_coverspace.title.text = @"space";
    slider_coverspace.maximumValue = 1000;
    slider_coverspace.minimumValue = 0;
    slider_coverspace.currentValue = ctlr.coverflow.coverSpacing;
    [slider_coverspace connect:kSignalValueChanged sel:@selector(space_changed) obj:self];
    [self addSubview:slider_coverspace];
    
    slider_centeroffset = [[UISliderTitleValueReset alloc] initWithZero];
    slider_centeroffset.title.text = @"centeroffset";
    slider_centeroffset.maximumValue = 0;
    slider_centeroffset.minimumValue = -1;
    slider_centeroffset.currentValue = ctlr.coverflow.centerOffset.y;
    [slider_centeroffset connect:kSignalValueChanged sel:@selector(centeroffset_changed) obj:self];
    [self addSubview:slider_centeroffset];
    
    slider_reflection = [[UISliderTitleValueReset alloc] initWithZero];
    slider_reflection.title.text = @"reflection";
    slider_reflection.maximumValue = 1;
    slider_reflection.minimumValue = 0;
    slider_reflection.currentValue = itemFractionReflection;
    [slider_reflection connect:kSignalValueChanged sel:@selector(reflection_changed) obj:self];
    [self addSubview:slider_reflection];
    
    slider_padtop = [[UISliderTitleValueReset alloc] initWithZero];
    slider_padtop.title.text = @"padtop";
    slider_padtop.maximumValue = 1;
    slider_padtop.minimumValue = 0;
    slider_padtop.currentValue = ctlr.coverflow.padding.top;
    [slider_padtop connect:kSignalValueChanged sel:@selector(padtop_changed) obj:self];
    [self addSubview:slider_padtop];
}

- (void)slant_changed {
    ctlr.coverflow.coverSlant = slider_slant.currentValue;
    [ctlr.coverflow relayoutData:NO];
}

- (void)zpos_changed {
    ctlr.coverflow.coverZPosition = slider_zpos.currentValue;
    [ctlr.coverflow relayoutData:NO];
}

- (void)angle_changed {
    ctlr.coverflow.coverAngle = slider_angle.currentValue;
    [ctlr.coverflow relayoutData:NO];
}

- (void)scale_changed {
    ctlr.coverflow.coverScale = slider_scale.currentValue;
    [ctlr.coverflow relayoutData:NO];
}

- (void)space_changed {
    ctlr.coverflow.coverSpacing = slider_coverspace.currentValue;
    [ctlr.coverflow reloadData];
}

- (void)reflection_changed {
    itemFractionReflection = slider_reflection.currentValue;
    [ctlr.coverflow reloadData];
}

- (void)centeroffset_changed {
    CGPoint of = ctlr.coverflow.centerOffset;
    of.y = slider_centeroffset.currentValue;
    ctlr.coverflow.centerOffset = of;
    [ctlr.coverflow relayoutData:NO];
}

- (void)padtop_changed {
    CGPadding pad = ctlr.coverflow.padding;
    pad.top = slider_padtop.currentValue;
    ctlr.coverflow.padding = pad;
    [ctlr.coverflow relayoutData:NO];
}

- (void)layoutSubviews {
    CGRectLayoutVBox lyt_main(self.bounds);
    CGRectLayoutLinear lnr_main(lyt_main);
    lnr_main << (flex)0 << (flex)1;
    lyt_main.add_pixel(lnr_main.start());
    main.frame = lyt_main.add_pixel(lnr_main.next());
    
    CGRectLayoutVBox lyt(self.bounds);
    CGRectLayoutLinear lnr(lyt);
    
    const int height = 30;
    lnr <<
    (pixel)height <<
    (pixel)height <<
    (pixel)height <<
    (pixel)height <<
    (pixel)height <<
    (pixel)height <<
    (pixel)height <<
    (pixel)height
    ;
    
    slider_slant.frame = lyt.add_pixel(lnr.start());
    slider_zpos.frame = lyt.add_pixel(lnr.next());
    slider_angle.frame = lyt.add_pixel(lnr.next());
    slider_scale.frame = lyt.add_pixel(lnr.next());
    slider_reflection.frame = lyt.add_pixel(lnr.next());
    slider_coverspace.frame = lyt.add_pixel(lnr.next());
    slider_centeroffset.frame = lyt.add_pixel(lnr.next());
    slider_padtop.frame = lyt.add_pixel(lnr.next());
}

@end

@interface CoverItem : UICoverFlowItem

@end

@implementation CoverItem

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    WCGMutableLineStyle* ls = [WCGMutableLineStyle lineStyle];
    ls.lineColor = [WCGColor blackColor];
    ls.lineWidth = 2.0f;
    [ls setLineStyleInView:self.imageView];
    
    self.fractionReflection = itemFractionReflection;
    
    return self;
}

@end

@implementation MainController

@dynamic coverflow;

- (void)dealloc {
    [ctlr release];
    [super dealloc];
}

- (void)loadView {
    MainView* view = [[MainView alloc] initWithZero];
    self.view = view;
    [view release];
    
    view.ctlr = self;
}

- (void)viewIsLoading {
    ctlr = [[UICoverFlowController alloc] init];
    
    for (uint i = 0; i < 20; ++i) {
        UICoverFlowData* data = [[UICoverFlowData alloc] init];
        data.image = [UIImage imageNamed:@"logo@114.png"];
        [ctlr.datas addObject:data];
        [data release];
    }
    
    UICoverFlow* coverflow = ctlr.coverFlow;
    coverflow.scaleToFit = YES;
    [coverflow connect:kSignalContentClicked sel:@selector(clicked:) obj:self];
    [coverflow connect:kSignalSelectChanged sel:@selector(select_changed:) obj:self];
    
    ctlr.itemClass = [CoverItem class];
    [ctlr reloadData];
    
    MainView* view = (MainView*)self.view;
    view.main = ctlr.view;
    [view addSubview:view.main];

    // create
    [view create];
}

- (UICoverFlow*)coverflow {
    return ctlr.coverFlow;
}

- (void)clicked:(WSIEventObj*)evt {
    UICoverFlowItem* item = (UICoverFlowItem*)evt.result;
    [item activeScale];
}

- (void)select_changed:(WSIEventObj*)evt {
    UIItemView* item = (UIItemView*)evt.result;
    UICoverFlowItem* cover = (UICoverFlowItem*)item.contentView;
    trace_fmt(@"select %d.", cover.number);
}

@end

WSI_END_OBJC