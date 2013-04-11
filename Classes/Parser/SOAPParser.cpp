
# include "Core.h"
# include "SOAPParser.h"
# include "../Core/ObjectDL.h"
# include "SoapObject.h"

NNT_BEGIN_CXX 

NNT_BEGIN_NS(soap)

lang::Namespace* getNamespace()
{
    return lang::addNamespace("soap");
}

NNT_END_NS

NNT_BEGIN_NS(parser)

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

NNT_END_NS 
NNT_END_CXX
