
# include <nnt/Foundation+NNt.h>
# include <nnt/Parser/XmlParser.h>
# include <nnt/Parser/SOAPParser.h>
# include <nnt/Core/ObjectDL.h>
# include <nnt/Parser/SoapObject.h>
# include <nnt/Parser/RiffParser.h>
# include <nnt/Parser/JsonObjParser.h>
# include <nnt/Parser/WavParser.h>
# include <nnt/Core/File+NNT.h>
# include <nnt/Core/Resource+NNt.h>

NNT_USINGCXXNAMESPACE;

class Stock
: public soap::Object
{
public:
    
    SOAPDECL_BEGIN_CLASS(Stock)
    SOAPDECL_METHOD_BEGIN(GetStockPrice) SOAPDECL_ARGUMENT(StockName) SOAPDECL_RETURN(Price) SOAPDECL_METHOD_END;        
    SOAPDECL_END_CLASS
    
    SOAPDECL_METHOD(GetStockPrice)
    {
        lang::Field* fid = returns["Price"];
        fid->value = variant_t(66.6);
        return 0;
    }
    
};

void test_soap()
{
    {
        parser::XmlDocument xml;
        core::string str = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?> \
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
    
    {
        core::string str = "<?xml version=\"1.0\"?>\
        <soap:Envelope\
        xmlns:soap=\"http://www.w3.org/2001/12/soap-envelope\"\
        soap:encodingStyle=\"http://www.w3.org/2001/12/soap-encoding\">\
        <soap:Body xmlns:m=\"Stock\">\
        <m:GetStockPrice>\
        <m:StockName>IBM</m:StockName>\
        </m:GetStockPrice>\
        </soap:Body>\
        </soap:Envelope>";
        
        parser::SoapDocument soap;
        soap.parse_string(str);
        trace_msg(soap.to_string());
        
        soap::Invoker invoker(soap);
        invoker.invoke();
        trace_msg(soap.to_string());
    }
}

void test_xml()
{
    {
        parser::XmlDocument xml;
        core::string str = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?> \
        <note><test>xx</test></note> ";
        xml.parse_string(str);
        trace_msg(xml.root()->to_string(false));
    }
    
    {
        parser::XmlDocument xml;
        if (xml.parse_file("test.xml"))
        {
            trace_msg(xml.to_string());
        }
        else
        {
            trace_msg("failed to open xml.");
        }
    }
}

void test_wav()
{
    core::File fd;
    fd.open(core::FileUrl<>("word.wav"), mask_t().on<Io::read>());
    core::data da(fd.length());
    fd.read(da);
    fd.close();
    
    parser::Wav wv;
    wv.parse(da);
    wv.set_channel(2);
    wv.set_bps(16);
    da.clear();
    wv.save(da);
    core::File::SaveAll(core::File::url_type("word-tmp.wav"), da);
}

void test_json()
{
    parser::JsonDocument json;
    core::string str = "{\"root\":[1, \"a\"]}";
    if (json.parse(core::type_cast<core::data>(str)) == false)
    {
        trace_msg("failed to parse json");
        return;
    }
    core::data da;
    if (json.save(da) == false || json.parse(da) == false)
    {
        trace_msg("failed to save json");
        return;
    }
    
}

int main (int argc, const char * argv[])
{
    lang::Namespace* nm = soap::getNamespace();
    nm->classes["Stock"] = Stock::Class();
    
    if (0) test_soap();
    if (0) test_xml();
    if (0) test_wav();
    if (1) test_json();
    
    return 0;
}

