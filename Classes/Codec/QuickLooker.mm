
# import "Core.h"
# import "QuickLooker.h"
# import <QuickLook/QuickLook.h>
# import "Resource+NNT.h"

NNT_BEGIN_OBJC

NNTDECL_PRIVATE_BEGIN(QuickLookerController, NNTObject) <QLPreviewControllerDataSource, QLPreviewControllerDelegate>
{
    QLPreviewController* _previewer;
}

@property (nonatomic, retain) QLPreviewController* previewer;

NNTDECL_PRIVATE_IMPL(QuickLookerController)

@synthesize previewer = _previewer;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    zero_release(_previewer);
    [super dealloc];
}

// datasource.

- (NSInteger)numberOfPreviewItemsInPreviewController:(QLPreviewController *)controller {
    return d_owner.documents.count;
}

- (id <QLPreviewItem>)previewController:(QLPreviewController *)controller previewItemAtIndex:(NSInteger)index {
    return [d_owner.documents objectAtIndex:index null:0];
}

// delegate.

- (void)previewControllerWillDismiss:(QLPreviewController *)controller {
    
}

- (void)previewControllerDidDismiss:(QLPreviewController *)controller {
    
}

- (BOOL)previewController:(QLPreviewController *)controller shouldOpenURL:(NSURL *)url forPreviewItem:(id <QLPreviewItem>)item {
    return YES;
}

/*
- (CGRect)previewController:(QLPreviewController *)controller frameForPreviewItem:(id <QLPreviewItem>)item inSourceView:(UIView **)view {
    
}

- (UIImage *)previewController:(QLPreviewController *)controller transitionImageForPreviewItem:(id <QLPreviewItem>)item contentRect:(CGRect *)contentRect {
    
}
*/

NNTDECL_PRIVATE_END

@interface QuickLookerView : UIView

@property (nonatomic, assign) UIView* looker;

@end

@implementation QuickLookerView

@synthesize looker;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];    
    return self;
}

- (void)layoutSubviews {
    CGRect rc = self.bounds;
    looker.frame = rc;
}

@end

@implementation QuickLookerController

@synthesize documents = _documents;
@synthesize currentPreviewItemIndex;

- (id)init {
    self = [super init];
    
    currentPreviewItemIndex = 0;
    
    NNTDECL_PRIVATE_INIT(QuickLookerController);
    return self;
}

- (void)dealloc {
    zero_release(_documents);
    
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)loadView {
    QuickLookerView* view = [[QuickLookerView alloc] initWithZero];
    self.view = view;
    [view release];
}

- (NSInteger)currentPreviewItemIndex {
    if (d_ptr.previewer)
        return d_ptr.previewer.currentPreviewItemIndex;
    return currentPreviewItemIndex;
}

- (void)setCurrentPreviewItemIndex:(NSInteger)idx {
    currentPreviewItemIndex = idx;
    if (d_ptr.previewer)
        d_ptr.previewer.currentPreviewItemIndex = idx;
}

- (void)reloadData {
    QLPreviewController* ctlr = [[QLPreviewController alloc] init];
    ctlr.dataSource = d_ptr;
    ctlr.delegate = d_ptr;
    ctlr.currentPreviewItemIndex = self.currentPreviewItemIndex;
    d_ptr.previewer = ctlr;
    [ctlr release];
    
    [ctlr viewWillAppear:NO];
    
    QuickLookerView* view = (QuickLookerView*)self.view;
    view.looker = ctlr.view;
    [view addSubview:view.looker];
    
    [ctlr viewDidAppear:NO];
    
    [view setNeedsLayout];
}

@end

_CXXCONTROLLER_IMPL(QuickLookerController);

NNT_END_OBJC
