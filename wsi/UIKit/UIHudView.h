
# ifndef __WSI_UIKIT_HUD_132C3285829A4DF0B958EAE8F7DAD310_H_INCLUDED
# define __WSI_UIKIT_HUD_132C3285829A4DF0B958EAE8F7DAD310_H_INCLUDED

# import "UILabel+WSI.h"
# import "UIView+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface UIHudView : WSIUIView {
    WSIUILabel* _label;
    CGMargin _margin;
}

@property (nonatomic, retain) WSIUILabel* label;
@property (nonatomic, copy) NSString* content;
@property (nonatomic, assign) CGMargin margin;

- (void)willOpen;
- (void)didOpen;

- (void)willHide;
- (void)didHiden;

@end

@interface UIHud : WSIObject {
    UIHudView* _hud;
    WSIUIView* _desk;
}

@property (nonatomic, retain) UIHudView* hud;
@property (nonatomic, retain, readonly) WSIUIView* desk;

- (void)open;
- (void)openone:(NSTimeInterval)val;
- (void)close;

@end

@interface UIHudProgressView : UIHudView {
    UIActivityIndicatorView* _activity;
}

@property (nonatomic, readonly) UIActivityIndicatorView* activityView;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_OBJC

_CXXVIEW_DECL(UIHudView);
_CXXVIEW_DECL(UIHudProgressView);

WSI_END_HEADER_OBJC

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

WSI_BEGIN_NS(tpl)

template <typename hudT = _CXXVIEW(UIHudView)>
class HudView
: public _NullView<hudT>
{
public:
    
    HudView()
    {
        
    }
    
    void set_content(ns::String const& cnt)
    {
        this->_self.content = cnt;
    }
    
    ns::String content() const
    {
        return this->_self.content;
    }
    
};

template <typename hudT>
class Hud
: public ns::Object<UIHud>
{
public:
    
    Hud()
    {
        this->_self.hud = _hud;
        _hud.set_removable(false);
    }    
    
    void open()
    {
        [this->_self open];
    }
    
    void open(NSTimeInterval tm)
    {
        [this->_self openone:tm];
    }
    
    void close()
    {
        [this->_self close];
    }
    
    hudT* operator -> ()
    {
        return &_hud;
    }
    
    hudT const* operator -> () const
    {
        return &_hud;
    }
    
protected:
    
    hudT _hud;
    
};

WSI_END_NS

static const NSTimeInterval kHudShow = 1.5f;

class Hud
: public tpl::Hud<tpl::HudView<> >
{
public:
    
    static void Show(ns::String const& str, NSTimeInterval tm = kHudShow)
    {
        Hud obj;
        obj->set_content(str);
        obj.open(tm);
    }
    
};

class HudProgress
: public tpl::Hud< tpl::HudView< _CXXVIEW(UIHudProgressView) > >
{
public:
  
    static void Show();
    static void Hide();
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif