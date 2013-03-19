
# import "Core.h"

# define NNT_LIBONLY
# import "NullObjParser.h"

NNT_BEGIN_OBJC

signal_t kSignalParserError = @"::nnt::parser::parse::error";

void ParserInit() {
    [NNT Register:NNTHookTypeFin hookFunc:[func_object withAddr:(void*)&ParserFin]];
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

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalParserError)
NNTEVENT_END

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

NNT_END_OBJC