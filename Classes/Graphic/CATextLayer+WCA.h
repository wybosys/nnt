
# ifndef __WSI_UIKIT_CATEXTLAYER_A0045FCE78F44B0BA9AAE5679E6C64C2_H_INCLUDED
# define __WSI_UIKIT_CATEXTLAYER_A0045FCE78F44B0BA9AAE5679E6C64C2_H_INCLUDED

# include "WCALayer.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WCGTextStyle);

@interface WCATextLayer : WCALayer {
    
    id string;
    WCGTextStyle *textStyle;
    
}

@property(copy) id string;
@property(nonatomic, retain) WCGTextStyle *textStyle;

@end

WSI_END_HEADER_OBJC

# endif