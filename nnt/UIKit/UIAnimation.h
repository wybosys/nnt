
# ifndef __NNT_UIANIMATION_35CB22361B2A40B3896936580C639798_H_INCLUDED
# define __NNT_UIANIMATION_35CB22361B2A40B3896936580C639798_H_INCLUDED

# ifdef NNT_CXX

# include "UIObject+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface NNTUIAnimation : NNTObject {
    NSString* _name;
    void* _context;
    BOOL _commited;
    real _duration;
    
# ifdef NNT_BLOCKS
    void (^_run)();
    void (^_finish)();
# endif
    
}

@property (nonatomic, copy) NSString* name;
@property (nonatomic, assign) void* context;
@property (nonatomic, readonly) BOOL commited;
@property (nonatomic, assign) real duration;

# ifdef NNT_BLOCKS

@property (nonatomic, copy) void (^run)();
@property (nonatomic, copy) void (^finish)();

# endif

- (void)begin;
- (void)commit;

@end

NNT_EXTERN signal_t kSignalAnimationStart;
NNT_EXTERN signal_t kSignalAnimationRun;
NNT_EXTERN signal_t kSignalAnimationStop;

NNT_END_HEADER_OBJC

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class Animation
: public ns::Object<NNTUIAnimation>
{
    typedef ns::Object<NNTUIAnimation> super;
    
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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif