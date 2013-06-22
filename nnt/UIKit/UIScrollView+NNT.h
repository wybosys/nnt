
# ifndef __NNT_UIKIT_UISCROLLVIEW_C0F51BEB4A1545EBA2A36FAB2A22CFCF_H_INCLUDED
# define __NNT_UIKIT_UISCROLLVIEW_C0F51BEB4A1545EBA2A36FAB2A22CFCF_H_INCLUDED

# import "UIHeaderView.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NgFill);

@interface UIScrollView (NNT)

- (CGRect)rectForLayout;
- (CGRect)visibleFrame;

@end

NNTDECL_CATEGORY(UIScrollView, NNT);

@interface NNTUIScrollView : UIScrollView <UIScrollViewDelegate> {
    NNTOBJECT_DECL;
    
    //! background fill.
    NgFill *_backgroundFill;
        
    //! send global event. default is YES.
    BOOL _sendGlobalEvent;
    
    //! header view. default is nil.
    UIHeaderView* _topHeaderView;
    UIHeaderView* _bottomHeaderView;
    
    //! content view.
    UIView* _contentView2;
    
    @private
    int __waiting_touch;
    
}

NNTOBJECT_PROP;

@property (nonatomic, assign) BOOL sendGlobalEvent;
@property (nonatomic, readonly) CGRect contentFrame;
@property (nonatomic, retain) NgFill *backgroundFill;
@property (nonatomic, retain) UIHeaderView *topHeaderView, *bottomHeaderView;
@property (nonatomic, retain) UIView* contentView;

@end

NNT_EXTERN signal_t kSignalBeginScroll;
NNT_EXTERN signal_t kSignalEndScroll;

_CXXVIEW_DECL(NNTUIScrollView);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "UIControl+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

template <typename implT,
typename scrollT = _CXXVIEW(NNTUIScrollView)
>
class ScrollView
: public View<implT, scrollT>
{
    typedef View<implT, scrollT> super;
    
public:
    
    ScrollView()
    {
        PASS;
    }
    
    explicit ScrollView(scrollT* scroll,
                        bool needremove = false)
    : super(scroll, needremove)
    {
        PASS;
    }
    
    ~ScrollView()
    {
        PASS;
    }
    
    CGRect content_frame() const
    {
        return this->_self.contentFrame;
    }
    
    CGPoint content_offset() const
    {
        return this->_self.contentOffset;
    }
    
    void set_content_size(cg::Rect const& rc)
    {
        this->_self.contentSize = rc.size();
    }
    
    void set_content_size(cg::Size const& rc)
    {
        this->_self.contentSize = rc;
    }
    
    void set_content_offset(cg::Point const& pt)
    {
        this->_self.contentOffset = pt;
    }
    
    void set_content_offset(cg::Rect const& rc)
    {
        this->_self.contentOffset = rc.pos();
    }
    
    template <typename viewT>
    void set_topheader(viewT const& view)
    {
        ntl::const_pointer<viewT> ptr(view);
        this->_self.topHeaderView = *ptr;
    }
    
    template <typename viewT>
    void set_bottomheader(viewT const& view)
    {
        ntl::const_pointer<viewT> ptr(view);
        this->_self.bottomHeaderView = *ptr;
    }
    
    virtual void layout_subviews()
    {
        PASS;
    }

    void set_directional_lock(bool val)
    {
        this->_self.directionalLockEnabled = val;
    }
    
    bool directional_lock() const
    {
        return this->_self.directionalLockEnabled;
    }
    
    void set_bounces(bool val)
    {
        this->_self.bounces = val;
    }
    
    bool bounces() const
    {
        return this->_self.bounces;
    }
    
    void set_bounces_vertical(bool val)
    {
        this->_self.alwaysBounceVertical = val;
    }
    
    bool bounces_vertical() const
    {
        return this->_self.alwaysBounceVertical;
    }
    
    void set_bounces_horizontal(bool val)
    {
        this->_self.alwaysBounceHorizontal = val;
    }
    
    bool bounces_horizontal() const
    {
        return this->_self.alwaysBounceHorizontal;
    }
    
    void set_pagingable(bool val)
    {
        this->_self.pagingEnabled = val;
    }
    
    bool pagingable() const
    {
        return this->_self.pagingEnabled;
    }
    
    void set_scrollable(bool val)
    {
        this->_self.scrollEnabled = val;
    }
    
    bool scrollable() const
    {
        return this->_self.scrollEnabled;
    }

    void set_horizontal_indicator_visible(bool val)
    {
        this->_self.showsHorizontalScrollIndicator = val;
    }
    
    bool horizontal_indicator_visible() const
    {
        return this->_self.showsHorizontalScrollIndicator;
    }
    
    void set_vertical_indicator_visible(bool val)
    {
        this->_self.showsVerticalScrollIndicator = val;
    }
    
    bool vertical_indicator_visible() const
    {
        return this->_self.showsVerticalScrollIndicator;
    }

    void set_indicator(UIScrollViewIndicatorStyle svis)
    {
        this->_self.indicatorStyle = svis;
    }
    
    UIScrollViewIndicatorStyle indicator_style() const
    {
        return this->_self.indicatorStyle;
    }
    
    void set_deceleration_rate(real val)
    {
        this->_self.decelerationRate = val;
    }
    
    real deceleration_rate() const
    {
        return this->_self.decelerationRate;
    }

    void delays_content_touches(bool val)
    {
        this->_self.delaysContentTouches = val;
    }
    
    bool delays_content_touches() const
    {
        return this->_self.delaysContentTouches;
    }
    
    void cancel_content_touches(bool val)
    {
        this->_self.canCancelContentTouches = val;
    }
    
    bool cancel_content_touches() const
    {
        return this->_self.canCancelContentTouches;
    }

};

class Scroll
: public ScrollView<Scroll>
{
public:
    
    Scroll()
    {
        PASS;
    }
    
};

template <typename contentT>
class Scrollable
: public Scroll
{
public:
    
    typedef contentT content_type;
    
    Scrollable()
    {
        this->_self.contentView = _content;
    }
    
    operator content_type& ()
    {
        return _content;
    }
    
    content_type* operator -> ()
    {
        return &_content;
    }
    
protected:
    
    content_type _content;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
