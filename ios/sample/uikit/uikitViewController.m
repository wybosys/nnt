
# import "Foundation+NNT.h"
# import "uikitViewController.h"
# import "UIOAToggleView.h"

@interface drawView : WSIUIView

@end

@implementation drawView

- (void)drawRect:(CGRect)rect {
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    CGPoint pt_center = CGRectCenterPoint(&rect);
    
    CGColorRef color_fill = [UIColor blackColor].CGColor;
    real radius_out = rect.size.width * .5f;
    real radius_in = radius_out * .8f;
    real start = 0;
    real end = M_PI_4;
    real offset = -M_PI_2;

    CGContextSetFillColorWithColor(ctx, color_fill);
    
    CGMutablePathRef fill_path = CGPathCreateMutable();
        
    // add out
    CGPathAddArc(fill_path, nil, pt_center.x, pt_center.y, radius_out, start + offset, end + offset, false);
    
    // add in
    CGPathAddArc(fill_path, nil, pt_center.x, pt_center.y, radius_in, end + offset, start + offset, true);
    
    // fill path
    CGContextAddPath(ctx, fill_path);

    CGPathRelease(fill_path);
    
    CGContextFillPath(ctx);
}

@end

@implementation uikitViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    WSIUIView *view = (WSIUIView*)self.view;
        
    WSIUITextField *txf = [[WSIUITextField alloc] initWithFrame:CGRectMake(0, 0, 500, 50)];
    txf.placeholder = @"xx@xx.com";
    txf.validRestrict = @"^[a-zA-Z0-9_]+@[a-zA-Z0-9_]+(?:\\.[a-zA-Z0-9]+)+$";
    txf.font = [UIFont systemFontOfSize:40];
    txf.keyboardType = UIKeyboardTypeAlphabet;
    [view addSubview:txf];
    [txf release];
    
    NSMutableArray *arr = [NSMutableArray array];
    WSIUIViewController *ctlr = nil;
    
    ctlr = [[WSIUIViewController alloc] init];
    ctlr.title = @"RED";
    ctlr.view.backgroundColor = [UIColor redColor];
    [arr addObject:ctlr];
    
    ctlr = [[WSIUIViewController alloc] init];
    ctlr.title = @"GREEN";
    ctlr.view.backgroundColor = [UIColor greenColor];
    [arr addObject:ctlr];
    
    WSIUITableViewController* table = [[WSIUITableViewController alloc] init];
    table.datas = [NSMutableArray arrayWithObjects:@"A", nil];
    [table.tableView enablePullMoreHeader];
    table.title = @"TABLE";
    [arr addObject:table];
    [table release];
    
    UISegmentedController *seg = [[UISegmentedController alloc] initWithItems:arr];
    seg.view.layer.borderColor = [UIColor blackColor].CGColor;
    seg.view.layer.borderWidth = 2;
    seg.segmentedPosition = UISegmentedControlPositionBottom;
    seg.segmentedPadding = CGPaddingMake(.1f, .1f, .2f, .2f);
    seg.segmentedControl.defaultColor = [UIColor orangeColor];
    seg.segmentedControl.selectedColor = [UIColor grayColor];
    seg.view.frame = CGRectMake(0, 50, 500, 200);
    [view addSubview:seg.view];
    [self storeSet:@"seg" obj:seg];
    [seg release];
    
    WSIUILabel* lbl = [[WSIUILabel alloc] initWithFrame:CGRectMake(0, 300, 100, 100)];
    lbl.backgroundColor = [UIColor yellowColor];
    //lbl.enableMarquee = YES;
    lbl.scaleToFit = YES;
    lbl.text = @"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY";
    //lbl.text = @"ZZZ";
    lbl.textAlignment = UITextAlignmentCenter;
    [view addSubview:lbl];
    [lbl release];
     
    NSString* url = @"http://image.91rb.com/2008/12/10/92402e8b687af19f1c88ee65819686b8.jpg";
    WSIUIImageView* img = [[WSIUIImageView alloc] initWithURL:[NSURL URLWithString:url] cache:NO];
    img.urlForScale = [NSURL URLWithString:url];
    img.backgroundColor = [UIColor blackColor];
    img.userInteractionEnabled = YES;
    img.contentMode = UIViewContentModeScaleAspectFill;
    [img connect:kSignalViewClicked sel:@selector(activeScale)];
    img.frame = CGRectMake(0, 400, 50, 50);
    [view addSubview:img];
    [img release];
    
    UIImageSwitch* imgswh = [[UIImageSwitch alloc] initWithFrame:CGRectMake(100, 400, 100, 100)];
    imgswh.backgroundColor = [UIColor redColor];
    imgswh.image = [UIImage imageNamed:@"choose.png"];
    [view addSubview:imgswh];
    [imgswh release];
    
    WSIUIActivityIndicatorView* activity = [[WSIUIActivityIndicatorView alloc] initWithFrame:CGRectMake(0, 500, 100, 100)];    
    activity.backgroundColor = [UIColor blackColor];
    activity.showProgressRing = YES;
    [view addSubview:activity];
    [activity startAnimating];
    [activity release];

    drawView* draw = [[drawView alloc] initWithFrame:CGRectMake(0, 600, 200, 200)];
    [view addSubview:draw];
    [draw release];
    
    UIFlowView* flow = [[UIFlowView alloc] initWithFrame:CGRectMake(200, 600, 200, 100)];
    flow.margin = CGMarginMake(5, 0, 5, 5);
    flow.backgroundColor = [UIColor grayColor];
    for (uint i = 0; i < 10; ++i) {
        UIBevelButton* button = [[UIBevelButton alloc] initWithZero];
        button.frame = CGRectMakeWH(50, 50);
        [flow addSubview:button];
        [button release];
    }
    [flow updateLayout];
    [view addSubview:flow];
    [flow release];
    
    UIFlowView *flow2 = [[UIFlowView alloc] initWithFrame:CGRectMake(300, 600, 200, 200)];
    flow2.margin = CGMarginMake(5, 5, 5, 5);
    flow2.backgroundColor = [UIColor redColor];
    for (int i = 0; i < 10; ++i) {
        UIImageSwitch *image = [[UIImageSwitch alloc] initWithFrame:CGRectMake(55, 55, 55, 55)];
        image.image = [UIImage imageNamed:@"choose.png"];
        [flow2 addSubview:image];
        [image release];
    }
    [flow2 updateLayout];
    [view addSubview:flow2];
    [flow2 release];
    
    //UIOAToggleView
    UIOAToggleView *toggleView = [[UIOAToggleView alloc] initWithFrame:CGRectMake(400, 800, 200, 200)];
    [toggleView updateLayout];
    [view addSubview:toggleView];
    [toggleView release];
    
    //[self performSelector:@selector(act_kill:) withObject:lbl afterDelay:2.f];
    [self performSelectorInBackground:@selector(act_progress:) withObject:activity];
    
    //! contact field.
    UIContactField* contact = [[UIContactField alloc] initWithFrame:CGRectMake(0, 250, 200, 30)];
    //contact.backgroundColor = [UIColor orangeColor];
    contact.borderStyle = UITextBorderStyleLine;
    [view addSubview:contact];
    [contact release];
    
    WSIUITextField* field = [[WSIUITextField alloc] initWithFrame:CGRectMake(0, 280, 200, 30)];
    field.borderStyle = UITextBorderStyleLine;
    [view addSubview:field];
    [field release];
}

- (void)act_progress:(WSIUIActivityIndicatorView*)view {
    while (1) {
        view.progressValue += 0.1;
        
        sleep(1);
    }
}

- (void)act_kill:(WSIUILabel*)lbl {
    [lbl removeFromSuperview];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return YES;
}

@end
