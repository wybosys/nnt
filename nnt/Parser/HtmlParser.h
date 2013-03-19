
# ifndef __WSI_PARSER_HTML_A607CE61ADF94A1493A4C8CCCEEFCD00_H_INCLUDED
# define __WSI_PARSER_HTML_A607CE61ADF94A1493A4C8CCCEEFCD00_H_INCLUDED

# ifdef first
#   undef first
# endif

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(html)

WSICLASS(Document);
WSICLASS(Element);
WSICLASS(Node);
WSICLASS(Attribute);

class Element
: public RefObject
{
public:
    
    Element();
    Element(void*);
    virtual ~Element();
    
    void set_element(void*);
    
    bool is_null() const
    {
        return _element == NULL;
    }
    
    core::string get_name() const;
    core::string get_value() const;
    
protected:
    
    void* _element;
    
};

class Attribute
: public Element
{
public:
    
    Attribute();
    Attribute(core::string const& name, core::string const& value = core::null_string);
    Attribute(Attribute const&);
    Attribute(void*);
    ~Attribute();
    
    //! name & value.
    core::string name, value;
    
    //! remove.
    void remove();
    
    //! set value.
    void set_value(core::string const& str);
    
};

class Node
: public Element
{
public:
    
    typedef enum 
    {
        NF_NOTEMPTY = 1,
    } NodeFilter;
    
    Node();
    Node(Node const&);
    Node(void*);
    ~Node();
    
    typedef core::pointer_vector<Element> query_result;
    
    //! query use jquery style command.
    void jquery(core::string const& cmd, query_result& result) const;
    
    //! remove.
    void remove();
    
    //! save node.
    void save(core::data&) const;
    
    //! count of children.
    usize count() const;
    
    //! node at.
    Node at(uint idx) const;
    
    //! first.
    Node first() const;
    
    //! last.
    Node last() const;
    
    //! next.
    Node next() const;
    
    //! next use filter.
    Node next(NodeFilter) const;
    
    //! previous.
    Node previous() const;
    
    //! has attr.
    bool has_attr(core::string const&) const;
    
    //! find attr.
    Attribute attr(core::string const&) const;
    
    //! has attr.
    bool has_node(core::string const&) const;
    
    //! find attr.
    Node node(core::string const&) const;
    
    //! add attr.
    Attribute& add(Attribute&);
    void add(Attribute const&);
    
    //! parent.
    Node parent() const;
    
    //! value.
    core::string value() const
    {
        return get_value();
    }
    
protected:
    
    bool _removed;
    
};

class Document
: public Node
{
public:
    
    Document();
    Document(core::data const&);
    ~Document();
    
    typedef core::pointer_vector<Element> query_result;
    
    static void combine(core::data&, query_result const&, core::string const& sepr);
    
public:
    
    //! parse data.
    bool parse(core::data const&);
    
    //! save to data.
    void save(core::data&) const;
    
    //! close parser.
    void close();
    
    //! string for encoding.
    core::string encoding;
    
    //! root.
    Node root() const
    {
        return at(0);
    }
    
protected:
    
    void* _doc;
    
    friend class Node;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif
