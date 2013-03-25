
# include "Core.h"
# include "XmlParser.h"
# include "../Security/Security+NNT.h"

# ifdef USE_LIBXERCESC
#   include "../../contrib/libxml/LIBXERCESC+NNT.h"
# endif

# ifdef USE_LIBXML
#   include "../../contrib/libxml/LIBXML+NNT.h"
# endif

NNT_BEGIN_CXX 

signal_t kSignalLoaded = "::nnt::loaded";

NNT_BEGIN_NS(parser)

XmlNode::XmlNode()
: first(NULL), last(NULL), prev(NULL), next(NULL), parent(NULL)
{
    PASS;
}

XmlNode::XmlNode(core::string const& nm, core::string const& val)
: first(NULL), last(NULL), prev(NULL), next(NULL), parent(NULL)
{
    this->name = nm;
    this->value = val;
}

XmlNode::~XmlNode()
{
    this->clear();
}

void XmlNode::clear()
{
    core::clear_destroy(children);
    core::clear_destroy(attributes);
    first = last = prev = next = NULL;
}

void XmlNode::clear_children()
{
    core::clear_destroy(children);
    first = last = prev = next = NULL;
}

void XmlNode::clear_attributes()
{
    core::clear_destroy(attributes);
}

XmlAttribute const* XmlNode::attribute(const core::string & name) const
{
    attributes_type::const_iterator found = attributes.find(name);
    if (found == attributes.end())
        return NULL;
    return found->second;
}

XmlAttribute* XmlNode::attribute(const core::string & name)
{
    attributes_type::iterator found = attributes.find(name);
    if (found == attributes.end())
        return NULL;
    return found->second;
}

XmlNode const* XmlNode::node(const core::string & name) const
{
    nodes_type::const_iterator found = children.find(name);
    if (found == children.end())
        return NULL;
    return found->second;
}

XmlNode* XmlNode::node(const core::string & name)
{
    nodes_type::iterator found = children.find(name);
    if (found == children.end())
        return NULL;
    return found->second;
}

core::list<XmlNode const*> XmlNode::nodes(core::string const& name) const
{
	typedef core::pair<nodes_type::const_iterator, nodes_type::const_iterator> range_type;
	range_type range = children.equal_range(name);
	core::list<XmlNode const*> ret;
	for (; range.first != range.second; ++range.first)
	{
		ret.push_back(range.first->second);
	}
	return ret;
}

core::list<XmlNode*> XmlNode::nodes(core::string const& name)
{
	typedef core::pair<nodes_type::iterator, nodes_type::iterator> range_type;
	range_type range = children.equal_range(name);
	core::list<XmlNode*> ret;
	for (; range.first != range.second; ++range.first)
	{
		ret.push_back(range.first->second);
	}
	return ret;
}

XmlNode* XmlNode::add(::nnt::parser::XmlNode *node)
{
    children.insert(core::make_pair(node->name, node));
    node->grab();
    
    if (!first && !last)
        first = last = node;
    else 
    {
        if (last)
            last->next = node;
        
        node->prev = last;
        last = node;
    }
    
    node->parent = this;
    
    return node;
}

XmlAttribute* XmlNode::add(::nnt::parser::XmlAttribute *attr)
{
    attributes.insert(core::make_pair(attr->name, attr));
    attr->grab();
    return attr;
}

XmlNode* XmlNode::add_node(const core::string & name, core::string const& value)
{
    XmlNode* node = new XmlNode(name, value);
    add(node);    
    node->drop();
    return node;
}

XmlAttribute* XmlNode::add_attr(const core::string & name, core::string const& value)
{
    XmlAttribute* attr = new XmlAttribute(name, value);
    add(attr);
    attr->drop();
    return attr;
}

XmlAttribute* XmlNode::ava_attribute(core::string const& name)
{
    XmlAttribute* attr = attribute(name);
    if (attr)
        return attr;
    return add_attr(name);
}

void XmlNode::remove_attribute(core::string const& name)
{
    attributes_type::iterator found = attributes.find(name);
    if (found != attributes.end())
        attributes.erase(found);
}

core::string XmlNode::full_name() const
{
    if (prefix.empty())
        return name;
    return prefix + ":" + name;
}

XmlAttribute::XmlAttribute()
{
    
}

XmlAttribute::XmlAttribute(core::string const& name, core::string const& value)
: XmlNode(name, value)
{
    
}

XmlAttribute::~XmlAttribute()
{
    
}

XmlDocumentType::XmlDocumentType()
{
    
}

XmlDocumentType::~XmlDocumentType()
{
    
}

XmlDocument::XmlDocument()
# ifdef USE_LIBXERCESC
: _env(NULL)
# endif
{
    _root = new XmlNode;
	_root->name = "ROOT";
    
# ifdef USE_LIBXERCESC
    this->_env = new xml::Environment;
# endif
}

XmlDocument::~XmlDocument()
{
    _root->drop();
    
# ifdef USE_LIBXERCESC
    delete (xml::Environment*)this->_env;
# endif

}

NNTDECL_SIGNALS_BEGIN(XmlDocument, cxx::Object<>)
NNT_SIGNAL(kSignalLoaded)
NNTDECL_SIGNALS_END

# ifdef USE_LIBXERCESC

static void load_dom_tree(XmlNode* tag, ::xercesc::DOMNode const* des)
{
    XmlNode* prev = tag->last;
    
    // load attributes.
    ::xercesc::DOMNamedNodeMap const* xeattrs = des->getAttributes();
    for (uint idx = 0; idx < xeattrs->getLength(); ++idx)
    {
        ::xercesc::DOMNode const* xeattr = xeattrs->item(idx);
        XmlAttribute* attr = new XmlAttribute;
        xml::set(attr->name, xeattr->getNodeName());
        xml::set(attr->value, xeattr->getNodeValue());
        
        tag->attributes.insert(core::make_pair(attr->name, attr));
    }
    
    // load prefix.
    if (des->getPrefix())
    {
        xml::set(tag->prefix, des->getPrefix());
        
        // remove for node.
        tag->name = tag->name.substr(tag->prefix.size() + 1);
    }
    
    // load namespace.
    if (des->getNamespaceURI())
        xml::set(tag->ns, des->getNamespaceURI());
    
    // load children.
    for (::xercesc::DOMNode* each = des->getFirstChild();
         each != NULL;
         each = each->getNextSibling())
    {
        uint type = each->getNodeType();
        
        if (type == ::xercesc::DOMNode::ELEMENT_NODE)
        {
            XmlNode* node = new XmlNode;
            xml::set(node->name, each->getNodeName());
            
            load_dom_tree(node, each);
            
            tag->children.insert(core::make_pair(node->name, node));
            node->parent = tag;
            
            if (prev == NULL)
            {
                if (tag->first == NULL)
                    tag->first = node;
                prev = node;
            }
            else
            {
                prev->next = node;
                node->prev = prev;
                prev = node;
            }
            
            tag->last = node;
        }
        else if (type == ::xercesc::DOMNode::TEXT_NODE)
        {
            xml::set(tag->value, each->getTextContent());
        }

    }
}

static void load_dom_document(XmlDocument* tgt, ::xercesc::DOMDocument const* doc)
{
    ::xercesc::DOMElement const* root = doc->getDocumentElement();
    if (root == NULL)
    {
        tgt->root()->name.clear();
        return;
    }
        
    // load root name.
    xml::set(tgt->root()->name, root->getNodeName());
    
    // load root value.
    if (root->getNodeValue())
        xml::set(tgt->root()->value, root->getNodeValue());
    
    // load childrend.
    load_dom_tree(tgt->root(), root);
}

class XmlDomParser
	: public ::xercesc::XercesDOMParser
{
	typedef ::xercesc::XercesDOMParser super;

protected:

	class XmlDomError
		: public ::xercesc::ErrorHandler
	{
	public:

		virtual void error(::xercesc::SAXParseException const& e)
		{
			PASS;
		}

		virtual void fatalError(::xercesc::SAXParseException const& e)
		{
			PASS;
		}

		virtual void warning(::xercesc::SAXParseException const& e)
		{
			PASS;
		}

		virtual void resetErrors() 
		{
			PASS;
		}

	};

public:

	XmlDomParser()
	{
		this->setDoNamespaces(true);
		this->setExitOnFirstFatalError(false);
		this->setErrorHandler(&_hdl_err);
	}

	virtual ~XmlDomParser()
	{
		PASS;
	}

protected:

	XmlDomError _hdl_err;

};

bool XmlDocument::parse_string(const core::string & str)
{
    XmlDomParser* parser = new XmlDomParser();
    
    core::string dig = md5::digest(core::type_cast<core::data>(str));
    ::xercesc::MemBufInputSource source((XMLByte const*)str.c_str(), str.length(), dig.c_str());
    
    try 
    {
        parser->parse(source);
    } 
    catch (...) 
    {
        safe_delete(parser);
        return false;
    }
    
    ::xercesc::DOMDocument* doc = parser->getDocument();
    if (doc == NULL)
    {
        safe_delete(parser);
        return false;
    }
    
    load_dom_document(this, doc);
    this->loaded();
    
    safe_delete(parser);    
    return true;
}

bool XmlDocument::parse_data(core::data const& da)
{
    XmlDomParser* parser = new XmlDomParser();
    
    core::string dig = md5::digest(da);
    ::xercesc::MemBufInputSource source((XMLByte const*)da.bytes(), da.length(), dig.c_str());
    
    try
    {
        parser->parse(source);
    }
    catch (...)
    {
        safe_delete(parser);
        return false;
    }
    
    ::xercesc::DOMDocument* doc = parser->getDocument();
    if (doc == NULL)
    {
        safe_delete(parser);
        return false;
    }
    
    load_dom_document(this, doc);
    this->loaded();
    
    safe_delete(parser);
    return true;
}

bool XmlNode::load(core::data const& da)
{
    XmlDomParser* parser = new XmlDomParser();
    
    core::string dig = md5::digest(da);
    ::xercesc::MemBufInputSource source((XMLByte const*)da.bytes(), da.length(), dig.c_str());
    
    try
    {
        parser->parse(source);
    }
    catch (...)
    {
        safe_delete(parser);
        return false;
    }
    
    ::xercesc::DOMDocument* doc = parser->getDocument();
    if (doc == NULL)
    {
        safe_delete(parser);
        return false;
    }
    
    load_dom_tree(this, doc);
    
    safe_delete(parser);
    return true;
}

bool XmlDocument::parse_file(const core::string & file)
{
    XmlDomParser* parser = new XmlDomParser();
    
    ::xercesc::LocalFileInputSource source(xml::tostr(file).c_str());
    
    try 
    {
        parser->parse(source);
    } 
    catch (...) 
    {
        safe_delete(parser);
        return false;
    }
    
    ::xercesc::DOMDocument* doc = parser->getDocument();
    if (doc == NULL)
    {
        safe_delete(parser);
        return false;
    }

    load_dom_document(this, parser->getDocument());
    this->loaded();
    
    safe_delete(parser);    
    return true;   
}

static void save_dom_tree(::xercesc::DOMDocument* doc, ::xercesc::DOMElement* tgt, XmlNode const* node)
{
    XMLCh* value = ::xercesc::XMLString::transcode(node->value.c_str());
    tgt->setTextContent(value);
    ::xercesc::XMLString::release(&value);
    
    // save attributes.
    for (XmlNode::attributes_type::const_iterator each = node->attributes.begin();
         each != node->attributes.end();
         ++each)
    {
        XmlAttribute const* attr = each->second;
        XMLCh* name = ::xercesc::XMLString::transcode(attr->name.c_str());
        XMLCh* val = ::xercesc::XMLString::transcode(attr->value.c_str());
        
        tgt->setAttribute(name, val);
        
        ::xercesc::XMLString::release(&name);
        ::xercesc::XMLString::release(&val);
    }

	XMLCh const* ns = tgt->getNamespaceURI();
    
    // save children.
	XmlNode const* child = node->first;
	while (child)
    {
        XMLCh* name = ::xercesc::XMLString::transcode(child->name.c_str());
                
        ::xercesc::DOMElement* elem = NULL;
        
        try 
        {
            if (child->ns.empty())
            {
                elem = doc->createElementNS(ns, name);
            }
            else
            {
                XMLCh* ns = ::xercesc::XMLString::transcode(child->ns.c_str());
                elem = doc->createElementNS(ns, name);
                ::xercesc::XMLString::release(&ns);
            }
        }
        catch (...)
        {
            trace_msg("exception: failed serial a xml node.");
        }
        
        ::xercesc::XMLString::release(&name);
        
        if (elem)
        {
            // append child.
            save_dom_tree(doc, elem, child);
        
            // add.
            tgt->appendChild(elem);
        }

		// next.
		child = child->next;
    }
}

# endif

# ifdef USE_LIBXML

static void load_dom_tree(XmlNode* tag, xmlNodePtr des)
{
    XmlNode* prev = tag->last;
    
    // load attributes.
    for (xmlAttrPtr each = des->properties;
         each != NULL;
         each = each->next)
    {
        XmlAttribute* attr = new XmlAttribute;
        attr->name = (char const*)each->name;
        attr->value = (char const*)xmlNodeGetContent(each->children);
        
        tag->attributes.insert(core::make_pair(attr->name, attr));
    }
    
    // load namespace.
    if (des->ns)
        tag->ns = (char const*)des->ns->href;
    
    // load children.
    for (xmlNodePtr each = xmlFirstElementChild(des);
         each != NULL;
         each = xmlNextElementSibling(each))
    {
        xmlElementType const type = each->type;
        
        if (type == XML_ELEMENT_NODE)
        {
            XmlNode* node = new XmlNode;
            
            // set name.
            node->name = (char const*)each->name;
            
            // set value.
            if (xmlNodeIsText(each->children))
                node->value = (char const*)xmlNodeGetContent(each->children);
            
            // load child.
            load_dom_tree(node, each);
            
            // add node.
            tag->children.insert(core::make_pair(node->name, node));
            node->parent = tag;
            
            // link.
            if (prev == NULL)
            {
                if (tag->first == NULL)
                    tag->first = node;
                prev = node;
            }
            else
            {
                prev->next = node;
                node->prev = prev;
                prev = node;
            }
            
            tag->last = node;
        }        
    }
}

static void load_dom_document(XmlDocument* tgt, xmlDocPtr doc)
{
    xmlNodePtr root = xmlDocGetRootElement(doc);    
    if (root == NULL)
    {
        tgt->root()->name.clear();
        return;
    }
    
    // load root name.
    tgt->root()->name = (char const*)root->name;
    
    // load root value.
    if (xmlNodeIsText(root->children))
        tgt->root()->value = (char const*)xmlNodeGetContent(root->children);
    
    load_dom_tree(tgt->root(), root);
}

static void load_dom_node(XmlNode* tgt, xmlDocPtr doc)
{
    xmlNodePtr root = xmlDocGetRootElement(doc);
    if (root == NULL)
    {
        tgt->name.clear();
        return;
    }
    
    // load root name.
    tgt->name = (char const*)root->name;
    
    // load root value.
    if (xmlNodeIsText(root->children))
        tgt->value = (char const*)xmlNodeGetContent(root->children);
    
    load_dom_tree(tgt, root);
}

bool XmlDocument::parse_string(core::string const& str)
{
    xmlDocPtr doc = xmlReadMemory(str.c_str(),
                                  str.length(),
                                  NULL,
                                  encoding.size() ? encoding.c_str() : NULL,
                                  XML_PARSE_DOM | XML_PARSE_NOERROR | XML_PARSE_NOWARNING);
    if (doc == NULL)
        return false;    

    // load nodes.
    load_dom_document(this, doc);
    this->loaded();
    
    xmlFreeDoc(doc);
    return true;
}

bool XmlDocument::parse_data(core::data const& da)
{
    xmlDocPtr doc = xmlReadMemory((char const*)da.bytes(),
                                  da.length(),
                                  NULL,
                                  encoding.size() ? encoding.c_str() : NULL,
                                  XML_PARSE_DOM | XML_PARSE_NOERROR | XML_PARSE_NOWARNING);
    if (doc == NULL)
        return false;    
    
    // load nodes.
    load_dom_document(this, doc);
    this->loaded();
    
    xmlFreeDoc(doc);
    return true;
}

bool XmlDocument::parse_file(const core::string & file)
{
    FILE* fd = fopen(file.c_str(), "rb");
    if (fd == NULL)
        return false;
    
    xmlDocPtr doc = xmlReadFd(fileno(fd),
                              NULL,
                              encoding.size() ? encoding.c_str() : NULL,
                              XML_PARSE_DOM | XML_PARSE_NOERROR | XML_PARSE_NOWARNING);

    // load nodes.
    load_dom_document(this, doc);
    this->loaded();
    
    xmlFreeDoc(doc);
    fclose(fd);
    return true;   
}

bool XmlNode::load(core::data const& da)
{
    xmlDocPtr doc = xmlReadMemory((char const*)da.bytes(),
                                  da.length(),
                                  NULL,
                                  "UTF-8",
                                  XML_PARSE_DOM | XML_PARSE_NOERROR | XML_PARSE_NOWARNING);
    if (doc == NULL)
        return false;
    
    // load nodes.
    load_dom_node(this, doc);
    
    xmlFreeDoc(doc);

    return true;
}

static void save_dom_tree(xmlDocPtr doc, xmlNodePtr tgt, XmlNode const* node)
{
    // set content.
    xmlNodeSetContent(tgt, (xmlChar*)node->value.c_str());
    
    // set namespace.
    if (!node->ns.empty())
    {
        xmlNsPtr ns = xmlNewNs(tgt,
                               (xmlChar*)node->ns.c_str(),
                               TRIEXP(node->prefix.empty(), NULL, (xmlChar*)node->prefix.c_str()));
        xmlSetNs(tgt, ns);
    }
    
    // set attribute.
    for (XmlNode::attributes_type::const_iterator each = node->attributes.begin();
         each != node->attributes.end();
         ++each)
    {
        XmlAttribute const* attr = each->second;
        
        xmlNewProp(tgt, 
                   (xmlChar*)attr->name.c_str(), 
                   (xmlChar*)attr->value.c_str());                    
    }
    
    // set children.
    XmlNode* each = node->first;
    while (each)
    {
        xmlNodePtr elem = xmlNewNode(tgt->ns,
                                     (xmlChar*)each->name.c_str());
                
        // append child.
        save_dom_tree(doc, elem, each);
                
        xmlAddChild(tgt, elem);
        
        each = each->next;
    }
}

# endif

void XmlDocument::loaded()
{
    this->emit(kSignalLoaded);
}

# ifdef USE_LIBXERCESC

class XmlNodeSerializationFilter
: public ::xercesc::DOMLSSerializerFilter
{
public:
    XmlNodeSerializationFilter()
    : root(NULL)
    {
        PASS;
    }
    
    virtual FilterAction acceptNode(const xercesc::DOMNode* node) const
    {
        if (node == root)
            return FILTER_SKIP;
        
        FilterAction ret = FILTER_SKIP;
        ::xercesc::DOMNode::NodeType const type = node->getNodeType();
        switch (type)
        {
            default: break;
            case ::xercesc::DOMNode::ELEMENT_NODE:
            case ::xercesc::DOMNode::ATTRIBUTE_NODE:
            {
                ret = FILTER_ACCEPT;
            } break;
            case ::xercesc::DOMNode::TEXT_NODE: 
            {                
                XMLCh const* val = node->getNodeValue();
                int len = ::xercesc::XMLString::stringLen(val);                
                ret = len ? FILTER_ACCEPT : FILTER_SKIP;
            } break;
        }
        
        return ret;
    }
    
    virtual ShowType getWhatToShow() const
    {
        return SHOW_ELEMENT | SHOW_ATTRIBUTE | SHOW_TEXT;
    }
    
    ::xercesc::DOMNode* root;
};

core::string XmlNode::to_string(bool rootvisible) const
{
    ::xercesc::DOMImplementation *dom = NULL;
    
    if (dom == NULL)
    {
        XMLCh tempStr[100];
        ::xercesc::XMLString::transcode("LS", tempStr, 99);
        dom = ::xercesc::DOMImplementationRegistry::getDOMImplementation(tempStr);
    }
    
    // create.    
    XMLCh *name = ::xercesc::XMLString::transcode(this->name.c_str());        
    ::xercesc::DOMDocument* xedoc = NULL;
    try
    {
        XMLCh* namespaceUri = NULL;
        if (!this->ns.empty())
            namespaceUri = ::xercesc::XMLString::transcode(this->ns.c_str());
        
        try
        {
            xedoc = dom->createDocument(namespaceUri, name, NULL);
        }
        catch (...)
        {
            if (namespaceUri)
                ::xercesc::XMLString::release(&namespaceUri);
            throw;
        }
        
        if (namespaceUri)
            ::xercesc::XMLString::release(&namespaceUri);
    }
    catch (::xercesc::DOMException const& ex)
    {
        core::string msg;
        xml::set(msg, ex.getMessage());
        trace_msg(msg);
        
        ::xercesc::XMLString::release(&name);
        return "";
    }
    ::xercesc::XMLString::release(&name);
        
    save_dom_tree(xedoc, xedoc->getDocumentElement(), this);
    
    // get string.
    ::xercesc::DOMLSSerializer* writer = ((::xercesc::DOMImplementationLS*)dom)->createLSSerializer();
    if (writer->getDomConfig()->canSetParameter(::xercesc::XMLUni::fgDOMWRTDiscardDefaultContent, true))
        writer->getDomConfig()->setParameter(::xercesc::XMLUni::fgDOMWRTDiscardDefaultContent, true);
    
    XmlNodeSerializationFilter* filter = new XmlNodeSerializationFilter();
    if (!rootvisible)
        filter->root = xedoc->getDocumentElement();
    writer->setFilter(filter);

    ::xercesc::MemBufFormatTarget* format = new ::xercesc::MemBufFormatTarget;
    ::xercesc::DOMLSOutput* output = ((::xercesc::DOMImplementationLS*)dom)->createLSOutput();
    output->setByteStream(format);
    
    try
    {
        writer->write(xedoc->getDocumentElement(), output);
    }
    catch (...)
    {
        trace_msg("failed to write node!");
    }
    
    core::data data(format->getRawBuffer(), format->getLen());
    core::string str = core::type_cast<core::string>(data);
    
    output->release();
    xedoc->release();
    writer->release();
    safe_delete(filter);
    safe_delete(format);
    
    return str;
}

bool XmlNode::save(core::data &da) const
{
    ::xercesc::DOMImplementation *dom = NULL;
    
    if (dom == NULL)
    {
        XMLCh tempStr[100];
        ::xercesc::XMLString::transcode("LS", tempStr, 99);
        dom = ::xercesc::DOMImplementationRegistry::getDOMImplementation(tempStr);
    }
    
    // create.
    XMLCh *name = ::xercesc::XMLString::transcode(this->name.c_str());
    ::xercesc::DOMDocument* xedoc = NULL;
    try
    {
        XMLCh* namespaceUri = NULL;
        if (!this->ns.empty())
            namespaceUri = ::xercesc::XMLString::transcode(this->ns.c_str());
        
        try
        {
            xedoc = dom->createDocument(namespaceUri, name, NULL);
        }
        catch (...)
        {
            if (namespaceUri)
                ::xercesc::XMLString::release(&namespaceUri);
            throw;
        }
        
        if (namespaceUri)
            ::xercesc::XMLString::release(&namespaceUri);
    }
    catch (::xercesc::DOMException const& ex)
    {
        core::string msg;
        xml::set(msg, ex.getMessage());
        trace_msg(msg);
        
        ::xercesc::XMLString::release(&name);
        return false;
    }
    ::xercesc::XMLString::release(&name);
    
    save_dom_tree(xedoc, xedoc->getDocumentElement(), this);
    
    // get string.
    ::xercesc::DOMLSSerializer* writer = ((::xercesc::DOMImplementationLS*)dom)->createLSSerializer();
    if (writer->getDomConfig()->canSetParameter(::xercesc::XMLUni::fgDOMWRTDiscardDefaultContent, true))
        writer->getDomConfig()->setParameter(::xercesc::XMLUni::fgDOMWRTDiscardDefaultContent, true);
    
    XmlNodeSerializationFilter* filter = new XmlNodeSerializationFilter();
    writer->setFilter(filter);
    
    ::xercesc::MemBufFormatTarget* format = new ::xercesc::MemBufFormatTarget;
    ::xercesc::DOMLSOutput* output = ((::xercesc::DOMImplementationLS*)dom)->createLSOutput();
    output->setByteStream(format);
    
    try
    {
        writer->write(xedoc->getDocumentElement(), output);
    }
    catch (...)
    {
        trace_msg("failed to write node!");
    }
    
    da = core::data(format->getRawBuffer(), format->getLen(), core::copy);
    
    output->release();
    xedoc->release();
    writer->release();
    safe_delete(filter);
    safe_delete(format);
    
    return true;
}

core::string XmlDocument::to_string() const
{    
    ::xercesc::DOMImplementation *dom = NULL;
    
    if (dom == NULL)
    {
        XMLCh tempStr[100];
        ::xercesc::XMLString::transcode("LS", tempStr, 99);
        dom = ::xercesc::DOMImplementationRegistry::getDOMImplementation(tempStr);
    }
    
    // create.    
    XMLCh *name = ::xercesc::XMLString::transcode(_root->name.c_str());        
    ::xercesc::DOMDocument* xedoc = NULL;
    try
    {
        XMLCh* namespaceUri = NULL;
        if (!_root->ns.empty())
            namespaceUri = ::xercesc::XMLString::transcode(_root->ns.c_str());
        
        try 
        {
            xedoc = dom->createDocument(namespaceUri, name, NULL);
        }
        catch (...)
        {
            if (namespaceUri)
                ::xercesc::XMLString::release(&namespaceUri);
            throw;
        }
        
        if (namespaceUri)
            ::xercesc::XMLString::release(&namespaceUri);
    }
    catch (::xercesc::DOMException const& ex)
    {
        core::string msg;
        xml::set(msg, ex.getMessage());
        trace_msg(msg);
        
        ::xercesc::XMLString::release(&name);
        return "";
    }
    ::xercesc::XMLString::release(&name);

    save_dom_tree(xedoc, xedoc->getDocumentElement(), this->root());
    
    // get string.
    ::xercesc::DOMLSSerializer* writer = ((::xercesc::DOMImplementationLS*)dom)->createLSSerializer();
    ::xercesc::MemBufFormatTarget* format = new ::xercesc::MemBufFormatTarget;
    ::xercesc::DOMLSOutput* output = ((::xercesc::DOMImplementationLS*)dom)->createLSOutput();
    output->setByteStream(format);
    
    try
    {
        writer->write(xedoc, output);
    }
    catch (...)
    {
        trace_msg("failed to write node!");
    }
    
    core::data data(format->getRawBuffer(), format->getLen());
    core::string str = core::type_cast<core::string>(data);
    
    output->release();
    xedoc->release();
    writer->release();
    safe_delete(format);
    
    return str;
}

bool XmlDocument::save(core::data & da) const
{
    ::xercesc::DOMImplementation *dom = NULL;
    
    if (dom == NULL)
    {
        XMLCh tempStr[100];
        ::xercesc::XMLString::transcode("LS", tempStr, 99);
        dom = ::xercesc::DOMImplementationRegistry::getDOMImplementation(tempStr);
    }
    
    // create.
    XMLCh *name = ::xercesc::XMLString::transcode(_root->full_name().c_str());
    ::xercesc::DOMDocument* xedoc = NULL;
    try
    {
        XMLCh* namespaceUri = NULL;
        if (!_root->ns.empty())
            namespaceUri = ::xercesc::XMLString::transcode(_root->ns.c_str());
        
        try
        {
            xedoc = dom->createDocument(namespaceUri, name, NULL);
        }
        catch (...)
        {
            if (namespaceUri)
                ::xercesc::XMLString::release(&namespaceUri);
            throw;
        }
        
        if (namespaceUri)
            ::xercesc::XMLString::release(&namespaceUri);
    }
    catch (::xercesc::DOMException const& ex)
    {
        core::string msg;
        xml::set(msg, ex.getMessage());
        trace_msg(msg);
        
        ::xercesc::XMLString::release(&name);
        return false;
    }
    ::xercesc::XMLString::release(&name);
    
    save_dom_tree(xedoc, xedoc->getDocumentElement(), this->root());
    
    // get string.
    ::xercesc::DOMLSSerializer* writer = ((::xercesc::DOMImplementationLS*)dom)->createLSSerializer();
    ::xercesc::MemBufFormatTarget* format = new ::xercesc::MemBufFormatTarget;
    ::xercesc::DOMLSOutput* output = ((::xercesc::DOMImplementationLS*)dom)->createLSOutput();
    output->setByteStream(format);
    
    try
    {
        writer->write(xedoc, output);
    }
    catch (...)
    {
        trace_msg("failed to write node!");
    }
    
    da = core::data(format->getRawBuffer(), format->getLen(), core::copy);
    
    output->release();
    xedoc->release();
    writer->release();
    safe_delete(format);
    
    return true;
}

# endif

# ifdef USE_LIBXML

core::string XmlNode::to_string(bool rootvisible) const
{
    xmlDocPtr doc = xmlNewDoc((xmlChar*)"1.0");    
    xmlNodePtr root = xmlNewNode(NULL, 
                                 (xmlChar*)this->name.c_str());
    xmlDocSetRootElement(doc, root);
    
    // safe.
    save_dom_tree(doc, root, this);
    
    // dump.
    xmlBufferPtr buf = xmlBufferCreate();        
    xmlNodeDump(buf,
                doc, 
                root,
                0,
                0
                );
    
    core::data da;
    if (buf->use)
    {
        da = core::data((byte const*)buf->content, buf->use, core::copy);
    }    
    xmlBufferFree(buf);
    xmlFreeDoc(doc);
    
    core::string str = core::type_cast<core::string>(da);
    return str;
}

bool XmlNode::save(core::data & da) const
{
    xmlDocPtr doc = xmlNewDoc((xmlChar*)"1.0"); 
    xmlNodePtr root = xmlNewNode(NULL, 
                                 (xmlChar*)this->name.c_str());
    xmlDocSetRootElement(doc, root);
    
    // safe.
    save_dom_tree(doc, root, this);
    
    // dump.
    xmlBufferPtr buf = xmlBufferCreate();        
    int ret = xmlNodeDump(buf,
                          doc, 
                          root,
                          0,
                          0
                          );
    
    if (buf->use)
    {
        da = core::data((byte const*)buf->content, buf->use, core::copy);
    }    
    xmlBufferFree(buf);
    xmlFreeDoc(doc);
    
    return ret != -1;
}

core::string XmlDocument::to_string() const
{    
    xmlDocPtr doc = xmlNewDoc((xmlChar*)"1.0");    
    xmlNodePtr root = xmlNewNode(NULL, 
                                 (xmlChar*)this->root()->name.c_str());
    xmlDocSetRootElement(doc, root);
    
    // safe.
    save_dom_tree(doc, root, this->root());
    
    // dump
    xmlChar* buf;
    int size;
    xmlDocDumpMemory(doc,
                     &buf,
                     &size);
    
    core::data da;
    if (size)
    {
        da.set_length(size);
        da.set_bytes(buf);
        da.set_release(true);
    }    
    xmlFreeDoc(doc);
    
    core::string str = core::type_cast<core::string>(da);
    return str;
}

bool XmlDocument::save(core::data & da) const
{    
    xmlDocPtr doc = xmlNewDoc((xmlChar*)"1.0");   
    xmlNodePtr root = xmlNewNode(NULL, 
                                 (xmlChar*)this->root()->name.c_str());
    xmlDocSetRootElement(doc, root);
    
    // safe.
    save_dom_tree(doc, root, this->root());
    
    // dump
    xmlChar* buf;
    int size;
    
    xmlDocDumpFormatMemory(doc,
                           &buf,
                           &size,
                           0);
    
    da.clear();
    if (size)
    {
        da.set_length(size - 1); // for skip \r at end.
        da.set_bytes(buf);
        da.set_release(true);
    }
    xmlFreeDoc(doc);

    return da.length() != 0;
}

# endif

XmlNode const* XmlDocument::root() const
{
    return _root;
}

XmlNode* XmlDocument::root()
{
    return _root;
}

core::string XmlDocument::Escape(core::string const& str)
{
    core::string ret = str;
    core::replace_of(ret, "\"", "&quot;");
    core::replace_of(ret, "'", "&apos;");
    core::replace_of(ret, "&", "&amp;");
    core::replace_of(ret, "<", "&lt;");
    core::replace_of(ret, ">", "&gt");
    return ret;
}

# ifdef USE_LIBXML

void sax_start_document(XmlSaxDocument* doc)
{
    doc->sck_nodes.push(doc->root());
}

void sax_end_document(XmlSaxDocument* doc)
{
    doc->loaded();
}

void sax_begin_element(XmlSaxDocument* doc, xmlChar const* name, xmlChar const* atts)
{
    XmlNode* node = new XmlNode((char const*)name);
    doc->sck_nodes.top()->add(node);
    node->drop();
    
    // set to current.
    doc->sck_nodes.push(node);
}

void sax_end_element(XmlSaxDocument* doc, xmlChar const* name)
{
    doc->sck_nodes.pop();
}

void sax_begin_element_ns(XmlSaxDocument* doc,
                          const xmlChar *localname,
                          const xmlChar *prefix,
                          const xmlChar *URI,
                          int nb_namespaces,
                          const xmlChar **namespaces,
                          int nb_attributes,
                          int nb_defaulted,
                          const xmlChar **attributes)
{
    
}

void sax_end_element_ns(XmlSaxDocument* doc,
                        const xmlChar *localname,
                        const xmlChar *prefix,
                        const xmlChar *URI)
{
    
}

void sax_get_entity(XmlSaxDocument* doc, const xmlChar *name)
{
    
}

void sax_reference(XmlSaxDocument* doc, const xmlChar *name)
{
    
}

void sax_characters(XmlSaxDocument* doc, const xmlChar *name, int len)
{
    doc->sck_nodes.top()->value = core::string((char const*)name, len);
}

# endif

XmlSaxDocument::XmlSaxDocument()
{
# ifdef USE_LIBXML
    _hdl = malloc(sizeof(xmlSAXHandler));
    
    // set hook function.
    xmlSAXHandler& hdl = *(xmlSAXHandler*)_hdl;
    hdl.startDocument = (startDocumentSAXFunc)sax_start_document;
    hdl.endDocument = (endDocumentSAXFunc)sax_end_document;
    hdl.startElement = (startElementSAXFunc)sax_begin_element;
    hdl.endElement = (endElementSAXFunc)sax_end_element;
    hdl.startElementNs = (startElementNsSAX2Func)sax_begin_element_ns;
    hdl.endElementNs = (endElementNsSAX2Func)sax_end_element_ns;
    hdl.getEntity = (getEntitySAXFunc)sax_get_entity;
    hdl.reference = (referenceSAXFunc)sax_reference;
    hdl.characters = (charactersSAXFunc)sax_characters;
    
# endif
}

XmlSaxDocument::~XmlSaxDocument()
{
# ifdef USE_LIBXML
    free(_hdl);
# endif
}

# ifdef USE_LIBXML

bool XmlSaxDocument::parse_string(core::string const& str)
{
    int sta = xmlSAXUserParseMemory((xmlSAXHandlerPtr)_hdl,
                                    this,
                                    str.c_str(),
                                    str.length());
    return sta == 0;
}

bool XmlSaxDocument::parse_data(core::data const& da)
{
    int sta = xmlSAXUserParseMemory((xmlSAXHandlerPtr)_hdl,
                                    this,
                                    (char const*)da.bytes(),
                                    da.length());
    return sta == 0;
}

bool XmlSaxDocument::parse_file(const core::string & file)
{
    int sta = xmlSAXUserParseFile((xmlSAXHandlerPtr)_hdl,
                                  this,
                                  file.c_str());
    return sta == 0;
}

# endif

NNT_END_NS 
NNT_END_CXX
