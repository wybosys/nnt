
# import <wsi/WSIFoundation.h>
# import "TMRAWController.h"

WSIAPP_BEGIN_OBJC

using namespace ::wsi::ui;

@interface TMRawView : WSINSView {
    TextView<>* text;
}

@property (nonatomic, readonly) TextView<>* text;

@end

@implementation TMRawView

@synthesize text;

- (id)initWithZero {
    self = [super initWithZero];
    
    text = new TextView<>;
    
    [self addSubview:*text];        
    
    return self;
}

- (void)dealloc {
    delete text;
    [super dealloc];
}

- (void)layoutSubviews {
    text->set_frame(self.bounds);
}

@end

@implementation TMRawController

- (id)init {
    self = [super init];
    self.identity = self.title = @"RAW";
    return self;
}

- (void)loadView {
    TMRawView* view = [[TMRawView alloc] initWithZero];
    self.view = view;
    [view release];
}

- (id)dataObject {
    TMRawView* view = (TMRawView*)self.view;
    return view.text->string_value();
}

- (void)setDataObject:(NSString*)str {
    TMRawView* view = (TMRawView*)self.view;
    view.text->set_value(str);
}

@end

WSIAPP_END_OBJC