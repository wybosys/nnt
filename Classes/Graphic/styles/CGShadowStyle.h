
# ifndef __NNT_CG_SHADOWSTYLE_F8F87F372CDC4A9396C576315BC1BC83_H_INCLUDED
# define __NNT_CG_SHADOWSTYLE_F8F87F372CDC4A9396C576315BC1BC83_H_INCLUDED

# import "CGStyle.h"

NNT_BEGIN_HEADER_OBJC

@interface WCGShadowStyle : WCGStyle {
    WCGColor*  _color;
    CGFloat   _blur;
    CGSize    _offset;
}

@property (nonatomic, retain) WCGColor*  color;
@property (nonatomic)         CGFloat   blur;
@property (nonatomic)         CGSize    offset;

@end

NNT_END_HEADER_OBJC

# endif