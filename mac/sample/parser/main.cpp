
# include <wsi/WSIFoundation.h>

# include <wsi/Parser/XmlParser.h>
# include <wsi/Parser/SOAPParser.h>
# include <wsi/Core/ObjectDL.h>
# include <wsi/Cross/SoapObject.h>
# include <wsi/Core/WSIResource.h>

class Stock
: public ::wsi::soap::Object
{
public:
    
    SOAPDECL_BEGIN_CLASS(Stock)
    SOAPDECL_METHOD_BEGIN(GetStockPrice) SOAPDECL_ARGUMENT(StockName) SOAPDECL_RETURN(Price) SOAPDECL_METHOD_END;        
    SOAPDECL_END_CLASS
    
    SOAPDECL_METHOD(GetStockPrice)
    {
        ::wsi::lang::Field* fid = returns["Price"];
        fid->value = ::wsi::variant_t(66.6);
        return 0;
    }
    
};

int main (int argc, const char * argv[])
{
    ::wsi::lang::Namespace* nm = ::wsi::soap::getNamespace();
    nm->classes["Stock"] = Stock::Class();
    
    if (1)
    {
        wsi::parser::XmlDocument xml;
        wsi::core::string str = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?> \
        <!--  Copyright w3school.com.cn --> \
        <note> \
        <to time=\"2012-3-1\">George</to> \
        <from>John</from> \
        <heading>Reminder</heading> \
        <body>Don't forget the meeting!</body> \
        </note> ";
        xml.parse_string(str);
        trace_msg(xml.to_string());
    }
    
    if (1)
    {
        wsi::parser::XmlDocument xml;
        wsi::core::string str = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?> \
        <note><test>xx</test></note> ";
        xml.parse_string(str);
        trace_msg(xml.root()->to_string(false));
    }
    
    if (1)
    {
        wsi::parser::XmlDocument xml;
        if (xml.parse_file("test.xml")) 
        {
            trace_msg(xml.to_string());
        }
        else
        {
            trace_msg("failed to open xml.");
        }
    }
    
    if (1)
    {
        wsi::core::string str = "<?xml version=\"1.0\"?>\
        <soap:Envelope\
        xmlns:soap=\"http://www.w3.org/2001/12/soap-envelope\"\
        soap:encodingStyle=\"http://www.w3.org/2001/12/soap-encoding\">\
        <soap:Body xmlns:m=\"Stock\">\
        <m:GetStockPrice>\
        <m:StockName>IBM</m:StockName>\
        </m:GetStockPrice>\
        </soap:Body>\
        </soap:Envelope>";
        
        wsi::parser::SoapDocument soap;
        soap.parse_string(str);
        trace_msg(soap.to_string());
        
        wsi::soap::Invoker invoker(soap);        
        invoker.invoke();
        trace_msg(soap.to_string());        
    }
    
    return 0;
}

