
# ifndef __NNT_CG_CGFILL_C1FFE32F318C4BC0AD2691DD1574D6D8_H_INCLUDED
# define __NNT_CG_CGFILL_C1FFE32F318C4BC0AD2691DD1574D6D8_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(WCGGradient);
NNTDECL_EXTERN_CLASS(WCGImage);
NNTDECL_EXTERN_CLASS(WCGColor);

@interface WCGFill : NSObject <NSCopying, NSCoding>

+ (WCGFill *)fillWithColor:(WCGColor *)aColor;
+ (WCGFill *)fillWithGradient:(WCGGradient *)aGradient;
+ (WCGFill *)fillWithImage:(WCGImage *)anImage;

- (id)initWithColor:(WCGColor *)aColor;
- (id)initWithGradient:(WCGGradient *)aGradient;
- (id)initWithImage:(WCGImage *)anImage;

@end

@interface WCGFill (AbstractMethods)

- (void)fillRect:(CGRect)theRect inContext:(CGContextRef)theContext;
- (void)fillPathInContext:(CGContextRef)theContext;

@end


NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "WCGColor.h"
# include "WCGGradient.h"
# include "WCGImage.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cg)

class Fill
: public ::wsi::ns::Object<WCGFill>
{
    typedef ::wsi::ns::Object<WCGFill> super;
    typedef Fill self_type;
    
public:
    
    Fill()
    {
        PASS;
    }
    
    Fill(WCGFill* fill)
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
        this->_self = [safe_alloc(WCGFill) initWithColor:color];
    }
    
    Fill(Gradient const& grad)
    : super(nil)
    {
        this->_self = [safe_alloc(WCGFill) initWithGradient:grad];
    }
    
    Fill(Image const& img)
    : super(nil)
    {
        this->_self = [safe_alloc(WCGFill) initWithImage:img];
    }
    
    static Fill const& Null()
    {
        static Fill __gs_fill((WCGFill*)nil);
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