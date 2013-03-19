
# ifndef __WSI_UIKIT_POPOVERCONTROLLER_F0D647AC9A7840AA8D9D3EB3ACE1D73E_H_INCLUDED
# define __WSI_UIKIT_POPOVERCONTROLLER_F0D647AC9A7840AA8D9D3EB3ACE1D73E_H_INCLUDED

# import "UIView+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface WSIUIPopoverController : WSIObject <UIPopoverControllerDelegate>
{
    UIPopoverController* _popover;
    UIPopoverArrowDirection _popoverArrowDirection;
}

@property (nonatomic, retain) UIViewController* contentViewController;
@property (nonatomic, readonly) BOOL popoverVisible;
@property (nonatomic) UIPopoverArrowDirection popoverArrowDirection;
@property (nonatomic) CGSize popoverContentSize;

/* This property allows direction manipulation of the content size of the popover. Changing the property directly is equivalent to animated=YES. The content size is limited to a minimum width of 320 and a maximum width of 600.
 */
- (void)setPopoverContentSize:(CGSize)size animated:(BOOL)animated;

- (void)presentPopoverFromRect:(CGRect)rect inView:(UIView *)view animated:(BOOL)animated;
- (void)presentPopoverFromBarButtonItem:(UIBarButtonItem *)item animated:(BOOL)animated;
- (void)dismissPopoverAnimated:(BOOL)animated;

CXXEXPRESS(@property (nonatomic) ::wsi::RefObject* cxxobj);

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

template <typename contentT,
typename objcT = WSIUIPopoverController
>
class Popover
: public Object<Popover<contentT, objcT>, objcT>
{
public:
    
    typedef contentT content_type;
    
    Popover()
    {
        this->_self = [[objcT alloc] init];
        this->_self.contentViewController = content;
        this->_self.cxxobj = this;
    }
    
    ~Popover()
    {
        this->_self.cxxobj = NULL;
    }
    
    bool is_visible() const
    {
        return this->_self.popoverVisible;
    }
    
    void set_direction(UIPopoverArrowDirection ad)
    {
        this->_self.popoverArrowDirection = ad;
    }
    
    UIPopoverArrowDirection direction() const
    {
        return this->_self.popoverArrowDirection;
    }
    
    void set_content(cg::Size const& sz, bool animated = ui::animate)
    {
        cg::Size tsz;
        tsz.set_height(sz.height());
        if (sz.width() < 320)
            tsz.set_width(320);
        else if (sz.width() > 600)
            tsz.set_width(600);
        else
            tsz.set_width(sz.width());
        
        if (animated)
            this->_self.popoverContentSize = tsz;
        else
            [this->_self setPopoverContentSize:tsz animated:NO];
    }
    
    cg::Size content_size() const
    {
        return this->_self.popoverContentSize;
    }
    
    template <typename viewT>
    void present(cg::Rect const& rc, viewT const& view, bool animated = ui::animate)
    {
        wtl::const_pointer<viewT> ptr(view);
        [this->_self presentPopoverFromRect:rc inView:*ptr animated:animated];
    }
    
    void dismiss(bool animated = ui::animate)
    {
        [this->_self dismissPopoverAnimated:animated];
    }
    
    content_type* operator -> ()
    {
        return &content;
    }
    
    content_type content;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
