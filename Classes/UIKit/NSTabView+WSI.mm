
# import "Core.h"
# import "NSTabView+WSI.h"
# import "NSViewController+WSI.h"

WSI_BEGIN_OBJC

@interface WSINSTabView ()

@property (nonatomic, assign) WSINSViewController* selectedViewController;

@end

@implementation WSINSTabView

@synthesize viewControllers;
@synthesize selectedViewController;

- (void)dealloc {
    zero_release(viewControllers);
    [super dealloc];
}

- (void)setViewControllers:(NSArray *)arr {
    for (WSINSViewController* ctlr in viewControllers) {
        if (ctlr.view.superview)
            [ctlr.view removeFromSuperview];
    }
    
    [WSIObject refobjSet:&viewControllers ref:arr];
    
    [self clear];
    for (WSINSViewController* ctlr in viewControllers) {
        NSTabViewItem* item = [[NSTabViewItem alloc] initWithIdentifier:ctlr.identity];
        [item setLabel:ctlr.title];
        [item setView:ctlr.view];
        [self addTabViewItem:item];
        [item release];
    }
}

- (void)clear {
    NSArray* items = [self tabViewItems];
    for (NSTabViewItem* each in items) {
        [self removeTabViewItem:each];
    }
}

- (WSINSViewController*)findControllerByItem:(NSTabViewItem*)item {
    for (WSINSViewController* ctlr in viewControllers) {
        if (item.view == ctlr.view)
            return ctlr;
    }
    return nil;
}

- (WSINSViewController*)findControllerByIdentity:(NSString*)identity {
    for (WSINSViewController* ctlr in viewControllers) {
        if ([identity isEqualToString:ctlr.identity])
            return ctlr;
    }
    return nil;
}

@end

@implementation nstabview_delegate

- (BOOL)tabView:(WSINSTabView *)tabView shouldSelectTabViewItem:(NSTabViewItem *)tabViewItem {
    return YES;
}

- (void)tabView:(WSINSTabView *)tabView willSelectTabViewItem:(NSTabViewItem *)tabViewItem {
    _prev_ctlr = [tabView findControllerByItem:tabView.selectedTabViewItem];
    WSINSViewController* next = [tabView findControllerByItem:tabViewItem];
    [_prev_ctlr viewWillDisappear];
    [next viewWillAppear];
}

- (void)tabView:(WSINSTabView *)tabView didSelectTabViewItem:(NSTabViewItem *)tabViewItem {
    [_prev_ctlr viewDidDisappear];
    WSINSViewController* next = [tabView findControllerByItem:tabViewItem];
    [next viewDidAppear];
    tabView.selectedViewController = next;
    
    //target->emit(kSignalSelectChanged, next);
}

- (void)tabViewDidChangeNumberOfTabViewItems:(NSTabView *)tabView {
    PASS;
}

@end

WSI_END_OBJC