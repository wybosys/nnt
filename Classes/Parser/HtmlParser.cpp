
# include "Core.h"
# include "HtmlParser.h"

# include <libxml2/libxml/xinclude.h>
# include <libxml2/libxml/HTMLtree.h>
# include <libxml2/libxml/HTMLparser.h>

# include "../Core/Boost+WSI.h"
# include <boost/spirit/include/classic.hpp>
# include <boost/spirit/include/phoenix.hpp>
# include <boost/spirit/include/qi.hpp>

# include <boost/algorithm/string.hpp>
# include <boost/algorithm/string/split.hpp>

# include "CSSParser.h"

WSI_BEGIN_CXX
WSI_BEGIN_NS(html)

using ::boost::spirit::qi::grammar;
using ::boost::spirit::qi::rule;
using ::boost::spirit::qi::unused_type;
using ::boost::phoenix::function;
using ::boost::spirit::ascii::space_type;

class jquery_grammar;

struct  _do_tag
{
	template <typename T> struct result { typedef void type; };
	void operator () (jquery_grammar* gmr) const;
};
function<_do_tag> const do_tag = _do_tag();

struct  _do_class
{
	template <typename T> struct result { typedef void type; };
	void operator () (jquery_grammar* gmr) const;
};
function<_do_class> const do_class = _do_class();

struct  _do_id
{
	template <typename T> struct result { typedef void type; };
	void operator () (jquery_grammar* gmr) const;
};
function<_do_id> const do_id = _do_id();

struct  _do_child
{
	template <typename T> struct result { typedef void type; };
	void operator () (jquery_grammar* gmr) const;
};
function<_do_child> const do_child = _do_child();

struct  _do_attr
{
	template <typename T> struct result { typedef void type; };
	void operator () (jquery_grammar* gmr) const;
};
function<_do_attr> const do_attr = _do_attr();

struct  _do_equal
{
	template <typename T> struct result { typedef void type; };
	void operator () (jquery_grammar* gmr) const;
};
function<_do_equal> const do_equal = _do_equal();

struct _do_filter
{
    template <typename T> struct result { typedef void type; };
    void operator () (jquery_grammar* gmr) const;
};
function<_do_filter> const do_filter = _do_filter();

class jquery_grammar
: public grammar<char const*>
{    
public:	
    
    jquery_grammar()
    : jquery_grammar::base_type(_rule, "JQueryGrammar"),
    _obj_tag(NULL),
    _child(false), _equal(false)
    {
		//using ::boost::spirit::qi::alnum;
		using ::boost::spirit::qi::lit;
		using ::boost::phoenix::push_back;
        using ::boost::phoenix::replace;
		using ::boost::phoenix::ref;
		using ::boost::spirit::qi::_1;
        using ::boost::spirit::qi::ascii::space;
        using ::boost::spirit::qi::skip;
        using ::boost::spirit::qi::char_;
        using ::boost::spirit::qi::string;
        
        _r_tag = +(char_("0-9a-zA-Z") | char_('-') | char_('_'))[push_back(ref(_str_tag), _1)];
        
        _r_class = char_('.') >> +(char_("0-9a-zA-Z") | char_('-') | char_('_'))[push_back(ref(_str_class), _1)];
        
        _r_id = char_('#') >> +(char_("0-9a-zA-Z") | char_('-') | char_('_'))[push_back(ref(_str_id), _1)];
        
        _r_attr = char_('[') >> +(char_("0-9a-zA-Z") | char_('-') | char_('_'))[push_back(ref(_str_attr_name), _1)] >> *space >> 
        -(char_("=")[do_equal(this)] >> *space >> char_("'\"") >> 
          +(char_("0-9a-zA-Z") | char_('-') | char_('_') | char_(':') | char_('#') | char_(';'))[push_back(ref(_str_attr_value), _1)] >> char_("'\""))
        >> *space >> char_(']');
        
        _r_filter = char_(':') >> (string("parent") | string("empty"));
        
        _r_sub = 
        _r_tag[do_tag(this)] |
        _r_class[do_class(this)] | 
        _r_id[do_id(this)] | 
        _r_attr[do_attr(this)] |
        _r_filter[do_filter(this)]
        ;
        
        _rule = *(*space[do_child(this)] >> (_r_sub));
    }
    
    ~jquery_grammar()
    {
        clear();
    }
    
    void clear()
    {
        if (_obj_tag)
        {
            _obj_tag->drop();
            _obj_tag = NULL;
        }
        _obj_tag_last = NULL;
    }
    
protected:
    
    rule<char const*> _rule, _r_sub;
    rule<char const*> _r_tag, _r_class, _r_id, _r_attr, _r_filter;
    
protected: 
    
    // for css.
    css::Class* _obj_tag, *_obj_tag_last;
    core::string _str_tag, _str_class, _str_id, _str_attr_name, _str_attr_value, _str_filter_name, _str_filter_param;
    bool _child, _equal;
    
    friend class _do_tag;
    friend class _do_class;
    friend class _do_id;
    friend class _do_child;
    friend class _do_attr;
    friend class _do_equal;
    friend class _do_filter;
    
    friend class Node;
};

static bool class_find(css::Attr const* tgt, core::string const& str)
{
    using namespace ::std;
    using namespace ::boost;
    
    typedef vector< string > result_type;
    result_type result;
    split(result, str, is_any_of(" "));
    
    for (result_type::const_iterator iter = result.begin();
         iter != result.end();
         ++iter)
    {
        if (*iter == tgt->value)
            return true;
    }
    
    return false;
}

static bool unknown_find(css::Attr const* tgt, core::string const& str)
{
    return str.find(tgt->value) != core::string::npos;
}

static bool attribute_find(css::Attr const* tgt, core::string const& str)
{
    if (tgt->value.size() > str.size())
        return false;
    
    if (tgt->name == "class")
        return class_find(tgt, str);
    else if (tgt->name == "id")
        return tgt->value == str;
    
    return unknown_find(tgt, str);
}

static void find_tag_r(xmlNodePtr node, css::Class const* cls, css::Class const* root, Node::query_result& result)
{
    xmlNodePtr each = xmlFirstElementChild(node);
    while (each)
    {
        // find name.
        if (cls->name.empty() == false)
        {
            // find class.
            if (each->type == XML_ELEMENT_NODE &&
                cls->name == (char const*)each->name)
            {
                // find class.
                if (cls->classes.size() == 0)
                {
                    if (cls->attributes.size() == 0)
                    {
                        Node* elem = new Node(each);
                        result.push_back(elem);                    
                    }
                    else
                    {
                        // equal attribute.
                        bool equal = true;
                        for (css::attributes_type::const_iterator iter = cls->attributes.begin();
                             equal && iter != cls->attributes.end();
                             ++iter)
                        {                            
                            xmlAttrPtr attr = xmlHasProp(each, (uchar const*)iter->first.c_str());
                            if (attr == NULL)
                            {
                                equal = false;
                                break;
                            }
                         
                            css::Attr const* tgt = (css::Attr const*)iter->second;
                            if (tgt->empty == false)
                            {                            
                                xmlChar* content = xmlNodeListGetString(attr->doc, attr->children, true);
                                core::string str = (char const*)content;
                                xmlFree(content);
                                                     
                                equal = attribute_find(tgt, str);
                            }
                        }
                        
                        if (equal)
                        {
                            // add element.
                            Node* elem = new Node(each);
                            result.push_back(elem); 
                        }
                    }
                    
                    // find in child.
                    find_tag_r(each, root, root, result); 
                }
                else
                {
                    if (cls->attributes.size() == 0)
                    {
                        // find sub class.
                        for (css::classes_type::const_iterator iter = cls->classes.begin();
                             iter != cls->classes.end();
                             ++iter)
                        {
                            find_tag_r(each, iter->second, root, result);
                        }
                    }
                    else
                    {
                        // equal attribute.
                        bool equal = true;
                        for (css::attributes_type::const_iterator iter = cls->attributes.begin();
                             equal && iter != cls->attributes.end();
                             ++iter)
                        {                            
                            xmlAttrPtr attr = xmlHasProp(each, (uchar const*)iter->first.c_str());
                            if (attr == NULL)
                            {
                                equal = false;
                                break;
                            }
                            
                            css::Attr const* tgt = (css::Attr const*)iter->second;
                            if (tgt->empty == false)
                            {
                                xmlChar* content = xmlNodeListGetString(attr->doc, attr->children, true);
                                core::string str = (char const*)content;
                                xmlFree(content);                            
                                
                                equal = attribute_find(tgt, str);
                            }
                        }
                        
                        if (equal)
                        {
                            // find sub class.
                            for (css::classes_type::const_iterator iter = cls->classes.begin();
                                 iter != cls->classes.end();
                                 ++iter)
                            {
                                find_tag_r(each, iter->second, root, result);
                            }  
                        }
                        else
                        {
                            // find in child.
                            find_tag_r(each, root, root, result); 
                        }

                    }
                }
            }
            else
            {
                // find in child.
                find_tag_r(each, root, root, result);   
            }
        }
        else // no class.
        {
            if (cls->attributes.size())
            {
                // equal attribute.
                bool equal = false;
                for (css::attributes_type::const_iterator iter = cls->attributes.begin();
                     !equal && iter != cls->attributes.end();
                     ++iter)
                {                            
                    core::string const& name = iter->first;
                    xmlAttrPtr attr = xmlHasProp(each, (uchar const*)name.c_str());
                    //core::string value = (char const*)attr->name;
                    if (attr == NULL)
                    {
                        equal |= false;
                        continue;
                    }
                                   
                    css::Attr const* tgt = (css::Attr const*)iter->second;
                    if (tgt->empty == false)                        
                    {
                        xmlChar* content = xmlNodeListGetString(attr->doc, attr->children, true);
                        core::string str = (char const*)content;
                        xmlFree(content);
                        
                        equal |= attribute_find(tgt, str);
                    }
                    else
                    {
                        equal = true;
                    }                    
                }
                
                if (equal)
                {
                    // add element.
                    Node* elem = new Node(each);
                    result.push_back(elem); 
                }
            }
            
            // find in child.
            find_tag_r(each, root, root, result);
        }
        
        // next sibling.
        each = xmlNextElementSibling(each);
    }
}

void _do_tag::operator () (jquery_grammar* gmr) const
{
    css::Class* tag = new css::Class;
    tag->name = gmr->_str_tag;
    gmr->_str_tag.clear();
    
    // add class list.
    if (gmr->_obj_tag == NULL)
    {
        gmr->_obj_tag = gmr->_obj_tag_last = tag;
    }
    else
    {        
        gmr->_obj_tag_last->classes[tag->name] = tag;
        
        if (gmr->_child)
        {
            gmr->_obj_tag_last = tag;
            gmr->_child = false;
        }
    }
}

void _do_class::operator () (jquery_grammar* gmr) const
{
    css::Attr* attr = new css::Attr;
    attr->name = "class";
    attr->value = gmr->_str_class;
    gmr->_str_class.clear();
    
    // add attr.
    if (gmr->_obj_tag == NULL)
    {
        gmr->_obj_tag = gmr->_obj_tag_last = new css::Class;
    }
    
    gmr->_obj_tag_last->attributes.insert(core::make_pair(attr->name, attr));
}

void _do_id::operator () (jquery_grammar* gmr) const
{
    css::Attr* attr = new css::Attr;
    attr->name = "id";
    attr->value = gmr->_str_id;
    gmr->_str_id.clear();
    
    // add attr.
    if (gmr->_obj_tag == NULL)
    {
        gmr->_obj_tag = gmr->_obj_tag_last = new css::Class;
    }
    
    gmr->_obj_tag_last->attributes.insert(core::make_pair(attr->name, attr));
}

void _do_child::operator () (jquery_grammar* gmr) const
{
    if (gmr->_obj_tag)
        gmr->_child = true;
}

void _do_attr::operator () (jquery_grammar* gmr) const
{
    css::Attr* attr = new css::Attr;
    attr->name = gmr->_str_attr_name;
    attr->value = gmr->_str_attr_value;
    attr->empty = !gmr->_equal;
    
    gmr->_str_attr_name.clear();
    gmr->_str_attr_value.clear();
    gmr->_equal = false;
    
    // add attr.
    if (gmr->_obj_tag == NULL)
    {
        gmr->_obj_tag = gmr->_obj_tag_last = new css::Class;
    }
    
    gmr->_obj_tag_last->attributes.insert(core::make_pair(attr->name, attr));
}

void _do_equal::operator () (jquery_grammar* gmr) const
{
    gmr->_equal = true;
}

void _do_filter::operator()(jquery_grammar* gmr) const
{
    PASS;
}

Element::Element()
: _element(NULL)
{
    
}

Element::Element(void* elem)
: _element(elem)
{
    PASS;
}

Element::~Element()
{

}

void Element::set_element(void* ptr)
{
    _element = ptr;
}

core::string Element::get_name() const
{
    return (char const*)((xmlNodePtr)_element)->name;
}

core::string Element::get_value() const
{
    if (_element == NULL)
        return core::null_string;
    xmlNodePtr elem = (xmlNodePtr)_element;
    xmlChar* content = xmlNodeListGetString(elem->doc,
                                            elem->children,
                                            true);
    if (content == NULL)
        return core::null_string;
    core::string str = (char const*)content;
    xmlFree(content);
    return str;
}

Attribute::Attribute()
{
    PASS;
}

Attribute::Attribute(core::string const& _name, core::string const& _value)
: name(_name),
value(_value)
{
    PASS;
}

Attribute::Attribute(Attribute const& r)
: Element(r._element)
{
    name = r.get_name();
    value = r.get_value();
}

Attribute::Attribute(void* attr)
: Element(attr)
{
    if (attr)
    {
        name = get_name();
        value = get_value();
    }
}

Attribute::~Attribute()
{
    PASS;
}

void Attribute::remove()
{
    xmlRemoveProp((xmlAttrPtr)_element);
    _element = NULL;
}

void Attribute::set_value(core::string const& val)
{
    if (_element == NULL)
        return;
    
    xmlAttrPtr attr = (xmlAttrPtr)_element;
    if (attr->parent == NULL)
        return;
    
    attr = xmlSetProp(attr->parent, (xmlChar const*)name.c_str(), (xmlChar const*)val.c_str());
    if (attr)
        value = val;
}

Node::Node()
: _removed(false)
{
    
}

Node::Node(Node const& r)
: Element(r._element),
_removed(false)
{
    
}

Node::Node(void* elem)
: Element(elem),
_removed(false)
{
    PASS;
}

Node::~Node()
{
    if (_removed)
    {
        if (_element)
        {
            xmlFreeNode((xmlNodePtr)_element);
            _element = NULL;
        }
        _removed = false;
    }
}

void Node::jquery(core::string const& cmd, query_result& result) const
{
    using ::boost::spirit::qi::phrase_parse;
    using ::boost::spirit::qi::space;
    
    jquery_grammar jquery;
    phrase_parse(cmd.c_str(), cmd.c_str() + cmd.length(), jquery, space);    
    
    // find data.
    if (jquery._obj_tag)
        find_tag_r((xmlNodePtr)_element, jquery._obj_tag, jquery._obj_tag, result);
}

void Node::remove()
{
    xmlNodePtr node = (xmlNodePtr)_element;
    xmlUnlinkNode(node);
    _removed = true;
}

void Node::save(core::data& da) const
{
    da.clear();
    
    xmlBufferPtr buf = xmlBufferCreate();    
    
    xmlNodePtr node = (xmlNodePtr)_element;
    htmlNodeDump(buf,
                 node->doc,
                 node);
    
    if (buf->use)
    {
        da = core::data((byte const*)buf->content, buf->use, core::copy);
    }
    
    xmlBufferFree(buf);
}

usize Node::count() const
{
    return xmlChildElementCount((xmlNodePtr)_element);
}

Node Node::parent() const
{
    xmlNodePtr node = (xmlNodePtr)_element;
    return Node(node->parent);
}

Node Node::at(uint idx) const
{
    xmlNodePtr node = xmlFirstElementChild((xmlNodePtr)_element);
    while (idx-- && node)
    {
        node = xmlNextElementSibling(node);
    }
    return Node(node);
}

Node Node::first() const
{
    xmlNodePtr node = xmlFirstElementChild((xmlNodePtr)_element);
    return Node(node);   
}

Node Node::last() const
{
    xmlNodePtr node = xmlLastElementChild((xmlNodePtr)_element);
    return Node(node);  
}

Node Node::next() const
{
    xmlNodePtr node = xmlNextElementSibling((xmlNodePtr)_element);
    return Node(node);  
}

Node Node::next(NodeFilter filter) const
{
    xmlNodePtr node = (xmlNodePtr)_element;
    switch (filter)
    {
        case NF_NOTEMPTY:
        {
            xmlChar* content = NULL;
            do
            {
                node = xmlNextElementSibling(node);                
                content = xmlNodeListGetString(node->doc, node->children, true);
                if (content)
                    xmlFree(content);
            } while (node && node->content);
            
        } break;
    }    
    return Node(node);  
}

Node Node::previous() const
{
    xmlNodePtr node = xmlPreviousElementSibling((xmlNodePtr)_element);
    return Node(node);  
}

bool Node::has_attr(core::string const& str) const
{
    xmlAttrPtr attr = xmlHasProp((xmlNodePtr)_element, (uchar const*)str.c_str());
    return attr != NULL;
}

Attribute Node::attr(core::string const& str) const
{
    xmlAttrPtr attr = xmlHasProp((xmlNodePtr)_element, (uchar const*)str.c_str());
    if (attr == NULL)
        return Attribute(NULL);
    return Attribute(attr);
}

bool Node::has_node(core::string const& str) const
{
    xmlNodePtr each = xmlFirstElementChild((xmlNodePtr)_element);
    xmlChar const* tgt = (xmlChar const*)str.c_str();
    while (each)
    {
        if (xmlStrEqual(each->name, tgt))
            return true;
        each = xmlNextElementSibling(each);
    }
    return false;
}

Node Node::node(core::string const& str) const
{
    xmlNodePtr each = xmlFirstElementChild((xmlNodePtr)_element);
    xmlChar const* tgt = (xmlChar const*)str.c_str();
    while (each)
    {
        if (xmlStrEqual(each->name, tgt))
            return each;
        each = xmlNextElementSibling(each);
    }
    return NULL;
}

Attribute& Node::add(Attribute& attr)
{
    xmlAttrPtr ptr = 
    xmlNewProp((xmlNodePtr)_element, 
               (xmlChar*)attr.name.c_str(), 
               (xmlChar*)attr.value.c_str());   
    attr.set_element(ptr);
    return attr;
}

void Node::add(Attribute const& attr)
{
    xmlAttrPtr ptr = 
    xmlNewProp((xmlNodePtr)_element, 
               (xmlChar*)attr.name.c_str(), 
               (xmlChar*)attr.value.c_str());   
    if (ptr == NULL)
        trace_msg("failed to create attribute");
}

Document::Document()
: _doc(NULL)
{
    
}

Document::Document(core::data const& da)
: _doc(NULL)
{    
    this->parse(da);
}

Document::~Document()
{
    close();
}

bool Document::parse(core::data const& da)
{
    close();
    
    htmlDocPtr doc = htmlReadMemory((char const*)da.bytes(),
                                    da.size(),
                                    NULL,
                                    encoding.size() ? encoding.c_str() : NULL,
                                    HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
    if (doc == NULL)
        return false;
    
    _doc = doc;
    _element = xmlDocGetRootElement(doc);
    
    // get encoding.
    char const* str = (char const*)htmlGetMetaEncoding(doc);
    encoding = str ? str : "UTF-8";
    
    return true;
}

void Document::close()
{
    if (_doc)
    {
        xmlFreeDoc((xmlDocPtr)_doc);
        _doc = NULL;
    }
}

void Document::save(core::data & da) const
{
    da.clear();
    
    xmlChar* buf = NULL;
    int sz = 0;
    htmlDocDumpMemory((xmlDocPtr)_doc, &buf, &sz);
    if (sz)
    {
        da = core::data(buf, sz, core::assign);
        da.set_release(true);
    }
}

void Document::combine(core::data& ret, query_result const& con, core::string const& sepr)
{
    core::data end = core::type_cast<core::data>(sepr);
    for (uint i = 0; i < con.size(); ++i)
    {
        if (i == con.size() - 1)
            end.clear();
        core::data da;
        Node const* node = (Node const*)con[i];
        node->save(da);
        da.append(end);
        ret.append(da);
    }
}

WSI_END_NS
WSI_END_CXX