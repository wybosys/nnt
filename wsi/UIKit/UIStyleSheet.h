
# ifndef __WSI_UI_STYLESHEET_B3000D00D8644A85874C9CF7E047E872_H_INCLUDED
# define __WSI_UI_STYLESHEET_B3000D00D8644A85874C9CF7E047E872_H_INCLUDED

# import "../Graphic/styles/CGStyle.h"

WSI_BEGIN_HEADER_OBJC

WSI_EXTERN NSString* kStyleBackground;

@interface UIStyleSheet : WCGStyleSheet

@property (nonatomic, retain) WCGFill* backgroundFill;

@end

WSI_END_HEADER_OBJC

# endif