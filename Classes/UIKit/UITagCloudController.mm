
# import "Core.h"
# import "UITagCloudController.h"

NNT_BEGIN_OBJC

NNT_USINGCXXNAMESPACE;

@implementation UITagCloudController

@synthesize dataSource = _dataSource;

- (id)init {
    self = [super init];
    
    _dataSource = self;
    
    return self;
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalContentClicked)
NNTEVENT_SIGNAL(kSignalItemClicked)
NNTEVENT_END

- (void)loadView {
    UITagCloudView* view = [[UITagCloudView alloc] initWithZero];
    self.view = view;
    [view release];
}

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)clear {
    UITagCloudView* view = (UITagCloudView*)self.view;
    [view clear];
}

- (void)reloadData {
    UITagCloudView* view = (UITagCloudView*)self.view;
        
    // add item
    NSUInteger count = [_dataSource tagCloudNumberOfTags:self];
    for (uint i = 0; i < count; ++i) {
        UIView* child = [_dataSource tagCloudViewOf:self index:i];
        UIItemView* item = [view addTag:child];                
        [item connect:kSignalViewClicked sel:@selector(_act_item_clicked:) obj:self];
    }
    
    // layout.
    [view relayout:YES];
}

- (void)_act_item_clicked:(NNTEventObj*)evt {
    UIItemView* item = (UIItemView*)evt.sender;
    [self emit:kSignalContentClicked result:item.contentView];
    [self emit:kSignalItemClicked result:item];
}

// data.

- (NSUInteger)tagCloudNumberOfTags:(UITagCloudController*)cd {
    return 0;
}

- (UIView*)tagCloudViewOf:(UITagCloudController*)cd index:(NSUInteger)index {
    return nil;
}

@end

_CXXCONTROLLER_IMPL_BEGIN(UITagCloudController)

- (NSUInteger)tagCloudNumberOfTags:(UITagCloudController*)cd {
    ui::ITagCloudController* cxx = (ui::ITagCloudController*)self._cxxobj;
    return cxx->count();
}

- (UIView*)tagCloudViewOf:(UITagCloudController*)cd index:(NSUInteger)index {
    ui::ITagCloudController* cxx = (ui::ITagCloudController*)self._cxxobj;
    return cxx->item(index);
}

_CXXCONTROL_IMPL_END

NNT_END_OBJC
