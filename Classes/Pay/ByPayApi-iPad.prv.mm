
# import "Core.h"
# import "ByPayApi-iPad.prv.h"
# import <unipay/bypay/ipad/UPOMP_iPad.h>

NNT_BEGIN_OBJC

NNTDECL_PRIVATE_BEGIN(ByPayApiPad, NSObject <UPOMP_iPad_Delegate>) {
    UPOMP_iPad* _pay;
}

@property (readonly) UPOMP_iPad* pay;

NNTDECL_PRIVATE_IMPL(ByPayApiPad)

@synthesize pay = _pay;

- (id)init {
    self = [super init];
    
    _pay = [[UPOMP_iPad alloc] init];
    _pay.viewDelegate = self;
    
    return self;
}

- (void)dealloc {
    safe_release(_pay);
    
    [super dealloc];
}

- (void)viewClose:(NSData *)data {        
    _pay.viewDelegate = nil;
    
    [d_owner processResult:data];
}

NNTDECL_PRIVATE_END

@implementation ByPayApiPad

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(ByPayApiPad);
    
    return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)viewIsLoading {
    ByPayApiView* view = (ByPayApiView*)self.view;
    view.pay = d_ptr.pay.view;
    
    // send.
    if (self.result) {
        [self send:self.result];
    } else {
        [self send:[self generateResult]];
    }
}

- (void)send:(NSData *)data {
    [d_ptr.pay setXmlData:data];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation {
    return UIInterfaceOrientationIsLandscape(toInterfaceOrientation);
}

@end

NNT_END_OBJC
