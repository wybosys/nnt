
# ifndef __NNT_UIKIT_UIWAITING_228AB52D1F4E492A9F0193A745B4E27F_H_INCLUDED
# define __NNT_UIKIT_UIWAITING_228AB52D1F4E492A9F0193A745B4E27F_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface UIWaitingPopup : NNTObject {
    UIAlertView* _alert;
}

+ (id)shared;
- (void)show;
- (void)hide;

@end

@interface UIWaitingOverlap : NNTObject {
    UIView* _hud;
}

+ (id)shared;
- (void)show;
- (void)hide;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)
NNT_BEGIN_NS(waiting)

class Popup
{
public:
    
    static void Open()
    {
        [[UIWaitingPopup shared] show];
    }
    
    static void Close()
    {
        [[UIWaitingPopup shared] hide];
    }
};

class Overlap
{
public:
    
    static void Open()
    {
        [[UIWaitingOverlap shared] show];
    }
    
    static void Close()
    {
        [[UIWaitingOverlap shared] hide];
    }
    
};

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif