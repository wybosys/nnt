
# import "Core.h"
# import "UITableViewCell+NNT.h"

NNT_BEGIN_OBJC

@implementation NNTUITableViewCell

NNTOBJECT_IMPL_NOSIGNALS

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
    NNTEVENT_SIGNAL(kSignalSelected);
    NNTEVENT_SIGNAL(kSignalDeselected);
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)updateLayout:(CGRect)rect {
    PASS;
}

+ (NNTUITableViewCell*)cell {
    return [[[NNTUITableViewCell alloc] init] autorelease];
}

- (void)setBackgroundFill:(NgFill*)fill {
    if (self.backgroundView == nil) {
        NNTUIView* view = [[NNTUIView alloc] initWithZero];
        view.backgroundFill = fill;
        self.backgroundView = view;
        [view release];
    } else if ([self.backgroundView isKindOfClass:[NNTUIView class]]) {
        NNTUIView* view = (NNTUIView*)self.backgroundView;
        view.backgroundFill = fill;
    }
}

- (NgFill*)backgroundFill {
    if (self.backgroundView && [self.backgroundView isKindOfClass:[NNTUIView class]]) {
        NNTUIView* view = (NNTUIView*)self.backgroundView;
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

_CXXVIEW_IMPL_BEGIN(NNTUITableViewCell)
_CXXVIEW_IMPL_END

// _W(@"DELETE");
// _W(@"INSERT");

NNT_END_OBJC
