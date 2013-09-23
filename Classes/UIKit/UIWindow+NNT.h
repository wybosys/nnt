
# ifndef __NNT_UIKIT_UIWINDOW_0FF9A4A16B9A4C748F0767B40B61148D_H_INCLUDED
# define __NNT_UIKIT_UIWINDOW_0FF9A4A16B9A4C748F0767B40B61148D_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface UIWindow (NNT)

//! get bounds with screen's coordinate.
- (CGRect)boundsOnScreen;

//! get frame with screen's coordinate.
- (CGRect)frameOnScreen;

//! location in screen's coordinate.
- (CGRect)locationIn:(UIView*)view;

//! offset in screen's coordinate.
- (void)offsetX:(int)x Y:(int)y;

@end

@interface NNTUIWindow : UIWindow {
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

@end

NNT_EXTERN signal_t kSignalBecomeKey;
NNT_EXTERN signal_t kSignalResignKey;

NNTDECL_CATEGORY(UIWindow, NNT);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "UIControl+NNT.h"

NNT_BEGIN_HEADER_CXX

class Application;

NNT_BEGIN_NS(ui)

class Window
: public ui::Control<Window, NNTUIWindow>
{   
    typedef ui::Control<Window, NNTUIWindow> super;    
    NNTDECL_NOCOPY(Window);
    
public:    
        
    Window(UIWindow* win = nil)
    : super((NNTUIWindow*)win)
    {
        PASS;
    }
    
    ~Window()
    {
        PASS;
    }
    
    void bind(objc_type* win)
    {
        super::_set(win);
    }
    
protected:

    friend class Application;
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif