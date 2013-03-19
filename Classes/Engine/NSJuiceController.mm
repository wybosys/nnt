
# import "Core.h"
# import "NSView+NNT.h"
# import "NSViewController+NNT.h"
# import "NSJuiceController.h"
# import <OpenGL/OpenGL.h>
# import "JuiceImpl.h"

JUICEIMPL_BEGIN

ScreenManager::ScreenManager()
{    
    // alloc tree.
    _tree = new Tree;
}

ScreenManager::~ScreenManager()
{
    safe_delete(_tree);
}

void ScreenManager::next_frame()
{
    _tree->render(_painter(), _tree, &_renderinfo);
}

JUICEIMPL_END

NNT_BEGIN_OBJC

@interface NSJuiceView : NNTNSView {        
    //! manager.
    ::juice::impl::ScreenManager* scrMgr;
}

@end

@implementation NSJuiceView

- (id)initWithZero {
    self = [super initWithZero];
    
    scrMgr = new ::juice::impl::ScreenManager;
    
    return self;
}

- (void)dealloc {
    safe_delete(scrMgr);
    [super dealloc];
}

- (void)lockFocus {
    [super lockFocus];        
    scrMgr->set_drawable(self);
    scrMgr->resume();
}

- (void)drawRect:(NSRect)dirtyRect {
    scrMgr->update();     
    scrMgr->flush();
}

- (void)viewDidMoveToWindow {
    [super viewDidMoveToWindow];
    if ([self window] == nil)
        scrMgr->clear_drawable();
}

- (BOOL)isOpaque {    
    return YES;
}

@end

@implementation NSJuiceController

- (id)init {
    self = [super init];
    return self;
}

- (void)loadView {
    NSJuiceView* view = [[NSJuiceView alloc] initWithZero];
    self.view = view;
    [view release];
}

@end

NNT_END_OBJC