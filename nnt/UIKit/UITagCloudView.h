
# ifndef __WSI_UIKIT_TAGCLOUDVIEW_BBE476876CD840CEB9ADB89673A03823_H_INCLUDED
# define __WSI_UIKIT_TAGCLOUDVIEW_BBE476876CD840CEB9ADB89673A03823_H_INCLUDED

# import "UIView+WSI.h"
# import "UIItemView.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(UITagCloudView);

@interface UITagCloudItem : UIItemView {
    
    @public
    real _al, _bl;
    bool _position;
    
}

@end

@interface UITagCloudView : WSIUIView {
    UIItemsContainer* _items;
    real _offal, _offbl;
    CGPoint _pos;
}

@property (nonatomic, retain) UIItemsContainer* items;
@property (nonatomic, assign) real offal, offbl;

- (UITagCloudItem*)addTag:(UIView*)view;
- (void)clear;
- (void)relayout:(BOOL)animated;

@end

# ifdef WSI_CXX

_CXXVIEW_DECL(UITagCloudView);

# endif

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class ITagCloudView
: public IView
{
    
};

class TagCloud
: public View<TagCloud, _CXXVIEW(UITagCloudView), ITagCloudView>
{
    
    typedef View<TagCloud, _CXXVIEW(UITagCloudView), ITagCloudView> super;
    
public:
    
    TagCloud()
    {
        PASS;
    }
    
    explicit TagCloud(UITagCloudView* r, bool needremove)
    : super((objc_type*)r, needremove)
    {
        PASS;
    }
    
    virtual void layout_subviews()
    {
        PASS;
    }
    
    void set_offset(real al, real bl)
    {
        this->_self.offal = al;
        this->_self.offbl = bl;
    }
    
    real offset_a() const
    {
        return this->_self.offal;
    }
    
    real offset_b() const
    {
        return this->_self.offbl;
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
