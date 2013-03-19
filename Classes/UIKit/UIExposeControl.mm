
# import "Core.h"
# import "UIExposeControl.h"
# import "UIGridView.h"

NNT_BEGIN_OBJC

@interface ExposeItem : UIGridViewItem {
    CGPadding _itemPadding;
}

@property (nonatomic, assign) CGPadding itemPadding;

@end

@implementation ExposeItem

@synthesize itemPadding = _itemPadding;

- (void)layoutSubviews {
    CGRect frm = self.content.frame;
    frm.origin.x += _itemPadding.left;
    frm.origin.y += _itemPadding.top;
    frm.size.width -= _itemPadding.left + _itemPadding.right;
    frm.size.height -= _itemPadding.top + _itemPadding.bottom;
    self.content.frame = frm;
}

@end

@interface UIExposeView : NNTUIView

@property (nonatomic, assign) UIExposeControl* expose;

@end

@implementation UIExposeView

@synthesize expose;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    return self;
}

- (void)layoutSubviews {
    [expose relayoutItems];
}

@end

@implementation UIExposeControl

@synthesize gridView = _gridView;
@dynamic count;
@synthesize prefferedCount = _prefferedCount;
@synthesize alignCenter = _alignCenter;
@synthesize itemPadding = _itemPadding;
@synthesize current = _current;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    _alignCenter = YES;
    
    UIExposeView* content = [[UIExposeView alloc] initWithZero];
    content.expose = self;
    self.contentView = content;
    safe_release(content);
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalContentClicked)
NNTEVENT_END

- (id)addItem:(UIView*)view {
    return [self addItem:view updateLayout:NO];
}

- (id)addItem:(UIView *)view updateLayout:(bool)layout {
    return nil;
}

- (UIView*)itemAt:(NSUInteger)idx {
    return nil;
}

- (UIView*)contentAt:(NSUInteger)idx {
    UIGridViewItem *item = (UIGridViewItem*)[self itemAt:idx];
    return item.content;
}

- (void)clear {    
    // reset grid's frame.
    _gridView.frame = CGRectZero;
    self.contentSize = CGSizeZero;
    
    // remove all items.
    [_gridView clearItems];
}

- (CGSize)bestSizeForItem {
    return CGSizeZero;
}

- (void)relayoutItems {
    PASS;
}

- (NSUInteger)indexOfItem:(UIGridViewItem*)item {
    return nil;
}

- (UIGridViewItem*)current {
    if (_current == nil)
        return [self itemAt:0];
    return _current;
}

@end

@implementation UIExposeHorControl

- (id)initWithFrame:(CGRect)frame {
    self = [self initWithFrame:frame count:0];
    return self;
}

- (id)initWithFrame:(CGRect)frame count:(NSUInteger)count {
    self = [super initWithFrame:frame];
    
    _gridView = [[UIGridView alloc] initWithFrame:CGRectZero rows:1 cols:count];
    _gridView.classItem = [ExposeItem class];
    [self.contentView addSubview:_gridView];
    safe_release(_gridView);
    
    [_gridView connect:kSignalContentClicked sig:kSignalContentClicked obj:self];
    
    self.delegate = self;
    
    return self;
}

- (NSUInteger)count {
    return _gridView.cols;
}

- (void)setCount:(NSUInteger)v {
    _gridView.cols = v;
}

- (id)addItem:(UIView *)view updateLayout:(bool)layout {
    UIGridViewItem *ret = [_gridView addChildView:view];
    if ([ret isKindOfClass:[ExposeItem class]])
        ((ExposeItem*)ret).itemPadding = self.itemPadding;
    
    CGRect rc_grid = _gridView.frame;
    CGRect bd_view = view.bounds;
    
    rc_grid.size.width = rc_grid.size.width + bd_view.size.width;
    rc_grid.size.height = MAX(rc_grid.size.height, bd_view.size.height);
    
    _gridView.frame = rc_grid;
    ret.bounds = bd_view;
        
    if (layout) {
        [self relayoutItems];
    }
    
    return ret;
}

- (UIGridViewItem*)itemAt:(NSUInteger)idx {
    return [_gridView itemAt:0 col:idx];
}

- (NSUInteger)indexOfItem:(UIGridViewItem*)item {
    CGPoint ret = [_gridView indexOfItem:item];
    return ret.y;
}

- (CGSize)bestSizeForItem {
    CGRect const rc_client = self.bounds;
    CGSize sz = CGSizeZero;
    real cnt = TRIEXP(_prefferedCount, _prefferedCount, self.count);
    if (cnt == 0)
        cnt = 1;
    sz.height = rc_client.size.height;
    sz.width = rc_client.size.width / cnt;
    return sz;
}

- (CGRect)frameForGridView {
    uint const cnt = [self count];
    CGRect rc_grid = CGRectZero;
    CGRect rc_best = CGRectMakeSz([self bestSizeForItem]);
    
    for (uint idx = 0; idx < cnt; ++idx) {
        UIGridViewItem* item = (UIGridViewItem*)[self itemAt:idx];      
        
        CGRect bd_item = item.bounds;
        if (CGSizeEqualToSize(bd_item.size, rc_best.size) == NO) {
            [item moveToSize:rc_best.size];
            [item updateLayout:item.bounds];
        }
        
        rc_grid.size.height = MAX(rc_grid.size.height, rc_best.size.height);
        rc_grid.size.width = rc_grid.size.width + rc_best.size.width;        
    }
    
    return rc_grid;
}

- (void)relayoutItems {
    // layout grid.
    uint const cnt = [self count];
    CGRect rc_grid = CGRectZero;
    CGRect rc_best = CGRectMakeSz([self bestSizeForItem]);
    
    for (uint idx = 0; idx < cnt; ++idx) {
        UIGridViewItem* item = (UIGridViewItem*)[self itemAt:idx];
        
        CGRect bd_item = item.bounds;
        if (CGSizeEqualToSize(bd_item.size, rc_best.size) == NO) {
            [item moveToSize:rc_best.size];
            [item updateLayout:item.bounds];
        }
        
        rc_grid.size.height = MAX(rc_grid.size.height, rc_best.size.height);
        rc_grid.size.width = rc_grid.size.width + rc_best.size.width;
    }
    
    CGSize sz_content = rc_grid.size;
    
    if (_alignCenter) {
        CGPoint center = self.clientCenter;
    
        real offset_left = center.x;
        real offset_right = center.x;
    
        if ([_gridView.children count]) {
            UIGridViewItem *item_first = _gridView.children.first;
            UIGridViewItem *item_last = _gridView.children.lastObject;
            
            CGRect rc_first = item_first.bounds;
            CGRect rc_last = item_last.bounds;
        
            offset_left -= CGRectCenterPoint(&rc_first).x;
            offset_right -= CGRectCenterPoint(&rc_last).x;
        }
    
        rc_grid.origin.x = offset_left;
        sz_content.width += offset_left + offset_right;
        
    }
    
    self.contentSize = sz_content;
    _gridView.frame = rc_grid;
}

- (void)scrollToItem:(CGPoint *)pt {    
    CGPoint tpt = *pt;
    tpt.x -= _itemPadding.left;
    tpt.y -= _itemPadding.top;
    CGMargin mgr = _gridView.margin;

    UIGridViewItem *item = nil;
    for (UIGridViewItem *each in _gridView.children) {
        CGRect frame = each.frame;
        frame.origin.x -= mgr.left;
        frame.origin.y -= mgr.top;
        frame.size.width += mgr.left + mgr.right;
        frame.size.height += mgr.top + mgr.bottom;
        
        if ((frame.origin.x <= tpt.x) &&
            (frame.origin.x + frame.size.width > tpt.x)) {
            item = each;
            break;
        }
    }
    if (item == nil) {
        _current = nil;
        return;
    }
    
    // set current.
    _current = item;
    
    // offset.
    CGRect frm = item.frame;
    CGPoint next_offset = CGPointMake(frm.origin.x, 0);
        
    [self setContentOffset:next_offset animated:YES];
}

- (void)scrollToItemByIndex:(NSUInteger)idx {
    UIGridViewItem* item = [self itemAt:idx];
    CGPoint pt = item.frame.origin;
    pt.y = 0;
    [self setContentOffset:pt animated:YES];
    _current = item;
}

# pragma mark delegate 

- (void)scrollViewDidScroll:(UIScrollView *)scrollView {
    [super scrollViewDidScroll:scrollView];
}

- (void)scrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate {
    [super scrollViewDidEndDragging:scrollView willDecelerate:decelerate];
    
    if (decelerate)
        return;
    
    CGPoint cur_offset = scrollView.contentOffset;
    [self scrollToItem:&cur_offset];
}

- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView {
    [super scrollViewDidEndDecelerating:scrollView];
    
    CGPoint cur_offset = scrollView.contentOffset;    
    [self scrollToItem:&cur_offset];
}

@end

@implementation UIExposeVecControl

- (id)initWithFrame:(CGRect)frame {
    self = [self initWithFrame:frame count:0];
    return self;
}

- (id)initWithFrame:(CGRect)frame count:(NSUInteger)count {
    self = [super initWithFrame:frame];
    
    _gridView = [[UIGridView alloc] initWithFrame:CGRectZero rows:count cols:1];
    _gridView.classItem = [ExposeItem class];
    [self addSubview:_gridView];
    safe_release(_gridView);
    
    // redirect content clicked.
    [_gridView connect:kSignalContentClicked sig:kSignalContentClicked obj:self];
    
    // set self as delegate.
    self.delegate = self;
    
    return self;
}

- (NSUInteger)count {
    return _gridView.rows;
}

- (void)setCount:(NSUInteger)v {
    _gridView.rows = v;
}

- (id)addItem:(UIView *)view updateLayout:(bool)layout {
    UIGridViewItem *ret = [_gridView addChildView:view];
    if ([ret isKindOfClass:[ExposeItem class]])
        ((ExposeItem*)ret).itemPadding = self.itemPadding;
    
    CGRect rc_grid = _gridView.frame;
    CGRect bd_view = view.bounds;
            
    rc_grid.size.width = MAX(rc_grid.size.width, bd_view.size.width);
    rc_grid.size.height = rc_grid.size.height + bd_view.size.height;
    
    _gridView.frame = rc_grid;
    ret.bounds = bd_view;
    
    if (layout) {
        [self updateLayout];
    }
    
    return ret;
}

- (void)updateSize {
    uint const cnt = [self count];
    CGRect rc_grid = CGRectZero;
    CGRect rc_best = CGRectMakeSz([self bestSizeForItem]);
    
    for (uint idx = 0; idx < cnt; ++idx) {
        UIGridViewItem* item = (UIGridViewItem*)[self itemAt:idx];      
        
        CGRect bd_item = item.bounds;
        if (CGSizeEqualToSize(bd_item.size, rc_best.size) == NO) {
            [item moveToSize:rc_best.size];
            [item updateLayout:item.bounds];
        }
        
        rc_grid.size.width = MAX(rc_grid.size.width, rc_best.size.width);
        rc_grid.size.height = rc_grid.size.height + rc_best.size.height;        
    }
    
    _gridView.frame = rc_grid;
}

- (UIGridViewItem*)itemAt:(NSUInteger)idx {
    return [_gridView itemAt:idx col:0];
}

- (NSUInteger)indexOfItem:(UIGridViewItem*)item {
    CGPoint ret = [_gridView indexOfItem:item];
    return ret.x;
}

- (void)updateLayout {    
    CGRect frm_grid = CGRectZero;
    CGSize sz_content = CGSizeZero;
    
    if (_alignCenter) {
        CGPoint center = self.clientCenter;
        
        real offset_left = center.y;
        real offset_right = center.y;
        
        if ([_gridView.children count]) {
            UIGridViewItem *item_first = [_gridView.children objectAtIndex:0];
            UIGridViewItem *item_last = [_gridView.children objectAtIndex:[_gridView.children count] - 1];
            
            CGRect rc_first = item_first.bounds;
            CGRect rc_last = item_last.bounds;
            
            offset_left -= CGRectCenterPoint(&rc_first).y;
            offset_right -= CGRectCenterPoint(&rc_last).y;
        }
        
        frm_grid = CGRectMake(_gridView.frame.origin.x, offset_left,
                              _gridView.frame.size.width, _gridView.frame.size.height);
        sz_content = CGSizeMake(_gridView.frame.size.width, _gridView.frame.size.height + offset_left + offset_right);
        
    } else {
        frm_grid = _gridView.frame;
        sz_content = frm_grid.size;
    }
        
    _gridView.frame = frm_grid;
    self.contentSize = sz_content;
}

- (CGSize)bestSizeForItem {
    CGSize sz = CGSizeZero;
    real cnt = TRIEXP(_prefferedCount, _prefferedCount, self.count);
    if (cnt == 0)
        cnt = 1;
    sz.width = self.bounds.size.width;
    sz.height = self.bounds.size.height / cnt;
    return sz;
}

- (void)scrollToItem:(CGPoint *)pt {            
    CGPoint tpt = *pt;
    tpt.x -= _itemPadding.left;
    tpt.y -= _itemPadding.top;
    CGMargin mgr = _gridView.margin;
    mgr.top += 5;
    mgr.bottom += 5;
    
    UIGridViewItem *item = nil;
    for (UIGridViewItem *each in _gridView.children) {
        CGRect frame = each.frame;
        frame.origin.x -= mgr.left;
        frame.origin.y -= mgr.top;
        frame.size.width += mgr.left + mgr.right;
        frame.size.height += mgr.top + mgr.bottom;
        
        if ((frame.origin.y <= tpt.y) &&
            (frame.origin.y + frame.size.height >= tpt.y)) {
            item = each;
            break;
        }
    }
    
    if (item == nil) {
        _current = nil;
        return;
    }
    
    // set current.
    _current = item;
    
    // offset.
    CGRect frm = item.frame;
    CGPoint next_offset = CGPointMake(0, frm.origin.y);
    
    if (item == _gridView.children.lastObject)
        next_offset.y += frm.size.height;
    
    [self setContentOffset:next_offset animated:YES];
}

- (void)scrollToItemByIndex:(NSUInteger)idx {
    UIGridViewItem* item = [self itemAt:idx];
    CGPoint pt = item.frame.origin;
    pt.x = 0;
    [self setContentOffset:pt animated:YES];
    _current = item;
}

- (void)scrollViewDidScroll:(UIScrollView *)scrollView {
    PASS;
}

- (void)scrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate {
    if (decelerate)
        return;
    CGPoint cur_offset = scrollView.contentOffset;
    //cur_offset.y = cur_offset.y / (self.contentSize.height - self.bounds.size.height) * gridView.bounds.size.height;
    real val = self.contentSize.height;// - self.bounds.size.height;
    val = cur_offset.y / val;
    val *= _gridView.bounds.size.height;
    cur_offset.y = val;
    [self scrollToItem:&cur_offset];
}

- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView {
    CGPoint cur_offset = scrollView.contentOffset;
    real val = self.contentSize.height;// - self.bounds.size.height;
    val = cur_offset.y / val;
    val *= _gridView.bounds.size.height;
    cur_offset.y = val;
    //cur_offset.y = cur_offset.y / (self.contentSize.height - self.bounds.size.height) * gridView.bounds.size.height;
    [self scrollToItem:&cur_offset];
}

@end

_CXXCONTROL_IMPL(UIExposeHorControl);
_CXXCONTROL_IMPL(UIExposeVecControl);

NNT_END_OBJC
