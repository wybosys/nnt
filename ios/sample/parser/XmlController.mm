
# include "Foundation+NNT.h"
# include "XmlController.h"
# include "XmlParser.h"
# include "XmlObjParser.h"

NNTAPP_BEGIN

class SaxImpl
: public parser::XmlSaxDocument
{
public:
    
    virtual void loaded()
    {
        core::string str = to_string();
        ::std::cout << str << ::std::endl;
        
        static int xx = 0;
        
        if (xx == 0)
        {
            ++xx;
            core::string xmlstr = "<abc>ABCD";
            parse_string(xmlstr);
        }
        else if (xx == 1)
        {
            ++xx;
            core::string xmlstr = "E</abc>";
            parse_string(xmlstr);            
        }
        
    }
    
};

XmlView::XmlView()
{
    set_background(ui::Color::White());
    
    add_sub(btn_sax);
    add_sub(btn_xml);
    add_sub(btn_obj);
    
    btn_sax.set_text(@"TEST SAX");
    btn_xml.set_text(@"TEST XML");
    btn_obj.set_text(@"TEST OBJECT");
}
 
void XmlView::layout_subviews()
{
    layout::vbox lyt(bounds());
    layout::linear lnr(lyt);
    lnr << (flex)1 << (flex)1 << (flex)1 << (flex)1 << (flex)1;
    lyt << lnr;
    
    btn_sax.set_frame(lyt << lnr);
    btn_xml.set_frame(lyt << lnr);
    btn_obj.set_frame(lyt << lnr);
}

XmlController::XmlController()
{
    
}

void XmlController::view_loaded()
{
    view().btn_sax.connect(kSignalButtonClicked, _action(_class::act_sax), this);
    view().btn_xml.connect(kSignalButtonClicked, _action(_class::act_xml), this);
    view().btn_obj.connect(kSignalButtonClicked, _action(_class::act_obj), this);
}

void XmlController::act_sax()
{
    core::string xmlstr = "<note><to>George</to><from>John</from><heading>Reminder</heading><body>Don't forget the meeting!</body></note>";
    SaxImpl xml;
    xml.parse_string(xmlstr);
}

void XmlController::act_xml()
{
    NSString *xmlstr = nil;
    
    // save    
    {
        XmlParser* xml = [[XmlParser alloc] initWithRootNode:[XmlNode nodeWithName:@"entry"]];
        XmlNode* root = xml.rootNode;
        [root addNamespace:@"" href:@"http://www.w3.org/2005/Atom"];
        [root addNamespace:@"db" href:@"http://www.douban.com/xmlns/"];        
        
        NSArray* arr = [NSArray arrayWithObjects:[NSPair pairWith:@"test" second:@"test"], [NSPair pairWith:@"abc" second:@"abc"],nil];
        
        for (NSPair* each in arr) {
            [root addNodeByName:each.first].value = each.second;
        }
        
        XmlNode* node = [root addNodeByName:@"db:attribute"];
        node.value = @"private";
        [node addAttributeByName:@"name" value:@"privacy"];
        
        node = [root addNodeByName:@"attribute"];
        node.value = @"yes";
        [node addAttributeByName:@"name" value:@"can_reply"];
        
        xmlstr = [xml toString];
        
        [xml release];
        
        trace_msg(xmlstr);
    }
    
    // load
    {
        XmlParser* xml = [[XmlParser alloc] initWithString:xmlstr];
        XmlNode* root = xml.rootNode;
        
        for (XmlNode* each in root.children) {
            NSString* str = [NSString stringWithFormat:@"node's name: %@, value: %@", each.name, each.value];
            trace_msg(str);
        }
        
        [xml release];
    }
}

void XmlController::act_obj()
{
    ns::String str_xml = @"<?xml version=\"1.0\" encoding=\"UTF-8\" ?><upomp application=\"LanchPay.Rsp\"><merchantId>303310048990001</merchantId><merchantOrderId>20121205174437877558</merchantOrderId><merchantOrderTime>20121205174437</merchantOrderTime><merchantOrderAmt>1</merchantOrderAmt><cupsQid></cupsQid><cupsTraceNum></cupsTraceNum><cupsTraceTime></cupsTraceTime><cupsRespCode></cupsRespCode><respCode>0001</respCode><respDesc>POS</respDesc></upomp>";
    ns::Data da_xml(str_xml);
    parser::XmlObject xml;
    ns::Dictionary dict = xml.parse(da_xml);
    trace_obj(dict);
}

NNTAPP_END
