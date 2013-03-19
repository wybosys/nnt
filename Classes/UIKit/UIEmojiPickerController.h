
# ifndef __EMOJICONTROLLER_D1FC21DD325445288D48C7CD77DF0CD4_H_INCLUDED
# define __EMOJICONTROLLER_D1FC21DD325445288D48C7CD77DF0CD4_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface UIEmojiPickerView : UISwitchView

@property (nonatomic, readonly) WSIUIPageControl *page;

@end

@interface UIEmojiPage : UIGridViewController

@end

@interface UIEmojiPickerController : UIPageSwitchController

@property (nonatomic, retain) NSMutableArray* emojis;

- (void)load_emoji;

@end

WSI_EXTERN signal_t kSignalEmojiSelected;

_CXXCONTROLLER_DECL(UIEmojiPickerController);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

#include "UIViewController+WSI.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class EmojiPickerController
: public SimpleController<
EmojiPickerController,
_CXXCONTROLLER(UIEmojiPickerController),
UIEmojiPickerView
>
{
    typedef SimpleController<
    EmojiPickerController,
    _CXXCONTROLLER(UIEmojiPickerController),
    UIEmojiPickerView
    > super;
    
public:
    
    void set_emojis(ns::MutableArray const emojis)
    {
        this->_self.emojis = emojis;
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif