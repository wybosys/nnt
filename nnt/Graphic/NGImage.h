
# ifndef __NNT_Ng_NgIMAGE_F477E3EABF0D48AEBF5B8937847823C6_H_INCLUDED
# define __NNT_Ng_NgIMAGE_F477E3EABF0D48AEBF5B8937847823C6_H_INCLUDED

# import "NGBase.h"

NNT_BEGIN_HEADER_OBJC

@interface NgImage : NSObject <NSCopying, NSCoding> {
@private
	CGImageRef image;
	BOOL tiled;
	BOOL tileAnchoredToContext;
}

//! image.
@property (assign) CGImageRef image;

//! if is tile.
@property (assign, getter=isTiled) BOOL tiled;

//! anchored.
@property (assign) BOOL	tileAnchoredToContext;

//! size.
@property (readonly) CGSize size;

/// @name Factory Methods
/// @{
+ (NgImage *)imageWithCGImage:(CGImageRef)anImage;
+ (NgImage *)imageForPNGFile:(NSString *)path;
+ (NgImage *)imageForJPEGFile:(NSString *)path;
+ (NgImage *)imageWithNamed:(NSString *)path;
+ (NgImage *)imageWithData:(NSData *)data;
///	@}

/// @name Initialization
/// @{
- (id)initWithCGImage:(CGImageRef)anImage;
- (id)initForPNGFile:(NSString *)path;
- (id)initForJPEGFile:(NSString *)path;
- (id)initWithNamed:(NSString *)path;
- (id)initWithRetinaNamed:(NSString*)path;
- (id)initWithData:(NSData *)data;

///	@}

/// @name Drawing
/// @{
- (void)drawInRect:(CGRect)rect inContext:(CGContextRef)context;
- (void)drawInRect:(CGRect)rect;
///	@}

//! get data as png format.
- (NSData*)dataAsPNG;

@end

//! add alpha channel to a image.
//! @return return a new image.
NgImage* NgAddAlphaChannelToImage(CGImageRef img);

//! mask src image with dst image
NgImage* NgMaskImage(CGImageRef dst, CGImageRef src);

//! load image from png-data.
NgImage* NgImageLoadPngData(byte const* data, usize const len);

//! get rect of image.
CGRect CGImageGetRect(CGImageRef img);

//! get size of image.
CGSize CGImageGetSize(CGImageRef img);

//! create a image use pixels.
CGImageRef NgLoadPixelsImage(rgba_t* pixels, uint width, uint height);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cg)

class Image
: public ::nnt::ns::Object<NgImage>
{    
    typedef ::nnt::ns::Object<NgImage> super;
    typedef Image self_type;
    
public:
    
    typedef Image image_type;
    
    Image()
    {
        PASS;
    }
    
    Image(CGImageRef img)
    : super(nil)
    {
        this->_self = [[NgImage alloc] initWithCGImage:img];
    }
    
    Image(ns::String const& file)
    : super(nil)
    {
        this->_self = [[NgImage alloc] initWithNamed:file];
    }
    
    Image(ns::Data const& data)
    : super(nil)
    {
        this->_self = [[NgImage alloc] initWithData:data];
    }
    
    Image(NgImage* img)
    : super(img)
    {
        PASS;
    }
    
    operator CGImageRef () const
    {
        return (CGImageRef)this->_self.image;
    }
    
    static Image Retina(ns::String const& named)
    {
        NgImage* img = [[NgImage alloc] initWithRetinaNamed:named];
        Image ret(img);
        [img release];
        return ret;
    }
    
    static Image const& Null()
    {
        static const Image ze((NgImage*)nil);
        return ze;
    }
    
    Size size() const
    {
        return Size(this->_self.size);
    }
    
protected:
    
    void _set(CGImageRef img)
    {
        this->_self.image = img;
    }
    
    void _set(self_type const& img)
    {
        this->_self.image = img;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif