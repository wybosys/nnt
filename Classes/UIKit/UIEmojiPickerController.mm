
# include "NNTFoundation.h"
# include "UIEmojiPickerController.h"

# define ROWS 4
# define COLS 6

NNT_BEGIN_OBJC

signal_t kSignalEmojiSelected = @"::nnt::uikit::emoji::pick";

@implementation UIEmojiPickerView

@synthesize page;

- (id)initWithZero {
    self = [super initWithZero];
    page = [[NNTUIPageControl alloc] initWithZero];
    page.selectedColor = [UIColor redColor];
    page.normalColor = [UIColor grayColor];
    [self addSubview:page];
    return self;
}

- (void)dealloc {
    [page release];
    [super dealloc];
}

- (void)layoutSubviews {
    ::nnt::CGRectLayoutVBox lyt_main(self.bounds);
    ::nnt::CGRectLayoutLinear lnr_main(lyt_main);
    lnr_main << (::nnt::flex)1 << (::nnt::pixel)10;
    [self.switcher cur_page].view.frame = lyt_main << lnr_main;
    page.frame = lyt_main << lnr_main;
}

@end

@implementation UIEmojiPage

- (id)init {
    self = [super init];
    self.rows = ROWS;
    self.cols = COLS;
    return self;
}

- (void)load:(NSMutableArray*) arr
{
    [self.gridView clearItems];
    for (uint idx = 0; idx < [arr count]; ++idx) {
        NNTUILabel* lbl_emoji = [[NNTUILabel alloc] initWithZero];
        lbl_emoji.textAlignment = UITextAlignmentCenter;
        lbl_emoji.text = [arr objectAtIndex:idx];
        [self.gridView addChildView:lbl_emoji];
        [lbl_emoji release];
    }
}

@end

@implementation UIEmojiPickerController

@synthesize emojis;

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalEmojiSelected)
NNTEVENT_END

- (id)init {
    self = [super init];
    
    self.pageClass = [UIEmojiPage class];
    self.numberOfGestureTouches = 1;
    self.transition = UISwitchTransitionSlide;// UISWitchController's transition change animation
    [self connect:kSignalPageCreate sel:@selector(act_page_create:)];
    [self connect:kSignalSelectChanged sel:@selector(act_select_changed:)];
    
    return self;
}

- (void)dealloc {
    [emojis release];
    [super dealloc];
}

- (void)loadView {
    UIEmojiPickerView* view = [[UIEmojiPickerView alloc] initWithZero];
    view.switcher = self;
    self.view = view;
    [view release];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self load_emoji];
}

- (void)load_emoji {
    if (nil == emojis)
        return;
    UIEmojiPickerView* view = (UIEmojiPickerView*)self.view;
    real page_capacity = ROWS * COLS;
    usize pages = ceil( [emojis count] / page_capacity);
    view.page.numberOfPages = pages;
    view.page.currentPage = 0;
    self.numberOfPages = pages;
    [self instanceRootPage];
}

- (void)act_page_create:(NNTEventObj*)evt {
    UIEmojiPage* page = (UIEmojiPage*)evt.result;
    [page.gridView connect:kSignalContentClicked sel:@selector(act_click_grid:) obj:self];
    uint page_num = [self index_of:page];
    uint page_capacity = ROWS * COLS;
    
    uint beg = page_num * page_capacity;
    uint end = 0;
    
    if (!([emojis count] % page_capacity == 0) && (page_num == self.numberOfPages - 1 )) {
        end = beg + [emojis count] % page_capacity;
    } else {
        end = beg + page_capacity;
    }
    
    NSMutableArray* temp = [[[NSMutableArray alloc] init] autorelease];
    for (uint idx = beg; idx < end; ++idx) {
        [temp addObject:[emojis objectAtIndex:idx]];
    }
    [page load:temp];
}

- (void)act_select_changed:(NNTEventObj*)evt {
    UIEmojiPickerView* view = (UIEmojiPickerView*)self.view;
    UISwitchPage* page = ((NSPair*)evt.result).first;
    uindex idx = [self index_of:page];
    if (idx != NSNotFound) {
        view.page.currentPage = idx;
    }
}

- (void)act_click_grid:(NNTEventObj*)evt {
    [self emit:kSignalEmojiSelected result:evt.result];
}

@end

_CXXCONTROLLER_IMPL(UIEmojiPickerController);

NNT_END_OBJC
