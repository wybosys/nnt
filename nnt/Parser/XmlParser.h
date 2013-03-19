
# ifndef __WSI_PARSER_XML_D346FEB6D4B640F285D9026742145E27_H_INCLUDED
# define __WSI_PARSER_XML_D346FEB6D4B640F285D9026742145E27_H_INCLUDED

# ifdef WSI_TARGET_IOS
#   define USE_LIBXML
# else
#   define USE_LIBXERCESC
# endif

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

@interface XmlAttribute : WSIObject {
    NSString *_name, *_value;
    
@protected
    
    //! raw node object.
    void* _node;
}

@property (nonatomic, copy, readonly) NSString *name;
@property (nonatomic, copy) NSString *value;

//! init.
- (id)initWithName:(NSString*)name value:(NSString*)value;

//! set.
- (void)set;

//! load.
- (void)load;

@end

@interface XmlNamespace : WSIObject {
    NSString *_name, *_value;
    
@protected
    
    //! raw node object.
    void* _node;
}

@property (nonatomic, copy, readonly) NSString *name;
@property (nonatomic, copy) NSString *value;

//! init.
- (id)initWithName:(NSString*)name value:(NSString*)value;

//! set.
- (void)set;

//! load.
- (void)load;

@end

@interface XmlNode : WSIObject {
    
    //! name.
    NSString* _name;
    
    //! value.
    NSString* _value;
    
    //! nodes.
    NSMutableArray* _children;
    
    //! attributes.
    NSMutableArray* _attributes;
    
    //! namespaces.
    NSMutableArray* _namespaces;
    
    @protected
    
    //! raw node object.
    void* _node;
}

@property (nonatomic, copy, readonly) NSString* name;
@property (nonatomic, copy) NSString* value;
@property (nonatomic, retain) NSMutableArray* children;
@property (nonatomic, retain) NSMutableArray* attributes;
@property (nonatomic, retain) NSMutableArray* namespaces;

//! init.
- (id)initWithName:(NSString*)name;

//! format node name.
//+ (NSString*)NodeName:(NSString*)name;

//! node.
+ (id)nodeWithName:(NSString*)name;

//! add node.
- (XmlNode*)addNode:(XmlNode*)node;

//! add node by name.
- (XmlNode*)addNodeByName:(NSString*)name;

//! add attribute.
- (XmlAttribute*)addAttribute:(XmlAttribute*)attribute;

//! add attribute by name & value.
- (XmlAttribute*)addAttributeByName:(NSString*)name value:(NSString*)value;

//! add namespace.
- (void)addNamespace:(NSString*)prefix href:(NSString*)href;

//! children for name.
- (NSArray*)childrenForName:(NSString*)name;

//! attribute for name.
- (XmlAttribute*)attributeForName:(NSString*)name;

//! set.
- (void)set;

//! load.
- (void)load;

@end

@interface XmlDocument : XmlNode {
    
    //! root node.
    XmlNode* _rootNode;
    
    //! version.
    NSString *_version, *_encoding;
    
}

@property (nonatomic, readonly, retain) XmlNode* rootNode;
@property (nonatomic, copy) NSString *version, *encoding;

//! init.
- (id)initWithRootNode:(XmlNode*)root;

@end

@interface XmlParser : XmlDocument

//! init with data.
- (id)initWithData:(NSData*)data;
- (id)initWithString:(NSString*)str;

//! get data.
- (NSData*)toData;

//! to string.
- (NSString*)toString;

@end

WSI_END_HEADER_OBJC

# endif

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(parser)

WSICLASS(XmlAttribute);
WSICLASS(XmlNode);
WSICLASS(XmlDocumentType);
WSICLASS(XmlDocument);

class XmlNode
: public cxx::Object<>
{
    WSIDECL_NOCOPY(XmlNode);
    
public:
    
    XmlNode();
    XmlNode(core::string const& name, core::string const& value = core::null_string);
    ~XmlNode();
    
public:
    
    typedef core::multimap<core::string, XmlNode*> nodes_type, children_type;
    nodes_type children;
    
    typedef core::map<core::string, XmlAttribute*> attributes_type;
    attributes_type attributes;
    
    //! clear children and attributes.
    void clear();
    
    //! clear children.
    void clear_children();
    
    //! clear attributes.
    void clear_attributes();
    
    //! find attr.
    XmlAttribute const* attribute(core::string const&) const;
    XmlAttribute* attribute(core::string const&);
    void remove_attribute(core::string const&);
    
    //! ava attr.
    XmlAttribute* ava_attribute(core::string const&);
    
    //! node.
    XmlNode const* node(core::string const&) const;
    XmlNode* node(core::string const&);

	//! nodes.
    typedef core::list<XmlNode const*> const_nodes_result;
    typedef core::list<XmlNode*> nodes_result;
	core::list<XmlNode const*> nodes(core::string const&) const;
	core::list<XmlNode*> nodes(core::string const&);
    
    //! first & trace.
    XmlNode *first, *last, *prev, *next, *parent;
    
    //! name & value.
    core::string name, value;
    
    //! namespace.
    core::string ns;
    
    //! prefix.
    core::string prefix;
    
    //! add node.
    XmlNode* add(XmlNode* node);
    XmlNode* add_node(core::string const&, core::string const& value = core::null_string);
    
    //! add attribute.
    XmlAttribute* add(XmlAttribute* attr);
    XmlAttribute* add_attr(core::string const&, core::string const& value = core::null_string);
    
    //! to string.
    core::string to_string(bool rootvisible = true) const;
    
    //! get full name.
    core::string full_name() const;

    //! save.
    bool save(core::data&) const;
    
    //! load.
    bool load(core::data const&);
    
};

class XmlAttribute
: public XmlNode
{
    WSIDECL_NOCOPY(XmlAttribute);
    
public:  
    
    XmlAttribute();    
    XmlAttribute(core::string const& name, core::string const& value = core::null_string);
    ~XmlAttribute();
        
};

class XmlDocumentType
: public XmlNode
{
    WSIDECL_NOCOPY(XmlDocumentType);
    
public:
    
    XmlDocumentType();
    ~XmlDocumentType();
    
    core::string publicId, systemId;
};

class XmlDocument
: public cxx::Object<>
{
    WSIDECL_NOCOPY(XmlDocument);
    WSIDECL_SIGNALS_SLOTS;
    
public:
    XmlDocument();
    virtual ~XmlDocument();
    
public:
    
    //! parse from string.
    bool parse_string(core::string const&);
    
    //! parse from data.
    bool parse_data(core::data const&);
    
    //! parse from file.
    bool parse_file(core::string const&);
    
    //! pase to string.
    core::string to_string() const;
    
    //! save.
    bool save(core::data&) const;
    
    //! root node.
    XmlNode const* root() const;
    XmlNode* root();
    
    //! invoke while loaded.
    virtual void loaded();
    
    //! escape.
    static core::string Escape(core::string const&);
    
public:
    
    //! type.
    XmlDocumentType type;
    
    //! encoding.
    core::string encoding;
    
protected:
    
    XmlNode* _root;
    
# ifdef USE_LIBXERCESC
    void* _env;
# endif
    
};

class XmlSaxDocument
: public XmlDocument
{
public:
    
    XmlSaxDocument();
    virtual ~XmlSaxDocument();
    
public:
    
    //! parse from string.
    bool parse_string(core::string const&);
    
    //! parse from data.
    bool parse_data(core::data const&);
    
    //! parse from file.
    bool parse_file(core::string const&);
    
    //! for sax.
    core::stack<XmlNode*> sck_nodes;
    
protected:
    
# ifdef USE_LIBXML
    void* _hdl;
# endif
    
};

WSI_END_NS 

WSI_EXTERN signal_t kSignalLoaded;

WSI_END_HEADER_CXX

# endif

# endif
