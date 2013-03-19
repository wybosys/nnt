
# ifndef __WSI_UIKIT_UIVALUEPICKERVIEW_7EF674ECBA9242D394FEFE9F30630CAB_H_INCLUDED
# define __WSI_UIKIT_UIVALUEPICKERVIEW_7EF674ECBA9242D394FEFE9F30630CAB_H_INCLUDED

# import "UIView+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WSIUIButton);

@interface UIValuePickerView : WSIUIView {
    
    UIPickerView *picker;
    UIBevelButton *btnInc;
    UIBevelButton *btnDec;
    
}

@property (nonatomic, retain) UIPickerView *picker;
@property (nonatomic, retain) UIBevelButton *btnInc, *btnDec;

@end

WSI_END_HEADER_OBJC

# endif