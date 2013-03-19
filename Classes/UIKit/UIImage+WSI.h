
# ifndef __NNT_UIKIT_UIIMAGE_0EA16C00F66747D9B2A3A4540759D85B_H_INCLUDED
# define __NNT_UIKIT_UIIMAGE_0EA16C00F66747D9B2A3A4540759D85B_H_INCLUDED

NNT_BEGIN_OBJC

@interface UIImage (NNT)

//! named auto check retina mode.
+ (UIImage *)retinaImageNamed:(NSString*)str;

//! add reflection to image.
- (UIImage *)addImageReflection:(CGFloat)reflectionFraction;

//! make reflection of image.
- (UIImage *)makeImageReflection:(CGFloat)reflectionFraction;

//! clip by mask.
- (UIImage *)maskBy:(UIImage*)mask;

//! ratio.
- (real)imageRatio;

//! crop image.
- (UIImage *)croppedImage:(CGRect)bounds;

//! thumbnail image.
- (UIImage *)thumbnailImage:(NSInteger)thumbnailSize
          transparentBorder:(NSUInteger)borderSize
               cornerRadius:(NSUInteger)cornerRadius
       interpolationQuality:(CGInterpolationQuality)quality;

//! resize image.
- (UIImage *)resizedImage:(CGSize)newSize
     interpolationQuality:(CGInterpolationQuality)quality;

//! resize image.
- (UIImage *)resizedImageWithContentMode:(UIViewContentMode)contentMode
                                  bounds:(CGSize)bounds
                    interpolationQuality:(CGInterpolationQuality)quality;

//! resize image percent.
- (UIImage *)resizedImagePercent:(real)percent;

//! rounded.
- (UIImage *)roundedCornerImage:(NSInteger)cornerSize borderSize:(NSInteger)borderSize;

//! alpha.
- (BOOL)hasAlpha;
- (UIImage *)imageWithAlpha;
- (UIImage *)transparentBorderImage:(NSUInteger)borderSize;

//! init with url.
- (id)initWithURL:(NSURL*)url;
- (id)initWithURL:(NSURL*)url cache:(BOOL)cache;

//! raw data.
- (NSData*)rawData;

//! gray.
- (UIImage*)grayImage;

//! normal image.
- (UIImage*)normalImage;

@end

//! mask src image with dst image
UIImage *UIMaskImage(UIImage *dst, UIImage *src);

@interface NNTUIImage : UIImage {
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

+ (NNTUIImage *)imageNamed:(NSString *)name;

@end

NNTDECL_CATEGORY(UIImage, NNT);

NNT_END_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class Image
: public ::wsi::ns::Object<UIImage>
{
    typedef ::wsi::ns::Object<UIImage> super;
    
public:
    
    typedef Image image_type;
    
    Image()
    {
        PASS;
    }
        
    Image(ns::String const& name)
    : super(nil)
    {
        this->_self = [[UIImage imageNamed:name] retain];
    }
    
    Image(NSData* data)
    : super(nil)
    {
        this->_self = [[UIImage alloc] initWithData:data];
    }
    
    Image(CGImageRef img)
    : super(nil)
    {
        this->_self = [[UIImage alloc] initWithCGImage:img];
    }
    
    Image(cg::Image const& img)
    : super(nil)
    {
        this->_self = [[UIImage alloc] initWithCGImage:img];   
    }
    
    Image(UIImage* img)
    : super(img)
    {
        PASS;
    }
    
    Image normal() const
    {
        return Image([this->_self normalImage]);
    }
    
    static Image Retina(NSString* name)
    {
        UIImage* img = [UIImage retinaImageNamed:name];
        return Image(img);
    }
    
    static Image File(ns::URL const& url)
    {
        UIImage* img = [UIImage imageWithContentsOfFile:url.std()];
        return Image(img);
    }
    
    void load(ns::String const& name)
    {
        this->_release();
        this->_self = [[UIImage imageNamed:name] retain];
    }
    
    void retina(ns::String const& name)
    {
        this->_release();
        this->_self = [UIImage retinaImageNamed:name];
    }
    
    operator CGImageRef () const
    {
        return (CGImageRef)this->_self.CGImage;
    }
    
    static Image Img(void* obj)
    {
        return Image((objc_type*)obj);
    }
    
    static Image Img(id obj)
    {
        return Image((objc_type*)obj);
    }
    
    static Image String(id obj)
    {
        return Image(ns::String((NSString*)obj));
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif