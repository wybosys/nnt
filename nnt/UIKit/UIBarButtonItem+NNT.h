
# ifndef __NNT_UIKIT_UIBARBUTTONITEM_04ADC336745941B3A2E60651B7E777BC_H_INCLUDED
# define __NNT_UIKIT_UIBARBUTTONITEM_04ADC336745941B3A2E60651B7E777BC_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NNTUILabel);

@interface NNTUIBarButtonItem : UIBarButtonItem {
    NNTOBJECT_DECL;
    
    UIColor *backgroundColor;
    NgFill* backgroundFill;
    
}

@property (nonatomic, retain) UIColor *backgroundColor;
@property (nonatomic, retain) NgFill* backgroundFill;

//! will enable button clicked signal.
- (id)initWithTitle:(NSString *)title style:(UIBarButtonItemStyle)style;
- (id)initWithBarButtonSystemItem:(UIBarButtonSystemItem)systemItem;
- (id)initWithTitle:(NSString *)title style:(UIBarButtonItemStyle)style target:(id)target action:(SEL)action;
- (id)initWithImage:(UIImage *)image style:(UIBarButtonItemStyle)style;

//! static.
+ (id)itemWithCustomView:(id)view;

NNTOBJECT_PROP;

@end

@interface NNTUIBarLabelItem : NNTUIBarButtonItem {
    NNTUILabel *label;
}

- (id)initWithTitle:(NSString*)title;

@property (nonatomic, readonly) NNTUILabel *label;

@end

NNT_EXTERN signal_t kSignalButtonClicked;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class BarButtonItem
: public ui::Object<BarButtonItem, NNTUIBarButtonItem>
{
    typedef ui::Object<BarButtonItem, NNTUIBarButtonItem> super;
    
public:
    
    BarButtonItem(ns::String const& title, UIBarButtonItemStyle style)
    {
        this->_self = [[NNTUIBarButtonItem alloc] initWithTitle:title style:style];
    }
    
    BarButtonItem(UIBarButtonSystemItem style)
    {
        this->_self = [[NNTUIBarButtonItem alloc] initWithBarButtonSystemItem:style];
    }
    
    BarButtonItem(Image const& img, UIBarButtonItemStyle style)
    {
        this->_self = [[NNTUIBarButtonItem alloc] initWithImage:img style:style];
    }
    
    BarButtonItem(BarButtonItem const& r)
    : super(r._self)
    {
        PASS;
    }
    
    BarButtonItem(UIView* view)
    : super(nil)
    {
        this->_self = [[NNTUIBarButtonItem alloc] initWithCustomView:view];
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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif