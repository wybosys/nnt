
# ifndef __NNT_UIKIT_WEBCONTROLLER_AED1FE20F10D4F079142B55F5C731311_H_INCLUDED
# define __NNT_UIKIT_WEBCONTROLLER_AED1FE20F10D4F079142B55F5C731311_H_INCLUDED

# import "UIViewController+NNT.h"
# import "UIWebView+NNT.h"
# import "UINavigationController+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface UIWebController : NNTUIViewController {
    NSURL* url;
}

@property (nonatomic, copy) NSURL* url;

- (NNTUIWebView*)webView;

@end

@interface UINaviWebController : NNTUIViewController {
    NNTUINavigationController* webNavigation;
    UIWebController* webController;
}

@property (nonatomic, retain, readonly) NNTUINavigationController* webNavigation;
@property (nonatomic, retain, readonly) UIWebController* webController;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

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
: public SimpleController< NaviWebController, UINaviWebController, NNTUIView >
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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif