
# ifndef __HTML_CTLR_8E75C6195CD1425B8D8682AB950213BB_H_INCLUDED
# define __HTML_CTLR_8E75C6195CD1425B8D8682AB950213BB_H_INCLUDED

NNTAPP_BEGIN

class HtmlView
: public ui::View<HtmlView>
{
public:
    
    HtmlView();
    
    void layout_subviews();
    
    ui::TextView text, texted;
    ui::WebView html, htmled;
    
};

class HtmlController
: public ui::Controller<HtmlController, HtmlView>
{
public:
    
    void view_loaded();
    
};

NNTAPP_END

# endif