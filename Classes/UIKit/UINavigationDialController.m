
# import "Core.h"
# import "UINavigationDialController.h"
# import "UINavigationDial.h"
# import "UINavigationDialView.h"
# import "UIDesktop.h"

NNT_BEGIN_OBJC

NSString *kIdentifyDialItem = @"::wsi::ui::dial::item";

@interface UINavigationDialControllerPrivate : NSObject {
    UINavigationDialController *d_owner;
    NNTUIDesktop *desktop;
}

@property (nonatomic, assign) UINavigationDialController *d_owner;
@property (nonatomic, retain) NNTUIDesktop *desktop;

@end

@implementation UINavigationDialControllerPrivate

@synthesize d_owner;
@synthesize desktop;

- (id)init {
    self = [super init];
    
    desktop = [[NNTUIDesktop desktop] retain];
    
    return self;
}

- (void)dealloc {
    zero_release(desktop);
    [super dealloc];
}

@end

@interface UINavigationDialController (hidden)

- (UINavigationDialItem*)_find_item_of_controller:(NNTUIViewController*)ctlr;

@end

@implementation UINavigationDialController (hidden)

- (UINavigationDialItem*)_find_item_of_controller:(NNTUIViewController *)ctlr {
    for (UINavigationDialItem *item in self.dialView.dial.items) {
        if (item.viewController == ctlr)
            return item;
    }
    return nil;
}

@end

@implementation UINavigationDialController

@synthesize itemControllers;
@synthesize selectedController;

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT_EX(UINavigationDialController, d_ptr_dial);

    return self;
}

- (void)dealloc {
    zero_release(itemControllers);
    
    NNTDECL_PRIVATE_DEALLOC_EX(d_ptr_dial);
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalSelectChanged)
NNTEVENT_END

- (void)loadView {
    UINavigationDialView *view = [[UINavigationDialView alloc] initWithZero];
    self.view = view;
    [view release];
    
    UINavigationDial *dial = view.dial;
    [dial connect:kSignalDialClicked sel:@selector(act_dial_item_clicked:) obj:self];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    UINavigationDialView *view = (UINavigationDialView*)self.view;
    [view.dial moveTo:CGPointMake(0, 0)];
}

- (void)act_dial_item_clicked:(NNTEventObj*)obj {
    UINavigationDialItem *item = obj.result;
    if (item == nil)
        return;
    NNTUIViewController *ctlr = item.viewController;
    self.selectedController = ctlr;
}

- (UINavigationDialView*)dialView {
    UINavigationDialView *view = (UINavigationDialView*)self.view;
    return view;
}

- (void)setItemControllers:(NSArray *)__itemControllers {
    [self clear];
    
    itemControllers = [__itemControllers retain];
    
    UINavigationDialView *view = (UINavigationDialView*)self.view;
    
    NSMutableArray *arr = [[NSMutableArray alloc] init];
    for (NNTUIViewController *each in itemControllers) {
# ifdef NNT_DEBUG
        if ([each isKindOfClass:[NNTUIViewController class]] == NO) {
            [arr release];
            @throw [NSException exceptionWithName:@"type error" reason:@"must be NNTUIViewController" userInfo:nil];
        }
# endif
        
        UINavigationDialItem *item = [[UINavigationDialItem alloc] init];
        
        item.viewController = each;
        item.imageMaskColor = view.dial.itemDefaultColor;
        item.labelFill = view.dial.labelFill;
        item.labelTextStyle = view.dial.labelTextStyle;
        
        [each attachSet:kIdentifyDialItem obj:item];
        
        [arr addObject:item];
        [item release];
    }
    view.dial.items = arr;
    [arr release];
    
    if (self.selectedController == nil)
        self.selectedController = [itemControllers objectAtIndex:0 null:nil];
}

- (void)clear {
    [itemControllers release];
    itemControllers = nil;
}

- (void)selectController:(NNTUIViewController *)ctlr animated:(BOOL)animated {
    if (ctlr == selectedController)
        return;
    
    // set select.
    UINavigationDialView *view = (UINavigationDialView*)self.view;    
    
    UINavigationDialItem *item = nil;
    
    item = [self _find_item_of_controller:selectedController];
    item.imageMaskColor = view.dial.itemDefaultColor;
    
    [selectedController viewDidDisappear:YES];
    selectedController = ctlr;
    [selectedController viewDidAppear:YES];
    
    view.contentView = ctlr.view;
    
    // update appear.
    item = [self _find_item_of_controller:ctlr];
    item.imageMaskColor = view.dial.itemSelectedColor;
    
    // event
    [self emit:kSignalSelectChanged];
}

- (void)setSelectedController:(NNTUIViewController *)__selectedController {
    [self selectController:__selectedController animated:NO];
}

@end

NNT_END_OBJC