
# import "Core.h"
# import "UIItemView.h"

WSI_BEGIN_OBJC

@implementation UIItemView

@synthesize contentView = _contentView;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (void)setContentView:(UIView *)contentView {
    if (_contentView == contentView)
        return;
    
    // remove old.
    [_contentView removeFromSuperview];
    
    // set new.
    _contentView = contentView;
    _contentView.userInteractionEnabled = NO;
    
    // add new.
    [self addSubview:_contentView];
    [self setNeedsLayout];
}

- (void)layoutSubviews {
    if (_contentView)
        _contentView.frame = self.bounds;
}

@end

@implementation UIItemsContainer

@synthesize dataSource = _dataSource, items = _items;

- (id)init {
    self = [super init];
    
    _items = [[NSMutableArray alloc] init];
    
    return self;
}

- (void)dealloc {
    safe_release(_items);
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalContentClicked)
WSIEVENT_SIGNAL(kSignalItemClicked)
WSIEVENT_END

- (NSUInteger)count {
    if ([_dataSource respondsToSelector:@selector(numberOfItems:)])
        return [_dataSource numberOfItems:self];
    return _items.count;
}

- (id)objectAtIndex:(NSUInteger)idx {
    if ([_dataSource respondsToSelector:@selector(itemAtIndex:)])
        return [_dataSource itemAtIndex:idx];
    return [_items objectAtIndex:idx];
}

+ (UIItemView*)View:(UIView*)view {
    UIItemView* item = [[UIItemView alloc] initWithZero];
    item.contentView = view;
    return [item autorelease];
}

- (UIItemView*)addView:(UIView *)view {
    UIItemView* item = [UIItemsContainer View:view];
    [self addItem:item];
    return item;
}

- (void)addItem:(UIItemView*)item {
    [_items addObject:item];
    
    // signal.
    [item connect:kSignalViewClicked sel:@selector(_act_item_clicked:) obj:self];
}

- (void)_act_item_clicked:(WSIEventObj*)evt {
    UIItemView* item = (id)evt.sender;
    
    [self emit:kSignalContentClicked result:item.contentView];
    [self emit:kSignalItemClicked result:item];
}

@end

_CXXVIEW_IMPL(UIItemView);

WSI_END_OBJC
