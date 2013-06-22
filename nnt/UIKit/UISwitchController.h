
# ifndef __NNT_CONTROLLER_PAGESWITCH_D05081DE2CE44B5D9021E7765706C869_H_INCLUDED
# define __NNT_CONTROLLER_PAGESWITCH_D05081DE2CE44B5D9021E7765706C869_H_INCLUDED

# import "UISwitchView.h"
# import "UIViewController+NNT.h"

NNT_BEGIN_HEADER_OBJC

typedef NNTUIViewController UISwitchPage;

NNTDECL_PRIVATE_HEAD(UISwitchController);

enum {
    UISwitchTransitionSlide,
    UISwitchTransitionCurl,
    UISwitchTransitionNatureCurl,
};
typedef uint UISwitchTransition;

//! @interface UIPageSwitchDelegate
@protocol UISwitchDelegate <NSObject>

//! @function prefetch next page.
- (UISwitchPage*)prefetchNextPage:(UISwitchController*)__ctl curpage:(UISwitchPage*)__cur;

@optional

//! @function prefetch previous page.
- (UISwitchPage*)prefetchPrePage:(UISwitchController*)__ctl curpage:(UISwitchPage*)__cur;

//! @function test should switch from oldpage to newpage.
- (BOOL)shouldSwitchPage:(UISwitchController*)__ctl pre:(UISwitchPage*)page next:(UISwitchPage*)page;

//! @function after switch page.
- (void)didSwitchPage:(UISwitchController*)__ctl page:(UISwitchPage*)page;

@end

//! @class UIPageSwitchController
//! @brief for manage multi-pages view.
@interface UISwitchController : NNTUIViewController <UISwitchDelegate> {
    
    //! current page.
    UISwitchPage *cur_page;
    
    //! transition, default is slide.
    UISwitchTransition transition;
    
    //! number of gesture touches. default is 2.
    uint numberOfGestureTouches;
    
    NNTDECL_PRIVATE_EX(UISwitchController, d_ptr_ctr);
}

@property (nonatomic, readonly) UISwitchPage *cur_page;
@property (nonatomic, assign) id <UISwitchDelegate> delegate;
@property (nonatomic, assign) UISwitchTransition transition;
@property (nonatomic, assign) uint numberOfGestureTouches;

//! @function use the __view as root view.
- (id)init;
- (id)initWithView:(UISwitchView*)__view;

//! @function add a page, can not be nil.
- (void)add_page:(UISwitchPage*)__ctl;

//! @function set a page as current page, can be nil.
- (void)set_page:(UISwitchPage*)__ctl;
- (void)set_page:(UISwitchPage*)__ctl event:(BOOL)__evt;

//! @function get a page.
- (UISwitchPage*)page_at:(NSUInteger)__index;

//! @function get previous of page.
- (UISwitchPage*)previous_page:(UISwitchPage*)__page;

//! @function get next of page.
- (UISwitchPage*)next_page:(UISwitchPage*)__page;

//! @function index of page.
//! @return NSNotFound if failed
- (NSInteger)index_of:(UISwitchPage*)__ctl;

//! @function pages count.
- (NSUInteger)count;

//! @function get first page.
- (UISwitchPage*)first_page;

//! @function freeze interactive.
- (void)freeze_page;

//! @function thaw interactive.
- (void)thaw_page;

//! @function clear all page.
- (void)clear;

//! @function swap current page to taget page.
- (void)swap_page:(UISwitchPage*)__tgt;

@end

NNT_EXTERN signal_t kSignalSelectChanged;

NNT_END_HEADER_OBJC

# endif