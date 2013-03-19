
# import "Core.h"
# import "UIMapAbcView.h"
# import <mapabc/MTMapView.h>

WSI_BEGIN_OBJC

@implementation UIMapAbcView

@synthesize animated;
@synthesize mapabc = _mapabc;

- (void)layoutSubviews {
    CGRect rc_client = self.bounds;
    CGRect rc_map = _mapabc.frame;
    
    if (CGRectEqualToRect(rc_map, rc_client))
        return;
    
    // re create mt map.
    if (_mapabc) {
        [_mapabc removeFromSuperview];
    }
    
    _mapabc = [[MTMapView alloc] initWithFrame:rc_client];
    [self addSubview:_mapabc];
    safe_release(_mapabc);
    
    // reset.
    [_mapabc setRegion:_region animated:animated];
    [_mapabc setCenterCoordinate:_coordcenter animated:animated];
}

- (void)setRegion:(CGRect)region {
    [_mapabc setRegion:region animated:animated];
    _region = region;
}

- (void)setCenterCoordinate:(CGPoint)coordcenter {
    [_mapabc setCenterCoordinate:coordcenter animated:animated];
    _coordcenter = coordcenter;
}

@end

WSI_END_OBJC