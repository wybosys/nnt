
# import "Core.h"

# import "AlipayApi.h"

# import "../../contrib/Alipay/include/AlixPay.h"
# import "../../contrib/Alipay/include/AlixPayOrder.h"
# import "../../contrib/Alipay/include/AlixPayResult.h"

NNT_BEGIN_HEADER_OBJC

# import "../../contrib/Alipay/Utilities/DataSigner.h"
# import "../../contrib/Alipay/Utilities/DataVerifier.h"

NNT_END_HEADER_OBJC

# import "App.h"

NNT_BEGIN_OBJC

@implementation AlipayApi

@synthesize errcode;

+ (NSString*)identity {
    return @"alipay";
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

# define RETURN_ERROR(code) { \
errcode = code; \
trace_msg(@"alipay::data is error."); \
return NO; \
}

- (BOOL)send:(id)data {
    [super send:data];
    
    if ([data isKindOfClass:[NSDictionary class]] == NO)
        RETURN_ERROR(AlipayApiTypeError);
    NSDictionary *dict = (NSDictionary*)data;
    
    NSString *partner = [dict valueForKey:@"partner" null:nil];
    if (partner == nil)
        RETURN_ERROR(AlipayApiLostPartner);
    
    NSString *seller = [dict valueForKey:@"seller" null:nil];
    if (seller == nil)
        RETURN_ERROR(AlipayApiLostSeller);
    
    NSString *trade_no = [dict valueForKey:@"trade_no" null:nil];
    if (trade_no == nil)
        trade_no = [AlipayApi generateTradeNo];
    
    NSNumber *obj_amount = [dict valueForKey:@"amount" null:nil];
    if (obj_amount == nil)
        RETURN_ERROR(AlipayApiLostAmount);
    NSString *amount = [NSString stringWithFormat:@"%.2f", [obj_amount realValue]];
    
    NSString *rsa_key = [dict valueForKey:@"private_key" null:nil];
    if (rsa_key == nil)
        RETURN_ERROR(AlipayApiLostRSAKey);
    
    NSString *goods_name = [dict valueForKey:@"goods_name" null:@""];
    NSString *goods_desc = [dict valueForKey:@"goods_desc" null:@""];
    NSString *callback_url = [dict valueForKey:@"callback_url" null:@""];
    
    NSString *app_scheme = [dict valueForKey:@"app_scheme" null:nil];
    if (app_scheme == nil)
        app_scheme = [NNTApplication shared].applicationURLScheme;
    
    // post.
    AlixPayOrder *order = [[AlixPayOrder alloc] init];
    order.partner = partner;
    order.seller = seller;
    order.productName = goods_name;
    order.productDescription = goods_desc;
    order.amount = amount;
    order.tradeNO = trade_no;
    order.notifyURL = callback_url;
    
    NSString *order_spec = [order description];
    //trace_msg(order_spec);
    
    id<DataSigner> signer = CreateRSADataSigner(rsa_key);
    NSString *signedString = [signer signString:order_spec];
	NSString *orderString = [NSString stringWithFormat:@"%@&sign=\"%@\"&sign_type=\"%@\"",
                             order_spec, signedString, @"RSA"];
    trace_msg(orderString);
    
    AlixPay * alixpay = [AlixPay shared];
	int ret = [alixpay pay:orderString applicationScheme:app_scheme];
    
    if (ret == kSPErrorAlipayClientNotInstalled) {
		UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:_W(@"info") 
															 message:_W(@"Can not find Alipay, please install it first!") 
															delegate:self 
												   cancelButtonTitle:_W(@"ok") 
												   otherButtonTitles:nil];
		[alertView setTag:123];
		[alertView show];
		[alertView release];
	}
	else if (ret == kSPErrorSignError) {
        trace_msg(@"signature error.");
	}
    
    [order release];
    
    // connect.
    [[NNTApplication shared] connect:kSignalAppOpenUrl sel:@selector(act_openurl:) obj:[self retain]];
    
    errcode = AlipayApiSuc;
    return YES;
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
	if (alertView.tag == 123) {
		NSString * URLString = @"http://itunes.apple.com/cn/app/id535715926?mt=8";
		[[UIApplication sharedApplication] openURL:[NSURL URLWithString:URLString]];
	}
}

- (void)act_openurl:(NNTEventObj*)obj {
    // receive from Alipay App.
    OpenURLObject *ouobj = (OpenURLObject*)obj.result;
    AlixPay *alixpay = [AlixPay shared];
	AlixPayResult *result = [alixpay handleOpenURL:ouobj.url];
    
    // process result.
	if (result) {
        NSNumber *code = [NSNumber numberWithInt:result.statusCode];
        NSString *message = @"";
		
		if (result.statusCode == 9000) {
            // check message with public key.
            NSString *pubkey = [(NSDictionary*)self.requestData valueForKey:@"public_key" null:@""];
			id<DataVerifier> verifier = CreateRSADataVerifier(pubkey);
			if ([verifier verifyString:result.resultString withSign:result.signString]) {
                message = result.statusMessage;
                [self emit:kSignalPaySuccess result:message];
			}
			else {
                message = _W(@"signature error.");
                [self emit:kSignalPayFailed result:message];
			}
		}
		else {
            message = result.statusMessage;
            [self emit:kSignalPayFailed result:message];
		}
        
        [self emit:kSignalPayReceive result:[NSDictionary dictionaryWithObjectsAndKeys:
                                             code, @"code",
                                             message, @"message",
                                             nil]];
        
	}                                         

    // disconnect.
    [[NNTApplication shared] disconnect:kSignalAppOpenUrl sel:@selector(act_openurl:) obj:self];

    // free.
    [self release];
}

@end

NNT_END_OBJC
