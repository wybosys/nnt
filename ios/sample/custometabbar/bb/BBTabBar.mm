
# import "Foundation+NNT.h"
# import "BBTabBar.h"
# import "BBTab.h"
# import "BBTabItem.h"
# import "BBTabBarInternal.h"

WSI_BEGIN_OBJC

@interface BBTabBar ()

- (void)addTab:(BBTab *)tab;

@end

//@interface BBTabBar (BBTabBarInternal)
//@end

@implementation BBTabBar

@synthesize  tabItems = _tabItems;
@synthesize  tabViews = _tabViews;
@synthesize  tabStyle = _tabStyle;

@synthesize selectedTabIndex = _selectedTabIndex;
@synthesize  delegate = _delegate;


- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        self.contentMode = UIViewContentModeRedraw;
        _selectedTabIndex = NSIntegerMax;
        _tabViews = [[NSMutableArray alloc] init];
        //self.backgroundColor = [UIColor yellowColor];
        //self.style =
        self.tabStyle = @"tab:";
    }
    return self;
}

- (void)dealloc
{
    [_tabStyle release];
    [_tabItems release];
    [_tabViews release];
    [super dealloc];
}

- (void)setTabItems:(NSArray *)tabItems {
    [_tabItems release];
    _tabItems = [tabItems retain];
    
    for (int i = 0; i < _tabViews.count; ++i) {
        BBTab *tab = [_tabViews objectAtIndex:i];
        [tab removeFromSuperview];
    }
    
    [_tabViews removeAllObjects];
    
    if (_selectedTabIndex >= _tabViews.count) {
        _selectedTabIndex = 0;
    }
    
    for (int i = 0; i < _tabItems.count; ++i) {
        BBTabItem *tabItem = [_tabItems objectAtIndex:i];
        BBTab *tab = [[[BBTab alloc] initWithItem:tabItem tabBar:self] autorelease];
        [tab addTarget:self action:@selector(tabTouchedUp:) forControlEvents:UIControlEventTouchUpInside];
        [self addTab:tab];
        [_tabViews addObject:tab];
        if (i == _selectedTabIndex) {
            tab.selected = YES;
        }
    }
    [self setNeedsLayout];
}

- (void)addTab:(BBTab *)tab {
    [self addSubview:tab];
}

- (void)tabTouchedUp:(BBTab *)tab {
    self.selectedTabView = tab;
    for (BBTab *obj in self.tabViews) {
        if (tab == obj) {
            obj.backgroundColor = [UIColor redColor];
        } else {
            obj.backgroundColor = [UIColor clearColor];
        }
    }
}

- (void)layoutSubviews {
    [super layoutSubviews];
    [self layoutTabs];
}

# pragma mark-
#pragma mark Public

- (BBTabItem *)selectedTabItem {
    if (_selectedTabIndex != NSIntegerMax) {
        return [_tabItems objectAtIndex:_selectedTabIndex];
    }
    return nil;
}

- (void)setSelectedTabItem:(BBTabItem *)tabItem {
    self.selectedTabIndex = [_tabItems indexOfObject:tabItem];
}

- (BBTab *)selectedTabView {
    if (_selectedTabIndex != NSIntegerMax && _selectedTabIndex < _tabViews.count) {
        return [_tabViews objectAtIndex:_selectedTabIndex];
    }
    return nil;
}

- (void)setSelectedTabView:(BBTab *)tab {
    self.selectedTabIndex = [_tabViews indexOfObject:tab];
}

- (void)setSelectedTabIndex:(NSInteger)selectedTabIndex {
    if (selectedTabIndex != _selectedTabIndex) {
        if (_selectedTabIndex != NSIntegerMax) {
            self.selectedTabView.selected = NO;
        }
        
        _selectedTabIndex = selectedTabIndex;
        
        if (_selectedTabIndex != NSIntegerMax) {
            self.selectedTabView.selected = YES;
        }
        
        if ([(id)self.delegate respondsToSelector:@selector(tabBar:tabSelected:)]) {
            [self.delegate tabBar:self tabSelected:_selectedTabIndex];
        }
        
    }
}

- (void)showTabAtIndex:(NSInteger)tabIndex {
    BBTab *tab = [_tabViews objectAtIndex:tabIndex];
    tab.hidden = NO;
}

- (void)hideTabAtIndex:(NSInteger)tabIndex {
    BBTab *tab = [_tabViews objectAtIndex:tabIndex];
    tab.hidden = YES;
}

@end

WSI_END_OBJC