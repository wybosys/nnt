
# import "Core.h"
# import "UIPDFController.h"
# import "UIPDFView.h"

NNT_BEGIN_OBJC

@interface UIPDFControllerPrivate : NSObject {
    UIPDFController *d_owner;
    CGPDFDocumentRef pdf;
}

@property (nonatomic, assign) UIPDFController *d_owner;
@property (nonatomic, assign) CGPDFDocumentRef pdf;

- (void)close;

@end

@implementation UIPDFControllerPrivate

@synthesize d_owner;
@synthesize pdf;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    [self close];
    [super dealloc];
}

- (void)setPdf:(CGPDFDocumentRef)ref {
    if (ref == pdf)
        return;
    CGPDFDocumentRelease(pdf);
    pdf = CGPDFDocumentRetain(ref);
}

- (void)close {
    if (pdf) {
        CGPDFDocumentRelease(pdf);
        pdf = nil;
    }
}

@end

@implementation UIPDFController

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(UIPDFController);
    return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (id)initWithURL:(NSURL *)url {
    self = [self init];
    CFURLRef cfurl = (CFURLRef)url;
    CGPDFDocumentRef ref = CGPDFDocumentCreateWithURL(cfurl);
    if (ref == 0) {
        [self release];
        return nil;
    }
    d_ptr.pdf = ref;
    CGPDFDocumentRelease(ref);
    return self;
}

- (void)loadView {
    UIPDFView *view = [[UIPDFView alloc] initWithZero];
    self.view = view;
    [view release];
}

@end

NNT_END_OBJC