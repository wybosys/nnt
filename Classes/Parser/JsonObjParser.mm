
# import "../Core/Core.h"
# import "JsonObjParser.h"
# import "Mime+WSI.h"

WSI_BEGIN_OBJC

@implementation JsonObjParser

- (id)init {
    self = [super init];
    
    self.contentType = kMimeTypeTextJson;
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (NSData*)parse_todata:(NSArray *)obj {    
    //NSString* str = [NSURL combineArguments:obj];
    //return [str dataUsingEncoding:NSUTF8StringEncoding];
    return nil;
}

- (id)to_object:(id)data {
    NSString* str = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    NSObject* obj = [WSIObject json_decode:str];
    [str release];
    return obj;
}

@end

WSI_END_OBJC

WSI_BEGIN_CXX
WSI_BEGIN_NS(parser)

ns::String JsonObject::content_type() const
{
    return this->_self.contentType;
}

ns::Data JsonObject::parse_todata(ns::Object<> const& obj)
{
    return [this->_self parse_todata:obj];
}

ns::Object<> JsonObject::to_object(ns::Data const& da)
{
    return [this->_self to_object:da];
}

WSI_END_NS
WSI_END_CXX
