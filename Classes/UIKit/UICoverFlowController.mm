
# import "Core.h"
# import "UICoverFlowController.h"
# import "UICoverFlow.h"
# import "UICoverFlowItem.h"

NNT_BEGIN_OBJC

@implementation UICoverFlowData

@synthesize image = _image, imageURL = _imageURL;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    zero_release(_image);
    zero_release(_imageURL);
    [super dealloc];
}

@end

@implementation UICoverFlowController

@dynamic coverFlow;
@synthesize datas = _datas;
@synthesize itemClass = _itemClass;

- (id)init {
    self = [super init];
    
    _itemClass = [UICoverFlowItem class];
    _datas = [[NSMutableArray alloc] init];
    
    return self;
}

- (void)dealloc {
    zero_release(_datas);    
    [super dealloc];
}

- (void)loadView {
    UICoverFlow *view = [[UICoverFlow alloc] initWithZero];
    self.view = view;
    [view release];
    
    view.delegate = self;
    view.items.dataSource = self;
}

- (UICoverFlow*)coverFlow {
    return (UICoverFlow*)self.view;
}

- (void)reloadData {
    [self.coverFlow reloadData];
}

- (id)itemAtIndex:(NSUInteger)idx {
    UICoverFlowItem* item = [[_itemClass alloc] init];
    UICoverFlowData* data = [_datas objectAtIndex:idx];
    
    if (data.image) {
        [item setImage:data.image];
    } else if (data.imageURL) {
        [item loadURL:data.imageURL];
    }
    
    return [item autorelease];
}

- (NSUInteger)numberOfItems:(id)obj {
    return _datas.count;
}

@end

NNT_END_OBJC
