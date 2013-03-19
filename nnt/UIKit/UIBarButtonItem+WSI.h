
# ifndef __WSI_UIKIT_UIBARBUTTONITEM_04ADC336745941B3A2E60651B7E777BC_H_INCLUDED
# define __WSI_UIKIT_UIBARBUTTONITEM_04ADC336745941B3A2E60651B7E777BC_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WSIUILabel);

@interface WSIUIBarButtonItem : UIBarButtonItem {
    WSIOBJECT_DECL;
    
    UIColor *backgroundColor;
    WCGFill* backgroundFill;
    
}

@property (nonatomic, retain) UIColor *backgroundColor;
@property (nonatomic, retain) WCGFill* backgroundFill;

//! will enable button clicked signal.
- (id)initWithTitle:(NSString *)title style:(UIBarButtonItemStyle)style;
- (id)initWithBarButtonSystemItem:(UIBarButtonSystemItem)systemItem;
- (id)initWithTitle:(NSString *)title style:(UIBarButtonItemStyle)style target:(id)target action:(SEL)action;
- (id)initWithImage:(UIImage *)image style:(UIBarButtonItemStyle)style;

//! static.
+ (id)itemWithCustomView:(id)view;

WSIOBJECT_PROP;

@end

@interface WSIUIBarLabelItem : WSIUIBarButtonItem {
    WSIUILabel *label;
}

- (id)initWithTitle:(NSString*)title;

@property (nonatomic, readonly) WSIUILabel *label;

@end

WSI_EXTERN signal_t kSignalButtonClicked;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class BarButtonItem
: public ui::Object<BarButtonItem, WSIUIBarButtonItem>
{
    typedef ui::Object<BarButtonItem, WSIUIBarButtonItem> super;
    
public:
    
    BarButtonItem(ns::String const& title, UIBarButtonItemStyle style)
    {
        this->_self = [[WSIUIBarButtonItem alloc] initWithTitle:title style:style];
    }
    
    BarButtonItem(UIBarButtonSystemItem style)
    {
        this->_self = [[WSIUIBarButtonItem alloc] initWithBarButtonSystemItem:style];
    }
    
    BarButtonItem(Image const& img, UIBarButtonItemStyle style)
    {
        this->_self = [[WSIUIBarButtonItem alloc] initWithImage:img style:style];
    }
    
    BarButtonItem(BarButtonItem const& r)
    : super(r._self)
    {
        PASS;
    }
    
    BarButtonItem(UIView* view)
    : super(nil)
    {
        this->_self = [[WSIUIBarButtonItem alloc] initWithCustomView:view];
    }
    
    void set_width(real width)
    {
        this->_self.width = width;
    }
    
    real width() const
    {
        return this->_self.width;
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif