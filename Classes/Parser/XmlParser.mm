
# import "Core.h"
# import "XmlParser.h"
# import <Google/GDataXMLNode.h>

NNT_BEGIN_OBJC

# define ATTR(node)    ((GDataXMLNode*)node)
# define NODE(node)    ((GDataXMLElement*)node)
# define DOC(doc)      ((GDataXMLDocument*)doc)
# define NAMES(node)   ((GDataXMLNode*)node) 

@interface XmlAttribute ()

@property (nonatomic, copy) NSString *name;
@property (nonatomic, assign) void* _node;

- (id)initWithRawNode:(void*)rnode;

@end

@implementation XmlAttribute 

@synthesize name = _name, value = _value;
@synthesize _node;

- (id)initWithName:(NSString *)name value:(NSString *)value {
    self = [super init];
    _node = [[GDataXMLNode attributeWithName:name stringValue:value] retain];
    if (_node == nil) {
        [self release];
        return nil;
    }
    
    self.name = name;
    self.value = value;
    
    return self;
}

- (id)initWithRawNode:(void *)rnode {
    self = [super init];
    
    _node = [ATTR(rnode) retain];
    _name = [ATTR(_node).name copy];
    _value = [[ATTR(_node) stringValue] copy];
    
    return self;
}

- (void)dealloc {
    safe_release(_name);
    safe_release(_value);
    [ATTR(_node) release]; _node = nil;
    
    [super dealloc];
}

- (void)set {
    [ATTR(_node) setStringValue:self.value];
}

- (void)load {
    self.name = ATTR(_node).name;
    self.value = [ATTR(_node) stringValue];
}

@end

@interface XmlNamespace ()

@property (nonatomic, copy) NSString *name;
@property (nonatomic, assign) void* _node;

- (id)initWithRawNode:(void*)rnode;

@end

@implementation XmlNamespace 

@synthesize name = _name, value = _value;
@synthesize _node;

- (id)initWithName:(NSString *)name value:(NSString *)value {
    self = [super init];
    _node = [[GDataXMLNode namespaceWithName:name stringValue:value] retain];
    if (_node == nil) {
        [self release];
        return nil;
    }
    
    self.name = name;
    self.value = value;
    
    return self;
}

- (id)initWithRawNode:(void *)rnode {
    self = [super init];
    
    _node = [NAMES(rnode) retain];    
    _name = [NAMES(_node).name copy];
    _value = [[NAMES(_node) stringValue] copy];
    
    return self;
}

- (void)dealloc {
    safe_release(_name);
    safe_release(_value);
    [NAMES(_node) release]; _node = nil;
    
    [super dealloc];
}

- (void)set {
    [NAMES(_node) setStringValue:self.value];
}

- (void)load {
    self.name = NAMES(_node).name;
    self.value = [NAMES(_node) stringValue];
}

@end

@interface XmlNode ()

@property (nonatomic, copy) NSString* name;

- (void)__init;
- (id)initWithRawNode:(void*)rnode;

@end

@implementation XmlNode

@synthesize name = _name;
@synthesize value = _value;
@synthesize children = _children;
@synthesize attributes = _attributes;
@synthesize namespaces = _namespaces;

- (void)__init {
    _children = [[NSMutableArray arrayWithCapacity] retain];
    _attributes = [[NSMutableArray arrayWithCapacity] retain];
    _namespaces = [[NSMutableArray arrayWithCapacity] retain];
}

- (id)init {
    self = [super init];
    [self __init];
    return self;
}

- (id)initWithRawNode:(void *)rnode {
    self = [super init];
    _node = [NODE(rnode) retain];
    [self __init];
    
    // load.
    [self load];
    
    return self;
}

- (id)initWithName:(NSString *)name {
    self = [super init];
    _node = [[GDataXMLElement elementWithName:name] retain];
    if (_node == nil) {
        [self release];
        return nil;
    }
    
    self.name = name;
    
    [self __init];
    return self;
}

+ (id)nodeWithName:(NSString *)name {
    return [[[XmlNode alloc] initWithName:name] autorelease];
}

//+ (NSString*)NodeName:(NSString *)name {
//    return [NSString stringWithFormat:@"<%@></%@>", name, name];
//}

- (void)dealloc {
    safe_release(_name);
    safe_release(_value);
    [NODE(_node) release]; _node = nil;
    safe_release(_children);
    safe_release(_attributes);
    safe_release(_namespaces);
    
    [super dealloc];
}

- (XmlNode*)addNode:(XmlNode *)node {
    [_children addObject:node];
    return node;
}

- (XmlNode*)addNodeByName:(NSString *)name {
    XmlNode* node = [[XmlNode alloc] initWithName:name];
    [self addNode:node];
    [node release];
    return node;
}

- (XmlAttribute*)addAttribute:(XmlAttribute*)attribute {
    [_attributes addObject:attribute];
    return attribute;
}

- (XmlAttribute*)addAttributeByName:(NSString *)name value:(NSString *)value {
    XmlAttribute* attr = [[XmlAttribute alloc] initWithName:name value:value];
    [self addAttribute:attr];
    [attr release];
    return attr;
}

- (void)addNamespace:(NSString *)prefix href:(NSString *)href {
    XmlNamespace* ns = [[XmlNamespace alloc] initWithName:prefix value:href];
    ns.value = href;
    [_namespaces addObject:ns];
    [ns release];
}

- (void)set {
    // add namespace.
    for (XmlNamespace* each in _namespaces) {
        [each set];
        [NODE(_node) addNamespace:NAMES(each._node)];
    }
    
    // set attributes.
    for (XmlAttribute* each in _attributes) {
        [each set];
        [NODE(_node) addAttribute:ATTR(each._node)];
    }
    
    // add children.
    for (XmlNode* each in _children) {
        [each set];
        [NODE(_node) addChild:NODE(each->_node)];
    }
    
    // set value.
    [NODE(_node) setStringValue:self.value];
}

- (void)load {        
    if (NODE(_node).kind == GDataXMLTextKind)
        return;
    
    // read namespace    
    for (GDataXMLNode* each in NODE(_node).namespaces) {
        XmlNamespace* ns = [[XmlNamespace alloc] initWithRawNode:each];
        [_namespaces addObject:ns];
        [ns release];
    }
    
    // read attributes
    for (GDataXMLNode* each in NODE(_node).attributes) {
        XmlAttribute* attr = [[XmlAttribute alloc] initWithRawNode:each];
        [_attributes addObject:attr];
        [attr release];
    }
    
    // read children
    for (GDataXMLNode* each in NODE(_node).children) {
        if (each.kind == GDataXMLTextKind)
            continue;
        XmlNode* node = [[XmlNode alloc] initWithRawNode:each];
        [_children addObject:node];
        [node release];
    }
    
    // read value
    self.name = NODE(_node).name;
    self.value = [NODE(_node) stringValue];
}

- (NSArray*)childrenForName:(NSString*)name {
    NSMutableArray* arr = [[NSMutableArray alloc] initWithCapacity:_children.count];
    for (XmlNode* each in _children) {
        if ([each.name isEqualToString:name]) {
            [arr addObject:each];
        }
    }
    return [arr autorelease];
}

- (XmlAttribute*)attributeForName:(NSString*)name {
    for (XmlAttribute* each in _attributes) {
        if ([each.name isEqualToString:name]) {
            return each;
        }
    }
    return nil;
}

@end

@interface XmlDocument ()

@property (nonatomic, retain) XmlNode* rootNode;

- (void)__init;

@end

@implementation XmlDocument

@synthesize rootNode = _rootNode;
@synthesize version = _version, encoding = _encoding;

- (void)__init {
    [super __init];
    
    self.version = @"1.0";
    self.encoding = @"UTF-8";
}

- (id)initWithRootNode:(XmlNode *)root {
    self = [super init];
    [self __init];
    
    self.rootNode = root;
    
    // add root.
    [self addNode:self.rootNode];
        
    return self;
}

- (void)dealloc {
    safe_release(_rootNode);
    safe_release(_version);
    safe_release(_encoding);
    
    [super dealloc];
}

- (XmlNode*)addNode:(XmlNode *)node {
    [_children addObject:node];
    return node;
}

- (void)set {       
    // set root.
    [self.rootNode set];
    
    // init.
    [DOC(_node) release];
    _node = [[GDataXMLDocument alloc] initWithRootElement:NODE(self.rootNode->_node)];
    
    // set
    [DOC(_node) setVersion:self.version];
    [DOC(_node) setCharacterEncoding:self.encoding];
}

@end

@implementation XmlParser

- (id)initWithString:(NSString *)str {
    NSData* data = [str dataUsingEncoding:NSUTF8StringEncoding];
    return [self initWithData:data];
}

- (id)initWithData:(NSData*)data {
    self = [super init];
    
    NSError* err = nil;
    _node = [[GDataXMLDocument alloc] initWithData:data options:0 error:&err];
    
    if (err) {
        [self release];
        return nil;
    }
    
    GDataXMLElement* root = [DOC(_node) rootElement];
    _rootNode = [[XmlNode alloc] initWithRawNode:root];
    [self addNode:_rootNode];
    
    return self;
}

- (NSData*)toData {
    [self set];
    return [DOC(_node) XMLData];
}

- (NSString*)toString {
    NSData* data = [self toData];
    NSString* str = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    return [str autorelease];
}

@end

NNT_END_OBJC