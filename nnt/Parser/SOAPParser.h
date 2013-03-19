
# ifndef __WSI_PARSER_SOAP_D5792B1291604AF4A30EA0F6D55DD1C5_H_INCLUDED
# define __WSI_PARSER_SOAP_D5792B1291604AF4A30EA0F6D55DD1C5_H_INCLUDED

# ifdef WSI_CXX

# include "XmlParser.h"

WSI_BEGIN_HEADER_CXX WSI_BEGIN_NS(parser)

class SoapDocument
: public XmlDocument
{
public:
    SoapDocument();
    ~SoapDocument();
    
protected:
    virtual void loaded();

};

WSI_END_NS WSI_END_HEADER_CXX

# endif

# endif