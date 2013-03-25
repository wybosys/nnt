
# ifndef __XERCESC_NNT_621C44AD041E42088893D630D4BC8851_H_INCLUDED
# define __XERCESC_NNT_621C44AD041E42088893D630D4BC8851_H_INCLUDED

# include <xercesc/dom/DOM.hpp>
# include <xercesc/dom/DOMException.hpp>
# include <xercesc/dom/DOMErrorHandler.hpp>
# include <xercesc/sax/SAXException.hpp>
# include <xercesc/sax/ErrorHandler.hpp>
# include <xercesc/sax/SAXParseException.hpp>
# include <xercesc/parsers/XercesDOMParser.hpp>
# include <xercesc/framework/MemBufInputSource.hpp>
# include <xercesc/framework/MemBufFormatTarget.hpp>
# include <xercesc/framework/LocalFileInputSource.hpp>
# include <xercesc/framework/LocalFileFormatTarget.hpp>

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(xml)

class Environment
{
public:

	Environment();
	~Environment();

};

class string
{
public:
    
    string(XMLCh* chs)
    : _chs(chs)
    {
        PASS;
    }
    
    ~string()
    {
        ::xercesc::XMLString::release(&_chs);   
    }
    
    XMLCh const* c_str() const
    {
        return _chs;
    }
    
protected:
    
    XMLCh* _chs;
    
};

static core::string& set(core::string& str, XMLCh const* xmlch)
{
    char* raw = ::xercesc::XMLString::transcode(xmlch);
    if (!raw)
    {
        str = "";
        return str;
    }
    str = raw;
    ::xercesc::XMLString::release(&raw);
    return str;
}

static string tostr(char const* str)
{
    XMLCh* raw = ::xercesc::XMLString::transcode(str);
    return string(raw);
}

static string tostr(core::string const& str)
{
    XMLCh* raw = ::xercesc::XMLString::transcode(str.c_str());
    return string(raw);
}

NNT_END_NS
NNT_END_HEADER_CXX

# endif