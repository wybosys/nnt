
# import "WSIFoundation.h"
# import "navidialViewController.h"
# import "UINavigationDialController.h"
# import "UINavigationDialLayers.h"
# import "UINavigationDialView.h"
# import "ColorPalette.h"

@implementation navidialViewController

- (id)initWithCoder:(NSCoder *)aDecoder {
    [super initWithCoder:aDecoder];
    
    ctlr_dial = [[UINavigationDialController alloc] init];
        
    return self;
}

- (void)dealloc {
    [ctlr_dial release];
    [super dealloc];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

#pragma mark - View lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    
    ctlr_dial.dialView.frame = self.view.bounds;
    ctlr_dial.dialView.dial.clockwise = NO;
    ctlr_dial.dialView.dial.startAngle -= M_PI_4;
    [ctlr_dial.dialView setPositionByEnum:UINavigationDialPositionCenter];
    
    WSIUIViewController *ctlr = nil;
    
    NSMutableArray *arr = [NSMutableArray new];
    ::wsi::core::ColorWheel cw;
    
    ctlr = [[WSIUIViewController alloc] init];
    ctlr.view.backgroundColor = [UIColor colorWithRGB:cw.next()];
    ctlr.title = @"A";
    ctlr.titleImage = [UIImage imageNamed:@"close_gray.png"];
    [arr addObject:ctlr];
    [ctlr release];
    
    ctlr = [[WSIUIViewController alloc] init];
    ctlr.view.backgroundColor = [UIColor colorWithRGB:cw.next()];
    ctlr.title = @"B";
    ctlr.titleImage = [UIImage imageNamed:@"close_gray.png"];
    [arr addObject:ctlr];
    [ctlr release];
    
    ctlr = [[WSIUIViewController alloc] init];
    ctlr.view.backgroundColor = [UIColor colorWithRGB:cw.next()];
    ctlr.title = @"C";
    ctlr.titleImage = [UIImage imageNamed:@"close_gray.png"];
    [arr addObject:ctlr];
    [ctlr release];
    
    ctlr = [[WSIUIViewController alloc] init];
    ctlr.view.backgroundColor = [UIColor colorWithRGB:cw.next()];
    ctlr.title = @"D";
    ctlr.titleImage = [UIImage imageNamed:@"close_gray.png"];
    [arr addObject:ctlr];
    [ctlr release];
    
    ctlr = [[WSIUIViewController alloc] init];
    ctlr.view.backgroundColor = [UIColor colorWithRGB:cw.next()];
    ctlr.title = @"E";
    ctlr.titleImage = [UIImage imageNamed:@"close_gray.png"];
    [arr addObject:ctlr];
    [ctlr release];
    
    ctlr = [[WSIUIViewController alloc] init];
    ctlr.view.backgroundColor = [UIColor colorWithRGB:cw.next()];
    ctlr.title = @"F";
    ctlr.titleImage = [UIImage imageNamed:@"close_gray.png"];
    [arr addObject:ctlr];
    [ctlr release];
    
    ctlr_dial.itemControllers = arr;    
    [arr release];

    [self.view addSubview:ctlr_dial.view];
}

- (void)viewDidUnload {
    [super viewDidUnload];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
    return YES;
}

@end
