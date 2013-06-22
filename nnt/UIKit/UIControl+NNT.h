
# ifndef __NNT_UIKIT_UICONTROL_207D01A25A2F41D2BE94BF75853EC49A_H_INCLUDED
# define __NNT_UIKIT_UICONTROL_207D01A25A2F41D2BE94BF75853EC49A_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@protocol UIItemProvider <NSObject>

- (NSUInteger)providerNumber:(id)obj;
- (id)providerItem:(id)obj index:(NSUInteger)index;

@end

@protocol UIItemSerial <NSObject>

- (BOOL)serialOut:(id)obj identity:(NSString*)identity data:(NSData*)data;
- (NSData*)serialIn:(id)obj identity:(NSString*)identity;

@end

NNTDECL_EXTERN_CLASS(NgFill);

@interface NNTUIControl : UIControl {
    NNTOBJECT_DECL;        
    
    //! background fill.
    NgFill *backgroundFill;
}

NNTOBJECT_PROP;

@property (nonatomic, retain) NgFill *backgroundFill;

@end

NNT_END_HEADER_OBJC

# ifndef NNT_CXX

# define _CXXCONTROL(cls)
# define _CXXCONTROL_DECL_BEGIN(cls)
# define _CXXCONTROL_DECL_END
# define _CXXCONTROL_DECL(cls)
# define _CXXCONTROL_IMPL_BEGIN(cls)
# define _CXXCONTROL_IMPL_END
# define _CXXCONTROL_IMPL(cls)

# endif

# ifdef NNT_CXX

# include "UIView+NNT.h"

# define _CXXCONTROL(cls) _objc_cxx_##cls##_wrapper

# define _CXXCONTROL_DECL_BEGIN(cls) \
@interface _CXXCONTROL(cls) : cls <_cxx_uiview_wrapper>

# define _CXXCONTROL_DECL_END @end

# define _CXXCONTROL_DECL(cls) \
_CXXCONTROL_DECL_BEGIN(cls) \
_CXXCONTROL_DECL_END

# define _CXXCONTROL_IMPL_BEGIN(cls) \
@implementation _CXXCONTROL(cls) \
@synthesize _cxxobj; \
- (void)dealloc { \
if (_cxxobj) _cxxobj->destroy(); \
[super dealloc]; \
} \
- (void)drawRect:(CGRect)rect { \
[super drawRect:rect]; \
if (_cxxobj) _cxxobj->draw(UIGraphicsGetCurrentContext(), rect); \
} \
- (void*)object { \
return _cxxobj->cxxobject(); \
}

# define _CXXCONTROL_IMPL_END @end

# define _CXXCONTROL_IMPL(cls) \
_CXXCONTROL_IMPL_BEGIN(cls) \
_CXXCONTROL_IMPL_END

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class IControl
: public IView
{
public:
    
    virtual void layout_subviews()
    {
        PASS;
    }
    
};

template <typename implT, typename ctlT, typename interT = IControl>
class Control
: public View<implT, ctlT, interT>
{   
    typedef View<implT, ctlT, interT> super;
    typedef Control<implT, ctlT, interT> self_type;
    NNTDECL_NOCOPY_EX(Control, self_type);
    
public:
    
    typedef ctlT control_type;
    
    Control()
    {
        PASS;
    }
    
    explicit Control(control_type* type, bool needremove = true)
    : super(type, needremove)
    {
        PASS;
    }
    
    ~Control()
    {
        PASS;
    }    
           
    virtual void layout_subviews()
    {
        PASS;
    }
    
    bool enabled() const
    {
        return this->_self.enabled;
    }
    
    void set_enable(bool val)
    {
        this->_self.enabled = val;
    }
        
};

template <typename controlT>
class InstanceControl
: public Instance<controlT>
{
public:
    
    InstanceControl()
    {
        this->_obj->set_removable(false);
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif