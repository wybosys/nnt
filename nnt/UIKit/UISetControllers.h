
# ifndef __WSI_UIKIT_SETCONTROLLERS_A043447233E54EC0BC3B92F704F3AC6D_H_INCLUDED
# define __WSI_UIKIT_SETCONTROLLERS_A043447233E54EC0BC3B92F704F3AC6D_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface UISetControllers : WSIUIViewController {
    
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

WSI_EXTERN signal_t kSignalItemInserted;
WSI_EXTERN signal_t kSignalItemRemoved;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "UIViewController+WSI.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class SetControllers
: public SimpleController<SetControllers, 
UISetControllers, 
WSIUIView>
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

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif