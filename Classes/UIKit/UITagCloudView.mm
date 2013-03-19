
# import "Core.h"
# import "UITagCloudView.h"
# import "Math+WSI.h"

WSI_BEGIN_OBJC

@implementation UITagCloudItem

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    _position = false;
    
    return self;
}

@end

@implementation UITagCloudView

@synthesize items = _items;
@synthesize offal = _offal, offbl = _offbl;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    _items = [[UIItemsContainer alloc] init];
    _offal = _offbl = 0;
    
    // bind signals.
    [self connect:kSignalTouchesBegin sel:@selector(_act_touchesbegin:)];
    [self connect:kSignalTouchesMoved sel:@selector(_act_touchesmoved:)];
    
    return self;
}

- (void)dealloc {
    safe_release(_items);
    [super dealloc];
}

- (UITagCloudItem*)addTag:(UIView *)view {
    UITagCloudItem* item = [[UITagCloudItem alloc] initWithZero];
    item.contentView = view;
    [_items addItem:item];
    safe_release(item);
    
    item.frame = item.contentView.frame;
    [self addSubview:item];
    
    return item;
}

- (void)clear {
    for (UIItemView* each in _items.items) {
        [each removeFromSuperview];
    }
    
    [_items.items removeAllObjects];
}

- (void)relayout:(BOOL)animated {
    CGRect const rc = self.bounds;
    real const radius = MIN(rc.size.width, rc.size.height) * .5f;
    if (radius == 0)
        return;
    
    CGPoint const center = CGRectCenterPoint(&rc);
    
    for (UITagCloudItem* each in _items.items) {
        [self relayoutItem:each radius:radius center:center];
    }
}

- (void)_act_touchesbegin:(WSIEventObj*)evt {
    NSSet* touches = (NSSet*)evt.result;
    _pos = [[touches anyObject] locationInView:self];
}

- (void)_act_touchesmoved:(WSIEventObj*)evt {    
    NSSet* touches = (NSSet*)evt.result;
    CGPoint pt = [[touches anyObject] locationInView:self];
    CGRect rc = self.bounds;
    real offal = (pt.x - _pos.x) / rc.size.width * M_2PI;
    real offbl = (pt.y - _pos.y) / rc.size.height * M_2PI;
    _offal += offal;
    _offbl += offbl;
    
    _pos = pt;
    
    // update.
    [self relayout:NO];
}

- (void)relayoutItem:(UITagCloudItem*)item radius:(real)radius center:(CGPoint)center {
    if (item->_position == false) {
        item->_al = rand01() * M_2PI;
        item->_bl = rand01() * M_2PI;
        item->_position = true;
    }
    
    real al = item->_al + _offal;
    real bl = item->_bl + _offbl;
    
    CGPoint pos;
    pos.x = radius * cos(bl) * sin(al);
    pos.y = radius * sin(bl);
    real z = radius * cos(bl) * cos(al);
    
    pos.x += center.x;
    pos.y += center.y;
    
    [item moveToCenter:pos];
    item.layer.zPosition = z;
}

- (void)updatePerspective {
    CATransform3D mat = CATransform3DIdentity;
    mat.m34 = -0.001;
    self.layer.sublayerTransform = mat;
}

- (void)layoutSubviews {
    CGRect const rc = self.bounds;
    real const radius = MIN(rc.size.width, rc.size.height) * .5f;
    if (radius == 0)
        return;
    
    [self updatePerspective];
    [self relayout:NO];
}

@end

_CXXVIEW_IMPL(UITagCloudView);

WSI_END_OBJC
