
# import "Core.h"
# import "RegexObjParser.h"
# import "Model.h"

NNT_BEGIN_OBJC

@implementation RegexObjParser

@synthesize queries = _queries;

- (id)init {
    self = [super init];
    
    _queries = [[NSMutableArray alloc] init];

    return self;
}

- (void)dealloc {
    safe_release(_queries);
    [super dealloc];
}

- (void)prepare:(id)obj {
    if ([obj isKindOfClass:[Model class]]) {
        Model* mdl = (Model*)obj;
        [self set_query:mdl.method];
    }    
}

- (NSObject*)parse_object:(NSData *)data {
    NSString* str = [[NSString alloc] initWithData:data encoding:self.dataEncoding];
    NSMutableArray* ret = [NSMutableArray array];
    for (NSString* re in _queries) {
        NSArray* cap = [str arrayOfCaptureComponentsMatchedByRegex:re];
        [ret addObjectsFromArray:cap];
    }
    safe_release(str);
    return ret;
}

- (void)add_query:(NSString*)str {
    [_queries addObject:str];
}

- (void)set_query:(NSString*)str {
    [_queries removeAllObjects];
    [_queries addObject:str];
}

@end

NNT_END_OBJC
