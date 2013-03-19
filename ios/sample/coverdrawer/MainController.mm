
# import "Foundation+NNT.h"
# import "MainController.h"
# import "Math+WSI.h"

WSI_BEGIN_OBJC

@interface MainView : WSIUIView {
    UISliderTitleValueReset *vpangle, 
    *itemangelx, *itemangely, *itemangelz, 
    *itemangelx_off, *itemangely_off, *itemangelz_off, 
    *itemposx_off, *itemposy_off, *itemposz_off, 
    *itemspace, *zposoff, *zpos;
}

@property (nonatomic, assign) UICoverDrawer* main;

- (void)create;

@end

@implementation MainView

@synthesize main;

- (id)initWithZero {
    self = [super initWithZero];    
    return self;
}

- (void)create {
    vpangle = [UISliderTitleValueReset sliderWith:@"vpangle" max:0.1 min:-0.1 cur:main.viewportAngle];
    [vpangle connect:kSignalValueChanged sel:@selector(vpangle_changed) obj:self];
    [self addSubview:vpangle];
    
    itemangelx = [UISliderTitleValueReset sliderWith:@"itemangle::x" max:M_PI_4 min:-M_PI_4 cur:main.itemAngle.x];
    [itemangelx connect:kSignalValueChanged sel:@selector(itemanglex_changed) obj:self];
    [self addSubview:itemangelx];
    
    itemangely = [UISliderTitleValueReset sliderWith:@"itemangle::y" max:M_PI_4 min:-M_PI_4 cur:main.itemAngle.y];
    [itemangely connect:kSignalValueChanged sel:@selector(itemangley_changed) obj:self];
    [self addSubview:itemangely];
    
    itemangelz = [UISliderTitleValueReset sliderWith:@"itemangle::z" max:M_PI_4 min:-M_PI_4 cur:main.itemAngle.z];
    [itemangelz connect:kSignalValueChanged sel:@selector(itemanglez_changed) obj:self];
    [self addSubview:itemangelz];
    
    itemangelx_off = [UISliderTitleValueReset sliderWith:@"itemangle::x::off" max:M_PI_4 min:-M_PI_4 cur:main.itemAngleStep.x];
    [itemangelx_off connect:kSignalValueChanged sel:@selector(itemangleoffx_changed) obj:self];
    [self addSubview:itemangelx_off];
    
    itemangely_off = [UISliderTitleValueReset sliderWith:@"itemangle::y::off" max:M_PI_4 min:-M_PI_4 cur:main.itemAngleStep.y];
    [itemangely_off connect:kSignalValueChanged sel:@selector(itemangleoffy_changed) obj:self];
    [self addSubview:itemangely_off];
    
    itemangelz_off = [UISliderTitleValueReset sliderWith:@"itemangle::z::off" max:M_PI_4 min:-M_PI_4 cur:main.itemAngleStep.z];
    [itemangelz_off connect:kSignalValueChanged sel:@selector(itemangleoffz_changed) obj:self];
    [self addSubview:itemangelz_off];
    
    itemposx_off = [UISliderTitleValueReset sliderWith:@"itempos::x::off" max:100 min:-100 cur:main.itemPositionStep.x];
    [itemposx_off connect:kSignalValueChanged sel:@selector(itemposoffx_changed) obj:self];
    [self addSubview:itemposx_off];
    
    itemposy_off = [UISliderTitleValueReset sliderWith:@"itempos::y::off" max:100 min:-100 cur:main.itemPositionStep.y];
    [itemposy_off connect:kSignalValueChanged sel:@selector(itemposoffy_changed) obj:self];
    [self addSubview:itemposy_off];
    
    itemposz_off = [UISliderTitleValueReset sliderWith:@"itempos::z::off" max:100 min:-100 cur:main.itemPositionStep.z];
    [itemposz_off connect:kSignalValueChanged sel:@selector(itemposoffz_changed) obj:self];
    [self addSubview:itemposz_off];
    
    itemspace = [UISliderTitleValueReset sliderWith:@"itemspace" max:100 min:0 cur:main.itemSpacing];
    [itemspace connect:kSignalValueChanged sel:@selector(itemspace_changed) obj:self];
    [self addSubview:itemspace];
    
    zposoff = [UISliderTitleValueReset sliderWith:@"zposoff" max:100 min:-100 cur:main.itemZPosStep];
    [zposoff connect:kSignalValueChanged sel:@selector(zposoff_changed) obj:self];
    [self addSubview:zposoff];
    
    zpos = [UISliderTitleValueReset sliderWith:@"zpos" max:0 min:-100 cur:main.itemZPosition];
    [zpos connect:kSignalValueChanged sel:@selector(zpos_changed) obj:self];
    [self addSubview:zpos];
}

