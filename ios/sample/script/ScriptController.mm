
# import "Foundation+NNT.h"
# import "ScriptController.h"
# import "WSIPython.h"
# import "WSILua.h"

WSI_BEGIN_OBJC

@interface ScriptView : WSIUIView

@property (nonatomic, readonly) WSIUITextView *input, *output;
@property (nonatomic, readonly) WSIUIButton* run;
@property (nonatomic, readonly) WSIUISegmentedControl* segment;

@end

@implementation ScriptView

@synthesize input, output;
@synthesize run;
@synthesize segment;

- (id)initWithZero {
    self = [super initWithZero];
    
    input = [[WSIUITextView alloc] initWithZero];
    input.layer.borderWidth = 1;
    
    output = [[WSIUITextView alloc] initWithZero];
    output.editable = NO;
    output.layer.borderWidth = 1;
    
    run = [[UIBevelButton alloc] initWithZero];
    run.backgroundColor = [UIColor blueColor];
    [run setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    
    segment = [[WSIUISegmentedControl alloc] initWithItems:[NSArray arrayWithObjects:@"Python", @"Lua", nil]];   
    
    [self addSubview:input];
    [self addSubview:output];
    [self addSubview:run];
    [self addSubview:segment];
    
    return self;
}

- (void)dealloc {
    [input release];
    [output release];
    [run release];
    [segment release];
    [super dealloc];
}

- (void)layoutSubviews {
    wsi::CGRectLayoutVBox lyt(self.bounds);
    lyt.set_margin(5, 5);
    
    wsi::CGRectLayoutLinear lnr(lyt);
    lnr << (wsi::pixel)50 << (wsi::flex)1 << (wsi::flex)1;
    
    segment.frame = lyt.stride_pixel(lnr.start());
    output.frame = lyt.stride_pixel(lnr.next());
    input.frame = lyt.stride_pixel(lnr.next());    
    
    run.frame = CGRectMakePtSz(CGPointAddX(CGRectRightTop2(output.frame), -50), CGSizeMake(50, 50));
}

@end

@interface ScriptControllerPrivate : WSIObject {
    WSIPython* python;
    WSILua* lua;
}

@property (nonatomic, assign) ScriptController* d_owner;
@property (nonatomic, retain) WSIPython* python;
@property (nonatomic, retain) WSILua* lua;

- (void)clear;
- (id<WSIScript>)script;

@end

@implementation ScriptControllerPrivate

@synthesize d_owner;
@synthesize python, lua;

- (id)init {
    self = [super init];    
    return self;
}

- (void)dealloc {
    [python release];
    [lua release];
    [super dealloc];
}

- (void)clear {
    zero_release(python);
    zero_release(lua);
}

- (id<WSIScript>)script {
    if (python) {
        return python;
    } else if (lua) {
        return lua;
    }
    return nil;
}

@end

@implementation ScriptController

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(ScriptController);
    return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)loadView {
    ScriptView* view = [[ScriptView alloc] initWithZero];
    self.view = view;
    [view release];
}

- (void)viewDidLoad {
    ScriptView* view = (ScriptView*)self.view;
    
    [view.segment connect:kSignalSelectChanged sel:@selector(script_changed:) obj:self];
    [view.run connect:kSignalButtonClicked sel:@selector(script_run:) obj:self];
    
    view.segment.selectedSegmentIndex = 0;
}

- (void)script_changed:(WSIEventObj*)evt {
    ScriptView* view = (ScriptView*)self.view;

    view.input.text = @"";
    view.output.text = @"";
    [d_ptr clear];
    
    switch (view.segment.selectedSegmentIndex) {
        case 0: {
            WSIPython* python = [[WSIPython alloc] init];
            d_ptr.python = python;
            [python release];
        } break;
        case 1: {
            WSILua* lua = [[WSILua alloc] init];
            d_ptr.lua = lua;
            [lua release];
        } break;
    }
}

- (void)script_run:(WSIEventObj*)evt {
    ScriptView* view = (ScriptView*)self.view;
    NSString* str = view.input.text;
    if (NO == [[d_ptr script] executeString:str]) {
        view.output.text = [[d_ptr script] errorMessage];
    } else {
        view.output.text = @"";
    }
}

@end

WSI_END_OBJC