
# ifndef __NNT_OBJC_UIVIEW_778B906B1AE14545A1D541B07D61324D_H_INCLUDED
# define __NNT_OBJC_UIVIEW_778B906B1AE14545A1D541B07D61324D_H_INCLUDED

# import <QuartzCore/QuartzCore.h>

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(UIImage);
NNTDECL_EXTERN_CLASS(UITearView);
NNTDECL_EXTERN_CLASS(NNTUIView);
NNTDECL_EXTERN_CLASS(WCGFill);
NNTDECL_EXTERN_CLASS(NNTUIViewController);
NNTDECL_EXTERN_CLASS(UIDrawerView);

@protocol NNTUIViewLock <NSObject>

//! lock position.
- (void)lockPosition;

//! unlock position.
- (void)unlockPosition;

@end

@protocol NNTUIViewInSight <NSObject>

- (void)viewInSight;
- (void)viewOutSight;

@end

NNTDECL_EXTERN_CLASS(UITheme);

//! protocol for theme.
@protocol UIViewTheme < NSObject >

//! invoked while theme changed.
- (void)viewTheme:(UIView*)view changeTheme:(UITheme*)theme;

@end

@interface UIView (NNT)

- (id)initWithZero;

//! covert to image
- (UIImage*)convertToImage;
- (UIImage*)convertToImage:(UIColor*)backgroundColor;

//! move to
- (void)moveTo:(CGPoint)pos;
- (void)moveToSize:(CGSize)sz;
- (void)moveRightTopTo:(CGPoint)pos;
- (void)moveOffsetX:(CGFloat)offx OffsetY:(CGFloat)offy;

//! move to and center with point
- (void)moveToCenter:(CGPoint)pos;

//! move to and center with origin center.
- (void)moveToRectCenter:(CGRect)rect;

//! remove all subviews.
- (void)removeAllSubviews;

//! tear view.
- (UITearView*)tearHov:(NSInteger)pos spacing:(NSUInteger)height;
- (UITearView*)tearVec:(NSInteger)pos spacing:(NSUInteger)width;

//! get boundingbox.
- (CGRect)boundingbox;

//! freeze.
- (void)freeze;

//! thaw.
- (void)thaw;

//! center of client.
- (CGPoint)clientCenter;

//! get the rect for layout.
- (CGRect)rectForLayout;

//! get the bounds for layout.
- (CGRect)boundsForLayout;

//! convert.
- (CGRect)convertRectToLogic:(CGRect)rc;
- (CGPoint)convertPointToLogic:(CGPoint)pt;
- (CGSize)convertSizeToLogic:(CGSize)sz;

- (CGRect)convertRectToDevice:(CGRect)rc;
- (CGPoint)convertPointToDevice:(CGPoint)pt;
- (CGSize)convertSizeToDevice:(CGSize)sz;

//! set logic frame, will auto transform to device.
- (void)setLogicFrame:(CGTransformRect)frame;
- (CGTransformRect)logicFrame;

- (void)setLogicBounds:(CGTransformRect)bounds;
- (CGTransformRect)logicBounds;

//! get owner window.
- (UIWindow*)window;

//! get root view.
- (UIView*)root;

@end

//! convert uiview to image
UIImage* UIConvertViewToImage(UIView* view);
UIImage* UIConvertViewToImageWithOptions(UIView* view, UIColor *backgroundColor);

//! touches event.
void UIViewEmitGlobalEvent(NSString* signal, UIView* view, NSSet* touches, UIEvent* event);

@interface UIViewGlobalEvent : NSObject

+ (NNTUIView*)getViewFrom:(NNTEventObj*)event;
+ (NSSet*)getTouchesFrom:(NNTEventObj*)event;
+ (UIEvent*)getEventFrom:(NNTEventObj*)event;

@end

@interface NNTUIView : UIView <NNTUIViewLock> {
    NNTOBJECT_DECL;
    
    //! background image.
    WCGFill *_backgroundFill;
    
    //! orientation.
    UIInterfaceOrientation _orientation;
        
    //! send global event. default is YES.
    BOOL _sendGlobalEvent;
    
    //! sub controllers.
    NSArray* _subControllers;
    
    //! if need assistant view. default is NO.
    BOOL _needAssistantView;
    
    //! identity for view.
    id _identity;
    
    //! is painting.
    BOOL _isPainting;
        
    @private
    int __lockposition;    
    UIView *__assistant_view;
    id _lock;
}

@property (nonatomic, assign) BOOL sendGlobalEvent;
@property (retain) WCGFill *backgroundFill;
@property (nonatomic, assign) UIInterfaceOrientation orientation;
@property (readonly) NSArray* subControllers;
@property (nonatomic, readonly) BOOL isPainting;

NNTOBJECT_PROP;

//! if need assistant view. default is NO.
@property (nonatomic, assign) BOOL needAssistantView;

//! should use assistant view.
@property (nonatomic, assign) BOOL shouldAssistantView;

//! identity for view.
@property (nonatomic, retain) id identity;

//! func for assitant view.
@property (nonatomic, assign) id (*funcAssistantView)(NNTUIView*);

# ifdef NNT_BLOCKS

@property (nonatomic, assign) id (^blockAssistantView)(NNTUIView*);

# endif

//! init.
- (id)initWithFrame:(CGRect)frame;
+ (id)view:(CGRect)frame;

//! get assistant view.
- (id)assistantView;
- (void)setAssistantView:(id)view;

//! orientation.
- (BOOL)isLandscape;
- (BOOL)isPortrait;

//! lock
- (void)lock;
- (void)unlock;
- (BOOL)tryLock;

//! scale to background image.
- (void)scaleToBackgroundImage;

//! update layout. it is a null implementation.
- (void)updateLayout:(CGRect)rect;

//! draw push state.
- (void)drawHighlight:(CGRect)rect ctx:(CGContextRef)ctx;

//! paint view.
- (void)paintRect:(CGRect)rect context:(CGContextRef)ctx;

//! get & set extent.
- (CGRect)extent;
- (void)setExtent:(CGRect)rc;

//! add subcontroller.
- (void)addSubController:(UIViewController*)ctlr;

//! remove subcontroller.
- (void)removeSubController:(UIViewController*)ctlr;

@end

# define NNTUIVIEW_NOTINHERIT_MUST_DECL \
- (CGRect)extent; \
- (void)setExtent:(CGRect)rc;

# define NNTUIVIEW_NOTINHERIT_MUST_IMPL \
- (CGRect)extent { return self.frame; } \
- (void)setExtent:(CGRect)rc { self.frame = rc; }

//! delay for touch signal.
NNT_EXTERN real kUITouchDelay;

//! drag time.
NNT_EXTERN real kUIDragDelay;

//! radius.
NNT_EXTERN int kUITouchRadius;

//! empty.
NNT_EXTERN CGPoint kUITouchSky;

NNTDECL_CATEGORY(UIView, NNT);

//! emit when user touch and release the view.
NNT_EXTERN signal_t kSignalViewClicked;

//! emit when select changed.
NNT_EXTERN signal_t kSignalSelectChanged;

//! emit when frame has changed.
NNT_EXTERN signal_t kSignalFrameChanged;

//! emit when bounds has changed.
NNT_EXTERN signal_t kSignalBoundsChanged;

//! selected
NNT_EXTERN signal_t kSignalSelected;
NNT_EXTERN signal_t kSignalDeselected;

//! draw.
NNT_EXTERN signal_t kSignalPainting;

# ifdef NNT_CXX

# define _CXXVIEW(cls) _objc_cxx_##cls##_wrapper

# define _CXXVIEW_DECL_BEGIN(cls) \
@interface _CXXVIEW(cls) : cls <_cxx_uiview_wrapper>

# define _CXXVIEW_DECL_END @end

# define _CXXVIEW_DECL(cls) \
_CXXVIEW_DECL_BEGIN(cls) \
_CXXVIEW_DECL_END

# define _CXXVIEW_IMPL_BEGIN(cls) \
@implementation _CXXVIEW(cls) \
@synthesize _cxxobj; \
- (void)dealloc { \
if (_cxxobj) _cxxobj->destroy(); \
[super dealloc]; \
} \
- (void)layoutSubviews { \
[super layoutSubviews]; \
if (_cxxobj) _cxxobj->layout_subviews(); \
} \
- (void)drawRect:(CGRect)rect { \
[super drawRect:rect]; \
if (_cxxobj) _cxxobj->draw(UIGraphicsGetCurrentContext(), rect); \
} \
- (void*)object { \
if (_cxxobj == NULL) return NULL; \
return _cxxobj->cxxobject(); \
}

# define _CXXVIEW_IMPL_END @end

# define _CXXVIEW_IMPL(cls) \
_CXXVIEW_IMPL_BEGIN(cls) \
_CXXVIEW_IMPL_END

# else

# define _CXXVIEW(cls)
# define _CXXVIEW_DECL_BEGIN(cls)
# define _CXXVIEW_DECL_END
# define _CXXVIEW_DECL(cls)

# endif

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "../Graphic/WCALayer.h"
# include "UITheme.h"

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(ui)

class IViewController;

class IView
: public IObject
{
public:
    
    //! callback to layout subviews.
    virtual void layout_subviews() = 0;
    
    //! function to draw view.
    virtual void draw(CGContextRef, CGRect const&) = 0;
    
    //! callback while orientation changed.
    virtual void layout_orientation(UIInterfaceOrientation) = 0;
    
    //! apply theme.
    virtual void theme(ui::Theme const&) = 0;
    
    //! add.
    virtual void add_sub(IView*) = 0;
    virtual void add_sub(IViewController*) = 0;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

NNT_BEGIN_HEADER_OBJC

@protocol _cxx_uiview_wrapper < NSObject >

@property (nonatomic, assign) ::wsi::ui::IView* _cxxobj;

@end

@interface _cxx_uiview_wrapper : NNTUIView <_cxx_uiview_wrapper, UIViewTheme>

@end

NNT_END_HEADER_OBJC

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(ui)

class HovTearView;
class VecTearView;

template <typename implT, 
typename viewT = _cxx_uiview_wrapper,
typename interT = IView
>
class View
: 
public Object<implT, viewT>, // for impl.
public interT // for wrapper.
{
    typedef View<implT, viewT, interT> self_type;
    typedef Object<implT, viewT> super;
    NNTDECL_NOCOPY_EX(View, self_type);
    
public:
    
    typedef viewT view_type;
    typedef empty_view_type empty_type;
    typedef ca::Layer layer_type;
    
    View()
    : _needremove(true)
    {
        ((implT*)this)->init();
        _updateself();
    }
    
    explicit View(view_type* view,
                  bool needremove = false)
    : super(view),
    _iswrapper(false),
    _needremove(needremove)
    {
        PASS;
    }
        
    ~View()
    {
        if (super::_needrelease == false)
            this->_self = nil;
        
        if (this->_self)
        {
            if (_iswrapper)
                ((id<_cxx_uiview_wrapper>)this->_self)._cxxobj = NULL;      
            
            if (_needremove && this->_self.superview)
                [this->_self removeFromSuperview];
        }
    }
    
    void init()
    {
        this->_self = [[view_type alloc] initWithZero];
    }                
    
    template <typename subcontrollerT>
    void add_subcontroller(subcontrollerT const& ctlr,
                                  typename wtl::mixin_type<subcontrollerT>::type::controller_type const* = NULL)
    {
        wtl::const_pointer<subcontrollerT> ptr(ctlr);
        [this->_self addSubController:*ptr];
    }
    
    template <typename subcontrollerT>
    void remove_subcontroller(subcontrollerT const& ctlr,
                                     typename wtl::mixin_type<subcontrollerT>::type::controller_type const* = NULL)
    {
        wtl::const_pointer<subcontrollerT> ptr(ctlr);
        [*ctlr removeFromSuperController];
    }
    
    CALayer* layer() const
    {
        return (CALayer*)this->_self.layer;
    }
    
    template <typename aniT>
    void add_animation(aniT const& ani, ns::String const& name = ns::null_string, 
                              typename wtl::mixin_type<aniT>::type::animation_type const* = NULL)
    {
        wtl::const_pointer<aniT> ptr(ani);
        [(CALayer*)this->_self.layer addAnimation:*ptr forKey:name];
    }
    
    template <typename effectT>
    void add_effect(effectT const& eff)
    {
        wtl::const_pointer<effectT> ptr(eff);
        [*ptr active:layer()];
    }
    
    template <typename gesT>
    void set_gesture(gesT const& eff)
    {
        wtl::const_pointer<gesT> ptr(eff);
        [this->_self addGestureRecognizer:*ptr];
    }
    
    void set_background(Color const& color)
    {
        this->_self.backgroundColor = color;
    }
    
    void set_background(cg::Fill const& fill)
    {
        this->_self.backgroundFill = fill;
        [this->_self setNeedsDisplay];
    }
    
    void set_visible(bool b)
    {
        b = !b;
        if (this->_self.hidden != b)
        {            
            this->_self.hidden = b;                        
            if (!b)
                [this->_self setNeedsDisplay];
        }
    }
        
    void set_visible(bool b, real w, real h)
    {
        b = !b;
        if (this->_self.hidden != b)
        {
            CGRect rc = this->_self.frame;

            [UIView setAnimationsEnabled:NO];
            CGRect trc = rc;
            if (w >= 0)
                trc.size.width = w;
            if (h >= 0)
                trc.size.height = h;
            this->_self.frame = trc;
            
            // set hidden.
            this->_self.hidden = b;
            
            // redraw.
            if (!b)
                [this->_self setNeedsDisplay];
            
            // animate.
            [UIView setAnimationsEnabled:YES];
            this->_self.frame = rc;            
        }
    }
    
    bool visible() const
    {
        return !this->_self.hidden;
    }
    
    cg::Rect bounds() const
    {
        return this->_self.bounds;
    }
    
    void set_bounds(cg::Rect const& rc)
    {
        this->_self.bounds = rc;
    }
    
    cg::Rect frame() const
    {
        return this->_self.frame;
    }
    
    real height() const
    {
        return this->_self.bounds.size.height;
    }
    
    real width() const
    {
        return this->_self.bounds.size.width;
    }
    
    void set_frame(cg::Rect const& rc)
    {
        this->_self.frame = rc;
        [this->_self setNeedsLayout];
    }
    
    void set_frame(int x, int y, int width, int height)
    {
        this->_self.frame = CGRectMake(x, y, width, height);
        [this->_self setNeedsLayout];
    }
    
    void set_size(cg::Size const& sz)
    {
        CGRect rc = this->_self.frame;
        rc.size = sz;
        this->set_frame(rc);
    }
    
    real scale_factor() const
    {
        return this->_self.contentScaleFactor;
    }
    
    void move_to(cg::Point const& pos)
    {
        CGRect rc = this->_self.frame;
        rc.origin = pos;
        this->_self.frame = rc;
    }
    
    void move_center(cg::Point const& pos)
    {
        CGRect rc = this->_self.frame;
        CGPoint center = CGRectCenterPoint(&rc);
        rc.origin.x += pos.x - center.x;
        rc.origin.y += pos.y - center.y;
        this->_self.frame = rc;
    }
    
    void redraw()
    {
        [this->_self setNeedsDisplay];
    }    
    
    void relayout()
    {
        [this->_self setNeedsLayout];
    }
    
    operator view_type* () const
    {
        return (view_type*)this->_self;
    }
    
    template <typename subviewT>
    void add_subview(subviewT const& view,
                            typename wtl::mixin_type<subviewT>::type::view_type const* = NULL)
    {
        wtl::const_pointer<subviewT> ptr(view);
        [this->_self addSubview:*ptr];
    }
    
    template <typename subviewT>
    void remove_subview(subviewT const& view,
                               typename wtl::mixin_type<subviewT>::type::view_type const* = NULL)
    {
        wtl::const_pointer<subviewT> ptr(view);
        [*ptr removeFromSuperview];
    }
    
    void add_subview(UIView* view)
    {
        [this->_self addSubview:view];
    }
    
    void remove_subview(UIView* view)
    {
        [view removeFromSuperview];
    }
    
    void remove_fromsuper()
    {
        [this->_self removeFromSuperview];
    }
    
    UIView* parent() const
    {
        return (UIView*)this->_self.superview;
    }
    
    template <typename vT>
    vT& parent()
    {
        return *(vT*)this->_self.superview.object;
    }
    
    void bring_totop()
    {
        [this->_self.superview bringSubviewToFront:this->_self];
    }
    
    void send_toback()
    {
        [this->_self.superview sendSubviewToBack:this->_self];
    }
        
    //! add sub controller or sub view smart.
    template <typename elementT>
    void add_sub(elementT& elemT,
                        typename wtl::mixin_type<elementT>::type::empty_type* empty = NULL)
    {
        this->_add_sub(elemT, empty);
    }
    
    virtual void add_sub(IView* view)
    {
        [this->_self addSubview:view->nsobject()];
    }
    
    virtual void add_sub(IViewController* ctlr);
    
    //! remove sub controller or sub view smart.
    template <typename elementT>
    void remove_sub(elementT& elemT,
                 typename wtl::mixin_type<elementT>::type::empty_type* empty = NULL)
    {
        this->_remove_sub(elemT, empty);
    }
    
    bool enabled() const
    {
        return this->_self.userInteractionEnabled;
    }
    
    void set_enable(bool val)
    {
        this->_self.userInteractionEnabled = val;
    }
    
    bool interaction() const
    {
        return this->_self.userInteractionEnabled;
    }
    
    void set_interaction(bool val)
    {
        this->_self.userInteractionEnabled = val;
    }
    
    void set_tag(int val)
    {
        this->_self.tag = val;
    }
    
    int tag() const
    {
        return this->_self.tag;
    }
    
    void set_content(UIViewContentMode mode)
    {
        this->_self.contentMode = mode;
    }
    
    UIViewContentMode content_mode() const
    {
        return this->_self.contentMode;
    }
    
    void set_removable(bool val)
    {
        this->_needremove = val;
    }
    
    HovTearView tear_hov(int pos, uint spacing);    
    VecTearView tear_vec(int pos, uint spacing);
    
    virtual void destroy()
    {
        this->_self = nil;
        super::destroy();
    }
    
    virtual void drop()
    {
        super::drop();
    }
    
    virtual void* cxxobject() const
    {
        return (implT*)this;
    }
    
    virtual id nsobject() const
    {
        return this->_self;
    }
    
    virtual void layout_orientation(UIInterfaceOrientation ori)
    {
        // adjust self.
        if (UIInterfaceOrientationIsLandscape(ori))
            this->layout_landscape();
        else
            this->layout_portrait();
    }
    
    virtual void layout_landscape()
    {
        PASS;
    }
    
    virtual void layout_portrait()
    {
        PASS;
    }
    
    virtual void draw(CGContextRef, CGRect const&)
    {
        PASS;
    }
    
    virtual void theme(ui::Theme const&)
    {
        PASS;
    }
    
    void change_self(view_type* obj)
    {
        ((implT*)this)->_set(obj);
        _updateself();
    }
    
    cg::AffineTransform transform() const
    {
        return this->_self.transform;
    }
    
    void set_transform(cg::AffineTransform const& af)
    {
        this->_self.transform = af;
    }
    
    static implT* From(id obj)
    {
        if ([obj conformsToProtocol:@protocol(_cxx_uiview_wrapper)] == NO)
            return NULL;
        id<_cxx_uiview_wrapper> mem = (id<_cxx_uiview_wrapper>)obj;
        return dynamic_cast<implT*>((interT*)mem._cxxobj);
    }
    
    layer_type& layer()
    {
        if (_layer.get() == NULL)
            _layer.reset(new layer_type(this->_self.layer));
        return *_layer;
    }
    
    void set_clip(bool clip = true)
    {
        this->_self.clipsToBounds = clip;
    }
    
protected:
    
    void _updateself()
    {
        _iswrapper = [this->_self conformsToProtocol:@protocol(_cxx_uiview_wrapper)];
        if (_iswrapper)
        {
            id<_cxx_uiview_wrapper> obj = (id<_cxx_uiview_wrapper>)this->_self;
            obj._cxxobj = (interT*)this;
        }
    }
    
    template <typename elementT>
    void _add_sub(elementT& v,
                         empty_view_type* = NULL)
    {
        this->impl()->add_subview(v);
    }
    
    template <typename elementT>
    void _add_sub(elementT& c,
                         empty_controller_type* = NULL)
    {
        this->impl()->add_subcontroller(c);
    }
    
    template <typename elementT>
    void _remove_sub(elementT& v,
                     empty_view_type* = NULL)
    {
        this->impl()->remove_subview(v);
    }
    
    template <typename elementT>
    void _remove_sub(elementT& c,
                     empty_controller_type* = NULL)
    {
        this->impl()->remove_subcontroller(c);
    }
    
    core::auto_ptr<layer_type> _layer;
    
private:
    
    bool _iswrapper;
    bool _needremove;
    
};

template <typename viewT>
class _NullView
: public View<_NullView<viewT>, viewT>
{
    typedef View<_NullView<viewT>, viewT> super;
    
public:
    
    _NullView()
    {
        PASS;
    }
    
    explicit _NullView(viewT* view,
              bool needremove = false)
    : super(view, needremove)
    {
        PASS;
    }
    
    ~_NullView()
    {
        PASS;
    }
    
    void layout_subviews() {}
    void draw(CGContextRef, CGRect const&) {}
};

template <typename implT>
class ContentView
{
public:
    
    template <typename elementT>
    void set_content(elementT const& elemT,
                            typename wtl::mixin_type<elementT>::type::empty_type* empty = NULL)
    {
        this->_set_content(elemT, empty);
    }
    
protected:
    
    template <typename elementT>
    void _set_content(elementT const& elemT,
                         empty_view_type* = NULL)
    {
        implT* impl = (implT*)this;
        impl->add_subview(elemT);
        if (_view)
            [_view removeFromSuperview];
        _view = elemT;
    }
    
    template <typename elementT>
    void _set_content(elementT const& elemT,
                         empty_controller_type* = NULL)
    {
        
    }
    
protected:
    
    UIView* _view;
    
};

class SimpleView
: public View<SimpleView>
{
public:
    
    SimpleView()
    {
        PASS;
    }
    
    virtual void layout_subviews()
    {
        PASS;
    }
    
};

class AnyView
: public View<AnyView>
{
    typedef View<AnyView> super;
    
public:
    
    AnyView(id v)
    : super(v)
    {
        PASS;
    }
    
    virtual void layout_subviews()
    {
        PASS;
    }
    
};

NNT_END_NS 
NNT_END_HEADER_CXX

# include "UITearView.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

template <typename implT, typename viewT, typename interT>
HovTearView View<implT, viewT, interT>::tear_hov(int pos, uint spacing)
{
    UITearViewHov* view = (UITearViewHov*)[this->_self tearHov:pos spacing:spacing];
    return HovTearView(view);
}

template <typename implT, typename viewT, typename interT>
VecTearView View<implT, viewT, interT>::tear_vec(int pos, uint spacing)
{
    UITearViewVec* view = (UITearViewVec*)[this->_self tearVec:pos spacing:spacing];
    return VecTearView(view);
}

class Fingers
{
public:
    
    Fingers(byte cnt)
    : count(cnt)
    {
        PASS;
    }
    
    operator byte () const
    {
        return count;
    }
    
    byte count;
};

NNT_BEGIN_NS(finger)

static const Fingers _1(1);
static const Fingers _2(2);
static const Fingers _3(3);
static const Fingers _4(4);
static const Fingers _5(5);

NNT_END_NS

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif