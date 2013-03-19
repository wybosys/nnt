
# import "Foundation+NNT.h"
# import "BBTab.h"

WSI_BEGIN_OBJC

@implementation BBTab

@synthesize tabItem = _tabItem;

- (id)init {
    self = [super init];
    if (self) {
        //[self initWithType:WSIUIButtonTypeInnerRound];   
    }
    return self;
}


- (id)initWithItem:(BBTabItem *)tabItem tabBar:(BBTabBar *)tabBar {
    self = [self init];
    if(self) {
        self.tabItem = tabItem;
    }
    return self;
}

- (void)dealloc
{
    [_tabItem release];
    [super dealloc];
}

- (void)updateBadgeNumber {
    
}

- (void)setTabItem:(BBTabItem *)tabItem {
    if (tabItem != _tabItem) {
        [_tabItem performSelector:@selector(setTabBar:) withObject:nil];
        [_tabItem release];
        _tabItem = [tabItem retain];
        [_tabItem performSelector:@selector(setTabBar:) withObject:self];    
        
        [self setTitle:[_tabItem title] forState:UIControlStateNormal];
        
        [self setImage:[UIImage imageNamed:[_tabItem icon]] forState:UIControlStateNormal];
        //[self setBackgroundImage:[UIImage imageNamed:[_tabItem icon]] forState:UIControlStateNormal];
    }    
}

@end

WSI_END_OBJC