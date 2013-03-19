
# import "Core.h"
# import "HtmlObjParser.h"
# import "HtmlParser.h"

WSI_USINGCXXNAMESPACE;

WSI_BEGIN_OBJC

@implementation HtmlObjParser

@synthesize queries = _queries;

- (id)init {
    self = [super init];
    
    _queries = [[NSMutableArray alloc] init];
    self.contentType = @"text/html";
    
    return self;
}

- (void)dealloc {
    zero_release(_queries);
    [super dealloc];
}

- (NSData*)parse_todata:(NSObject *)obj {    
    NSString* str = [NSURL combineArguments:(NSArray*)obj];
    return [str dataUsingEncoding:NSUTF8StringEncoding];
}

- (id)to_object:(id)data {
    ns::Data da(data);
    core::data wrap = core::type_cast< core::data>(da);
    html::Document doc;
    
    // set encoding.
    doc.encoding = core::tostr(GetStringEncodingName(self.dataEncoding));
    
    // parse.
    if (doc.parse(wrap) == false)
        return nil;
    
    // query.
    html::Document::query_result result;
    for (NSString* each in _queries) {
        doc.jquery(core::tostr(each), result);
    }
    
    // combine result.
    core::data ret;
    html::Document::combine(ret, result, core::null_string);
    
    return [NSData dataWithBytes:(void const*)ret.bytes()
                          length:ret.length()];
}

- (void)add_query:(NSString*)str {
    [_queries addObject:str];
}

- (void)set_query:(NSString*)str {
    [_queries removeAllObjects];
    [_queries addObject:str];
}

@end

WSI_END_OBJC

WSI_BEGIN_CXX
WSI_BEGIN_NS(parser)

ns::String HtmlObject::content_type() const
{
    return this->_self.contentType;
}

ns::Data HtmlObject::parse_todata(ns::Object<> const& obj)
{
    return [this->_self parse_todata:obj];
}

ns::Object<> HtmlObject::to_object(ns::Data const& da)
{
    return [this->_self to_object:da];
}

WSI_END_NS
WSI_END_CXX