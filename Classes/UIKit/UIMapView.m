
# import "Core.h"
# import "UIMapView.h"

WSI_BEGIN_OBJC

@interface UIMapViewPrivate : NSObject <MKMapViewDelegate>

@property (nonatomic, assign) UIMapView *d_owner;

@end

@implementation UIMapViewPrivate

@synthesize d_owner;

@end

@interface UIMapView ()

- (void)__init;

@end

@implementation UIMapView

WSIOBJECT_IMPL;

- (void)__init {
    WSIDECL_PRIVATE_INIT_EX(UIMapView, d_ptr_map);
    
    self.delegate = d_ptr_map;
}

- (id)init {
    self = [super init];
    [self __init];
    return self;
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    [self __init];
    return self;
}

- (void)dealloc {
    self.delegate = nil;
    
    WSIOBJECT_DEALLOC;
    WSIDECL_PRIVATE_DEALLOC_EX(d_ptr_map);
    [super dealloc];
}

@end

WSI_END_OBJC