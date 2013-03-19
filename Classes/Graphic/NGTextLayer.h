
# ifndef __NNT_UIKIT_CATEXTLAYER_A0045FCE78F44B0BA9AAE5679E6C64C2_H_INCLUDED
# define __NNT_UIKIT_CATEXTLAYER_A0045FCE78F44B0BA9AAE5679E6C64C2_H_INCLUDED

# include "NGLayer.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NgTextStyle);

@interface NgTextLayer : NgLayer {
    
    id string;
    NgTextStyle *textStyle;
    
}

@property(copy) id string;
@property(nonatomic, retain) NgTextStyle *textStyle;

@end

NNT_END_HEADER_OBJC

# endif