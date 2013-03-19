
# ifndef __NNT_PARSER_SOAP_D5792B1291604AF4A30EA0F6D55DD1C5_H_INCLUDED
# define __NNT_PARSER_SOAP_D5792B1291604AF4A30EA0F6D55DD1C5_H_INCLUDED

# ifdef NNT_CXX

# include "XmlParser.h"

NNT_BEGIN_HEADER_CXX NNT_BEGIN_NS(parser)

class SoapDocument
: public XmlDocument
{
public:
    SoapDocument();
    ~SoapDocument();
    
protected:
    virtual void loaded();

};

NNT_END_NS NNT_END_HEADER_CXX

# endif

# endif