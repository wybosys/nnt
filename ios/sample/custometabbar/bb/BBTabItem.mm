
# import "Foundation+NNT.h"
# import "BBTabItem.h"

WSI_BEGIN_OBJC

@implementation BBTabItem

@synthesize title   = _title;
@synthesize icon    = _icon;
@synthesize object  = _object;
@synthesize badgeNumber = _badgeNumber;

- (id)initWithTitle:(NSString *)theTitle {
    self = [self init];
    if (self) {
        self.title = theTitle;
    }
    return self;
}

- (id)initWithImage:(NSString *)theImage {
    self = [self init];
    if (self) {
        self.icon = theImage;
    }
    return self;
}

- (id)initWithTitle:(NSString *)title withImage:(NSString *)image {
    self = [self init];
    if (self) {
        self.title = title;
        self.icon = image;
    }
    return self;
}

- (void)dealloc {
    [_title release];
    [_icon release];
    [_object release];
    [super dealloc];
}

- (void)setTabBar:(BBTabBar *)tabBar {
    _tabBar = tabBar;
}

- (NSString *)title {
    return _title;
}

- (NSString *)icon {
    return _icon;
}

- (id)object {
    return _object;
}

- (int)badgeNumber {
    return _badgeNumber;
}

@end

WSI_END_OBJC
