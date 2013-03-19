
# import "Core.h"
# import "XmlRpc.h"
# import "Model.h"

WSI_BEGIN_OBJC

@interface XmlRpcPrivate : WSIObject <XmlRpcDelegate, NSXMLParserDelegate> {
	XmlRpc *owner;
	//NSURL *url;
	NSString *protocol;
	
	// result
	NSMutableDictionary* result;
	NSMutableArray *t_sck;
}

@property (nonatomic, assign) XmlRpc *owner;
//@property (nonatomic, retain) NSURL *url;
@property (nonatomic, retain) NSString *protocol;
@property (nonatomic, retain) NSMutableDictionary *result;

- (NSDictionary*)send_call:(NSData*)__reqdata url:(NSURL*)url;
- (NSDictionary*)call:(NSString*)__method service:(NSString*)service params:(NSArray*)__params url:(NSURL*)url;
- (NSDictionary*)call:(NSString *)__method service:(NSString*)service url:(NSURL*)url;
- (NSString*)strtype:(id)__obj;
- (NSString*)strvalue:(id)__obj;

- (NSString*)make_value:(NSObject*)__value;
- (id)simplify_result:(NSDictionary*)__result;
- (void)simplify_struct:(NSMutableDictionary*)__struct node:(NSArray*)__node;
- (id)simplify_value:(NSDictionary*)__node;
- (void)simplify_array:(NSMutableArray*)__array node:(NSDictionary*)__node;

@end

@implementation XmlRpcPrivate

@synthesize owner, protocol, result;

- (id)init {
	self = [super init];
	protocol = @"1.0";    
	return self;
}

- (void)dealloc {
	zero_release(protocol);
	zero_release(result);
    
	[super dealloc];
}

- (NSString*)strtype:(id)__obj {
	NSString *ret = nil;
	if (object_getClassName(__obj) == nil) {// is pure type
		return nil;
	}
	if ([__obj isKindOfClass:[NSNumber class]]) {
		char const* type = [(NSNumber*)__obj objCType];
		if (strcmp(type, "i") == 0)
			ret = @"int";
		else if (strcmp(type, "f") == 0)
			ret = @"double";
	} else if ([__obj isKindOfClass:[NSString string]]) {
		ret = @"string";
	}
	return ret;
}

- (NSString*)strvalue:(id)__obj {
	NSString *ret = nil;
	if (object_getClassName(__obj) == nil) {// is pure type
		return nil;
	}
	if ([__obj isKindOfClass:[NSNumber class]]) {
		ret = [(NSNumber*)__obj stringValue];
	} else if ([__obj isKindOfClass:[NSString string]]) {
		ret = (NSString*)__obj;
	}
	return ret;
}

- (NSDictionary*)call:(NSString *)__method service:(NSString*)service params:(NSArray*)__params url:(NSURL*)url {
	NSMutableString *body = [[NSMutableString new] autorelease];
	[body appendFormat:@"<?xml version=\"%@\"?>", protocol];
	[body appendString:@"<methodCall>"];
	[body appendFormat:@"<methodName>%@.%@</methodName>", service, __method];
	if ([__params count]) {
		[body appendString:@"<params>"];
		for (id param in __params) {
            [body appendString:@"<param>"];
            [body appendString:[self make_value:param]];
            [body appendString:@"</param>"];
		}
		[body appendString:@"</params>"];
	}
	[body appendString:@"</methodCall>"];
	
	NSData *xml_data = [body dataUsingEncoding:NSUTF8StringEncoding];
	return [self send_call:xml_data url:url];
}

- (NSString *)make_value:(NSObject *)__value {
    NSMutableString *str = [[NSMutableString new] autorelease];
    [str appendString:@"<value>"];
    if (__value == nil) {
        [str appendString:@"<int>0</int>"];        
        goto LABEL_RETURN;
    }
    if ([__value isKindOfClass:[NSNumber class]]) {
        NSNumber *param = (NSNumber*)__value;
        char const* ctype = [param objCType];
        NSString *type = nil;
        if (0 == strcmp(ctype, "i")) type = @"int";
        else if (0 == strcmp(ctype, "f")) type = @"double";
        if (type) {
            [str appendFormat:@"<%@>%@</%@>", type, [param stringValue], type];
        }
        goto LABEL_RETURN;
    }
    if ([__value isKindOfClass:[NSString class]]) {
        [str appendFormat:@"<string>%@</string>", (NSString*)__value];
        goto LABEL_RETURN;
    }
    if ([__value isKindOfClass:[NSArray class]]) {
        [str appendString:@"<array><data>"];
        for (NSObject *each in (NSArray*)__value) {
            [str appendString:[self make_value:each]];
        }
        [str appendString:@"</data></array>"];
        goto LABEL_RETURN;
    }
    
LABEL_RETURN:
    [str appendString:@"</value>"];    
    return str;
}

- (NSDictionary*)call:(NSString *)__method service:(NSString*)service url:(NSURL*)url{
	return [self call:__method
              service:service
               params:[NSArray array]
                  url:url];
}

- (NSDictionary*)send_call:(NSData *)__reqdata  url:(NSURL*)url {
    WSIMACRO_LOCKOBJ(self);

	NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url];
	[request setValue:[[NSNumber numberWithInt:(int)[__reqdata length]] stringValue] forHTTPHeaderField:@"Content-length"];
	[request setValue:@"text/xml" forHTTPHeaderField:@"Content-Type"];
	[request setHTTPMethod:@"POST"];
	[request setHTTPBody:__reqdata];
	
	NSURLResponse *respone;
	NSError *error;
	[self xmlrpcDidStartLoading:owner];
	
	NSData *data = [NSURLConnection sendSynchronousRequest:request returningResponse:&respone error:&error];
	
	if (data == nil && error) {
		[Msgbox warn:@"Can not connect to server"];
		return nil;
	}
	
	if (data) {
		result = nil;
		NSXMLParser *xml = [[NSXMLParser new] autorelease];
		[xml setDelegate:self];
		NSXMLParser *reader = [xml initWithData:data];
		if (reader) {
			if (NO == [reader parse]) {
				[Msgbox warn:@"data error"];
				result = nil;
			}
		}
	}
	
	return result;
}

- (id)simplify_result:(NSDictionary*)__result {
	if ([__result objectForKey:@"fault"]) {
		// error
		return nil;
	}
	id ret = nil;
	NSDictionary *r_params = [__result objectForKey:@"params"];
	NSDictionary *r_param = [r_params objectForKey:@"param"];
	NSDictionary *r_value = [r_param objectForKey:@"value"];
	NSArray *r_struct = [r_value objectForKey:@"struct"];
	NSDictionary *r_array = [r_value objectForKey:@"array"];
	if (r_struct) {
		ret = [[NSMutableDictionary new] autorelease];
		[self simplify_struct:ret node:r_struct];
	} else if (r_array) {
		ret = [[NSMutableArray new] autorelease];
		[self simplify_array:ret node:r_array];
	} else {
		ret = [self simplify_value:r_value];
	}
	return ret;
}

- (void)simplify_struct:(NSMutableDictionary *)__struct node:(NSArray *)__node {
	for (NSObject *each in __node) {
		if (NO == [each isKindOfClass:[NSDictionary class]]) 
            continue;
        
		NSDictionary *member = (NSDictionary*)each;
		if (member == nil)
            return;
        
		NSString *name = [[member valueForKey:@"name"] valueForKey:@"#value"];
		id value_node = [member valueForKey:@"value"];
		id value = [self simplify_value:value_node];
		[__struct setValue:value forKey:name];	
	}
}

- (void)simplify_array:(NSMutableArray *)__array node:(NSDictionary *)__node {
	NSArray *data = [__node valueForKey:@"data"];
	if (data == nil)
        return;

	for (NSObject *each in data) {
		if (NO == [each isKindOfClass:[NSDictionary class]]) 
            continue;
        
		id value = [self simplify_value:(NSDictionary*)each];
		[__array addObject:value];
	}
}

- (id)simplify_value:(NSDictionary *)__node {
	NSArray *r_struct = [__node valueForKey:@"struct"];
	NSDictionary *r_array = [__node valueForKey:@"array"];
	if (r_struct) {
		NSMutableDictionary *ret = [[NSMutableDictionary new] autorelease];
		[self simplify_struct:ret node:r_struct];
		return ret;
	} else if (r_array) {
		NSMutableArray *ret = [[NSMutableArray new] autorelease];
		[self simplify_array:ret node:r_array];
		return ret;
	}
	NSString* key = [[__node allKeys] lastObject];
	if (key == nil) return @"";
	if ([key isEqualToString:@"int"] || [key isEqualToString:@"i4"]) {
		return [NSNumber numberWithInt:[[[__node valueForKey:key] valueForKey:@"#value"] intValue]];
	}
	if ([key isEqualToString:@"double"]) {
		return [NSNumber numberWithDouble:[[[__node valueForKey:key] valueForKey:@"#value"] doubleValue]];
	}
	if ([key isEqualToString:@"string"]) {
		return [[__node valueForKey:key] valueForKey:@"#value"];
	}
	return @"";
}

# pragma mark xml-delegate

- (void)parserDidStartDocument:(NSXMLParser *)parser {
	result = [NSMutableDictionary new];
	t_sck = [NSMutableArray new];
}

- (void)parserDidEndDocument:(NSXMLParser *)parser {
	[t_sck release];
}

- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qualifiedName attributes:(NSDictionary *)attributeDict {
	if ([elementName isEqualToString:@"methodResponse"]) {
		[t_sck addObject:result];
		return;
	}
	if ([t_sck count] == 0) return;
	id lst_obj = [t_sck lastObject];
	// new object
	id tgt = nil;
	if ([elementName isEqualToString:@"data"] ||
		[elementName isEqualToString:@"struct"]
		) {
		tgt = [NSMutableArray new];
	} else {
		tgt = [NSMutableDictionary new];
		[(NSMutableDictionary*)tgt setValue:[NSNull null] forKey:elementName];
	}
	// add a array object for its child element
	if ([lst_obj isKindOfClass:[NSArray class]]) {
		NSMutableArray *arr = (NSMutableArray*)lst_obj;
		[arr addObject:tgt];
		[t_sck addObject:tgt];
        [tgt release];
		return;
	} else if ([lst_obj isKindOfClass:[NSDictionary class]]) {
		NSMutableDictionary *dict = (NSMutableDictionary*)lst_obj;
		[dict setValue:tgt forKey:elementName];
		[t_sck addObject:tgt];
        [tgt release];
		return;
	}
    [tgt release];
}

- (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string {
	if ([t_sck count] == 0) return;
	if ([string length] == 0) return;
	id lst_obj = [t_sck lastObject];
	if ([lst_obj isKindOfClass:[NSArray class]]) {
		NSMutableArray *arr = (NSMutableArray*)lst_obj;
		[arr addObject:string];
		return;
	} else if ([lst_obj isKindOfClass:[NSDictionary class]]) {
		NSMutableDictionary *dict = (NSMutableDictionary*)lst_obj;
		[dict setValue:string forKey:@"#value"];
		return;
	}
}

- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName {
	if ([t_sck count] == 0) return;
	[t_sck removeLastObject];
}

# pragma mark impl-delegate

- (void)xmlrpcDidStartLoading:(XmlRpc *)rpc {
	if ([owner.delegate respondsToSelector:@selector(xmlrpcDidStartLoading:)]) {
		[owner.delegate xmlrpcDidStartLoading:rpc];
	}
}

- (void)xmlrpcDidReceiveResult:(XmlRpc *)rpc result:(id)__result {
	if ([owner.delegate respondsToSelector:@selector(xmlrpcDidReceiveResult:result:)]) {
		[owner.delegate xmlrpcDidReceiveResult:rpc result:__result];
	}
}

@end

@implementation XmlRpc

@synthesize delegate;

- (id)init {
	self = [super init];
	d_ptr = [XmlRpcPrivate new];
	d_ptr.owner = self;
	return self;
}

- (void)dealloc {
	zero_release(delegate);
	zero_release(d_ptr);
    
	[super dealloc];
}

- (NSObject*)call:(Model *)model withUrl:(NSURL*)url {
    [super call:model withUrl:url];
    
    WSIRPC_CALLROUND;
    
    NSString* __method = model.method;
    NSArray* __params = model.params;
    
	NSDictionary* ret = (NSDictionary*)[d_ptr call:__method
                                           service:model.service 
                                            params:__params
                                               url:url];
	if (ret == nil)
        return nil;
    
	return (NSDictionary*)[d_ptr simplify_result:ret];
}

/*
- (id<IRpc>)confWithModel:(Model *)__model {
	url = __model.url;
	service = __model.service;
	return self;
}
 */

/*
- (BOOL)connect:(NSURL *)__url {
	d_ptr.url = __url;
	return YES;
}
 */

- (BOOL)is_connected {
	return YES;
}

- (void)disconnect {
    PASS;
}

@end

WSI_END_OBJC