
# import "Core.h"
# import "UILayoutGridView.h"
# import "Vector+NNT.h"
# import "Layout.h"
# include <map>
# import "CoreGraphic+NNT.h"
# import "UILabel+NNT.h"

NNT_BEGIN_OBJC

@interface UILayoutGridViewPrivate : NSObject {
    UILayoutGridView *d_owner;
    ::nnt::CGRectLayoutGrid *lyt;
    BOOL add_mode;
    NSUInteger am_row, am_col;
}

@property (nonatomic, assign) UILayoutGridView *d_owner;
@property (nonatomic, assign) ::nnt::CGRectLayoutGrid *lyt;
@property (nonatomic, assign) BOOL add_mode;
@property (nonatomic, assign) NSUInteger am_row, am_col;

@end

@implementation UILayoutGridViewPrivate

@synthesize d_owner;
@synthesize lyt;
@synthesize add_mode, am_row, am_col;

- (id)init {
    self = [super init];
    
    lyt = new ::nnt::CGRectLayoutGrid();
    add_mode = NO;
    
    return self;
}

- (void)dealloc {
    delete lyt; lyt = NULL;
    [super dealloc];
}

@end

@implementation UILayoutGridView

@synthesize rows = _rows, cols = _cols;
@synthesize padding = _padding, margin = _margin;
@synthesize rowLineStyle = _rowLineStyle, colLineStyle = _colLineStyle;
@synthesize reuseLabel = _reuseLabel;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    NNTDECL_PRIVATE_INIT(UILayoutGridView)
    
    _rowlines = [NSMutableArray new];
    _collines = [NSMutableArray new];
    
    return self;
}

- (id)initWithGrid:(NSUInteger)rows cols:(NSUInteger)cols {
    self = [self initWithZero];
    
    _rows = rows;
    _cols = cols;
    d_ptr.lyt->set_cols(_cols);
    d_ptr.lyt->set_rows(_rows);
    
    return self;
}

- (void)dealloc {
    zero_release(_rowLineStyle);
    zero_release(_colLineStyle);
    zero_release(_rowlines);
    zero_release(_collines);
    zero_release(_reuseLabel);
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)setRows:(NSUInteger)val {
    _rows = val;
    d_ptr.lyt->set_rows(_rows);
}

- (void)setCols:(NSUInteger)val {
    _cols = val;
    d_ptr.lyt->set_cols(_cols);
}

- (void)setFrame:(CGRect)frame {
    [super setFrame:frame];
}

- (void)setRowLineStyle:(NgLineStyle *)__rowLineStyle {
    [_rowLineStyle release];
    _rowLineStyle = [__rowLineStyle retain];
    
    for (UIView *line in _rowlines) {
        [line removeFromSuperview];
    }
    [_rowlines removeAllObjects];

    if (_rowLineStyle) {
        for (uint r = 0; r < _rows - 1; ++r) {
            UIView *line = [[UIView alloc] initWithZero];
            
            line.backgroundColor = [UIColor colorWithCGColor:_rowLineStyle.lineColor.cgColor];
            line.frame = CGRectMakeSz(CGSizeMake(0, _rowLineStyle.lineWidth));
            
            [super addSubview:line];
            
            [_rowlines addObject:line];
            
            [line release];
        }
    }
}

- (void)setColLineStyle:(NgLineStyle *)__colLineStyle {
    [_colLineStyle release];
    _colLineStyle = [__colLineStyle retain];
    
    for (UIView *line in _collines) {
        [line removeFromSuperview];
    }
    [_collines removeAllObjects];
    
    if (_colLineStyle) {
        for (uint c = 0; c < _cols - 1; ++c) {
            UIView *line = [[UIView alloc] initWithZero];
            
            line.backgroundColor = [UIColor colorWithCGColor:_colLineStyle.lineColor.cgColor];
            line.frame = CGRectMakeSz(CGSizeMake(0, _colLineStyle.lineWidth));
            
            [super addSubview:line];
            
            [_collines addObject:line];
            
            [line release];
        }
    }
}

- (void)layoutSubviews {
    [self updateLayout];
}

- (void)updateLayout {
    NNTDECL_D(UILayoutGridView);
    
    CGRect f_bounds = self.bounds;
    CGRect bounds = self.bounds;
    bounds.origin.x += _padding.left;
    bounds.origin.y += _padding.top;
    bounds.size.width -= _padding.left + _padding.right;
    bounds.size.height -= _padding.top + _padding.bottom;
    d_ptr.lyt->set_rc(bounds);
    
    BOOL need_rowline = [_rowlines count] != 0;
    
    if (!CGRectEqualToRect(bounds, CGRectZero)) {
        
        std::map<UIView*, CGRect> map;
        
        ::nnt::CGRectLayoutVBox vbox(bounds);
        //vbox.margin_top = margin.top;
        //vbox.margin_bottom = margin.bottom;
        
        for (uint r = 0; r < _rows; ++r) {
            vbox.add_pixel(_margin.top);
            ::nnt::CGRectLayoutHBox hbox(vbox.add_pixel(d_ptr.lyt->value(r) - _margin.top - _margin.bottom));
            vbox.add_pixel(_margin.bottom);
            
            //hbox.margin_left = margin.left;
            //hbox.margin_right = margin.right;
            
            for (uint c = 0; c < _cols; ++c) {
                UIView *view = (UIView*)d_ptr.lyt->get_ctx(r, c);
                
                hbox.add_pixel(_margin.left);
                CGRect rc = hbox.add_pixel(d_ptr.lyt->value(r, c) - _margin.left - _margin.right);
                hbox.add_pixel(_margin.right);
                                
                if (view) {
                    //view.frame = rc;
                    std::map<UIView*, CGRect>::iterator found = map.find(view);
                    if (found == map.end()) {
                        map.insert(std::make_pair(view, rc));
                    } else {
                        found->second = CGRectUnion(rc, found->second);
                    }
                }
            }
            
            // add row lines.
            if (need_rowline && (r != _rows - 1)) {
                UIView *line = [_rowlines objectAtIndex:r];
                line.frame = CGRectMake(0, vbox.get_rc().origin.y, f_bounds.size.width, line.frame.size.height);
                [self bringSubviewToFront:line];
            }
        }
        
        // set frame.
        for (std::map<UIView*, CGRect>::iterator iter = map.begin();
             iter != map.end(); ++iter) {
            UIView* view = iter->first;
            view.frame = iter->second;
        }
    
    }
}

- (UIView*)getRowLine:(NSUInteger)row {
    return [_rowlines objectAtIndex:row];
}

- (NNTUILabel*)addLabel:(NSString *)label row:(NSUInteger)row col:(NSUInteger)col {
    NNTUILabel *ctl = [[NNTUILabel alloc] initWithZero];
    if (_reuseLabel)
        [ctl copyStyle:_reuseLabel];
    ctl.text = label;
    [self addSubview:ctl row:row col:col];
    [ctl release];
    return ctl;
}

- (NNTUILabel*)addLabel:(NSString *)label {
    NNTUILabel *ctl = [[NNTUILabel alloc] initWithZero];
    if (_reuseLabel)
        [ctl copyStyle:_reuseLabel];
    ctl.text = label;
    [self addSubview:ctl];
    [ctl release];
    return ctl;
}

- (void)addSubview:(UIView *)view row:(NSUInteger)row col:(NSUInteger)col {
    
# ifdef NNT_DEBUG
    if (col >= _cols || row > _rows) {
        throw [NSException exceptionWithName:@"::nnt::ui::UILayoutGridView" reason:@"Out of Range" userInfo:nil];
    }
# endif
    
    if (view.superview == nil) {
        [super addSubview:view];
    }
    
    d_ptr.lyt->set_ctx(row, col, view);
}

- (void)setSubview:(UIView *)view row:(NSUInteger)row col:(NSUInteger)col {
    
# ifdef NNT_DEBUG
    if (col >= _cols || row > _rows) {
        throw [NSException exceptionWithName:@"::nnt::ui::UILayoutGridView" reason:@"Out of Range" userInfo:nil];
    }
# endif
    
    d_ptr.lyt->set_ctx(row, col, view);
}

- (UIView*)viewAt:(NSUInteger)row col:(NSUInteger)col {
    
# ifdef NNT_DEBUG
    if (col >= _cols || row > _rows) {
        throw [NSException exceptionWithName:@"::nnt::ui::UILayoutGridView" reason:@"Out of Range" userInfo:nil];
    }
# endif
    
    return (UIView*)d_ptr.lyt->get_ctx(row, col);
}

- (UILabel*)labelAt:(NSUInteger)row col:(NSUInteger)col {
    return (UILabel*)[self viewAt:row col:col];
}

- (id)objectAt:(NSUInteger)row col:(NSUInteger)col {
    return [self viewAt:row col:col];
}

- (id)objectAt:(NSUInteger)idx {
    NSUInteger row = (NSUInteger)(idx / [self cols]);
    NSUInteger col = idx % [self cols];
    return [self objectAt:row col:col];
}

- (void)setLayoutCol:(NSUInteger)col pixel:(int)pixel {
    d_ptr.lyt->set_pixel_col(col, pixel);
}

- (void)setLayoutCol:(NSUInteger)col flex:(real)flex {
    d_ptr.lyt->set_flex_col(col, flex);
}

- (void)setLayoutRow:(NSUInteger)row pixel:(int)pixel {
    d_ptr.lyt->set_pixel_row(row, pixel);
}

- (void)setLayoutRow:(NSUInteger)row flex:(real)flex {
    d_ptr.lyt->set_flex_row(row, flex);
}

- (void)beginAdd {
    d_ptr.add_mode = YES;
    d_ptr.am_row = 0;
    d_ptr.am_col = 0;
}

- (void)endAdd {
    d_ptr.add_mode = NO;
}

- (void)addSubview:(UIView *)view {
    if (d_ptr.add_mode) {
        
        if (view) {
            [self addSubview:view row:d_ptr.am_row col:d_ptr.am_col];
        }
                
        if (++d_ptr.am_col >= self.cols) {
            d_ptr.am_col = 0;
            ++d_ptr.am_row;
        }
        
    } else {
        [super addSubview:view];
    }
}

- (void)clear {
    for (uint r = 0; r < _rows; ++r) {
        for (uint c = 0; c < _cols; ++c) {
            UIView *view = (UIView*)d_ptr.lyt->get_ctx(r, c);
            if (view)
                [view removeFromSuperview];
            d_ptr.lyt->set_ctx(r, c, nil);
        }
    }
}

@end

_CXXVIEW_IMPL(UILayoutGridView);

NNT_END_OBJC
