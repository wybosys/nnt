
# import "Core.h"
# import "UISearchDisplayController+WSI.h"

WSI_BEGIN_OBJC

@implementation WSIUISearchDisplayController

WSIOBJECT_IMPL;

@synthesize accordingView = _accordingView;

- (id)initWithSearchBar:(UISearchBar *)searchBar contentsController:(UIViewController *)viewController {
    self = [super initWithSearchBar:searchBar contentsController:viewController];
    
    self.delegate = self;
    
    return self;
}

- (void)dealloc {
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

- (void)viewDidLoad {
    PASS;
}

# pragma mark delegate.

// when we start/end showing the search UI
- (void) searchDisplayControllerWillBeginSearch:(UISearchDisplayController *)controller {
    if (_accordingView) {
        self.searchContentsController.view.frame = _accordingView.frame;
        [_accordingView.superview addSubview:self.searchContentsController.view];
        //self.searchContentsController.view.hidden = NO;
    }
}

- (void) searchDisplayControllerDidBeginSearch:(UISearchDisplayController *)controller {
    
}

- (void) searchDisplayControllerWillEndSearch:(UISearchDisplayController *)controller {

}

- (void) searchDisplayControllerDidEndSearch:(UISearchDisplayController *)controller {
    if (_accordingView) {
        //self.searchContentsController.view.hidden = YES;
        [self.searchContentsController.view removeFromSuperview];
    }
}

// called when the table is created destroyed, shown or hidden. configure as necessary.
- (void)searchDisplayController:(UISearchDisplayController *)controller didLoadSearchResultsTableView:(UITableView *)tableView {
    
}

- (void)searchDisplayController:(UISearchDisplayController *)controller willUnloadSearchResultsTableView:(UITableView *)tableView {
    
}

// called when table is shown/hidden
- (void)searchDisplayController:(UISearchDisplayController *)controller willShowSearchResultsTableView:(UITableView *)tableView {

}

- (void)searchDisplayController:(UISearchDisplayController *)controller didShowSearchResultsTableView:(UITableView *)tableView {
    
}

- (void)searchDisplayController:(UISearchDisplayController *)controller willHideSearchResultsTableView:(UITableView *)tableView {
    
}

- (void)searchDisplayController:(UISearchDisplayController *)controller didHideSearchResultsTableView:(UITableView *)tableView {

}

// return YES to reload table. called when search string/option changes. convenience methods on top UISearchBar delegate methods
- (BOOL)searchDisplayController:(UISearchDisplayController *)controller shouldReloadTableForSearchString:(NSString *)searchString {
    return YES;
}

- (BOOL)searchDisplayController:(UISearchDisplayController *)controller shouldReloadTableForSearchScope:(NSInteger)searchOption {
    return YES;
}

@end

using namespace ::wsi;

_CXXCONTROLLER_IMPL_BEGIN(WSIUISearchDisplayController)

- (BOOL)searchDisplayController:(UISearchDisplayController *)controller shouldReloadTableForSearchString:(NSString *)searchString {
    ui::tpl::ISearchDisplayController* ctlr = dynamic_cast<ui::tpl::ISearchDisplayController*>(self._cxxobj);
    return ctlr->searchByString(searchString);
}

- (BOOL)searchDisplayController:(UISearchDisplayController *)controller shouldReloadTableForSearchScope:(NSInteger)searchOption {
    ui::tpl::ISearchDisplayController* ctlr = dynamic_cast<ui::tpl::ISearchDisplayController*>(self._cxxobj);
    return ctlr->searchByScope(searchOption);
}

_CXXCONTROLLER_IMPL_END

WSI_END_OBJC
