
# import "Foundation+NNT.h"
# import "MapabcController.h"
# import "UIMapAbcView.h"

NNTAPP_BEGIN_OBJC

@implementation MapabcController

- (void)loadView {
    UIMapAbcView* view = [[UIMapAbcView alloc] initWithZero];
    self.view = view;
    [view release];
}

- (void)viewIsLoading {
    UIMapAbcView* view = (UIMapAbcView*)self.view;
    
    CGPoint mapcenter = CGPointMake(116.39716f, 39.91669f);
    CGSize mapsize = CGSizeMake(0.04f, 0.03f);
    CGRect region = CGRectMake(mapcenter.x - mapsize.width / 2, mapcenter.y + mapsize.height / 2, mapsize.width, mapsize.height);
    [view setRegion:region];
    
    CGPoint coordcenter = CGPointMake(116.39716f, 39.91669f + 0.005f);
    [view setCenterCoordinate:coordcenter];
}

@end

NNTAPP_END_OBJC