- (void)layoutSubviews {
    main.frame = self.bounds;
    
    wsi::CGRectLayoutVBox lyt(self.bounds);
    wsi::CGRectLayoutLinear lnr(lyt);
    lnr << (wsi::pixel)30 << (wsi::pixel)30 << (wsi::pixel)30 << (wsi::pixel)30 << (wsi::pixel)30 << (wsi::pixel)30 << (wsi::pixel)30 << (wsi::pixel)30 << (wsi::pixel)30 << (wsi::pixel)30 << (wsi::pixel)30 << (wsi::pixel)30 << (wsi::pixel)30;
    
    vpangle.frame = lyt.add_pixel(lnr.start());
    itemangelx.frame = lyt.add_pixel(lnr.next());
    itemangely.frame = lyt.add_pixel(lnr.next());
    itemangelz.frame = lyt.add_pixel(lnr.next());
    itemangelx_off.frame = lyt.add_pixel(lnr.next());
    itemangely_off.frame = lyt.add_pixel(lnr.next());
    itemangelz_off.frame = lyt.add_pixel(lnr.next());
    itemposx_off.frame = lyt.add_pixel(lnr.next());
    itemposy_off.frame = lyt.add_pixel(lnr.next());
    itemposz_off.frame = lyt.add_pixel(lnr.next());
    itemspace.frame = lyt.add_pixel(lnr.next());
    zposoff.frame = lyt.add_pixel(lnr.next());
    zpos.frame = lyt.add_pixel(lnr.next());
}

- (void)vpangle_changed {
    main.viewportAngle = vpangle.currentValue;
    [main reloadData];
}

- (void)itemanglex_changed {
    point3df val = main.itemAngle;
    val.x = itemangelx.currentValue;
    main.itemAngle = val;
    [main reloadData];
}

- (void)itemangley_changed {
    point3df val = main.itemAngle;
    val.y = itemangely.currentValue;
    main.itemAngle = val;
    [main reloadData];
}

- (void)itemanglez_changed {
    point3df val = main.itemAngle;
    val.z = itemangelz.currentValue;
    main.itemAngle = val;
    [main reloadData];
}

- (void)itemangleoffx_changed {
    point3df val = main.itemAngleStep;
    val.x = itemangelx_off.currentValue;
    main.itemAngleStep = val;
    [main reloadData];
}

- (void)itemangleoffy_changed {
    point3df val = main.itemAngleStep;
    val.y = itemangely_off.currentValue;
    main.itemAngleStep = val;
    [main reloadData];
}

- (void)itemangleoffz_changed {
    point3df val = main.itemAngleStep;
    val.z = itemangelz_off.currentValue;
    main.itemAngleStep = val;
    [main reloadData];
}

- (void)itemposoffx_changed {
    point3df val = main.itemPositionStep;
    val.x = itemposx_off.currentValue;
    main.itemPositionStep = val;
    [main reloadData];
}

- (void)itemposoffy_changed {
    point3df val = main.itemPositionStep;
    val.y = itemposy_off.currentValue;
    main.itemPositionStep = val;
    [main reloadData];
}

- (void)itemposoffz_changed {
    point3df val = main.itemPositionStep;
    val.z = itemposz_off.currentValue;
    main.itemPositionStep = val;
    [main reloadData];
}

- (void)itemspace_changed {
    main.itemSpacing = itemspace.currentValue;
    [main reloadData];
}

- (void)zposoff_changed {
    main.itemZPosStep = zposoff.currentValue;
    [main reloadData];
}

- (void)zpos_changed {
    main.itemZPosition = zpos.currentValue;
    [main reloadData];
}

@end

@implementation MainController

- (id)init {
    self = [super init];
    
    ctlr_draw = [[UICoverDrawer alloc] init];
    ctlr_draw.delegate = self;
    ctlr_draw.dataSource = self;
    ctlr_draw.backgroundColor = [UIColor blueColor];
    self.orientationEnable = UIOrientationEnableAll;
    [ctlr_draw reloadData];

    return self;
}

- (void)dealloc {
    [ctlr_draw release];
    [super dealloc];
}

- (void)loadView {
    MainView* view = [[MainView alloc] initWithZero];
    self.view = view;
    view.main = ctlr_draw;
    [view insertSubview:view.main atIndex:0];
    [view release];    
    [view create];
}

- (void)viewIsLoading {    
//    ctlr_draw.datas = [NSArray arrayWithObjects:
//                       [UICoverDrawData dataWith:@"a" image:[UIImage imageNamed:@"Default.png"]],
//                       [UICoverDrawData dataWith:@"b" image:[UIImage imageNamed:@"Default.png"]], 
//                       [UICoverDrawData dataWith:@"c" image:[UIImage imageNamed:@"Default.png"]], 
//                       [UICoverDrawData dataWith:@"d" image:[UIImage imageNamed:@"Default.png"]], 
//                       [UICoverDrawData dataWith:@"e" image:[UIImage imageNamed:@"Default.png"]], 
//                       [UICoverDrawData dataWith:@"f" image:[UIImage imageNamed:@"Default.png"]], 
//                       [UICoverDrawData dataWith:@"g" image:[UIImage imageNamed:@"Default.png"]], 
//                       nil];
//    
//    //ctlr_draw.datas = [NSArray arrayWithObject:[UICoverDrawData dataWith:@"a" image:[UIImage imageNamed:@"Default.png"]]];
//    
//    [ctlr_draw reloadData];
}

# pragma mark datasource and delegate for covers

- (uint)coverdrawerNumberCovers:(UICoverDrawer*)cd {
    return 6;
}

- (UICoverDrawerItem*)coverdrawerCover:(UICoverDrawer*)cd idx:(uint)idx {
    UICoverDrawerItem *item = [[UICoverDrawerItem alloc] initWithFrame:CGRectZero];
     
    UIView *view = [[UIView alloc] initWithZero];
    view.backgroundColor = [UIColor redColor];
    [item addSubview:view];
    
    item.layer.shadowOpacity = .3f;
    
    return [item autorelease];
}

- (void)coverdrawerItemSelectedChanged:(UICoverDrawer*)cd cur:(UICoverDrawerItem*)curitem pas:(UICoverDrawerItem*)pasitem {
//    NSDictionary *tgt = [self.datas objectAtIndex:curitem.index_sta];
//    NSString *str_info = [NSString stringWithFormat:@"%@", [tgt valueForKey:@"cat_name"]];
//    NSString *str_detail = [NSString stringWithFormat:@"%@", [tgt valueForKey:@"cat_name"]];
//    info_main.text = str_info;
//    info_detail.text = str_detail;
}

- (void)coverdrawerItemDragBegin:(UICoverDrawer*)cd item:(UICoverDrawerItem*)item touchs:(NSSet*)touchs {
    
}

@end

WSI_END_OBJC