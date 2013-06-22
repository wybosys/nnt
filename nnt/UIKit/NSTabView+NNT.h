
# ifndef __NNTNS_TABVIEW_4F1F2ADAF85C4C938078FD01034F2F91_H_INCLUDED
# define __NNTNS_TABVIEW_4F1F2ADAF85C4C938078FD01034F2F91_H_INCLUDED

# include "NSControl+NNT.h"
# include "NSViewController+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNT_EXTERN signal_t kSignalSelectChanged;

@interface NNTNSTabView : NSTabView {
    NSArray* viewControllers;
    NNTNSViewController* selectedViewController;
}

@property (nonatomic, retain) NSArray* viewControllers;
@property (nonatomic, readonly, assign) NNTNSViewController* selectedViewController;

- (void)clear;
- (NNTNSViewController*)findControllerByItem:(NSTabViewItem*)item;
- (NNTNSViewController*)findControllerByIdentity:(NSString*)identity;

@end

# ifdef NNT_CXX

@interface nstabview_delegate : cxxnsobject <NSTabViewDelegate> {
    NNTNSViewController* _prev_ctlr;
}

@end

# endif

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX NNT_BEGIN_NS(ui)

template <typename tabT = NNTNSTabView, typename delegateT = nstabview_delegate>
class TabView
: public Control<tabT, TabView<tabT> >
{
    typedef Control<tabT, TabView<tabT> > super;
    
public:
    
    TabView()
    {
        tabT* tab = [[tabT alloc] initWithZero];
        //_delegate = [[delegateT alloc] init];
        //_delegate.target = this;
        //tab.delegate = _delegate;
        
        this->_sethandle(tab);
        [tab release];
    }
    
    ~TabView()
    {
        //zero_release(_delegate);
    }
    
    //NNTEVENT_IMPLBEGIN_CXX(super)
    //NNTEVENT_SIGNAL_CXX(kSignalSelectChanged)
    //NNTEVENT_IMPLEND_CXX
        
    inline void set_controllers(::NSArray* arr)
    {
        this->hdl().viewControllers = arr;
    }
    
    inline sinteger index_of(NSTabViewItem* item) const
    {
        return [this->hdl() indexOfTabViewItem:item];
    }
    
    inline void clear()
    {
        [this->hdl() clear];
    }
    
    inline void select(NSTabViewItem* item)
    {
        [this->hdl() selectTabViewItem:item];
    }
    
    inline void select(uindex idx)
    {
        [this->hdl() selectTabViewItemAtIndex:idx];
    }
    
    inline void select(::NSString* identity)
    {
        [this->hdl() selectTabViewItemWithIdentifier:identity];
    }
    
    inline void select(NNTNSViewController* ctlr)
    {
        this->select(ctlr.identity);
    }

    inline NNTNSViewController* selected() const
    {
        return this->hdl().selectedViewController;
    }
    
protected:
    
    delegateT* _delegate;
    
};

NNT_END_NS NNT_END_HEADER_CXX

# endif

# endif