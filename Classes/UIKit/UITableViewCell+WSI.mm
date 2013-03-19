
# import "Core.h"
# import "UITableViewCell+WSI.h"

WSI_BEGIN_OBJC

@implementation WSIUITableViewCell

WSIOBJECT_IMPL_NOSIGNALS

@synthesize isUsed = _isUsed;
@dynamic backgroundFill;

- (id)init {
    self = [super init];
    
    self.detailTextLabel.backgroundColor = [UIColor clearColor];
    self.textLabel.backgroundColor = [UIColor clearColor];
    self.selectionStyle = UITableViewCellSelectionStyleGray;
    
    return self;
}

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    
    self.detailTextLabel.backgroundColor = [UIColor clearColor];
    self.textLabel.backgroundColor = [UIColor clearColor];
    self.selectionStyle = UITableViewCellSelectionStyleGray;
    
    return self;
}

- (void)initSignals {
    WSIEVENT_SIGNAL(kSignalSelected);
    WSIEVENT_SIGNAL(kSignalDeselected);
}

- (void)dealloc {
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

- (void)updateLayout:(CGRect)rect {
    PASS;
}

+ (WSIUITableViewCell*)cell {
    return [[[WSIUITableViewCell alloc] init] autorelease];
}

- (void)setBackgroundFill:(WCGFill*)fill {
    if (self.backgroundView == nil) {
        WSIUIView* view = [[WSIUIView alloc] initWithZero];
        view.backgroundFill = fill;
        self.backgroundView = view;
        [view release];
    } else if ([self.backgroundView isKindOfClass:[WSIUIView class]]) {
        WSIUIView* view = (WSIUIView*)self.backgroundView;
        view.backgroundFill = fill;
    }
}

- (WCGFill*)backgroundFill {
    if (self.backgroundView && [self.backgroundView isKindOfClass:[WSIUIView class]]) {
        WSIUIView* view = (WSIUIView*)self.backgroundView;
        return view.backgroundFill;
    }
    return nil;
}

- (void)setSelected:(BOOL)selected {
    [super setSelected:selected];
    
    if (selected) {
        [self emit:kSignalSelected];
    } else {
        [self emit:kSignalDeselected];
    }
}

@end

_CXXVIEW_IMPL_BEGIN(WSIUITableViewCell)
_CXXVIEW_IMPL_END

// _W(@"DELETE");
// _W(@"INSERT");

WSI_END_OBJC
