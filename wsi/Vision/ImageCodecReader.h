
# ifndef __WSI_IMAGECODECREADER_70F56C4C8F0E46C79EF298F16C608E98_H_INCLUDED
# define __WSI_IMAGECODECREADER_70F56C4C8F0E46C79EF298F16C608E98_H_INCLUDED

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

@interface ImageCodecReader : WSIObject

- (NSData*)readPNG:(NSString*)file;
- (NSData*)readRaw:(byte*)raw dlen:(uint)dlen width:(uint)width height:(uint)height;

@end

WSI_END_HEADER_OBJC

# endif

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX


WSI_END_HEADER_CXX

# endif

# endif