
# import "Core.h"
# import "JsonRpc.h"
# import "Model.h"

WSI_BEGIN_OBJC

@interface JsonRpcPrivate : WSIObject <JsonRpcDelegate> {
	NSString *protocol;
	NSString *reqid;
	JsonRpc *owner;
	NSURL *url;
}

@property (nonatomic, assign) JsonRpc *owner;
@property (nonatomic, retain) NSURL *url;

# pragma mark private-delegate

- (NSDictionary*)send_call:(NSData*)__reqdata; 
- (NSDictionary*)call:(NSString*)__method params:(NSArray*)__params;
- (NSDictionary*)call:(NSString*)__method;

@end

@implementation JsonRpcPrivate

@synthesize owner, url;

- (id)init {
	self = [super init];
    
	protocol = @"2.0";
	reqid = @"0";
    
	return self;
}

- (NSDictionary*)call:(NSString *)__method params:(NSArray*)__params {
	NSArray *req = [NSDictionary dictionaryWithObjectsAndKeys:
						protocol, @"jsonrpc",
						[owner service], @"service",
						__method, @"method",
						__params, @"params",
						reqid, @"id",
					nil];
	NSString *json = [WSIObject json_encode:req];
	
	NSData *json_data = [json dataUsingEncoding:NSUTF8StringEncoding];
	
	return [self send_call:json_data];
}

- (NSDictionary*)call:(NSString *)__method {
	return [self call:__method params:[NSArray array]];
}

- (NSDictionary*)send_call:(NSData *)__reqdata {
    WSIMACRO_LOCKOBJ(self);

	NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url];
	[request setValue:[[NSNumber numberWithInt:(int)[__reqdata length]] stringValue] forHTTPHeaderField:@"Content-Length"];
    [request setValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
	[request setHTTPMethod:@"POST"];
	[request setHTTPBody: __reqdata];
	
	NSURLResponse *respone;
	NSError *error;
	[self jsonRpcDidStartLoading:owner];
	
	NSData *data = [NSURLConnection sendSynchronousRequest:request returningResponse:&respone error:&error];
	
	if (data == nil) {
		[Msgbox warn:@"Can not connect to server"];
		return nil;
	}
	
	// parse receive
	NSString *str = [[[NSString alloc] initWithBytes:[data bytes] length:[data length] encoding:NSUTF8StringEncoding] autorelease];
	NSDictionary *json = [WSIObject json_decode:str];
	if (json == nil)
        return nil;
	
	// if error
	if ([json objectForKey:@"error"]) {
		NSDictionary *error = [json objectForKey:@"error"];
		[self jsonRpcExec:owner didFailWithErrorCode:[error objectForKey:@"code"] message:[error objectForKey:@"message"] data:data];
		[Msgbox info:[error objectForKey:@"message"]];
		return nil;
	}
	
	// result
	NSDictionary* result = [json objectForKey:@"result"];
	[self jsonRpcExec:owner didReceiveResult:result];

	return result;
}

# pragma mark delegate-implementation

- (void)jsonRpcDidStartLoading:(JsonRpc *)client {
	if ([owner.delegate respondsToSelector:@selector(jsonRpcDidStartLoading:)]) {
		[owner.delegate jsonRpcDidStartLoading:client];
	}
}

- (void)jsonRpcExec:(JsonRpc*)client didReceiveResult:(id)result {
	if ([owner.delegate respondsToSelector:@selector(jsonRpcExec:didReceiveResult:)]) {
		[owner.delegate jsonRpcExec:client didReceiveResult:result];
	}
}

- (void)jsonRpcExec:(JsonRpc *)client didFailWithErrorCode:(NSNumber*)code message:(NSString*)message {
	if ([owner.delegate respondsToSelector:@selector(jsonRpcExec:didFailWithErrorCode:)]) {
		[owner.delegate jsonRpcExec:client didFailWithErrorCode:code message: message];
	}
}

- (void)jsonRpcExec:(JsonRpc*)client didFailWithErrorCode:(NSNumber*)code message:(NSString*)message data:(NSData*)responseData {
	if ([owner.delegate respondsToSelector:@selector(jsonRpcExec:didFailWithErrorCode:message:data:)]) {
		[owner.delegate jsonRpcExec:client didFailWithErrorCode:code message:message data:responseData];
	}
	[owner.delegate jsonRpcExec:client didFailWithErrorCode:code message:message];
}

@end

@implementation JsonRpc

@synthesize delegate, url, service;

- (id)init {
	self = [super init];
    
	d_ptr = [JsonRpcPrivate new];
	d_ptr.owner = self;
    
	return self;
}

- (void)dealloc {
	zero_release(d_ptr);
	[super dealloc];
}

- (BOOL)connect:(NSURL *)__url {
	d_ptr.url = __url;
	return YES;
}

- (BOOL)is_connected {
	return YES;
}

- (void)disconnect {
    PASS;
}

- (id<IRpc>)confWithModel:(Model *)__model {
	url = __model.url;
	service = __model.service;
	return self;
}

- (NSObject*)call:(NSString *)__method params:(NSObject *)__params parser:(id)__parser {
    WSIRPC_CALLROUND;
    
	return [d_ptr call:__method params:(NSArray*)__params];
}

@end

WSI_END_OBJC