
# import "WSIFoundation.h"
# import "TestView.h"
# import "BBTabBar.h"
# import "BBTab.h"
# import "BBTabItem.h"
# import "BBTabCustom.h"

WSI_BEGIN_OBJC

@implementation TestView

- (void)viewIsLoading {
    self.view.backgroundColor = [UIColor grayColor];
//    BBTabStrip *tabBar = [[BBTabStrip alloc] initWithFrame:CGRectMake(0, 40, self.view.frame.size.width, 40)];
//    tabBar.delegate = self;
//    WSI_AUTORELEASEPOOL_BEGIN
//    tabBar.tabItems = [NSArray arrayWithObjects:
//                       [[[BBTabItem alloc] initWithTitle:@"qqq" withImage:@"3.png"] autorelease],
//                       [[[BBTabItem alloc] initWithTitle:@"www" withImage:@"3.png"] autorelease],
//                       [[[BBTabItem alloc] initWithTitle:@"eee" withImage:@"3.png"] autorelease],
//                       [[[BBTabItem alloc] initWithTitle:@"rrr" withImage:@"3.png"] autorelease],
//                       [[[BBTabItem alloc] initWithTitle:@"ttt" withImage:@"3.png"] autorelease],
//                       [[[BBTabItem alloc] initWithTitle:@"aaa" withImage:@"3.png"] autorelease],
//                       [[[BBTabItem alloc] initWithTitle:@"sss" withImage:@"3.png"] autorelease],
//                       [[[BBTabItem alloc] initWithTitle:@"ddd" withImage:@"3.png"] autorelease],
//                       [[[BBTabItem alloc] initWithTitle:@"fff" withImage:@"3.png"] autorelease],
//                       [[[BBTabItem alloc] initWithTitle:@"ccc" withImage:@"3.png"] autorelease],
//                       nil];
//    WSI_AUTORELEASEPOOL_END
//    [self.view addSubview:tabBar];
//    [tabBar release];
    
    //[[[BBTabItem alloc] initWithTitle:@"ppp"] autorelease],
   
    BBTabGrid *tabBar1 = [[BBTabGrid alloc] initWithFrame:CGRectMake(0, 0, 320, 41)];
    tabBar1.delegate = self;
    WSI_AUTORELEASEPOOL_BEGIN
    tabBar1.tabItems = [NSArray arrayWithObjects:
                        [[[BBTabItem alloc] initWithTitle:@"Item1"] autorelease],
                        [[[BBTabItem alloc] initWithTitle:@"Banana"] autorelease],
                        [[[BBTabItem alloc] initWithTitle:@"Cherry"] autorelease],
                        [[[BBTabItem alloc] initWithTitle:@"Orange"] autorelease],
                        [[[BBTabItem alloc] initWithTitle:@"Pineapple"] autorelease],
                        [[[BBTabItem alloc] initWithTitle:@"Grape"] autorelease],
                        [[[BBTabItem alloc] initWithTitle:@"Mango"] autorelease],
                        [[[BBTabItem alloc] initWithTitle:@"Blueberry"] autorelease],
                        [[[BBTabItem alloc] initWithTitle:@"Apple"] autorelease],
                         [[[BBTabItem alloc] initWithTitle:@"SRGsdf"] autorelease],
                         nil];
    WSI_AUTORELEASEPOOL_END
    [self.view addSubview:tabBar1];
    
}

- (void)tabBar:(BBTabBar *)tabBar tabSelected:(NSInteger)selectedIndex {
    //  UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil message:[NSString stringWithFormat:@"%d selected",selectedIndex] delegate:nil cancelButtonTitle:nil otherButtonTitles:nil, nil];
//    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil 
//                                                    message:[NSString stringWithFormat:@"%d selected",selectedIndex] 
//                                                   delegate:nil 
//                                          cancelButtonTitle:@"OK" 
//                                          otherButtonTitles:nil, nil];
//    [alert show];
//    [alert release];
}

@end

WSI_END_OBJC