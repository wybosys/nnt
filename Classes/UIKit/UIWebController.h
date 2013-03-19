
# ifndef __WSI_UIKIT_WEBCONTROLLER_AED1FE20F10D4F079142B55F5C731311_H_INCLUDED
# define __WSI_UIKIT_WEBCONTROLLER_AED1FE20F10D4F079142B55F5C731311_H_INCLUDED

# import "UIViewController+WSI.h"
# import "UIWebView+WSI.h"
# import "UINavigationController+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface UIWebController : WSIUIViewController {
    NSURL* url;
}

@property (nonatomic, copy) NSURL* url;

- (WSIUIWebView*)webView;

@end

@interface UINaviWebController : WSIUIViewController {
    WSIUINavigationController* webNavigation;
    UIWebController* webController;
}

@property (nonatomic, retain, readonly) WSIUINavigationController* webNavigation;
@property (nonatomic, retain, readonly) UIWebController* webController;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class WebController
: public Controller< WebController, WebView, UIWebController >
{
    typedef Controller< WebController, WebView, UIWebController > super;
    
public:
    
    WebController()
    {
        super::_view.reset(
                           new view_type((UIWebView*)this->_self.view)
                           );
    }
    
    explicit WebController(UIWebController* ctlr)
    : super(ctlr)
    {
        if (ctlr.view != nil)
        {
            super::_view.reset(
                               new view_type((UIWebView*)ctlr.view)
                               );                               
        }
    }
    
    virtual void view_loaded()
    {
        PASS;
    }
    
};

class NaviWebController
: public SimpleController< NaviWebController, UINaviWebController, WSIUIView >
{
public:
    
    NaviWebController()
    : _web(NULL)
    {
        this->_self.navigationController = this->_self.webNavigation;
    }
    
    ~NaviWebController()
    {
        safe_delete(_web);
    }
    
    WebController& web()
    {
        if (_web == NULL)
        {
            _web = new WebController(this->_self.webController);
        }
        return *_web;
    }
    
    WebController const& web() const
    {
        return *_web;
    }
    
protected:
    
    WebController* _web;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif