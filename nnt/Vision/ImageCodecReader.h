
# ifndef __NNT_IMAGECODECREADER_70F56C4C8F0E46C79EF298F16C608E98_H_INCLUDED
# define __NNT_IMAGECODECREADER_70F56C4C8F0E46C79EF298F16C608E98_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

@interface ImageCodecReader : NNTObject

- (NSData*)readPNG:(NSString*)file;
- (NSData*)readRaw:(byte*)raw dlen:(uint)dlen width:(uint)width height:(uint)height;

@end

NNT_END_HEADER_OBJC

# endif

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX


NNT_END_HEADER_CXX

# endif

# endif