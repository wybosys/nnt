
# ifndef __NNT_UIKIT_STACKCONTROLLERS_327512831325431E8DDBF046AD07B377_H_INCLUDED
# define __NNT_UIKIT_STACKCONTROLLERS_327512831325431E8DDBF046AD07B377_H_INCLUDED

# import "UIViewController+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface UIStackControllers : NNTUIViewController {
    
    //! set for all controller.
    NSMutableArray* _stack;
    
}

@property (nonatomic, retain) NSMutableArray* stack;
@property (nonatomic, assign) BOOL holdOthers;

- (void)add:(UIViewController*)ctlr;
- (UIViewController*)pop;

@end

NNT_EXTERN signal_t kSignalItemInserted;
NNT_EXTERN signal_t kSignalItemRemoved;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class StackControllers
: public SimpleController<StackControllers,
UIStackControllers,
NNTUIView>
{
public:
    
    StackControllers()
    {
        PASS;
    }
    
    template <typename ctlrT>
    void add(ctlrT const& ctlr)
    {
        ntl::const_pointer<ctlrT> ptr(ctlr);
        [this->_self add:*ptr];
    }
    
    void pop()
    {
        [this->_self pop];
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
