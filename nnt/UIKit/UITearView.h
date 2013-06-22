
# ifndef __NNT_UIKIT_UITEARVIEW_3A2524AD54FF496289910F19384D14E5_H_INCLUDED
# define __NNT_UIKIT_UITEARVIEW_3A2524AD54FF496289910F19384D14E5_H_INCLUDED

# import "UIView+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(CGShadow);
NNTDECL_PRIVATE_HEAD(UITearView);
NNTDECL_EXTERN_CLASS(NgFill);

@interface UITearView : NNTUIView {
    
    //! view of target.
    UIView *targetView;
    
    //! view of source.
    UIView *sourceView;
    
    //! position.
    NSInteger location;
    
    //! spacing.
    NSUInteger spacing;
    
    //! shadow.
    CGShadow *edgeShadow;
    
    //! edge color.
    UIColor *edgeColor;
    
    //! edge length.
    NSUInteger edgeWidth;
    
    //! fill.
    NgFill *fill;
    
    //! main rect.
    CGRect contentRect;
    
    //! padding. default is zero.
    CGPadding padding;
    
    //! arrow.
    real lenArrow;
    
    //! arrow positon.
    real locationArrow;
    
    //! auto close. default is YES.
    BOOL autoClose;
    
    //! content view.
    UIView *contentView;
    
    //! drak color.
    UIColor *darkColor;
    
    //! use desktop. default is YES.
    BOOL desktopMode;
    
    NNTDECL_PRIVATE(UITearView);
}

@property (nonatomic, assign) UIView *targetView, *sourceView;
@property (nonatomic, assign) NSInteger location;
@property (nonatomic, assign) NSUInteger spacing;
@property (nonatomic, retain) CGShadow *edgeShadow;
@property (nonatomic, retain) UIColor *edgeColor;
@property (nonatomic, assign) NSUInteger edgeWidth;
@property (nonatomic, retain) NgFill *fill;
@property (nonatomic, assign) real lenArrow, locationArrow;
@property (nonatomic, readonly) CGRect contentRect;
@property (nonatomic, assign) BOOL autoClose;
@property (nonatomic, assign) UIView *contentView;
@property (nonatomic, retain) UIColor *darkColor;
@property (nonatomic, assign) BOOL desktopMode;
@property (nonatomic, assign) CGPadding padding;

//! init.
- (id)initWith:(NSInteger)pos spacing:(NSUInteger)spacing;

//! open.
- (void)open;
- (void)open:(BOOL)animated;

//! close.
- (void)close;
- (void)close:(BOOL)animated;

@end

NNT_EXTERN signal_t kSignalViewClose;

@interface UITearViewHov : UITearView {
    
}

@end

@interface UITearViewVec: UITearView {
    
}

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

template <typename tearT>
class TearView
: public View<TearView<tearT>, tearT>
{
    typedef View<TearView<tearT>, tearT> super;
    typedef TearView<tearT> self_type;
    
public:
    
    TearView(tearT* r)
    : super(r)
    {
        PASS;
    }
    
    TearView(self_type const& r)
    : super(r._self)
    {
        PASS;
    }
    
    void open(bool animated = true)
    {
        [this->_self open:animated];
    }
    
    void close(bool animated = true)
    {
        [this->_self close:animated];
    }
    
    virtual void layout_subviews()
    {
        PASS;
    }
    
};

class HovTearView
: public TearView<UITearViewHov>
{
    typedef TearView<UITearViewHov> super;
    
public:
    
    HovTearView(UITearViewHov* r)
    : super(r)
    {
        PASS;
    }
    
    HovTearView(HovTearView const& r)
    : super(r._self)
    {
        PASS;
    }
    
};

class VecTearView
: public TearView<UITearViewVec>
{
    typedef TearView<UITearViewVec> super;
    
public:
    
    VecTearView(UITearViewVec* r)
    : super(r)
    {
        PASS;
    }
    
    VecTearView(VecTearView const& r)
    : super(r._self)
    {
        PASS;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif