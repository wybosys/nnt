
# import "Core.h"
# import "UISearchBar+NNT.h"

NNT_BEGIN_OBJC

signal_t kSignalSearchClicked = @"::nnt::ui::clicked::search";
signal_t kSignalBookmarkClicked = @"::nnt::ui::clicked::bookmark";
signal_t kSignalCancelClicked = @"::nnt::ui::clicked::cancel";
signal_t kSignalResultsClicked = @"::nnt::ui::clicked::results";
signal_t kSignalBeginEditing = @"::nnt::ui::editing::begin";
signal_t kSignalEndEditing = @"::nnt::ui::editing::end";

@interface NNTUISearchBar ()

- (void)__init;

@end

@implementation NNTUISearchBar

NNTOBJECT_IMPL_NOSIGNALS;

- (void)__init {
    self.delegate = self;
}

- (id)init {
    self = [super init];
    [self __init];
    return self;
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    [self __init];
    return self;
}

- (id)initWithCoder:(NSCoder *)aDecoder {
    self = [super initWithCoder:aDecoder];
    [self __init];
    return self;
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    NNTEVENT_SIGNAL(kSignalSearchClicked)
    NNTEVENT_SIGNAL(kSignalBookmarkClicked)
    NNTEVENT_SIGNAL(kSignalCancelClicked)
    NNTEVENT_SIGNAL(kSignalResultsClicked)
    NNTEVENT_SIGNAL(kSignalBeginEditing)
    NNTEVENT_SIGNAL(kSignalEndEditing)
}

- (void)visibleCancelButton {
    self.showsCancelButton = YES;
}

- (void)invisibleCancelButton {
    self.showsCancelButton = NO;
}

# pragma mark delegate.

- (BOOL)searchBarShouldBeginEditing:(UISearchBar *)searchBar {
    return YES;
}

- (void)searchBarTextDidBeginEditing:(UISearchBar *)searchBar {
    [self emit:kSignalBeginEditing];
}

- (BOOL)searchBarShouldEndEditing:(UISearchBar *)searchBar {
    return YES;
}

- (void)searchBarTextDidEndEditing:(UISearchBar *)searchBar {
    [self emit:kSignalEndEditing];
}

- (void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText {
    PASS;    
}

- (BOOL)searchBar:(UISearchBar *)searchBar shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text {
    return YES;
}

- (void)searchBarSearchButtonClicked:(UISearchBar *)searchBar {
    if (searchBar != self)
        return;
    
    [self emit:kSignalSearchClicked];
    [self resignFirstResponder];
}

- (void)searchBarBookmarkButtonClicked:(UISearchBar *)searchBar {
    if (searchBar != self)
        return;
    
    [self emit:kSignalBookmarkClicked];
    [self resignFirstResponder];
}

- (void)searchBarCancelButtonClicked:(UISearchBar *) searchBar {
    if (searchBar != self)
        return;
    
    [self emit:kSignalCancelClicked];
    [self resignFirstResponder];
}

- (void)searchBarResultsListButtonClicked:(UISearchBar *)searchBar {
    if (searchBar != self)
        return;
    
    [self emit:kSignalResultsClicked];
    [self resignFirstResponder];
}

@end

NNT_END_OBJC