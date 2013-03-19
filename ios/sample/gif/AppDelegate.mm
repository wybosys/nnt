
# import "Foundation+NNT.h"
# import "AppDelegate.h"
# import "WSIResource.h"
# import "GifParser.h"

using namespace wsi;

@interface MainView : WSIUIView {
    WSIUIImageView* image;
    WSIUIImageView* image2;
    WSIUIImageView* image3;
    WSIUIImageView* image4;
}

@end

@implementation MainView

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];    
    
    image = [[WSIUIImageView alloc] initWithFrame:CGRectMake(0, 0, 200, 200)];
    [self addSubview:image];
    [image release];
    
    image2 = [[WSIUIImageView alloc] initWithFrame:CGRectMake(0, 200, 200, 200)];
    [self addSubview:image2];
    [image2 release];
    
    image3 = [[WSIUIImageView alloc] initWithFrame:CGRectMake(0, 400, 200, 200)];
    [self addSubview:image3];
    [image3 release];
    
    image4 = [[WSIUIImageView alloc] initWithFrame:CGRectMake(0, 600, 200, 200)];
    [self addSubview:image4];
    [image4 release];
    
    NSData* da = nil;
    
    //da = [WSIResource DataOf:@"1.gif"];
    //[image loadData:da];
    
    da = [WSIResource DataOf:@"2.jpg"];
    [image2 loadData:da];
    
    da = [WSIResource DataOf:@"3.png"];
    [image3 loadData:da];
    
    [image4 loadURL:[NSURL URLWithString:@"http://im.qq.com/face/authed/5/b2646.gif"] cache:YES];
    
    return self;
}

@end

@interface MainController : WSIUIViewController

@end

@implementation MainController

- (void)loadView {
    MainView* view = [[MainView alloc] initWithZero];
    self.view = view;
    [view release];
}

@end

@implementation WSIAppDelegate

- (void)load {
    MainController* ctlr = [[MainController alloc] init];
    self.rootViewController = ctlr;
    [ctlr release];
}

@end
