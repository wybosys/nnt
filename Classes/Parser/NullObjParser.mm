
# import "Core.h"

# define WSI_LIBONLY
# import "NullObjParser.h"

WSI_BEGIN_OBJC

signal_t kSignalParserError = @"::wsi::parser::parse::error";

void ParserInit() {
    [WSI Register:WSIHookTypeFin hookFunc:[func_object withAddr:(void*)&ParserFin]];
}

void ParserFin() {
    PASS;
}

NSStringEncoding kParserDataEncoding = NSUTF8StringEncoding;

@implementation NullObjParser

@synthesize owner;
@synthesize byteCount;
@synthesize contentType;
@synthesize dataEncoding;

- (id)init {
    self = [super init];
    
    self.contentType = @"text/plain";
    self.dataEncoding = kParserDataEncoding;
    
    return self;
}

- (void)dealloc {
    safe_release(contentType);
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalParserError)
WSIEVENT_END

- (NSData*)parse_todata:(NSObject *)obj {
    return nil;
}

- (NSObject*)parse_object:(NSData *)data {
    byteCount = [data length];
    return [self to_object:data];
}

- (id)to_object:(id)data {
    return nil;
}

- (void)prepare:(id)obj {
    PASS;
}

@end

@implementation _cxxnull_objectparser

- (id)to_object:(id)data {
    return [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease];
}

@end

WSI_END_OBJC