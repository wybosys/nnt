
# import "Core.h"
# import "NSViewController+NNT.h"
# import "NSView+NNT.h"

NNT_BEGIN_OBJC

@implementation NNTNSViewController (NNT)

- (void)viewDidLoad {
    [self viewIsLoading];
}

- (void)viewIsLoading {
    PASS;
}

- (void)viewWillAppear {
    PASS;
}

- (void)viewDidAppear {
    PASS;
}

- (void)viewWillDisappear {
    PASS;
}

- (void)viewDidDisappear {
    PASS;
}

@end

@implementation NNTNSViewController

@synthesize identity;

- (void)dealloc {
    zero_release(identity);
    [super dealloc];
}

- (NSView*)view {
    if (_view)
        return _view;

    [self loadView];
    if ((_view = [super view])) {
        [self viewDidLoad];
    }
    return _view;
}

- (void)loadView {
    NNTNSView* view = [[NNTNSView alloc] initWithFrame:NSZeroRect];
    [self setView:view];
    [view release];
}

- (void)awakeFromNib {
    [super awakeFromNib];
}

@end

@implementation _cxx_nsviewcontroller_wrapper

@synthesize _cxxobj;

- (void)dealloc {
    if (_cxxobj)
        _cxxobj->destroy();
    
    [super dealloc];
}

- (void)loadView {
    NSView* view = _cxxobj->load_view();
    if (view == nil)
    {
        [super loadView];
        return;
    }
    
    self.view = view;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    if (_cxxobj)
        _cxxobj->view_loaded();
}

- (void*)object {
    return _cxxobj->cxxobject();
}

@end

NNT_END_OBJC