
# ifndef __NNT_UIKIT_UIVALUEPICKERVIEW_7EF674ECBA9242D394FEFE9F30630CAB_H_INCLUDED
# define __NNT_UIKIT_UIVALUEPICKERVIEW_7EF674ECBA9242D394FEFE9F30630CAB_H_INCLUDED

# import "UIView+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NNTUIButton);

@interface UIValuePickerView : NNTUIView {
    
    UIPickerView *picker;
    UIBevelButton *btnInc;
    UIBevelButton *btnDec;
    
}

@property (nonatomic, retain) UIPickerView *picker;
@property (nonatomic, retain) UIBevelButton *btnInc, *btnDec;

@end

NNT_END_HEADER_OBJC

# endif