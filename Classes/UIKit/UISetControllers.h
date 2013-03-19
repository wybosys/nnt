
# ifndef __NNT_UIKIT_SETCONTROLLERS_A043447233E54EC0BC3B92F704F3AC6D_H_INCLUDED
# define __NNT_UIKIT_SETCONTROLLERS_A043447233E54EC0BC3B92F704F3AC6D_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface UISetControllers : NNTUIViewController {
    
    //! set for all controller.
    NSMutableSet* _set;
    
    //! current controller.
    UIViewController* _current;
    
    //! hold other invisible controller.
    BOOL _holdOthers;
}

@property (nonatomic, retain) NSMutableSet* set;
@property (nonatomic, readonly) UIViewController* current;
@property (nonatomic, assign) BOOL holdOthers;

//! add new controller and visible.
- (void)add:(UIViewController*)ctlr;

@end

NNT_EXTERN signal_t kSignalItemInserted;
NNT_EXTERN signal_t kSignalItemRemoved;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "UIViewController+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class SetControllers
: public SimpleController<SetControllers, 
UISetControllers, 
NNTUIView>
{
public:
    
    SetControllers()
    {
        PASS;
    }
    
    template <typename ctlrT>
    void add(ctlrT const& ctlr)
    {
        wtl::const_pointer<ctlrT> ptr(ctlr);
        [this->_self add:*ptr];
    }
    
    void* current() const
    {
        return this->_self.current;
    }
    
    void set_hold(bool val)
    {
        this->_self.holdOthers = val;
    }
    
    bool is_holdothers() const
    {
        return this->_self.holdOthers;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif