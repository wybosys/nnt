
# ifndef __XML_CTLR_FA064EBCD78445CABD49CCD3615654EA_H_INCLUDED
# define __XML_CTLR_FA064EBCD78445CABD49CCD3615654EA_H_INCLUDED

NNTAPP_BEGIN

class XmlView
: public ui::View<XmlView>
{
public:
    XmlView();
    void layout_subviews();
    ui::BevelButton btn_sax, btn_xml, btn_obj;
};

class XmlController
: public ui::Controller<XmlController, XmlView>
{
public:
    XmlController();
    void view_loaded();
    
    void act_sax();
    void act_xml();
    void act_obj();
    
};

NNTAPP_END

# endif
