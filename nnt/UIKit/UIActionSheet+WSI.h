
# ifndef __WSI_UIKIT_ACTIONSHEET_3D38E9B5B0C34E08981D6240854902DD_H_INCLUDED
# define __WSI_UIKIT_ACTIONSHEET_3D38E9B5B0C34E08981D6240854902DD_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface WSIUIActionSheet : UIActionSheet <UIActionSheetDelegate> {
    NSMutableDictionary* _items;
    
    WSIOBJECT_DECL;
}

WSIOBJECT_PROP;

- (id)initWithTitle:(NSString*)title;
- (id)addItem:(NSString*)title;
- (id)setCancel:(NSString*)title;

@end

WSI_EXTERN signal_t kSignalCancelButtonClicked;
WSI_EXTERN signal_t kSignalDestructButtonClicked;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class ActionSheet
: public Object<ActionSheet, WSIUIActionSheet>
{
public:
    
    ActionSheet()
    {
        this->_self = [[WSIUIActionSheet alloc] initWithTitle:@""];
    }
    
    explicit ActionSheet(ns::String const& title)
    {
        this->_self = [[WSIUIActionSheet alloc] initWithTitle:title];
    }
        
    void set_title(ns::String const& title)
    {
        this->_self.title = title;
    }
    
    ns::String title() const
    {
        return this->_self.title;
    }
    
    ns::Object<> add(ns::String const& title)
    {
        return [this->_self addItem:title];
    }
    
    ns::Object<> cancel(ns::String const& title)
    {
        return [this->_self setCancel:title];
    }
    
    void show(UIView* view)
    {
        [this->_self showInView:view.window];
    }
    
    void show(CGRect const& rc, UIView* view, bool animated = true)
    {
        [this->_self showFromRect:rc inView:view.window animated:animated];
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif