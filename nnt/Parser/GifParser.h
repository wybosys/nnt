
# ifndef __WSI_PARSER_GIF_5B07783BD9AB4849A5F9EC90089B899E_H_INCLUDED
# define __WSI_PARSER_GIF_5B07783BD9AB4849A5F9EC90089B899E_H_INCLUDED

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

@interface GifImage : WSIObject {
    CGImageRef image;
    uint delay; //! in milliseconds.
}

@property (nonatomic) CGImageRef image;
@property (nonatomic, assign) uint delay;

@end

@interface GifParser : WSIObject {
    NSArray* images; //! GifImage array.
}

@property (nonatomic, readonly) NSArray* images;

- (id)initWithData:(NSData*)da;
+ (BOOL)isGifData:(NSData*)da;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX

class gif_image_t
{
public:    
    gif_image_t(CGImageRef ref, int d)
    : delay(d)
    {
        image = ref;
        CGImageRetain(ref);
    }
    
    gif_image_t(gif_image_t const& r)
    {
        image = r.image;
        CGImageRetain(r.image);
        delay = r.delay;
    }
    
    ~gif_image_t()
    {
        CGImageRelease(image);
    }
    
    int delay; // in milliseconds.
    CGImageRef image;
};

WSI_END_HEADER_CXX

# endif

# endif

# endif