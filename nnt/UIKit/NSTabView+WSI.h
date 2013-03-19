
# ifndef __WSINS_TABVIEW_4F1F2ADAF85C4C938078FD01034F2F91_H_INCLUDED
# define __WSINS_TABVIEW_4F1F2ADAF85C4C938078FD01034F2F91_H_INCLUDED

# include "NSControl+WSI.h"
# include "NSViewController+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSI_EXTERN signal_t kSignalSelectChanged;

@interface WSINSTabView : NSTabView {
    NSArray* viewControllers;
    WSINSViewController* selectedViewController;
}

@property (nonatomic, retain) NSArray* viewControllers;
@property (nonatomic, readonly, assign) WSINSViewController* selectedViewController;

- (void)clear;
- (WSINSViewController*)findControllerByItem:(NSTabViewItem*)item;
- (WSINSViewController*)findControllerByIdentity:(NSString*)identity;

@end

# ifdef WSI_CXX

@interface nstabview_delegate : cxxnsobject <NSTabViewDelegate> {
    WSINSViewController* _prev_ctlr;
}

@end

# endif

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX WSI_BEGIN_NS(ui)

template <typename tabT = WSINSTabView, typename delegateT = nstabview_delegate>
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
    
    //WSIEVENT_IMPLBEGIN_CXX(super)
    //WSIEVENT_SIGNAL_CXX(kSignalSelectChanged)
    //WSIEVENT_IMPLEND_CXX
        
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
    
    inline void select(WSINSViewController* ctlr)
    {
        this->select(ctlr.identity);
    }

    inline WSINSViewController* selected() const
    {
        return this->hdl().selectedViewController;
    }
    
protected:
    
    delegateT* _delegate;
    
};

WSI_END_NS WSI_END_HEADER_CXX

# endif

# endif