
# import "MainController.h"
# import "71squared/EAGLView.h"
# import "71squared/ParticleEmitter.h"

@interface MainView ()
{
    EAGLView* _viewPex;   
}

@end

@implementation MainView

@synthesize btnPlay;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    btnPlay = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [btnPlay setTitle:@"PLAY" forState:UIControlStateNormal];
    btnPlay.frame = CGRectMake(0, 0, 100, 50);
    [self addSubview:btnPlay];
    
    return self;
}

- (void)layoutSubviews {
    CGRect rc = self.bounds;
    if (CGRectEqualToRect(rc, CGRectZero))
        return;
    
    [_viewPex removeFromSuperview];
    
    _viewPex = [[EAGLView alloc] initWithFrame:rc];
    [self insertSubview:_viewPex atIndex:0];
    [_viewPex release];
}

- (void)dealloc {
    [super dealloc];
}

@end

@interface MainController ()
{
    ParticleEmitter* _pe;
}

@end

@implementation MainController

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    [_pe release];
    [super dealloc];
}

- (void)loadView {
    MainView* view = [[MainView alloc] initWithFrame:CGRectZero];
    self.view = view;
    [view release];
}

- (void)viewDidLoad {
    MainView* view = (MainView*)self.view;
    [view.btnPlay addTarget:self action:@selector(cbClicked) forControlEvents:UIControlEventTouchUpInside];
}

- (void)cbClicked {
    [_pe release];
    _pe = [[ParticleEmitter alloc] initParticleEmitterWithFile:@"demo.pex"];
    [_pe renderParticles];
}

@end
