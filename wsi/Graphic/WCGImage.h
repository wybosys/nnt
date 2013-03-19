
# ifndef __WSI_WCG_WCGIMAGE_F477E3EABF0D48AEBF5B8937847823C6_H_INCLUDED
# define __WSI_WCG_WCGIMAGE_F477E3EABF0D48AEBF5B8937847823C6_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface WCGImage : NSObject <NSCopying, NSCoding> {
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
+ (WCGImage *)imageWithCGImage:(CGImageRef)anImage;
+ (WCGImage *)imageForPNGFile:(NSString *)path;
+ (WCGImage *)imageForJPEGFile:(NSString *)path;
+ (WCGImage *)imageWithNamed:(NSString *)path;
+ (WCGImage *)imageWithData:(NSData *)data;
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
WCGImage* WCGAddAlphaChannelToImage(CGImageRef img);

//! mask src image with dst image
WCGImage* WCGMaskImage(CGImageRef dst, CGImageRef src);

//! load image from png-data.
WCGImage* WCGImageLoadPngData(byte const* data, usize const len);

//! get rect of image.
CGRect CGImageGetRect(CGImageRef img);

//! get size of image.
CGSize CGImageGetSize(CGImageRef img);

//! create a image use pixels.
CGImageRef WCGLoadPixelsImage(rgba_t* pixels, uint width, uint height);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(cg)

class Image
: public ::wsi::ns::Object<WCGImage>
{    
    typedef ::wsi::ns::Object<WCGImage> super;
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
        this->_self = [[WCGImage alloc] initWithCGImage:img];
    }
    
    Image(ns::String const& file)
    : super(nil)
    {
        this->_self = [[WCGImage alloc] initWithNamed:file];
    }
    
    Image(ns::Data const& data)
    : super(nil)
    {
        this->_self = [[WCGImage alloc] initWithData:data];
    }
    
    Image(WCGImage* img)
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
        WCGImage* img = [[WCGImage alloc] initWithRetinaNamed:named];
        Image ret(img);
        [img release];
        return ret;
    }
    
    static Image const& Null()
    {
        static const Image ze((WCGImage*)nil);
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

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif