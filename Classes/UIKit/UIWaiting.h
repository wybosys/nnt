
# ifndef __WSI_UIKIT_UIWAITING_228AB52D1F4E492A9F0193A745B4E27F_H_INCLUDED
# define __WSI_UIKIT_UIWAITING_228AB52D1F4E492A9F0193A745B4E27F_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface UIWaitingPopup : WSIObject {
    UIAlertView* _alert;
}

+ (id)shared;
- (void)show;
- (void)hide;

@end

@interface UIWaitingOverlap : WSIObject {
    UIView* _hud;
}

+ (id)shared;
- (void)show;
- (void)hide;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)
WSI_BEGIN_NS(waiting)

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

WSI_END_NS
WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif