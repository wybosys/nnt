
# ifndef __WSI_UIANIMATION_35CB22361B2A40B3896936580C639798_H_INCLUDED
# define __WSI_UIANIMATION_35CB22361B2A40B3896936580C639798_H_INCLUDED

# ifdef WSI_CXX

# include "WSIUIObject.h"

WSI_BEGIN_HEADER_OBJC

@interface WSIUIAnimation : WSIObject {
    NSString* _name;
    void* _context;
    BOOL _commited;
    real _duration;
    
# ifdef WSI_BLOCKS
    void (^_run)();
    void (^_finish)();
# endif
    
}

@property (nonatomic, copy) NSString* name;
@property (nonatomic, assign) void* context;
@property (nonatomic, readonly) BOOL commited;
@property (nonatomic, assign) real duration;

# ifdef WSI_BLOCKS

@property (nonatomic, copy) void (^run)();
@property (nonatomic, copy) void (^finish)();

# endif

- (void)begin;
- (void)commit;

@end

WSI_EXTERN signal_t kSignalAnimationStart;
WSI_EXTERN signal_t kSignalAnimationRun;
WSI_EXTERN signal_t kSignalAnimationStop;

WSI_END_HEADER_OBJC

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class Animation
: public ns::Object<WSIUIAnimation>
{
    typedef ns::Object<WSIUIAnimation> super;
    
public:
        
    Animation(ns::String const& name = ns::null_string, void* ctx = NULL)
    {
        this->_self.name = name;
        this->_self.context = ctx;
        
        [this->_self begin];
    }        
    
    ~Animation()
    {
        PASS;
    }
    
    void set_duration(real sec)
    {
        this->_self.duration = sec;
    }
    
    void set_transition(id _view, UIViewAnimationTransition _mode, bool _cache = true)
    {
        [UIView setAnimationTransition:_mode forView:_view cache:_cache];
    }
    
    void commit()
    {
        [this->_self commit];
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif