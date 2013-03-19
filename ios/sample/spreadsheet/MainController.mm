
# import "Foundation+NNT.h"
# import "MainController.h"
# import "AlphabetFlow.h"

NNTAPP_BEGIN_OBJC

@interface MainView : WSIUIView

@property (nonatomic, readonly) UISpreadSheet* sheet;
@property (nonatomic, readonly) UIBevelButton *reload, *clear;

@end

@implementation MainView

@synthesize sheet, reload, clear;

- (id)initWithZero {
    self = [super initWithZero];
    
    sheet = [[UISpreadSheet alloc] initWithZero];
    [self addSubview:sheet];
    safe_release(sheet);
    
    reload = [[UIBevelButton alloc] initWithZero];
    [self addSubview:reload];
    safe_release(reload);
    reload.text = @"RELOAD";
    
    clear = [[UIBevelButton alloc] initWithZero];
    [self addSubview:clear];
    safe_release(clear);
    clear.text = @"CLEAR";
    
    return self;
}

- (void)layoutSubviews {
    wsi::CGRectLayoutVBox lyt(self.bounds);
    wsi::CGRectLayoutLinear lnr(lyt);
    lnr << (wsi::flex)1 << (wsi::pixel)50;
    
    CGRect rc = lyt << lnr;
    sheet.frame = rc;
    
    wsi::CGRectLayoutHBox lytb(lyt << lnr);
    wsi::CGRectLayoutLinear lnrb(lytb);
    lnrb << (wsi::flex)1 << (wsi::flex)1;
    reload.frame = lytb << lnrb;
    clear.frame = lytb << lnrb;
}

@end

NNTDECL_PRIVATE_BEGIN(MainController, NSObject) <UISpreadSheetDataSource, UISpreadSheetDelegate>
{
    ::wsi::AlphabetFlow af;
}

NNTDECL_PRIVATE_IMPL(MainController)

- (NSUInteger)sheetRowsNumber:(UISpreadSheet*)sheet {
    return 100;
}

- (NSUInteger)sheetColsNumber:(UISpreadSheet*)sheet {
    return 100;
}

- (NSString*)sheetTextString:(UISpreadSheet*)sheet row:(NSUInteger)row col:(NSUInteger)col {
    NSString* ret = ::wsi::core::type_cast< ::NSString* >(af.curValue);
    af.next();
    return ret;
}

- (NSUInteger)sheetHeadersNumber:(UISpreadSheet*)sheet dir:(WCGDirection)dir {
    NSUInteger ret = 0;
    switch (dir)
    {
        case WCGDirectionLeft: ret = 2; break;
        case WCGDirectionRight: ret = 1; break;
        case WCGDirectionTop: ret = 1; break;
        case WCGDirectionBottom: ret = 2; break;
    }
    return ret;
}

NNTDECL_PRIVATE_END

@implementation MainController

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(MainController);
    self.title = @"SpreadSheet";
    return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)loadView {
    MainView* view = [[MainView alloc] initWithZero];
    self.view = view;
    [view release];
}

- (void)viewIsLoading {
    MainView* view = (MainView*)self.view;
    
    // background to white.
    view.backgroundColor = [UIColor whiteColor];
    
    // add spread sheet.
    view.sheet.dataSource = d_ptr;
    view.sheet.delegate = d_ptr;    
    [view.sheet reloadAll];
    
    [view.reload connect:kSignalButtonClicked sel:@selector(act_reload) obj:self];
    [view.clear connect:kSignalButtonClicked sel:@selector(act_clear) obj:self];
}

- (void)act_reload {
    MainView* view = (MainView*)self.view;
    [view.sheet reloadAll];
}

- (void)act_clear {
    MainView* view = (MainView*)self.view;
    [view.sheet clear];
}

@end

NNTAPP_END_OBJC