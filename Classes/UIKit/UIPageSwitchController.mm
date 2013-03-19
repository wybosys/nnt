
# import "Core.h"
# import "UIPageSwitchController.h"

NNT_BEGIN_OBJC

signal_t kSignalPageCreate = @"::wsi::uikit::page::create";

@implementation UIPageSwitchController

@synthesize pageClass, numberOfPages;

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalPageCreate)
NNTEVENT_END

- (UISwitchPage*)previous_page:(UISwitchPage *)__page {
    if (0 == [self index_of:__page]) return nil;
    UISwitchPage *page = [self page_at:[self index_of:__page] - 1];
    return page;
}

- (UISwitchPage*)next_page:(UISwitchPage *)__page {
    if (__page == nil)
        return nil;
    
    UISwitchPage* page = nil;
    uindex idx = [self index_of:__page];
    if (idx + 1 >= self.numberOfPages) {
        return nil;
    }
    
    if ([self count] == idx + 1) {
        page = [[pageClass alloc] init];
        [self add_page:page];
        safe_release(page);
        
        // emit the signal.
        [self emit:kSignalPageCreate result:page];
        
    } else {
        page = [self page_at:idx + 1];
    }
    
    return page;
}

- (UISwitchPage*)prefetchNextPage:(UISwitchController *)__ctl curpage:(UISwitchPage *)__cur {
    return [self next_page:__cur];
}

- (UISwitchPage*)prefetchPrePage:(UISwitchController *)__ctl curpage:(UISwitchPage *)__cur {
    return [self previous_page:__cur];
}

- (void)instanceRootPage {
    if (self.numberOfPages == 0) {
        trace_msg(@"skip instace root page, because the numberOfPage is 0.");
        return;
    }
    
    UISwitchPage* page = [[pageClass alloc] init];    
    
    // add to switch.
    [self add_page:page];
    [self set_page:page];
    
    // event.
    [self emit:kSignalPageCreate result:page];
    
    safe_release(page);
}

- (void)clear {
    [super clear];
    self.numberOfPages = 0;
}

@end

_CXXCONTROLLER_IMPL(UIPageSwitchController);

NNT_END_OBJC