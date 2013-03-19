
# ifndef __WSI_UIKIT_STACKCONTROLLERS_327512831325431E8DDBF046AD07B377_H_INCLUDED
# define __WSI_UIKIT_STACKCONTROLLERS_327512831325431E8DDBF046AD07B377_H_INCLUDED

# import "UIViewController+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface UIStackControllers : WSIUIViewController {
    
    //! set for all controller.
    NSMutableArray* _stack;
    
}

@property (nonatomic, retain) NSMutableArray* stack;
@property (nonatomic, assign) BOOL holdOthers;

- (void)add:(UIViewController*)ctlr;
- (UIViewController*)pop;

@end

WSI_EXTERN signal_t kSignalItemInserted;
WSI_EXTERN signal_t kSignalItemRemoved;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class StackControllers
: public SimpleController<StackControllers,
UIStackControllers,
WSIUIView>
{
public:
    
    StackControllers()
    {
        PASS;
    }
    
    template <typename ctlrT>
    void add(ctlrT const& ctlr)
    {
        wtl::const_pointer<ctlrT> ptr(ctlr);
        [this->_self add:*ptr];
    }
    
    void pop()
    {
        [this->_self pop];
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
