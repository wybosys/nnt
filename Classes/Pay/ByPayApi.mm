
# import "Core.h"
# import "UnipayApi.h"
# import "ByPayApi-iPhone.prv.h"
# import "ByPayApi-iPad.prv.h"
# import "App.h"
# import "MDN+WSI.h"
# import "RSA+WSI.h"
# import "BaseN+WSI.h"

WSI_USINGCXXNAMESPACE;

WSI_BEGIN_OBJC

@implementation ByPayApi

@synthesize client_id, partner_id;
@synthesize result;

- (id)init {
    self = [super init];
    
    self.client_id = @"LanchPay.Req";
    self.partner_id = @"303310048990001";
    
    return self;
}

- (void)dealloc {
    safe_release(client_id);
    safe_release(partner_id);
    safe_release(result);
    
    [super dealloc];
}

+ (NSString*)identity {
    return @"unipay";
}

+ (NSString *)generateTradeNo {
	const int N = 15;
	
	NSString *sourceString = @"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	NSMutableString *result = [[[NSMutableString alloc] init] autorelease];
	srand(time(0));
	for (int i = 0; i < N; i++)
	{
		unsigned index = rand() % [sourceString length];
		NSString *s = [sourceString substringWithRange:NSMakeRange(index, 1)];
		[result appendString:s];
	}
	return result;
}

- (BOOL)send:(id)data {
    [super send:data];
    
    ns::Dictionary props(data);
    
    ByPayApiController* ctlr = nil;
    if (WSI_DEVICE_ISIPAD) {
        ctlr = [[ByPayApiPad alloc] init];
    } else {
        ctlr = [[ByPayApiPhone alloc] init];
    }
    
    ctlr.Owner = self;
    [ctlr connect:kSignalPaySuccess sig:kSignalPaySuccess obj:self];
    [ctlr connect:kSignalPayFailed sig:kSignalPayFailed obj:self];
    [ctlr connect:kSignalByPayClose sel:@selector(dismissModalViewControllerAnimated)];
    
    ctlr.result = self.result;
    
    if (ctlr.result == nil) {
        ctlr.application = props[@"client_id"] ? props[@"client_id"] : client_id;
        ctlr.merchantId = props[@"partner"] ? props[@"partner"] : partner_id;
    
        ctlr.merchantOrderId = props[@"order_id"] ? props[@"order_id"] : [ByPayApi generateTradeNo];
        
        if (props[@"order_time"]) {
            ctlr.merchantOrderTime = props[@"order_time"];
        } else {
            core::Time tm = core::Time::Local();
            ctlr.merchantOrderTime = ns::String::Format(@"%4d%2d%2d%2d%2d%2d", tm.year(), tm.month(), tm.dayofmonth(), tm.hour(), tm.minute(), tm.second());
        }
    }

    [[WSIApplication shared].window.rootViewController presentModalViewControllerWithAnimated:ctlr];

    safe_release(ctlr);
    
    return YES;
}

@end

WSI_END_OBJC
