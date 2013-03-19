
# import "Core.h"
# import "ByPayApi-iPhone.prv.h"
# import <unipay/bypay/iphone/UPOMP.h>

WSI_BEGIN_OBJC

WSIDECL_PRIVATE_BEGIN(ByPayApiPhone, NSObject <UPOMPDelegate> ) {
    UPOMP* _pay;
}

@property (readonly) UPOMP* pay;

WSIDECL_PRIVATE_IMPL(ByPayApiPhone)

@synthesize pay = _pay;

- (id)init {
    self = [super init];
    
    _pay = [[UPOMP alloc] init];
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

WSIDECL_PRIVATE_END

@implementation ByPayApiPhone

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(ByPayApiPhone);
    return self;
}

- (void)dealloc {
    WSIDECL_PRIVATE_DEALLOC();
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

@end

WSI_END_OBJC
