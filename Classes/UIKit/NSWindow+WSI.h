
# ifndef __NNT_UIKIT_NSWINDOW_27BE1DCDAA73403293DDC9A4F580AD88_H_INCLUDED
# define __NNT_UIKIT_NSWINDOW_27BE1DCDAA73403293DDC9A4F580AD88_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NSWindow (NNT)

- (id)initWithFrame:(NSRect)frame;
- (id)initWithZero;

@end

@interface NNTNSWindow : NSWindow {
    NNTOBJECT_DECL;
    
    BOOL keyWindow;
}

NNTOBJECT_PROP;

@property (nonatomic, assign) BOOL keyWindow;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "NNTUIObject.h"

NNT_BEGIN_HEADER_CXX

class Application;

NNT_BEGIN_NS(ui)

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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif