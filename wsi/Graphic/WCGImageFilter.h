
# ifndef __WSI_WCG_IMAGEFILTER_21BF8A8D521B42F6A7D2059248ADAC69_H_INCLUDED
# define __WSI_WCG_IMAGEFILTER_21BF8A8D521B42F6A7D2059248ADAC69_H_INCLUDED

# import "WCGImage.h"

WSI_BEGIN_HEADER_OBJC

@protocol WCGImageFilter <NSObject>

- (WCGImage*)apply:(WCGImage*)image;

@end

@interface WCGImageFilter : WSIObject < WCGImageFilter >

@end

WSIDECL_OBJCXX_WRAPPER(WCGImageFilter);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(cg)

class IImageFilter
: public ns::cxx::IObject
{
public:
    
    virtual cg::Image apply(cg::Image const&) const = 0;
    
};

class ImageFilter
: public ns::cxx::Object<WSI_OBJCXX_WRAPPER(WCGImageFilter), IImageFilter>
{
public:
    
    ImageFilter()
    {
        PASS;
    }
    
    virtual cg::Image apply(cg::Image const&) const
    {
        return cg::Image::Null();
    }
    
};

WSI_BEGIN_NS(filter)

class SetColor
: public ImageFilter
{
public:
    
    virtual cg::Image apply(cg::Image const&) const;
    
    Color color;
    
};

class OverColor
: public ImageFilter
{
public:
    
    virtual cg::Image apply(cg::Image const&) const;
    
    Color color;
    
};

WSI_END_NS

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
