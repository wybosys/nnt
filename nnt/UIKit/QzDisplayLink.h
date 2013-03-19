
# ifndef __WSI_QZ_DISPLAYLINK_17B5F597C50F4D71AEE00352C1EAE3D7_H_INCLUDED
# define __WSI_QZ_DISPLAYLINK_17B5F597C50F4D71AEE00352C1EAE3D7_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface UIDisplayLink : WSIObject {
    CADisplayLink* _ca;
}

@property (nonatomic, readonly) CADisplayLink* displayLink;

- (void)unhook;

@end

WSI_EXTERN signal_t kSignalDisplayLink;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(qz)

class DisplayLink
: public ns::Object<UIDisplayLink>
{
public:
    
    DisplayLink()
    {
        PASS;
    }
    
    void hook(ns::Runloop const& lp, ns::String const& mode = NSDefaultRunLoopMode)
    {
        [this->_self.displayLink addToRunLoop:lp forMode:mode];
    }
    
    void unhook()
    {
        [this->_self unhook];
    }
    
    CFTimeInterval timestamp() const
    {
        return this->_self.displayLink.timestamp;
    }
    
    CFTimeInterval duration() const
    {
        return this->_self.displayLink.duration;
    }
    
    bool is_paused() const
    {
        return this->_self.displayLink.paused;
    }
    
    void pause()
    {
        this->_self.displayLink.paused = YES;
    }
    
    void resume()
    {
        this->_self.displayLink.paused = NO;
    }
    
    NSInteger frameinterval() const
    {
        return this->_self.displayLink.frameInterval;
    }
    
    void set_frameinterval(uint val = 1)
    {
        this->_self.displayLink.frameInterval = val;
    }
        
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
