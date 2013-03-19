
# import "Core.h"
# import "UIGridView.h"
# import "WCAArrowIndicator.h"
# import "UILineSeparator.h"

WSI_BEGIN_OBJC

@interface UIGridView ()

- (NSMutableArray*)RowLines;
- (NSMutableArray*)ColLines;

@end

@interface UIGridContent : WSIUIView {
    @public
    UIGridView* _grid;
    BOOL _animated;
}

- (void)relayoutItems:(BOOL)animated;

@end

@implementation UIGridContent

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    _animated = NO;
    
    return self;
}

- (void)layoutSubviews {
    CGRect rc = self.bounds;
    if (CGRectEqualToRect(rc, CGRectZero))
        return;
    
    [self relayoutItems:_animated];
    
    _animated = NO;
}

- (void)removeAllLines {
    for (UIView* each in _grid.RowLines) {
        [each removeFromSuperview];
    }
    for (UIView* each in _grid.ColLines) {
        [each removeFromSuperview];
    }
    
    [_grid.RowLines removeAllObjects];
    [_grid.ColLines removeAllObjects];
}

- (void)relayoutItems:(BOOL)animated {
    uint const count = [_grid.children count];
    if (0 == count || _grid.rows == 0 || _grid.cols == 0)
        return;
    
    // remove lines.
    [self removeAllLines];
    
    // calc each item's position.
    CGRect rc_region = self.bounds;
    CGRect rc_main = CGRectMakeSz(_grid.bounds.size);
    CGRect rc_valid = CGRectMake(rc_main.origin.x + _grid.padding.left,
                                 rc_main.origin.y + _grid.padding.top,
                                 rc_main.size.width - _grid.padding.left - _grid.padding.right,
                                 rc_main.size.height - _grid.padding.top - _grid.padding.bottom);
    
    CGPoint pt_cur = rc_valid.origin;
    
    real doff_width = 0, doff_height = 0, item_width = 0, item_height = 0;
    
    real lyt_cols = _grid.preferredCols ? _grid.preferredCols : _grid.cols;
    doff_width = (rc_valid.size.width - lyt_cols * (_grid.margin.left + _grid.margin.right));
    doff_width /= lyt_cols;
    
    real lyt_rows = _grid.preferredRows ? _grid.preferredRows : _grid.rows;
    doff_height = (rc_valid.size.height - lyt_rows * (_grid.margin.top + _grid.margin.bottom));
    doff_height /= lyt_rows;
    
    if (_grid.preferredItemSize.width != 0) {
        item_width = _grid.preferredItemSize.width;
    } else {
        item_width = doff_width;
    }
    
    if (_grid.preferredItemSize.height != 0) {
        item_height = _grid.preferredItemSize.height;
    } else {
        item_height = doff_height;
    }
    
    // each row.
    for (uint irow = 0; irow < _grid.rows; ++irow) {
        
        pt_cur.y = pt_cur.y + _grid.margin.top;
        
        // echo col.
        for (uint icol = 0; icol < _grid.cols; ++icol) {
            pt_cur.x = pt_cur.x + _grid.margin.left;
            
            uint id_child = irow * _grid.cols + icol;
            if (id_child >= count)
                break;
            
            UIGridViewItem *child = [_grid.children objectAtIndex:id_child];
            
            CGRect rc_child = CGRectMake(pt_cur.x, pt_cur.y, item_width, item_height);
            CGRect rc_frame = CGRectMake(pt_cur.x, pt_cur.y, doff_width, doff_height);
            rc_child = CGRectMoveCenter(rc_child, CGRectCenterPoint2(rc_frame));
            
            // set frame.
            child.frame = CGRectIntegral(rc_child);
            
            // if child is support delay loading, then if child is in visible region, begin its loading.
            if ([child.content conformsToProtocol:@protocol(WSIUIViewInSight)]) {
                [(id<WSIUIViewInSight>)child.content viewInSight];                
            }
            
            if (animated) {
                CATransform3D mat = CATransform3DMakeRotation(M_PI, 0, 1, 0);
                child.layer.opacity = 0.0f;
                child.layer.transform = mat;
            }
            
            pt_cur.x = pt_cur.x + doff_width + _grid.margin.right;
        }
        
        pt_cur.x = rc_valid.origin.x;
        pt_cur.y = pt_cur.y + doff_height + _grid.margin.bottom;
        
        // add row line.
        if (_grid.rowLineStyle) {
            UIHovLineSeparator* line = [[UIHovLineSeparator alloc] initWithLineStyle:_grid.rowLineStyle];
            line.frame = CGRectMake(pt_cur.x, pt_cur.y, rc_region.size.width, 0);
            [self addSubview:line];
            [_grid.RowLines addObject:line];
            [line release];
        }
    }
    
    if (animated) {
        [UIView beginAnimations:nil context:nil];
        [UIView setAnimationDuration:.7f];
        [UIView setAnimationCurve:UIViewAnimationCurveEaseOut];
        [UIView setAnimationBeginsFromCurrentState:YES];
        
        for (UIView *each in _grid.children) {
            each.layer.opacity = 1.f;
            each.layer.transform = CATransform3DIdentity;
        }
        
        [UIView commitAnimations];
    }
}

@end

WSIDECL_PRIVATE_BEGIN(UIGridView, NSObject) {
    UIGridContent* _content;
    NSMutableArray *_rowlines, *_collines;
}

@property (nonatomic, readonly) UIGridContent* content;
@property (nonatomic, readonly) NSMutableArray *rowlines, *collines;

WSIDECL_PRIVATE_IMPL(UIGridView)

@synthesize content = _content;
@synthesize rowlines = _rowlines, collines = _collines;

- (id)init {
    self = [super init];
    
    _content = [[UIGridContent alloc] initWithZero];
    _content->_grid = d_owner;
    
    _rowlines = [[NSMutableArray alloc] init];
    _collines = [[NSMutableArray alloc] init];
    
    return self;
}

- (void)dealloc {
    safe_release(_content);
    safe_release(_rowlines);
    safe_release(_collines);
    
    [super dealloc];
}

WSIDECL_PRIVATE_END

@implementation UIGridView

@synthesize rows = _rows, cols = _cols, preferredCols = _preferredCols, preferredRows = _preferredRows;
@synthesize padding = _padding, margin = _margin;
@synthesize enableFillIndex = _enableFillIndex;
@synthesize children = _children;
@synthesize itemBackgroundFill = _itemBackgroundFill;
@synthesize itemScaleToFit = _itemScaleToFit;
@synthesize itemShadow = _itemShadow;
@synthesize preferredItemSize = _preferredItemSize;
@synthesize itemBorder = _itemBorder;
@synthesize enableAnimated = _enableAnimated;
@synthesize classItem = _classItem;
@synthesize itemHighlight = _itemHighlight;
@synthesize rowLineStyle = _rowLineStyle, colLineStyle = _colLineStyle;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    WSIDECL_PRIVATE_INIT(UIGridView);
    
    self.contentView = d_ptr.content;
    
    _children = [[NSMutableArray alloc] init];
    _enableAnimated = NO;
    _classItem = [UIGridViewItem class];
        
    return self;
}

- (id)initWithFrame:(CGRect)frame rows:(NSUInteger)rows cols:(NSUInteger)cols {
    self = [self initWithFrame:frame];
    if (self == nil)
        return nil;

    _rows = rows;
    _cols = cols;

    return self;
}

- (void)dealloc {
    safe_release(_children);
    safe_release(_itemBackgroundFill);
    safe_release(_itemShadow);
    safe_release(_itemBorder);
    safe_release(_itemHighlight);
    safe_release(_rowLineStyle);
    safe_release(_colLineStyle);
    
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalContentClicked)
WSIEVENT_SIGNAL(kSignalItemClicked)
WSIEVENT_END

- (void)layoutSubviews {
    [super layoutSubviews];
}

- (void)setFrame:(CGRect)frame {
    if (CGRectEqualToRect(self.frame, frame))
        return;
    
    // set.
    [super setFrame:frame];
    
    // set content.
    self.contentSize = self.calcContentSize;
}

- (CGSize)calcItemSize {    
    CGRect rc_main = self.bounds;    
    CGSize rc_valid = CGSizeMake(rc_main.size.width - _padding.left - _padding.right,
                                 rc_main.size.height - _padding.top - _padding.bottom);
    
    NSUInteger each_width = 0;
    NSUInteger each_height = 0;
    
    if (_preferredItemSize.width != 0) {
        each_width = _preferredItemSize.width;
    } else {
        real lyt_cols = _preferredCols ? _preferredCols : _cols;
        each_width = (rc_valid.width - lyt_cols * (_margin.left + _margin.right));
        each_width /= lyt_cols ? lyt_cols : 1;
    }
    
    if (_preferredItemSize.height != 0) {
        each_height = _preferredItemSize.height;
    } else {
        real lyt_rows = _preferredRows ? _preferredRows : _rows;
        each_height = (rc_valid.height - lyt_rows * (_margin.top + _margin.bottom));
        each_height /= lyt_rows ? lyt_rows : 1;
    }
    
    return CGSizeMake(each_width, each_height);
}

- (CGSize)calcContentSize {
    uint const count = [_children count];
    if (0 == count || _rows == 0 || _cols == 0)
        return CGSizeZero;
    
    CGRect rc_main = self.bounds;    
    CGSize rc_valid = CGSizeMake(rc_main.size.width - _padding.left - _padding.right,
                                 rc_main.size.height - _padding.top - _padding.bottom);
    
    real doff_width = 0, doff_height = 0;
    
    real lyt_cols = _preferredCols ? _preferredCols : _cols;
    doff_width = (rc_valid.width - lyt_cols * (_margin.left + _margin.right));
    doff_width /= lyt_cols;
    
    real lyt_rows = _preferredRows ? _preferredRows : _rows;
    doff_height = (rc_valid.height - lyt_rows * (_margin.top + _margin.bottom));
    doff_height /= lyt_rows;
        
    // calc contentSize
    CGSize sz_content = CGSizeZero;
    sz_content.width = (doff_width + _margin.left + _margin.right) * _cols + _padding.left + _padding.right;
    sz_content.height = (doff_height + _margin.top + _margin.bottom) * _rows + _padding.top + _padding.bottom;
    
    return sz_content;
}

- (void)relayoutItems:(BOOL)animated {
    self.contentSize = self.calcContentSize;
    
    // mark animate flag.
    d_ptr.content->_animated = animated;
    
    // relayout.
    [self setNeedsLayout];
}

- (UIGridViewItem*)addChildView:(UIView *)child {
# ifdef WSI_DEBUG
    if ([child isKindOfClass:[UIGridViewItem class]])
        dthrow_msg(@"Type Error", @"Add a item but use the add child method of GridView.");
# endif
    
    if ([_children count] == _cols * _rows)
        return nil;
    
    UIGridViewItem *item = [[_classItem alloc] initWithZero];
    item.scaleToFill = _itemScaleToFit;
    item.highlightFill = _itemHighlight;
    [self addChildView:child item:item];
    [item release];
    return item;
}

- (UIGridViewItem*)addChildView:(UIView *)child item:(UIGridViewItem *)item {
    if ([_children count] == _cols * _rows)
        return nil;
    [child moveTo:CGPointZero];        
    [item addSubview:child];    
    item.content = child;
    [self addChild:item];
    return item;
}

- (UIGridViewItem*)addChild:(UIGridViewItem *)child {
    if ([_children count] == _cols * _rows)
        return nil;
    
    child.content.userInteractionEnabled = NO;
    
    NSMutableArray *rstore = (NSMutableArray*)_children;
    [rstore addObject:child];
    
    child.gridView = self;
    
    // add child.
    [d_ptr.content addSubview:child];
    
    // set shadow
    if (_itemShadow) {
        child.layer.shadowColor = _itemShadow.shadowColor.cgColor;
        child.layer.shadowOffset = _itemShadow.offset;
        child.layer.shadowOpacity = _itemShadow.opacity;
        child.layer.shadowRadius = _itemShadow.radius;
    }
    
    // set border
    if (_itemBorder) {
        child.layer.borderWidth = _itemBorder.lineWidth;
        child.layer.borderColor = _itemBorder.lineColor.cgColor;
    }
    
    // connect signal.
    [child connect:kSignalContentClicked sel:@selector(_act_itemcontent_clicked:) obj:self];
    
    return child;
}

- (void)_act_itemcontent_clicked:(WSIEventObj*)evt {
    // content.
    [self emit:kSignalContentClicked result:evt.result];
    
    // item.
    [self emit:kSignalItemClicked result:(id)evt.sender];
}

- (void)removeItem:(UIGridViewItem *)item {
    NSMutableArray *rstore = (NSMutableArray*)_children;
    [item removeFromSuperview];
    [rstore removeObject:item];
    item.gridView = nil;
}

- (UIGridViewItem*)itemAt:(NSUInteger)row col:(NSUInteger)col {
    NSUInteger pos = row * _cols + col;
    if (pos >= [_children count])
        return nil;
    return [_children objectAtIndex:pos];
}

- (CGPoint)indexOfItem:(UIGridViewItem*)item {
    CGPoint idx = CGPointMake(NSNotFound, NSNotFound);
    uint uidx = [_children indexOfObject:item];
    if (uidx == NSNotFound)
        return idx;
    
    idx.x = uidx / _cols;
    idx.y = uidx % _cols;
    
    return idx;
}

- (void)clearItems {
    NSMutableArray *rstore = (NSMutableArray*)_children;
    for (UIGridViewItem *each in rstore) {
        [each removeFromSuperview];
        each.gridView = nil;
    }
    [rstore removeAllObjects];
}

- (UIGridViewItem*)hitTestForItem:(CGPoint *)pt {
    for (UIGridViewItem *each in _children) {
        CGRect frm = each.frame;
        if (CGRectContainsPoint(frm, *pt)) {
            return each;
        }
    }
    return nil;
}

- (NSMutableArray*)RowLines {
    return d_ptr.rowlines;
}

- (NSMutableArray*)ColLines {
    return d_ptr.collines;
}

@end

_CXXVIEW_IMPL(UIGridView);

WSI_END_OBJC
