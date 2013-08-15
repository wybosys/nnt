
# import <nnt/Foundation+NNT.h>
# import "TMImageController.h"

NNT_USINGNAMESPACE;

NNTAPP_BEGIN_OBJC

@interface TMImageView : NNTNSView {
    ui::PushButton *btn_open, *btn_export;
    ui::TextField *txt_path;
    ui::ImageView<> *img_main;
}

@property (nonatomic, readonly) ui::PushButton *btn_open, *btn_export;
@property (nonatomic, readonly) ui::TextField *txt_path;
@property (nonatomic, readonly) ui::ImageView<> *img_main;

@end

@implementation TMImageView

@synthesize btn_open, btn_export, txt_path, img_main;

- (id)initWithZero {
    self = [super initWithZero];
    
    btn_open = new PushButton;
    btn_export = new PushButton;
    txt_path = new TextField<>;
    img_main = new ImageView<>;
    
    btn_open->set_title(@"OPEN");
    btn_export->set_title(@"EXPORT");
    
    [self addSubview:*btn_open];
    [self addSubview:*btn_export];
    [self addSubview:*txt_path];
    [self addSubview:*img_main];
    
    return self;
}

- (void)dealloc {
    delete btn_open;
    delete btn_export;
    delete txt_path;
    delete img_main;
    [super dealloc];
}

- (void)layoutSubviews {
    lb::CGRectLayoutVBox lyt(self.bounds, 5);
    CGRectLayoutLinear lnr(lyt);
    lnr << (pixel)30 << (flex)1;
    
    lb::CGRectLayoutHBox lyt_open(lyt << lnr, CGMarginMake(0, 0, 0, 5));
    CGRectLayoutLinear lnr_open(lyt_open);
    lnr_open << (pixel)70 << (flex)1 << (pixel)80;
    
    btn_open->set_frame(lyt_open << lnr_open);
    txt_path->set_frame(lyt_open << lnr_open);
    btn_export->set_frame(lyt_open << lnr_open);
    img_main->set_frame(lyt << lnr);
}

@end

@implementation TMImageController

- (id)init {
    self = [super init];
    self.identity = self.title = @"IMAGE";
    return self;
}

- (void)loadView {
    TMImageView* view = [[TMImageView alloc] initWithZero];
    self.view = view;
    [view release];
}

- (void)viewIsLoading {
    TMImageView* view = (TMImageView*)self.view;
    view.btn_open->connect(kSignalAction, @selector(act_open), self);
    view.btn_export->connect(kSignalAction, @selector(act_export), self);
}

- (void)act_open {
    TMImageView* view = (TMImageView*)self.view;
    NSOpenPanel* panel = [NSOpenPanel openPanel];
    [panel setCanChooseFiles:YES];
    NSInteger clicked = [panel runModal];
    if (clicked == NSFileHandlingPanelOKButton) {
        view.txt_path->set_text([panel.URL relativeString]);
        view.img_main->set_image(panel.URL);
    }
}

- (void)act_export {
    NSSavePanel* panel = [NSSavePanel savePanel];
    NSInteger clicked = [panel runModal];
    if (clicked == NSFileHandlingPanelOKButton) {
        NSImage* image = (NSImage*)self.dataObject;
        [image saveAsPNG:panel.URL];
    }
}

- (id)dataObject {
    TMImageView* view = (TMImageView*)self.view;
    NSImage* img = view.img_main->get_image();
    NSData* data = [img dataAsPNG];
    WCGImage* image = [WCGImage imageWithData:data];
    return image;
}

- (void)setDataObject:(WCGImage*)obj {
    TMImageView* view = (TMImageView*)self.view;
    NSData* data = [obj dataAsPNG];
    NSImage* img = [[NSImage alloc] initWithData:data];
    view.img_main->set_image(img);
    [img release];
}

@end

WSIAPP_END_OBJC