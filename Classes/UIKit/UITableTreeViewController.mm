
# import "Core.h"
# import "UITableTreeViewController.h"
# import "UITableTreeView.h"

using namespace ::wsi;

NNT_BEGIN_CXX
NNT_BEGIN_NS(ui)

typedef _CXXVIEW(UITableViewGroupCell) UITableViewGroupCell;

NNT_END_NS
NNT_END_CXX

NNT_BEGIN_OBJC

@implementation UITableTreeViewController

- (id)init {
    self = [super init];
    
    return self;
}

- (void)dealloc {    
    [super dealloc];
}

@end

_CXXCONTROLLER_IMPL_BEGIN(UITableTreeViewController)

@synthesize _cxxtable;

- (id)init {
    self = [super init];
    
    self.delegate = self;
    self.dataSource = self;
    
    return self;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    ui::impl::TableTreeController* table = (ui::impl::TableTreeController*)self._cxxtable;
    
    NSInteger ret = 0;
    ret = table->count_sections();
    
    return ret;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    ui::impl::TableTreeController* table = (ui::impl::TableTreeController*)self._cxxtable;

    // protect.
    if (section > table->count_sections())
        return 0;
    
    // sum.
    ui::TableTreeSection& sec = table->section_at(section);
    NSInteger ret = sec.count();
    
    if (sec.parent)
        ret += 1;
    
    return ret;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    ui::impl::TableTreeController* table = (ui::impl::TableTreeController*)self._cxxtable;
    ui::TableTreeSection const& sec = table->section_at(indexPath.section);
    ui::TableTreeCellObject const* cellobj = NULL; 

    NSUInteger rowIndex = indexPath.row;
    
    // if has parent and is first row, replace by parent.
    if (sec.parent) {
        if (rowIndex == 0) {
            cellobj = sec.var();
        } else {
            rowIndex -= 1;
            cellobj = &sec.object_at(rowIndex);
        }
    } else {
        cellobj = &sec.object_at(rowIndex);
    }

    // self height.
    real height = cellobj->height;
    if (height == 0) {
        height = self.rowHeight;
    }
    
    if (sec.parent && indexPath.row == 0) {
        height += 0;
    } else if (cellobj->is_expanded) {
        // sub height.
        ui::TableTreeSection const& item = sec.item_at(rowIndex);
        for (uint i = 0; i < item.count(); ++i) {
            ui::TableTreeCellObject const& obj = item.object_at(i);
            real h = obj.height;
            if (h == 0) {
                h = self.rowHeight;
            }
            height += h;
        }
    }
    
    return height;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {        
    ui::impl::TableTreeController* table = (ui::impl::TableTreeController*)self._cxxtable;

    ui::impl::TableTreeController::IndexPath idx(indexPath);
    ui::TableTreeSection const& sec = table->section_at(indexPath.section);
    
    // create cell.
    RefObject* cellptr = NULL;
    ui::TableTreeCellObject* cellobj = NULL;

    NSUInteger rowIndex = indexPath.row;
    if (sec.parent) {
        if (indexPath.row == 0) {
            cellobj = core::down_const(sec.var());
            cellptr = (RefObject*)table->makegroupcell(idx, *cellobj);
        } else {
            rowIndex -= 1;                        
        }
    }
    
    if (cellptr == NULL) {
    
        ui::TableTreeSection const& item = table->section_at(indexPath.section).item_at(rowIndex);
        cellobj = core::down_const(item.var());
    
        if (item.count() == 0) {
            // make cell
            cellptr = (RefObject*)table->makecell(idx, *cellobj);
        } else {
            if (cellobj->is_expanded) {
                RefObject* obj = (RefObject*)table->makegroupcell(idx, *cellobj);
                ui::ITableGroupCell* cell = dynamic_cast<ui::ITableGroupCell*>(obj);
                cellptr = (RefObject*)cell->makesimple();
                safe_drop(obj);
            } else {
                // has group.
                cellptr = (RefObject*)table->makegroupcell(idx, *cellobj);
            }
        }
        
    }

    // protect.
    if (cellptr == NULL)
        return nil;
    
    ui::ITableCell* cell = dynamic_cast<ui::ITableCell*>(cellptr);
    cell->set_owner(table);
    cell->set_object(cellobj);
    
    // get ns cell.
    UITableViewCell* ret = [cell->nsobject() consign];
    cell->drop();
    return ret;
}

- (void)tableView:(UITableView *)_tableView willDisplayCell:(UITableViewCell *)_cell forRowAtIndexPath:(NSIndexPath *)indexPath {    
    _CXXVIEW(NNTUITableViewCell)* cell = (_CXXVIEW(NNTUITableViewCell)*)_cell;
    ui::impl::TableTreeController* table = (ui::impl::TableTreeController*)self._cxxtable;
    ui::TableTreeSection const& sec = table->section_at(indexPath.section);
    ui::ITableCell* cxxcell = dynamic_cast<ui::ITableCell*>((::wsi::RefObject*)[cell object]);
    ui::TableTreeCellObject& cellobj = (ui::TableTreeCellObject&)cxxcell->object();
    
    // set to cell.
    if (sec.parent &&
        indexPath.row == 0) {
        // is sub group.
        bool val = cellobj.is_expanded;
        cellobj.is_expanded = false;
        cxxcell->update();
        cellobj.is_expanded = val;
    } else {
        cxxcell->update();
    }  
}

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    ui::impl::TableTreeController* table = (ui::impl::TableTreeController*)self._cxxtable;
    
    ui::TableTreeSection const& sec = table->section_at(indexPath.section);
    NSUInteger rowIndex = indexPath.row;
    if (sec.parent) {
        if (rowIndex == 0)
            return NO;
        rowIndex -= 1;
    }
    
    ui::TableTreeCellObject const& cellobj = sec.object_at(rowIndex);
    return cellobj.editable;
}

- (void)tableView:(UITableView *)_tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {        
    _CXXVIEW(NNTUITableViewCell)* cell = (_CXXVIEW(NNTUITableViewCell)*)[_tableView cellForRowAtIndexPath:indexPath]; 
    ui::impl::TableTreeController* table = (ui::impl::TableTreeController*)self._cxxtable;
    ui::ITableCell* cxxcell = dynamic_cast<ui::ITableCell*>((::wsi::RefObject*)[cell object]);
    ui::TableTreeCellObject& cellobj = (ui::TableTreeCellObject&)cxxcell->object();
    
    if (cellobj.selectable == false)
        return;                
    
    if (cellobj.is_expanded) {
        ui::ITableViewController* tab = table->owner_cell->owner();
        table->owner_cell->collapse();
        tab->reload();
        return;
    }
    
    NSUInteger rowIndex = indexPath.row;
    if (table->owner_cell)
        rowIndex -= 1;
        
    // emit tableview's signal.
    [self emit:kSignalSelectChanged result:cell data:indexPath];
    
    // emit object's signal.        
    [cellobj.nsobject() emit:kSignalSelected];
    
    // cell select status changed.
    cxxcell->selected();
        
    // reload identity.
    BOOL needreload = NO;
    
    // group process.    
    if ([cell isKindOfClass:[ui::UITableViewGroupCell class]]) {
        ui::UITableViewGroupCell* gcell = (ui::UITableViewGroupCell*)cell;
        gcell.isExpanded = cellobj.is_expanded;
        ui::ITableGroupCell* cxxgcell = dynamic_cast<ui::ITableGroupCell*>((::wsi::RefObject*)[cell object]);
        
        if (cxxgcell->is_expanded()) {
            needreload = cxxgcell->collapse();
        } else {
            needreload = cxxgcell->expand();

            if (needreload) {
                ui::impl::TableTreeController* table = (ui::impl::TableTreeController*)self._cxxtable;                
                ui::TableTreeSection* item = &table->section_at(indexPath.section).item_at(rowIndex);
                cellobj.section = item;
            }
        }
                
        cellobj.is_expanded = cxxgcell->is_expanded();
    }
    
    // reload all.
    if (needreload)
        [self reloadData];
}

- (void)tableView:(UITableView *)_tableView didDeselectRowAtIndexPath:(NSIndexPath *)indexPath {
    _CXXVIEW(NNTUITableViewCell)* cell = (_CXXVIEW(NNTUITableViewCell)*)[_tableView cellForRowAtIndexPath:indexPath]; 
    ui::ITableCell* cxxcell = dynamic_cast<ui::ITableCell*>((::wsi::RefObject*)[cell object]);

    // cell select status changed.
    cxxcell->deselected();
}

- (UITableViewCellEditingStyle)tableView:(UITableView *)_tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath {
    ui::impl::TableTreeController* table = (ui::impl::TableTreeController*)self._cxxtable;
    UITableViewCellEditingStyle ret = UITableViewCellEditingStyleNone;
    if (indexPath.section >= table->count_sections())
        return ret;
    ui::TableTreeSection const& sec = table->section_at(indexPath.section);
    if (indexPath.row >= sec.count())
        return ret;
    ui::TableCellObject const& cellobj = sec.object_at(indexPath.row);
    if (cellobj.editable == false)
        return ret;
    return cellobj.editing_style;
}

- (NSString *)tableView:(UITableView *)_tableView titleForDeleteConfirmationButtonForRowAtIndexPath:(NSIndexPath *)indexPath {
    ui::impl::TableTreeController* table = (ui::impl::TableTreeController*)self._cxxtable;

    return table->section_at(indexPath.section).object_at(indexPath.row).editing_text;
}

- (void)tableView:(UITableView *)_tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    ui::impl::TableTreeController* table = (ui::impl::TableTreeController*)self._cxxtable;

    _CXXVIEW(NNTUITableViewCell)* cell = (_CXXVIEW(NNTUITableViewCell)*)[_tableView cellForRowAtIndexPath:indexPath]; 
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
            
            // signal.
            [self emit:kSignalItemRemoved result:cell];
            
            [cell release];
        }
    }
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    ui::impl::TableTreeController* table = (ui::impl::TableTreeController*)self._cxxtable;

    return table->section_at(section).header;
}

- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section {
    ui::impl::TableTreeController* table = (ui::impl::TableTreeController*)self._cxxtable;

    return table->section_at(section).footer;    
}

_CXXCONTROLLER_IMPL_END

NNT_END_OBJC
