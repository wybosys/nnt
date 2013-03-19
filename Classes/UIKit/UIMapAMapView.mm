
# import "Core.h"
# import "UIMapAMapView.h"

# import <amap/MAMapKit.h>
# import <amap/MAUserLocation.h>

NNT_BEGIN_OBJC

MACoordinateRegion convert(CGRect const& r)
{
    MACoordinateRegion ret;
    ret.center.latitude = r.origin.y - r.size.height * .5f;
    ret.center.longitude = r.origin.x + r.size.width * .5f;
    ret.span.latitudeDelta = r.size.height;
    ret.span.longitudeDelta = r.size.width;
    return ret;
}

CLLocationCoordinate2D convert(CGPoint const& r)
{
    CLLocationCoordinate2D ret;
    ret.latitude = r.y;
    ret.longitude = r.x;
    return ret;
}

NNTDECL_PRIVATE_BEGIN(UIMaMapView, NNTObject) <MAMapViewDelegate>
{
    MAMapView* mamap;
    CGRect region;
    CGPoint coordcenter;
}

@property (nonatomic, assign) MAMapView* mamap;
@property (nonatomic, assign) CGRect region;
@property (nonatomic, assign) CGPoint coordcenter;

NNTDECL_PRIVATE_IMPL(UIMaMapView)

@synthesize mamap, region, coordcenter;

NNTDECL_PRIVATE_END

@implementation UIMaMapView

@synthesize animated;

- (id)initWithFrame:(CGRect)aFrame {
    self = [super initWithFrame:aFrame];
    NNTDECL_PRIVATE_INIT(UIMaMapView);
    return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)layoutSubviews {   
    CGRect rc_client = self.bounds;
    CGRect rc_map = d_ptr.mamap.frame;
    
    if (CGRectEqualToRect(rc_map, rc_client))
        return;
    
    // re create mt map.
    if (d_ptr.mamap) {
        [d_ptr.mamap removeFromSuperview];
    }
    
    d_ptr.mamap = [[MAMapView alloc] initWithFrame:rc_client];
    d_ptr.mamap.mapType = MAMapTypeStandard;
    d_ptr.mamap.delegate = d_ptr;
    
    [self addSubview:d_ptr.mamap];
    safe_release(d_ptr.mamap);
    
    // reset.
    [d_ptr.mamap setRegion:convert(d_ptr.region) animated:animated];
    [d_ptr.mamap setCenterCoordinate:convert(d_ptr.coordcenter) animated:animated];
}

- (void)setRegion:(CGRect)region animated:(BOOL)_animated {
    [d_ptr.mamap setRegion:convert(region) animated:_animated];
    d_ptr.region = region;
}

- (void)setPosition:(CGPoint)location animated:(BOOL)_animated {
    [d_ptr.mamap setCenterCoordinate:convert(location) animated:_animated];
    d_ptr.coordcenter = location;
}

@end

NNT_END_OBJC