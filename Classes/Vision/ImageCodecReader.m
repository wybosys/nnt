
# import "Core.h"
# import "ImageCodecReader.h"
# import "../../contrib/libpng/png.h"
# import "WSIResource.h"
# import "../../contrib/zbar/include/zbar.h"

WSI_BEGIN_OBJC

@implementation ImageCodecReader

bool _png_getdata (NSString *name,
                   int *width, int *height,
                   byte **raw)
{
    name = [WSIResource PathOf:name];
    FILE *file = fopen(name.UTF8String, "rb");
    if(!file)
        return false;
    png_structp png =
    png_create_read_struct(PNG_LIBPNG_VER_STRING,
                           NULL, NULL, NULL);
    if(!png)
        return false;
    if(setjmp(png_jmpbuf(png)))
        return false;
    png_infop info = png_create_info_struct(png);
    if(!info)
        return false;
    png_init_io(png, file);
    png_read_info(png, info);
    /* configure for 8bpp grayscale input */
    int color = png_get_color_type(png, info);
    int bits = png_get_bit_depth(png, info);
    if(color & PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);
    if(color == PNG_COLOR_TYPE_GRAY && bits < 8)
        png_set_expand_gray_1_2_4_to_8(png);
    if(bits == 16)
        png_set_strip_16(png);
    if(color & PNG_COLOR_MASK_ALPHA)
        png_set_strip_alpha(png);
    if(color & PNG_COLOR_MASK_COLOR)
        png_set_rgb_to_gray_fixed(png, 1, -1, -1);
    /* allocate image */
    *width = png_get_image_width(png, info);
    *height = png_get_image_height(png, info);
    *raw = (byte*)malloc(*width * *height);
    png_bytep rows[*height];
    int i;
    for(i = 0; i < *height; i++)
        rows[i] = *raw + (*width * i);
    png_read_image(png, rows);
    fclose(file);
    return true;
}

- (NSData*)readRaw:(byte *)raw dlen:(uint)dlen width:(uint)width height:(uint)height {
# ifdef WSI_DEBUG

    if (dlen != (width * height))
        trace_msg(@"length of grayscaled data is not equal to image's size.");
    
# endif
    
    /* create a reader */
    zbar_image_scanner_t *scanner = zbar_image_scanner_create();
    
    /* configure the reader */
    zbar_image_scanner_set_config(scanner, 0, ZBAR_CFG_ENABLE, 1);
    
    /* wrap image data */
    zbar_image_t *image = zbar_image_create();
    zbar_image_set_format(image, *(int*)"Y800");
    zbar_image_set_size(image, width, height);
    //zbar_image_set_data(image, raw, width * height, 0/*zbar_image_free_data*/);
    zbar_image_set_data(image, raw, dlen, NULL);
    
    /* scan the image for barcodes */
    //int n = 
    zbar_scan_image(scanner, image);        
    
    // alloc data.
    NSMutableData* ret = NULL;
    
    /* extract results */
    const zbar_symbol_t *symbol = zbar_image_first_symbol(image);
    
    if (symbol)
        ret = [NSMutableData data];
    
    for(; symbol; symbol = zbar_symbol_next(symbol)) {
        /* do something useful with results */
        //zbar_symbol_type_t typ = 
        zbar_symbol_get_type(symbol);
        const char *data = zbar_symbol_get_data(symbol);
        //printf("decoded %s symbol \"%s\"\n",
        //       zbar_get_symbol_name(typ), data);
        [ret appendBytes:data length:strlen(data)];
    }
    
    /* clean up */
    zbar_image_destroy(image);
    zbar_image_scanner_destroy(scanner);
    
    return ret;
}

- (NSData*)readPNG:(NSString*)file {
    /* obtain image data */
    int width = 0, height = 0;
    byte *raw = NULL;
    if (_png_getdata(file, &width, &height, &raw) == false )
        return nil;
    
    NSData* ret = [self readRaw:raw dlen:(width*height) width:width height:height];
    
    free(raw);
    
    return ret;
}

@end

WSI_END_OBJC