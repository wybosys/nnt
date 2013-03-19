
# ifndef __NNT_UIKIT_GESTURE_73FC5FF59BC44842A00F9DB0EA535DB6_H_INCLUDED
# define __NNT_UIKIT_GESTURE_73FC5FF59BC44842A00F9DB0EA535DB6_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NNTUISwipeGestureRecognizer : UISwipeGestureRecognizer {
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

@end

@interface NNTUITapGestureRecognizer : UITapGestureRecognizer {
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

@end

@interface NNTUIPinchGestureRecognizer : UIPinchGestureRecognizer {
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

@end

@interface NNTUIRotationGestureRecognizer : UIRotationGestureRecognizer {
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

@end

@interface NNTUIPanGestureRecognizer : UIPanGestureRecognizer {
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

@end

@interface NNTUILongPressGestureRecognizer : UILongPressGestureRecognizer {
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

@end

NNT_EXTERN signal_t kSignalGestureActive;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)
NNT_BEGIN_NS(gesture)

NNT_BEGIN_NS(tpl)

template <typename implT, typename gesT>
class Gesture
: public Object<implT, gesT>
{
public:
    
    Gesture()
    {
        PASS;
    }
    
};

NNT_END_NS

class Swipe
: public tpl::Gesture<Swipe, NNTUISwipeGestureRecognizer>
{
public:
    
    Swipe()
    {
        PASS;
    }
    
    void set(UISwipeGestureRecognizerDirection dir)
    {
        this->_self.direction = dir;
    }
    
    void set(Fingers const& fg = finger::_1)
    {
        this->_self.numberOfTouchesRequired = fg;
    }
    
};

class Tap
: public tpl::Gesture<Tap, NNTUITapGestureRecognizer>
{
public:
    
    Tap()
    {
        PASS;
    }
    
};

class Pinch
: public tpl::Gesture<Pinch, NNTUIPinchGestureRecognizer>
{
public:
    
    Pinch()
    {
        PASS;
    }
    
};

class Pan
: public tpl::Gesture<Pan, NNTUIPanGestureRecognizer>
{
public:
    
    Pan()
    {
        PASS;
    }
    
};

class Rotation
: public tpl::Gesture<Rotation, NNTUIRotationGestureRecognizer>
{
public:
    
    Rotation()
    {
        PASS;
    }
    
};

class LongPress
: public tpl::Gesture<LongPress, NNTUILongPressGestureRecognizer>
{
public:
    
    LongPress()
    {
        PASS;
    }
    
};

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
