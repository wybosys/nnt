
# import "WSIFoundation.h"
# import "MamapController.h"
# import "UIMapAMapView.h"

WSIAPP_BEGIN_OBJC

@implementation MamapController

- (void)loadView {
    UIMaMapView* view = [[UIMaMapView alloc] initWithZero];
    self.view = view;
    [view release];
}

- (void)viewIsLoading {
    UIMaMapView* view = (UIMaMapView*)self.view;
    
    CGPoint mapcenter = CGPointMake(116.39716f, 39.91669f);
    CGSize mapsize = CGSizeMake(0.04f, 0.03f);
    
    CGRect region = CGRectMake(mapcenter.x - mapsize.width / 2, mapcenter.y + mapsize.height / 2, mapsize.width, mapsize.height);
    [view setRegion:region animated:NO];
    
    CGPoint coordcenter = CGPointMake(116.39716f, 39.91669f + 0.005f);
    [view setPosition:coordcenter animated:NO];
}

@end

WSIAPP_END_OBJC