
# import "Core.h"
# import "ByPayApi.prv.h"
# import "XmlObjParser.h"
# import "XmlParser.h"
# import "PayNullApi.h"

WSI_BEGIN_OBJC

signal_t kSignalByPayClose = @"::wsi::pay::unipay::close";

@implementation ByPayApiView

@synthesize pay;

- (void)setPay:(UIView *)_pay {
    if (pay == _pay)
        return;
    
    [pay removeFromSuperview];
    pay = _pay;
    [self addSubview:pay];
}

- (void)layoutSubviews {
    pay.frame = self.bounds;
}

@end

@implementation ByPayApiController

@synthesize application, merchantId, merchantOrderId, merchantOrderTime, signResult;
@synthesize result;
@synthesize Owner;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    safe_release(application);
    safe_release(merchantId);
    safe_release(merchantOrderId);
    safe_release(merchantOrderTime);
    safe_release(signResult);
    safe_release(result);
    safe_release(Owner);
    
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalPaySuccess)
WSIEVENT_SIGNAL(kSignalPayFailed)
WSIEVENT_SIGNAL(kSignalByPayClose)
WSIEVENT_END

- (void)loadView {
    ByPayApiView* view = [[ByPayApiView alloc] init];
    self.view = view;
    [view release];
}

- (NSString*)generateSign {
    return @"";
}

- (NSData*)generateResult {
    WSI_USINGCXXNAMESPACE;
    
    parser::XmlDocument doc;
    doc.encoding = "utf-8";
    
    doc.root()->name = "upomp";
    doc.root()->add_attr("application", core::type_cast<core::string>(application));
    doc.root()->add_attr("version", "1.0.0");
    
    doc.root()->add_node("merchantId", core::type_cast<core::string>(merchantId));
    doc.root()->add_node("merchantOrderId", core::type_cast<core::string>(merchantOrderId));
    doc.root()->add_node("merchantOrderTime", core::type_cast<core::string>(merchantOrderTime));
    
    if (signResult == nil) {
        NSString* str_signed = [self generateSign];
        doc.root()->add_node("sign", core::type_cast<core::string>(str_signed));
    } else {
        doc.root()->add_node("sign", core::type_cast<core::string>(signResult));
    }
    
    core::data raw;
    if (doc.save(raw) == false)
        return nil;
    
    return core::dup_cast<ns::Data>(raw).consign();
}

- (void)processResult:(NSData*)data {
    WSI_USINGCXXNAMESPACE;
    
# ifdef WSI_DEBUG
    ns::String str = core::type_cast<ns::String>(data);
    trace_msg(str.nsobject());
# endif
    
    parser::XmlObject xml;
    ns::Dictionary da = xml.parse(data);
    ns::String code = da[@"respCode"];
    
    if (code == @"0000") {
        [self emit:kSignalPaySuccess];
    } else {
        [self emit:kSignalPayFailed];
    }
    
    [self emit:kSignalByPayClose];
}

@end

WSI_END_OBJC
