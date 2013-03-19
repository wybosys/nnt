
# ifndef __NNT_UIKIT_ACTIONSHEET_3D38E9B5B0C34E08981D6240854902DD_H_INCLUDED
# define __NNT_UIKIT_ACTIONSHEET_3D38E9B5B0C34E08981D6240854902DD_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NNTUIActionSheet : UIActionSheet <UIActionSheetDelegate> {
    NSMutableDictionary* _items;
    
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

- (id)initWithTitle:(NSString*)title;
- (id)addItem:(NSString*)title;
- (id)setCancel:(NSString*)title;

@end

NNT_EXTERN signal_t kSignalCancelButtonClicked;
NNT_EXTERN signal_t kSignalDestructButtonClicked;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class ActionSheet
: public Object<ActionSheet, NNTUIActionSheet>
{
public:
    
    ActionSheet()
    {
        this->_self = [[NNTUIActionSheet alloc] initWithTitle:@""];
    }
    
    explicit ActionSheet(ns::String const& title)
    {
        this->_self = [[NNTUIActionSheet alloc] initWithTitle:title];
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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif