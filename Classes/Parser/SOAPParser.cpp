
# include "Core.h"
# include "SOAPParser.h"
# include "../Core/ObjectDL.h"
# include "../Cross/SoapObject.h"

WSI_BEGIN_CXX 

WSI_BEGIN_NS(soap)

lang::Namespace* getNamespace()
{
    return lang::addNamespace("soap");
}

WSI_END_NS

WSI_BEGIN_NS(parser)

SoapDocument::SoapDocument()
{
    PASS;
}

SoapDocument::~SoapDocument()
{
    PASS;
}

void SoapDocument::loaded()
{
    // process namespace.
    XmlAttribute* namespaceUri = this->root()->attribute("xmlns:soap");
    if (namespaceUri)
        this->root()->ns = namespaceUri->value;
    else
        this->root()->ns = "http://www.w3.org/2001/12/soap-envelope";
    
    // super.
    XmlDocument::loaded();
}

WSI_END_NS 
WSI_END_CXX
