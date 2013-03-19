
# import "Core.h"
# import "UISearchBar+WSI.h"

WSI_BEGIN_OBJC

signal_t kSignalSearchClicked = @"::wsi::ui::clicked::search";
signal_t kSignalBookmarkClicked = @"::wsi::ui::clicked::bookmark";
signal_t kSignalCancelClicked = @"::wsi::ui::clicked::cancel";
signal_t kSignalResultsClicked = @"::wsi::ui::clicked::results";
signal_t kSignalBeginEditing = @"::wsi::ui::editing::begin";
signal_t kSignalEndEditing = @"::wsi::ui::editing::end";

@interface WSIUISearchBar ()

- (void)__init;

@end

@implementation WSIUISearchBar

WSIOBJECT_IMPL_NOSIGNALS;

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
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    WSIEVENT_SIGNAL(kSignalSearchClicked)
    WSIEVENT_SIGNAL(kSignalBookmarkClicked)
    WSIEVENT_SIGNAL(kSignalCancelClicked)
    WSIEVENT_SIGNAL(kSignalResultsClicked)
    WSIEVENT_SIGNAL(kSignalBeginEditing)
    WSIEVENT_SIGNAL(kSignalEndEditing)
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

WSI_END_OBJC