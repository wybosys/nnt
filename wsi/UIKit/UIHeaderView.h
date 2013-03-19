
# ifndef __WSI_UI_HEADERVIEW_F07055FCC87B40C89CB8ED217F6EF701_H_INCLUDED
# define __WSI_UI_HEADERVIEW_F07055FCC87B40C89CB8ED217F6EF701_H_INCLUDED

# import "UIView+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(UIHeaderView);

@protocol UIHeaderView <NSObject>

- (void)headerBeginAction:(UIHeaderView*)view;
- (void)headerEndAction:(UIHeaderView*)view;
- (void)headerDidAction:(UIHeaderView*)view;
- (void)headerWillAction:(UIHeaderView*)view;
- (void)headerMovedAction:(WSIUIView*)view;

@end

@interface UIHeaderView : WSIUIView <UIHeaderView> {
    
    //! height of header.
    real _height;
    
    //! auto scale. default is true.
    BOOL _autoScale;
    
    //! direction.
    WCGDirection _direction;
}

@property (nonatomic, assign) real height;
@property (nonatomic, assign) BOOL autoScale;
@property (nonatomic, assign) WCGDirection direction;

@end

@interface UIActivityHeaderView : UIHeaderView {        
    WSIUILabel *_normalLabel, *_actionLabel;
}

@property (nonatomic, readonly) WSIUILabel *normalLabel, *actionLabel;

@end

//! emit while header toggle.
WSI_EXTERN signal_t kSignalAction;

_CXXVIEW_DECL(UIHeaderView);
_CXXVIEW_DECL(UIActivityHeaderView);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "UIView+WSI.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

WSI_BEGIN_NS(tpl)

template <typename implT, typename headerT = _CXXVIEW(UIHeaderView)>
class HeaderView
: public View<implT, headerT>
{
public:
    
    HeaderView()
    {
        PASS;
    }
    
    virtual ~HeaderView()
    {
        PASS;
    }
    
    void set_height(real val)
    {
        this->_self.height = val;
    }
    
    real height() const
    {
        return this->_self.height;
    }
    
    void layout_subviews()
    {
        PASS;
    }
    
    void set_autoscale(bool val)
    {
        this->_self.autoScale = val;
    }
    
    bool is_autoscale() const
    {
        return this->_self.autoScale;
    }
    
};

WSI_END_NS

class HeaderView
: public tpl::HeaderView<HeaderView>
{
public:
    
    HeaderView()
    {
        PASS;
    }
    
};

class ActivityHeaderView
: public tpl::HeaderView<ActivityHeaderView, _CXXVIEW(UIActivityHeaderView)>
{
public:
    
    ActivityHeaderView()
    {
        PASS;
    }
    
    Label& normal_text()
    {
        if (_normalLabel.get() == NULL)
            _normalLabel.reset(new Label(this->_self.normalLabel));
        return *_normalLabel;
    }
    
    Label& action_text()
    {
        if (_actionLabel.get() == NULL)
            _actionLabel.reset(new Label(this->_self.actionLabel));
        return *_actionLabel;
    }
    
protected:
    
    core::auto_ptr<Label> _normalLabel, _actionLabel;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif