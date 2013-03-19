
# ifndef __NNT_CG_CGFILL_C1FFE32F318C4BC0AD2691DD1574D6D8_H_INCLUDED
# define __NNT_CG_CGFILL_C1FFE32F318C4BC0AD2691DD1574D6D8_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NgGradient);
NNTDECL_EXTERN_CLASS(NgImage);
NNTDECL_EXTERN_CLASS(NgColor);

@interface NgFill : NSObject <NSCopying, NSCoding>

+ (NgFill *)fillWithColor:(NgColor *)aColor;
+ (NgFill *)fillWithGradient:(NgGradient *)aGradient;
+ (NgFill *)fillWithImage:(NgImage *)anImage;

- (id)initWithColor:(NgColor *)aColor;
- (id)initWithGradient:(NgGradient *)aGradient;
- (id)initWithImage:(NgImage *)anImage;

@end

@interface NgFill (AbstractMethods)

- (void)fillRect:(CGRect)theRect inContext:(CGContextRef)theContext;
- (void)fillPathInContext:(CGContextRef)theContext;

@end


NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "NGColor.h"
# include "NGGradient.h"
# include "NGImage.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cg)

class Fill
: public ::nnt::ns::Object<NgFill>
{
    typedef ::nnt::ns::Object<NgFill> super;
    typedef Fill self_type;
    
public:
    
    Fill()
    {
        PASS;
    }
    
    Fill(NgFill* fill)
    : super(fill)
    {
        PASS;
    }
    
    Fill(self_type const& r)
    : super(r._self)
    {
        PASS;
    }
    
    Fill(Color const& color)
    : super(nil)
    {
        this->_self = [safe_alloc(NgFill) initWithColor:color];
    }
    
    Fill(Gradient const& grad)
    : super(nil)
    {
        this->_self = [safe_alloc(NgFill) initWithGradient:grad];
    }
    
    Fill(Image const& img)
    : super(nil)
    {
        this->_self = [safe_alloc(NgFill) initWithImage:img];
    }
    
    static Fill const& Null()
    {
        static Fill __gs_fill((NgFill*)nil);
        return __gs_fill;
    }
    
    void fill(CGRect const& rc, CGContextRef ctx) const
    {
        [this->_self fillRect:rc inContext:ctx];
    }
    
    void fill(CGContextRef ctx) const
    {
        [this->_self fillPathInContext:ctx];
    }

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif