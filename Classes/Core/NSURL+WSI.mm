
# import "Core.h"
# import "NSURL+WSI.h"
# import "WSIResource.h"

WSI_BEGIN_OBJC

WSIIMPL_CATEGORY(NSURL, WSI);

@implementation NSURL (WSI)

+ (NSURL*)URLWithUTF8String:(NSString*)str {
    return [NSURL URLWithString:[str stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]];
}

# ifndef WSI_iOS_4

- (NSString *)pathExtension {
    return @"/";
}

- (NSURL *)URLByAppendingPathComponent:(NSString *)pathComponent {
    NSString* abs = [self absoluteString];

# ifdef WSI_TARGET_IOS
    abs = [abs stringByAppendFormat:@"%@%@", [self pathExtension], pathComponent];
# else
    abs = [abs stringByAppendingFormat:@"%@%@", [self pathExtension], pathComponent];
# endif
    
    return [NSURL URLWithString:abs];
}

# endif

+ (NSString*)combineArguments:(NSArray*)arr {        
    NSMutableArray* t_arr = [[NSMutableArray alloc] initWithCapacity:4];
        
    for (id each in arr) {
        if ([each isKindOfClass:[NSPair class]]) {
            NSPair* pair = (NSPair*)each;
            NSString* seg = [NSString stringWithFormat:@"%@=%@", pair.first, pair.second];
            [t_arr addObject:seg];
        }
    }
    
    NSString* ret = [t_arr componentsJoinedByString:@"&"];
    [t_arr release];   
    
    return ret;
}

+ (NSString*)combineArgumentsDictionary:(NSDictionary*)dict {
    NSMutableArray* t_arr = [[NSMutableArray alloc] initWithCapacity:4];
        
    for (NSString* key in dict.allKeys) {
        NSString* seg = [NSString stringWithFormat:@"%@=%@",
                         key,
                         [dict valueForKey:key]];
        [t_arr addObject:seg];
    }
        
    NSString* ret = [t_arr componentsJoinedByString:@"&"];
    [t_arr release];
    
    return ret;   
}

@end

WSI_END_OBJC

WSI_BEGIN_CXX
WSI_BEGIN_NS(ns)

URL const null_url = URL(@"");

URL URL::Bundle(ns::String const& path)
{
    if (path.is_null())
        return null_url;
    ns::String str = [WSIResource PathOf:path];
    NSURL* url = [[NSURL alloc] initFileURLWithPath:str];
    URL ret(url);
    [url release];
    return ret;
}

WSI_END_NS
WSI_END_CXX