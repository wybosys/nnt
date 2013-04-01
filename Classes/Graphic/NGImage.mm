
# import "Core.h"
# import "NGBase.h"
# import "NGImage.h"
# import "Resource+NNT.h"
# import "Directory+NNT.h"
# import "NGContext.h"

NNT_BEGIN_OBJC

/**	@brief Wrapper around CGImageRef.
 *
 *	A wrapper class around CGImageRef.
 *
 *	@todo More documentation needed 
 **/

@implementation NgImage

/**	@property image 
 *	@brief The CGImageRef to wrap around.
 **/
@synthesize image;

/**	@property tiled
 *	@brief Draw as a tiled image?
 *
 *	If YES, the image is drawn repeatedly to fill the current clip region.
 *	Otherwise, the image is drawn one time only in the provided rectangle.
 *	The default value is NO.
 **/
@synthesize tiled;

/**	@property tileAnchoredToContext
 *	@brief Anchor the tiled image to the context origin?
 *
 *	If YES, the origin of the tiled image is anchored to the origin of the drawing context.
 *	If NO, the origin of the tiled image is set to the orgin of rectangle passed to
 *	<code>drawInRect:inContext:</code>.
 *	The default value is YES.
 *	If <code>tiled</code> is NO, this property has no effect.
 **/
@synthesize tileAnchoredToContext;

//! size.
@dynamic size;

#pragma mark -
#pragma mark Initialization

/** @brief Initializes a NgImage instance with the provided CGImageRef.
 *
 *	This is the designated initializer.
 *
 *  @param anImage The image to wrap.
 *  @return A NgImage instance initialized with the provided CGImageRef.
 **/
- (id)initWithCGImage:(CGImageRef)anImage {
    self = [super init];
	if ( self ) {
 		CGImageRetain(anImage);
    	image = anImage;
        tiled = NO;
		tileAnchoredToContext = YES;
    }
    return self;
}

- (id)init {
	return [self initWithCGImage:NULL];
}

/** @brief Initializes a NgImage instance with the contents of a PNG file.
 *  @param path The file system path of the file.
 *  @return A NgImage instance initialized with the contents of the PNG file.
 **/
- (id)initForPNGFile:(NSString *)path {
    CGDataProviderRef dataProvider = CGDataProviderCreateWithFilename([path cStringUsingEncoding:NSUTF8StringEncoding]);
    CGImageRef cgImage = CGImageCreateWithPNGDataProvider(dataProvider, NULL, YES, kCGRenderingIntentDefault);
    if ( cgImage ) {
        self = [self initWithCGImage:cgImage];
    }
    else {
        [self release];
        self = nil;
    }
    CGImageRelease(cgImage);
    CGDataProviderRelease(dataProvider);
    return self;
}

- (id)initForJPEGFile:(NSString *)path {
    CGDataProviderRef dataProvider = CGDataProviderCreateWithFilename([path cStringUsingEncoding:NSUTF8StringEncoding]);
    CGImageRef cgImage = CGImageCreateWithJPEGDataProvider(dataProvider, NULL, YES, kCGRenderingIntentDefault);
    if ( cgImage ) {
        self = [self initWithCGImage:cgImage];
    }
    else {
        [self release];
        self = nil;
    }
    CGImageRelease(cgImage);
    CGDataProviderRelease(dataProvider);
    return self;
}

- (id)initWithRetinaNamed:(NSString*)path {
    return [self initWithNamed:[NSDirectory retinaImageNamed:path]];
}

- (id)initWithNamed:(NSString *)path {
    path = [NNTResource PathOf:path];
    CGDataProviderRef dataProvider = CGDataProviderCreateWithFilename([path cStringUsingEncoding:NSUTF8StringEncoding]);
    CGImageRef cgImage = nil;
    if ([path hasSuffix:@".png"]) {
        cgImage = CGImageCreateWithPNGDataProvider(dataProvider, NULL, YES, kCGRenderingIntentDefault);
    } else {
        cgImage = CGImageCreateWithJPEGDataProvider(dataProvider, NULL, YES, kCGRenderingIntentDefault);
    }
    if ( cgImage ) {
        self = [self initWithCGImage:cgImage];
    }
    else {
        [self release];
        self = nil;
    }
    CGImageRelease(cgImage);
    CGDataProviderRelease(dataProvider);
    return self;
}

- (id)initWithData:(NSData *)data {
    CGDataProviderRef dataProvider = CGDataProviderCreateWithCFData((CFDataRef)data);
    CGImageRef cgImage = CGImageCreateWithPNGDataProvider(dataProvider, NULL, YES, kCGRenderingIntentDefault);
    if ( cgImage ) {
        self = [self initWithCGImage:cgImage];
    }
    else {
        [self release];
        self = nil;
    }
    CGImageRelease(cgImage);
    CGDataProviderRelease(dataProvider);
    return self;

}

- (void)dealloc {
	CGImageRelease(image);
	[super dealloc];
}

- (void)finalize {
	CGImageRelease(image);
	[super finalize];
}

- (id)copyWithZone:(NSZone *)zone {
    NgImage *copy = [[[self class] allocWithZone:zone] init];
	
	copy->image = CGImageCreateCopy(self.image);
	copy->tiled = self->tiled;
	copy->tileAnchoredToContext = self->tileAnchoredToContext;
	
    return copy;
}

#pragma mark NSCoding methods

- (void)encodeWithCoder:(NSCoder *)coder {
    NSData* data = [self dataAsPNG];
    [coder encodeBytes:(uint8_t const*)[data bytes] length:[data length] forKey:@"raw_data"];
}

- (id)initWithCoder:(NSCoder *)coder {
    self = [self init];
    
    NSUInteger raw_len;
    const uint8_t* raw_data = [coder decodeBytesForKey:@"raw_data" returnedLength:&raw_len];
    NSData* data = [[NSData alloc] initWithBytesNoCopy:(void*)raw_data length:raw_len freeWhenDone:NO];
    CGDataProviderRef dataProvider = CGDataProviderCreateWithCFData((CFDataRef)data);
    CGImageRef cgImage = CGImageCreateWithPNGDataProvider(dataProvider, NULL, YES, kCGRenderingIntentDefault);
    if (cgImage == NULL) {
        trace_msg(@"failed to create image from data by coder.");
        
        self.image = nil;
        CFRelease(dataProvider);
        [data release];
        return self;
    }
    
    self.image = cgImage;
    
    CFRelease(cgImage);
    CFRelease(dataProvider);
    [data release];
    return self;
}

#pragma mark -
#pragma mark Factory Methods

/** @brief Creates and returns a new NgImage instance initialized with the provided CGImageRef.
 *  @param anImage The image to wrap.
 *  @return A new NgImage instance initialized with the provided CGImageRef.
 **/
+ (NgImage *)imageWithCGImage:(CGImageRef)anImage {
	return [[[self alloc] initWithCGImage:anImage] autorelease];
}

/** @brief Creates and returns a new NgImage instance initialized with the contents of a PNG file.
 *  @param path The file system path of the file.
 *  @return A new NgImage instance initialized with the contents of the PNG file.
 **/
+ (NgImage *)imageForPNGFile:(NSString *)path {
	return [[[self alloc] initForPNGFile:path] autorelease];
}

+ (NgImage *)imageForJPEGFile:(NSString *)path {
    return [[[self alloc] initForJPEGFile:path] autorelease];
}

+ (NgImage *)imageWithNamed:(NSString *)path {
    return [[[self alloc] initWithNamed:path] autorelease];
}

+ (NgImage *)imageWithData:(NSData *)data {
    return [[[self alloc] initWithData:data] autorelease];
}

#pragma mark -
#pragma mark Accessors

- (void)setImage:(CGImageRef)newImage {
	if ( newImage != image ) {
		CGImageRetain(newImage);
		CGImageRelease(image);
		image = newImage;
	}
}

- (CGImageRef)image {
    return image;
}

#pragma mark -
#pragma mark Drawing

/** @brief Draws the image into the given graphics context.
 *
 *  If the tiled property is TRUE, the image is repeatedly drawn to fill the clipping region, otherwise the image is
 *  scaled to fit in rect.
 *  
 *  @param rect The rectangle to draw into.
 *  @param context The graphics context to draw into.
 **/
- (void)drawInRect:(CGRect)rect inContext:(CGContextRef)context {
	CGImageRef theImage = self.image;
	if ( theImage ) {
        CGContextSaveGState(context);
        
		if ( self.isTiled ) {
            
			CGContextClipToRect(context, *(CGRect *)&rect);
			if ( !self.tileAnchoredToContext ) {
				CGContextTranslateCTM(context, rect.origin.x, rect.origin.y);
			}
			CGRect imageBounds = CGRectMake(0, 0, (CGFloat)CGImageGetWidth(theImage), (CGFloat)CGImageGetHeight(theImage));
			CGContextDrawTiledImage(context, imageBounds, theImage);
            
		} else {
            
            CGContextDrawImageOri(context, rect, theImage);
		}
        
        CGContextRestoreGState(context);
	}
}

- (void)drawInRect:(CGRect)rect {
    
# ifdef NNT_TARGET_IOS
    UIImage *img = [UIImage imageWithCGImage:self.image];
    [img drawInRect:rect];
# endif
    
}

# pragma mark others.

- (CGSize)size {
    return CGImageGetSize(self.image);
}

- (NSData*)dataAsPNG {
# ifdef NNT_TARGET_IOS
    NSData* data = nil;
    
    UIImage* uiimg = [[UIImage alloc] initWithCGImage:self.image];
    data = UIImagePNGRepresentation(uiimg);
    [uiimg release];
    
    return data;
# endif
    
# ifdef NNT_TARGET_MAC
    NSMutableData* data = [NSMutableData data];
    CGImageDestinationRef ref_des = CGImageDestinationCreateWithData((CFMutableDataRef)data, kUTTypePNG, 1, NULL);
    CGImageDestinationAddImage(ref_des, self.image, nil);
    if (!CGImageDestinationFinalize(ref_des))
        trace_msg(@"failed to convert CGImageRef to data");
    CFRelease(ref_des);
    return data;
# endif
}

@end

NgImage* NgAddAlphaChannelToImage(CGImageRef img) {
    CGImageRef retVal = NULL;
    
    size_t width = CGImageGetWidth(img);
    size_t height = CGImageGetHeight(img);
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    
    CGContextRef offscreenContext = CGBitmapContextCreate(NULL, 
                                                          width, height, 
                                                          8,
                                                          0, 
                                                          colorSpace, 
                                                          kCGImageAlphaPremultipliedFirst);
    
    if (offscreenContext != NULL) {
        CGContextDrawImage(offscreenContext, CGRectMake(0, 0, width, height), img);
        
        retVal = CGBitmapContextCreateImage(offscreenContext);
        CGContextRelease(offscreenContext);
    }

    CGColorSpaceRelease(colorSpace);
    
    if (retVal == nil)
        return nil;
    
    NgImage* image = [NgImage imageWithCGImage:retVal];
    CGImageRelease(retVal);
    return image;
}

NgImage* NgMaskImage(CGImageRef dst, CGImageRef src) {
    NgImage* imageWithAlpha = [NgImage imageWithCGImage:src];
    if ((CGImageGetAlphaInfo(src) == kCGImageAlphaNone) ||
        (CGImageGetAlphaInfo(src) == kCGImageAlphaNoneSkipFirst)) {
        imageWithAlpha = NgAddAlphaChannelToImage(src);
    }
    CGImageRef mask = CGImageMaskCreate(CGImageGetWidth(dst),
                                        CGImageGetHeight(dst),
                                        CGImageGetBitsPerComponent(dst),
                                        CGImageGetBitsPerPixel(dst),
                                        CGImageGetBytesPerRow(dst),
                                        CGImageGetDataProvider(dst), NULL, false);
    CGImageRef masked = CGImageCreateWithMask(imageWithAlpha.image, mask);
    CGImageRelease(mask);
    NgImage* image = [NgImage imageWithCGImage:masked];
    CGImageRelease(masked);
    return image;
}

NgImage* NgImageLoadPngData(byte const* data, usize const len) {
	CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, data, len, NULL);
    if (provider == NULL)
        return nil;
    CGImageRef cgImage = CGImageCreateWithPNGDataProvider(provider, 
                                                          NULL, 
                                                          YES, 
                                                          kCGRenderingIntentDefault);
    CGDataProviderRelease(provider);
    if (cgImage == NULL)
        return nil;
    NgImage* image = [NgImage imageWithCGImage:cgImage];
    CGImageRelease(cgImage);
    return image;
}

CGRect CGImageGetRect(CGImageRef img) {
    return CGRectMake(0, 0, CGImageGetWidth(img), CGImageGetHeight(img));
}

CGSize CGImageGetSize(CGImageRef img) {
    return CGSizeMake(CGImageGetWidth(img), CGImageGetHeight(img));
}

// need manual release.
CGImageRef NgLoadPixelsImage(rgba_t* pixels, uint width, uint height)
{
    CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();
    CGContextRef ctx = CGBitmapContextCreate(pixels,
                                                 width,
                                                 height,
                                                 8,
                                                 width * 4,
                                                 colorspace,
                                                 kCGImageAlphaPremultipliedLast);
    CGImageRef ref_img = CGBitmapContextCreateImage(ctx);
    CGColorSpaceRelease(colorspace);
    CGContextRelease(ctx);
    return ref_img;
}

NNT_END_OBJC