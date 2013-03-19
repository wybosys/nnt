
# import "Core.h"
# import "GifParser.h"
# include "../../contrib/giflib/gif_lib.h"
# import "WCGImage.h"

NNT_BEGIN_OBJC

struct _gif_data_t
{
byte const* data;
usize left;
usize const length;
};

static int _gif_data(GifFileType* ft, GifByteType* bytes, int len)
{
    struct _gif_data_t* data = (struct _gif_data_t*)ft->UserData;
    if (len <= data->left)
    {
        memcpy(bytes, data->data, len);
        data->data += len;
        data->left -= len;
        return len;
    }
    return 0;
}

@implementation GifImage

@synthesize image, delay;

- (void)setImage:(CGImageRef)img {
    CGImageRelease(image);
    image = img;
    CGImageRetain(img);
}

- (void)dealloc {
    CGImageRelease(image);
    [super dealloc];
}

@end

@interface GifParser ()

- (bool)_decode:(NSData*)da;

@end

@implementation GifParser

@synthesize images;

- (id)initWithData:(NSData*)da {
    self = [super init];
    if ([GifParser isGifData:da] == NO)
        zero_release(self);
    if (self)
    {
        if (NO == [self _decode:da])
            zero_release(self);
    }        
    return self;
}

- (void)dealloc {
    safe_release(images);
    [super dealloc];
}

+ (BOOL)isGifData:(NSData*)da {
    byte const* buf = (byte const*)[da bytes];
	if (buf[0] == 0x47 && buf[1] == 0x49 && buf[2] == 0x46 && buf[3] == 0x38) {
		return YES;
	}
	return NO;   
}

- (bool)_decode:(NSData*)da {
    // clear.
    NSMutableArray* ret_images = [[NSMutableArray alloc] init];
    
    // decode.
    struct _gif_data_t data = { (byte const*)[da bytes], [da length], [da length] };
    GifFileType* ft = DGifOpen(&data, _gif_data);
    
    usize const cnt_pixels_screen = ft->SWidth * ft->SHeight;
    GifPixelType* pixels_screen = (GifPixelType*)malloc(cnt_pixels_screen * sizeof(GifPixelType));
    GifPixelType* pixels_screen_buffer = (GifPixelType*)malloc(cnt_pixels_screen * sizeof(GifPixelType));
    // fill background.
    for (uint i = 0; i < cnt_pixels_screen; ++i)
    {
        pixels_screen[i] = ft->SBackGroundColor;
        pixels_screen_buffer[i] = ft->SBackGroundColor;
    }       
    
    // stack.
    uint lst_delay = 0;
    uint lst_transcolor = 0;
    
    int sta = GIF_ERROR;
    do
    {
        // ret record type.
        GifRecordType rt;
        sta = DGifGetRecordType(ft, &rt);
        if (sta == GIF_ERROR)
            break;
        
        // process record type.
        switch (rt)
        {
            case TERMINATE_RECORD_TYPE: 
            { 
                sta = GIF_ERROR; 
            } break;
            case UNDEFINED_RECORD_TYPE:
            {
                trace_msg(@"undefined record type.");
                sta = GIF_ERROR;
            } break;
            case IMAGE_DESC_RECORD_TYPE:
            {
                sta = DGifGetImageDesc(ft);
                if (sta == GIF_ERROR)
                {
                    trace_msg(@"failed to get image desc.");
                    break;
                }
                
                int posx = ft->Image.Left;
                int posy = ft->Image.Top;
                int width = ft->Image.Width;
                int height = ft->Image.Height;
                
                if ((posx + width > ft->SWidth) ||
                    (posy + height > ft->SHeight))
                {
                    trace_msg(@"the image is no fit in current screen.");
                    break;
                }
                
                if (ft->Image.Interlace)
                {
                    trace_msg(@"unsupport to interlace mode.");
                }
                else
                {
                    // draw to buffer.
                    for (uint r = 0; 
                         (r < height) && (sta != GIF_ERROR);
                         ++r)
                    {
                        sta = DGifGetLine(ft, 
                                          pixels_screen_buffer + (posy + r) * width + posx, 
                                          width);
                    }
                }
                
                ColorMapObject* colormap = ft->Image.ColorMap ? ft->Image.ColorMap : ft->SColorMap;
                if (colormap == NULL) 
                {
                    trace_msg(@"can't find color map.");
                    sta = GIF_ERROR;
                    break;
                }
                
                // convert to rgba buffer.
                rgba_t* rgba_buf = (rgba_t*)malloc(cnt_pixels_screen * sizeof(rgba_t));
                for (uint i = 0; i < cnt_pixels_screen; ++i)
                {
                    rgba_t* val = (rgba_t*)(rgba_buf + i);                        
                    
                    if ((lst_transcolor != -1) && 
                        (lst_transcolor == pixels_screen_buffer[i]))
                    {
                        pixels_screen_buffer[i] = pixels_screen[i];
                    }
                                                            
                    GifColorType const* entry = &colormap->Colors[pixels_screen_buffer[i]];
                    val->d.r = entry->Red;
                    val->d.g = entry->Green;
                    val->d.b = entry->Blue;
                    val->d.a = 0xFF;
                }
                
                // save buffer to screen.
                memcpy(pixels_screen, pixels_screen_buffer, cnt_pixels_screen * sizeof(GifPixelType));
                
                CGImageRef img = WCGLoadPixelsImage(rgba_buf, ft->SWidth, ft->SHeight); 
                
                GifImage* gif_img = [[GifImage alloc] init];
                gif_img.image = img;
                gif_img.delay = lst_delay;
                [ret_images addObject:gif_img];
                [gif_img release];

                CGImageRelease(img);
                
                free(rgba_buf);
            } break;
            case EXTENSION_RECORD_TYPE:
            {
                int extcode;
                GifByteType* ext;
                sta = DGifGetExtension(ft, &extcode, &ext);
                
                while ((sta != GIF_ERROR) &&
                       ext)
                {
                    switch (extcode)
                    {
                        case COMMENT_EXT_FUNC_CODE:
                        {
                            PASS;
                        } break;
                        case GRAPHICS_EXT_FUNC_CODE:
                        {
                            if (ext[0] != 4)
                                continue;
                            
                            // get transparent.
                            if (ext[1] & 0x1)
                                lst_transcolor = ext[4];
                            else
                                lst_transcolor = -1;
                            // get delay time.
                            lst_delay = (ext[3] << 8 | ext[2]) * 10;       
                            
                        } break;
                        case PLAINTEXT_EXT_FUNC_CODE:
                        {
                            PASS;
                        } break;
                        case APPLICATION_EXT_FUNC_CODE:
                        {
                            PASS;
                        } break;                            
                    };
                    
                    sta = DGifGetExtensionNext(ft, &ext);
                }
            } break;
            case SCREEN_DESC_RECORD_TYPE:
            {
                sta = DGifGetScreenDesc(ft);
            } break;
            default:
            {
                trace_msg(@"unknown gif type.");
            } break;
        }
        
    } while (sta != GIF_ERROR);
    
    DGifCloseFile(ft);
    free(pixels_screen);
    free(pixels_screen_buffer);
    
    [NNTObject refobjSet:&images ref:ret_images];
    
    [ret_images release];
    
    return sta != GIF_ERROR || [ret_images count];
}

@end

NNT_END_OBJC