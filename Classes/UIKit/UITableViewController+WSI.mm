
# import "Core.h"
# import "UITableViewController+WSI.h"
# import "UITableView+WSI.h"
# import "UIViewController+WSI.h"
# import "UITableViewCell+WSI.h"

using namespace ::wsi;

WSI_BEGIN_OBJC

signal_t kSignalItemRemoving = @"::wsi::ui::item::removing";
signal_t kSignalItemRemoved = @"::wsi::ui::item::removed";
signal_t kSignalItemInserted = @"::wsi::ui::item::inserted";
signal_t kSignalItemMoved = @"::wsi::ui::item::moved";

NSUInteger kTableCellHeight = 44;

@interface WSIUITableView (hidden)

- (void)processHeaders;
- (void)scrollHeaders;

@end

@implementation WSIUITableViewController

@synthesize rowHeight = _rowHeight;
@synthesize tableViewStyle = _tableViewStyle;
@dynamic dataSource, delegate;
@dynamic tableView;
@synthesize datas = _datas;

- (id)init {
    self = [super init];
    
    _tableViewStyle = UITableViewStylePlain;
    _rowHeight = kTableCellHeight;
    
    return self;
}

- (id)initWithStyle:(UITableViewStyle)style {    
    self = [super init];

    _tableViewStyle = style;
    _rowHeight = kTableCellHeight;
    
    return self;
}

- (void)dealloc {
    zero_release(_datas);
    
    self.delegate = nil;
    self.dataSource = nil;
    
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalSelectChanged)
WSIEVENT_SIGNAL(kSignalItemRemoving)
WSIEVENT_SIGNAL(kSignalItemRemoved)
WSIEVENT_END

- (void)loadView {
    WSIUITableView *view = [[WSIUITableView alloc] initWithFrame:CGRectZero 
                                                           style:_tableViewStyle];
    self.view = view;
    [view release];
}

- (void)viewDidLoad {
    // call super.
    [super viewDidLoad];
    
    // set.
    WSIUITableView* table = (WSIUITableView*)self.view;
    if (table.dataSource == nil)
        table.dataSource = self;
    if (table.delegate == nil)
        table.delegate = self;
}

- (void)reloadData {
    [self.tableView reloadData];
}

- (void)setDataSource:(id<UITableViewDataSource>)obj {
    self.tableView.dataSource = obj;
}

- (id<UITableViewDataSource>)dataSource {
    return self.tableView.dataSource;
}

- (void)setDelegate:(id<UITableViewDelegate>)obj {
    self.tableView.delegate = obj;
}

- (id<UITableViewDelegate>)delegate {
    return self.tableView.delegate;
}

- (WSIUITableView*)tableView {
    return (WSIUITableView*)self.view;
}

# pragma mark delegate.

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [_datas count];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return _rowHeight;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    WSIUITableViewCell* cell = [WSIUITableViewCell cell];
    id obj = [_datas objectAtIndex:indexPath.row];
    if ([obj isKindOfClass:[NSString class]]) {
        cell.textLabel.text = (NSString*)obj;
    }
    return cell;
}

- (void)tableView:(UITableView *)_tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    WSIUITableViewCell* cell = (WSIUITableViewCell*)[_tableView cellForRowAtIndexPath:indexPath];
    [self emit:kSignalSelectChanged result:cell data:indexPath];
}

// delegate.

- (void)scrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate {    
    // old header.
    [self.tableView endPullMoreHeader];
    
    // headers.
    [self.tableView processHeaders];
}

- (void)scrollViewDidScroll:(UIScrollView *)scrollView {
    // old header.
    [self.tableView startPullMoreHeader];
    
    // headers.
    [self.tableView scrollHeaders];
}

@end

@implementation UINavigationTableViewController

@synthesize rootTable;

- (id)init {
    self = [super init];
    rootTable = nil;
    return self;
}

- (id)initWithRootTitle:(NSString*)title {
    self = [super initWithRootViewController:nil];
    if (self) {
        rootTable = [[WSIUITableViewController alloc] init];
        rootTable.title = title;
        [self pushViewController:rootTable animated:NO];
        [rootTable release];
    }
    return self;
}

@end

_CXXCONTROLLER_IMPL_BEGIN(WSIUITableViewController)

- (id)init {
    self = [super init];

    // view auto set in viewDidLoaded
    //self.delegate = self;
    //self.dataSource = self;
    
    return self;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    ui::impl::TableController* table = (ui::impl::TableController*)self._cxxobj;
    
# ifdef WSI_DEBUG
    NSInteger ret = table->count_sections();
    return ret;
# else
    return table->count_sections();
# endif
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    ui::impl::TableController* table = (ui::impl::TableController*)self._cxxobj;

    if (section > table->count_sections())
        return 0;
    ui::TableSection& sec = table->section_at(section);
    return sec.count();
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    ui::impl::TableController* table = (ui::impl::TableController*)self._cxxobj;

    real height = table->section_at(indexPath.section).object_at(indexPath.row).height;
    if (height == 0) {
        height = self.rowHeight;
    }
    return height;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    ui::impl::TableController* table = (ui::impl::TableController*)self._cxxobj;
    
    ui::impl::TableController::IndexPath idx(indexPath);
    ui::TableCellObject& var = table->section_at(indexPath.section).object_at(indexPath.row);

    RefObject* cellptr = (RefObject*)table->makecell(idx, var);
    if (cellptr == NULL)
        return nil;
    
    ui::ITableCell* cell = dynamic_cast<ui::ITableCell*>(cellptr);
    
    cell->set_owner(table);
    cell->set_object(&var);
    //cell->update();
    
    UITableViewCell* ret = [cell->nsobject() consign];
    cell->drop();
    return ret;
}

- (void)tableView:(UITableView *)_tableView willDisplayCell:(UITableViewCell *)_cell forRowAtIndexPath:(NSIndexPath *)indexPath {
    if ([_cell isKindOfClass:[_CXXVIEW(WSIUITableViewCell) class]] == NO)
        return;
    
    _CXXVIEW(WSIUITableViewCell)* cell = (_CXXVIEW(WSIUITableViewCell)*)_cell;
    
    ui::ITableCell* cxxcell = dynamic_cast<ui::ITableCell*>((::wsi::RefObject*)[cell object]);
    cxxcell->update();
}

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    ui::impl::TableController* table = (ui::impl::TableController*)self._cxxobj;
    ui::TableSection const& sec = table->section_at(indexPath.section);
    ui::TableCellObject const& cellobj = sec.object_at(indexPath.row);
    return cellobj.editable;
}

- (void)tableView:(UITableView *)_tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    _CXXVIEW(WSIUITableViewCell)* cell = (_CXXVIEW(WSIUITableViewCell)*)[_tableView cellForRowAtIndexPath:indexPath]; 
    ui::ITableCell* cxxcell = dynamic_cast<ui::ITableCell*>((::wsi::RefObject*)[cell object]);
    if (cxxcell->object().selectable == false)
        return;
    
    // cell select status changed.
    cxxcell->selected();
    
    // emit object's signal.
    cxxcell->object().emit(kSignalSelected);
    
    // emit tableview's signal.
    [self emit:kSignalSelectChanged result:cell data:indexPath];
}

- (void)tableView:(UITableView *)_tableView didDeselectRowAtIndexPath:(NSIndexPath *)indexPath {
    _CXXVIEW(WSIUITableViewCell)* cell = (_CXXVIEW(WSIUITableViewCell)*)[_tableView cellForRowAtIndexPath:indexPath];
    ui::ITableCell* cxxcell = dynamic_cast<ui::ITableCell*>((::wsi::RefObject*)[cell object]);

    // cell select status changed.
    cxxcell->deselected();
}

- (UITableViewCellEditingStyle)tableView:(UITableView *)_tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath {
    ui::impl::TableController* table = (ui::impl::TableController*)self._cxxobj;
    UITableViewCellEditingStyle ret = UITableViewCellEditingStyleNone;
    if (indexPath.section >= table->count_sections())
        return ret;
    ui::TableSection const& sec = table->section_at(indexPath.section);
    if (indexPath.row >= sec.count())
        return ret;
    ui::TableCellObject const& cellobj = sec.object_at(indexPath.row);
    if (cellobj.editable == false)
        return ret;
    return cellobj.editing_style;
}

- (NSString *)tableView:(UITableView *)_tableView titleForDeleteConfirmationButtonForRowAtIndexPath:(NSIndexPath *)indexPath {
    ui::impl::TableController* table = (ui::impl::TableController*)self._cxxobj;

    return table->section_at(indexPath.section).object_at(indexPath.row).editing_text;
}

- (void)tableView:(UITableView *)_tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    ui::impl::TableController* table = (ui::impl::TableController*)self._cxxobj;

    _CXXVIEW(WSIUITableViewCell)* cell = (_CXXVIEW(WSIUITableViewCell)*)[_tableView cellForRowAtIndexPath:indexPath]; 
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        ui::TableCellObject const& var = table->section_at(indexPath.section).object_at(indexPath.row);
        if (var.removable) {
            [cell retain];
            
            // event.
            [self emit:kSignalItemRemoving result:cell];
            
            // remove action.
            table->section_at(indexPath.section).remove(indexPath.row);
            
            // update table.
            [_tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] 
                              withRowAnimation:UITableViewRowAnimationFade];
            
            // send signal.
            [self emit:kSignalItemRemoved result:cell];
            
            [cell release];
        }
    }
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    ui::impl::TableController* table = (ui::impl::TableController*)self._cxxobj;

    return table->section_at(section).header;
}

- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section {
    ui::impl::TableController* table = (ui::impl::TableController*)self._cxxobj;

    return table->section_at(section).footer;    
}

_CXXCONTROLLER_IMPL_END

WSI_END_OBJC
