
# import "Foundation+NNT.h"
# import "BBTabCustom.h"
# import "BBLayouts.h"
# import "BBTabBarInternal.h"
# import "UIViewAdditions.h"

WSI_BEGIN_OBJC

@implementation BBTabGrid

@synthesize columnCount = _columCount;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if(self){
        _columCount = 3;
        
    }
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (NSInteger)rowCount {
    return ceil((float)self.tabViews.count / self.columnCount);
}

- (CGSize)layoutTabs {
    if (self.frame.size.width && self.frame.size.height) {
        BBGridLayout *layout = [[BBGridLayout alloc] init];
        layout.padding = 1;
        layout.columnCount = [self columnCount];
        return [layout layoutSubviews:self.tabViews forView:self];
    } else {
        return self.frame.size;
    }
}

- (CGSize)sizeThatFits:(CGSize)size {
    CGSize styleSize = [super sizeThatFits:size];
    for (BBTab *tab in self.tabViews) {
        CGSize tabSize = [tab sizeThatFits:CGSizeZero];
        NSInteger rowCount = [self rowCount];
        return CGSizeMake(size.width,
                          rowCount ? tabSize.height * [self rowCount] + styleSize.height : 0);
    }
    
    return size;
}

- (void)setTabItems:(NSArray *)tabItems {
    [super setTabItems:tabItems];
}

@end


@interface BBTabStrip ()

- (void)updateOverflow;

@end

@implementation BBTabStrip

- (id)initWithFrame:(CGRect)frame  {
	self = [super initWithFrame:frame];
    if (self) {
        _scrollView = [[UIScrollView alloc] init];
        _scrollView.scrollEnabled = YES;
        _scrollView.scrollsToTop = NO;
        _scrollView.showsVerticalScrollIndicator = NO;
        _scrollView.showsHorizontalScrollIndicator = NO;
        _scrollView.autoresizingMask = UIViewAutoresizingFlexibleWidth;
        [self addSubview:_scrollView];
        
        self.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    }
    
    return self;
}

- (void)dealloc {
    safe_release(_overLeft);
    safe_release(_overRight);
    safe_release(_scrollView);
    [super dealloc];
}

- (void)addTab:(BBTab*)tab {
    [_scrollView addSubview:tab];
    _contentSizeCached = NO;
}


- (CGSize)layoutTabs {
    if (_contentSizeCached) {
        return _contentSize;
    }
    
    CGSize size = [super layoutTabs];
    
    CGPoint contentOffset = _scrollView.contentOffset;
    _scrollView.frame = self.bounds;
    
    _scrollView.contentSize = CGSizeMake(size.width + mTabMargin, self.frame.size.height);
    _scrollView.contentOffset = contentOffset;
    
    _contentSize = size;
    _contentSizeCached = YES;
    
    return size;
}

- (void)layoutSubviews {
    [super layoutSubviews];
    [self updateOverflow];
}

- (void)setTabItems:(NSArray*)tabItems {
    [super setTabItems:tabItems];
    _contentSizeCached = NO;
    [self updateOverflow];
}

- (void)updateOverflow {
    if (_scrollView.contentOffset.x < (_scrollView.contentSize.width-self.frame.size.width)) {
        if (!_overRight) {
            _overRight = [[UIView alloc] init];
            _overRight.backgroundColor = [UIColor yellowColor];
            //_overRight.style = TTSTYLE(tabOverflowRight);
            _overRight.userInteractionEnabled = NO;
            [_overLeft sizeToFit];
            [self addSubview:_overRight];
        }
        
        _overRight.left = self.width - _overRight.width;
        _overRight.hidden = NO;
        
    } else {
        _overRight.hidden = YES;
    }
    
    
    if (_scrollView.contentOffset.x > 0) {
        if (!_overLeft) {
            _overLeft = [[UIView alloc] init];
            _overLeft.backgroundColor = [UIColor blueColor];
            //_overLeft.style = TTSTYLE(tabOverflowLeft);
            _overLeft.userInteractionEnabled = NO;
            [_overLeft sizeToFit];
            [self addSubview:_overLeft];
        }
        //_overLeft.frame = CGRectMake(10, 0, 20, self.frame.size.height);
        _overLeft.hidden = NO;
        
    } else {
        _overLeft.hidden = YES;
    }
}


@end

WSI_END_OBJC