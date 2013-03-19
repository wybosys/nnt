
# ifndef __WSI_UIKIT_NSWINDOW_27BE1DCDAA73403293DDC9A4F580AD88_H_INCLUDED
# define __WSI_UIKIT_NSWINDOW_27BE1DCDAA73403293DDC9A4F580AD88_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface NSWindow (WSI)

- (id)initWithFrame:(NSRect)frame;
- (id)initWithZero;

@end

@interface WSINSWindow : NSWindow {
    WSIOBJECT_DECL;
    
    BOOL keyWindow;
}

WSIOBJECT_PROP;

@property (nonatomic, assign) BOOL keyWindow;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "WSIUIObject.h"

WSI_BEGIN_HEADER_CXX

class Application;

WSI_BEGIN_NS(ui)

class Window
: public Object<Window, NSWindow>
{
    typedef Object<Window, NSWindow> super;
    friend class Application;
    
public:
    
    Window()
    {
        PASS;
    }
    
    Window(NSWindow* r)
    : super(r)
    {
        PASS;
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif