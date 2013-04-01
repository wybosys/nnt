
# import "Core.h"
# import "XmlObjParser.h"
# import "Mime+NNT.h"
# import "XmlParser.h"

NNT_BEGIN_OBJC

NNTDECL_PRIVATE_BEGIN(XmlObjParser, NSObject)

- (NSString*)xml_header;
- (NSString*)xml_object:(NSObject*)__obj needClosure:(BOOL)__closure;

NNTDECL_PRIVATE_IMPL(XmlObjParser)

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (NSString*)xml_header {
    return [NSString stringWithFormat:@"<?xml version=\"%@\" encoding=\"%@\" ?>", d_owner.version, d_owner.encoding];
}

- (NSString*)xml_object:(NSObject *)__obj needClosure:(BOOL)__closure {
    NSMutableString *str = [[NSMutableString new] autorelease];
    if ([__obj isKindOfClass:[NSNumber class]]) {
        if (__closure)
            [str appendString:@"<value>"];
        [str appendString:[(NSNumber*)__obj stringValue]];
        if (__closure)
            [str appendString:@"</value>"];
        goto LABEL_RETURN;
    }
    if ([__obj isKindOfClass:[NSString class]]) {
        if (__closure)
            [str appendString:@"<value>"];
        [str appendString:(NSString*)__obj];
        if (__closure)
            [str appendString:@"</value>"];
        goto LABEL_RETURN;
    }
    if ([__obj isKindOfClass:[NSArray class]]) {
        for (NSObject* each in (NSArray*)__obj) {
            [str appendString:[self xml_object:each needClosure:YES]];
        }
        goto LABEL_RETURN;
    }
    if ([__obj isKindOfClass:[NSDictionary class]]) {
        for (NSString *key in [(NSDictionary*)__obj allKeys]) {
            [str appendFormat:@"<%@>", key];
            [str appendString:[self xml_object:[(NSDictionary*)__obj valueForKey:key] needClosure:NO]];
            [str appendFormat:@"</%@>", key];
        }
        goto LABEL_RETURN;
    }
LABEL_RETURN:
    return str;
}

NNTDECL_PRIVATE_END

@implementation XmlObjParser

@synthesize encoding = _encoding, version = _version, root = _root;
@synthesize hideRoot = _hideRoot;

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(XmlObjParser);
    
    self.encoding = @"utf-8";
    self.version = @"1.0";
    self.root = @"root";
    self.hideRoot = YES;

    self.contentType = kMimeTypeTextXml;
    
    return self;
}

- (void)dealloc {
    safe_release(_encoding);
    safe_release(_version);
    safe_release(_root);
    
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (NSData*)parse_todata:(NSObject *)__obj {
    NSMutableString *str = [[NSMutableString new] autorelease];
    [str appendString:[d_ptr xml_header]];
    [str appendFormat:@"<%@>", _root];
    [str appendString:[d_ptr xml_object:__obj needClosure:NO]];
    [str appendFormat:@"</%@>", _root];
    return [str dataUsingEncoding:NSUTF8StringEncoding];
}

extern void xml_load_node(XmlNode*, ::nnt::ns::MutableDictionary&);
void xml_load_node(XmlNode* node, ::nnt::ns::MutableDictionary& dict)
{
    NNT_USINGCXXNAMESPACE;
    
    if (node.children.count == 0) {
        if (node.value == nil)
            dict[node.name] = [NSNull null];
        else
            dict[node.name] = node.value;
    } else {
        ns::MutableDictionary items;
        
        id exist = dict[node.name];
        if (exist == nil) {
            dict[node.name] = items;
        } else if ([exist isKindOfClass:[NSMutableArray class]]) {
            NSMutableArray* arr = (NSMutableArray*)exist;
            [arr addObject:items];
        } else {
            NSMutableArray* arr = [[NSMutableArray alloc] init];
            [arr addObject:exist];
            [arr addObject:items];
            dict[node.name] = arr;
            safe_release(arr);
        }
        
        for (XmlNode* each in node.children) {
            xml_load_node(each, items);
        }
    }
}

- (id)to_object:(id)data {
    NNT_USINGCXXNAMESPACE;
    
    XmlParser* xml = [[XmlParser alloc] initWithData:data];
    if (xml == nil)
        return nil;
    
    ns::MutableDictionary dict;
    
    ns::String rootkey = xml.rootNode.name;
    xml_load_node(xml.rootNode, dict);
    
    safe_release(xml);
    
    if (_hideRoot)
        return [dict[rootkey] consign];
    
    return dict.consign();
}

@end

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(parser)

ns::Data XmlObject::parse_todata(ns::Object<> const& obj)
{
    return [this->_self parse_todata:obj];
}

ns::Object<> XmlObject::to_object(ns::Data const& da)
{
    return [this->_self to_object:da];
}

NNT_END_NS
NNT_END_CXX
