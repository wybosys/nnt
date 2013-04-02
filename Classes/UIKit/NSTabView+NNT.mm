
# import "Core.h"
# import "NSTabView+NNT.h"
# import "NSViewController+NNT.h"

NNT_BEGIN_OBJC

@interface NNTNSTabView ()

@property (nonatomic, assign) NNTNSViewController* selectedViewController;

@end

@implementation NNTNSTabView

@synthesize viewControllers;
@synthesize selectedViewController;

- (void)dealloc {
    zero_release(viewControllers);
    [super dealloc];
}

- (void)setViewControllers:(NSArray *)arr {
    for (NNTNSViewController* ctlr in viewControllers) {
        if (ctlr.view.superview)
            [ctlr.view removeFromSuperview];
    }
    
    [NNTObject refobjSet:&viewControllers ref:arr];
    
    [self clear];
    for (NNTNSViewController* ctlr in viewControllers) {
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

- (NNTNSViewController*)findControllerByItem:(NSTabViewItem*)item {
    for (NNTNSViewController* ctlr in viewControllers) {
        if (item.view == ctlr.view)
            return ctlr;
    }
    return nil;
}

- (NNTNSViewController*)findControllerByIdentity:(NSString*)identity {
    for (NNTNSViewController* ctlr in viewControllers) {
        if ([identity isEqualToString:ctlr.identity])
            return ctlr;
    }
    return nil;
}

@end

@implementation nstabview_delegate

- (BOOL)tabView:(NNTNSTabView *)tabView shouldSelectTabViewItem:(NSTabViewItem *)tabViewItem {
    return YES;
}

- (void)tabView:(NNTNSTabView *)tabView willSelectTabViewItem:(NSTabViewItem *)tabViewItem {
    _prev_ctlr = [tabView findControllerByItem:tabView.selectedTabViewItem];
    NNTNSViewController* next = [tabView findControllerByItem:tabViewItem];
    [_prev_ctlr viewWillDisappear];
    [next viewWillAppear];
}

- (void)tabView:(NNTNSTabView *)tabView didSelectTabViewItem:(NSTabViewItem *)tabViewItem {
    [_prev_ctlr viewDidDisappear];
    NNTNSViewController* next = [tabView findControllerByItem:tabViewItem];
    [next viewDidAppear];
    tabView.selectedViewController = next;
    
    //target->emit(kSignalSelectChanged, next);
}

- (void)tabViewDidChangeNumberOfTabViewItems:(NSTabView *)tabView {
    PASS;
}

@end

NNT_END_OBJC