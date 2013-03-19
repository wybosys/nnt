
# ifndef __WSI_UIKIT_UIWINDOW_0FF9A4A16B9A4C748F0767B40B61148D_H_INCLUDED
# define __WSI_UIKIT_UIWINDOW_0FF9A4A16B9A4C748F0767B40B61148D_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface UIWindow (WSI)

//! get bounds with screen's coordinate.
- (CGRect)boundsOnScreen;

//! get frame with screen's coordinate.
- (CGRect)frameOnScreen;

//! location in screen's coordinate.
- (CGRect)locationIn:(UIView*)view;

//! offset in screen's coordinate.
- (void)offsetX:(int)x Y:(int)y;

@end

@interface WSIUIWindow : UIWindow {
    WSIOBJECT_DECL;
}

WSIOBJECT_PROP;

@end

WSI_EXTERN signal_t kSignalBecomeKey;
WSI_EXTERN signal_t kSignalResignKey;

WSIDECL_CATEGORY(UIWindow, WSI);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "UIControl+WSI.h"

WSI_BEGIN_HEADER_CXX

class Application;

WSI_BEGIN_NS(ui)

class Window
: public ui::Control<Window, WSIUIWindow>
{   
    typedef ui::Control<Window, WSIUIWindow> super;    
    WSIDECL_NOCOPY(Window);
    
public:    
        
    Window(UIWindow* win = nil)
    : super((WSIUIWindow*)win)
    {
        PASS;
    }
    
    ~Window()
    {
        PASS;
    }

    friend class Application;
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif