
# import "Core.h"
# import "TextObjParser.h"
# import "Mime+NNT.h"

NNT_BEGIN_OBJC

@implementation TextObjParser

- (id)init {
    self = [super init];
    
    self.contentType = kMimeTypeTextPlain;
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (NSData*)parse_todata:(NSArray *)obj {
    return nil;
}

- (id)to_object:(id)data {
    NSString* str = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    return [str autorelease];
}

@end

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(parser)

ns::String TextObject::content_type() const
{
    return this->_self.contentType;
}

ns::Data TextObject::parse_todata(ns::Object<> const& obj)
{
    return [this->_self parse_todata:obj];
}

ns::Object<> TextObject::to_object(ns::Data const& da)
{
    return [this->_self to_object:da];
}

NNT_END_NS
NNT_END_CXX
