
# ifndef __WSI_UIKIT_UITABLEVIEWCONTROLLER_E656BAE2FB4D4EF18D1C311369954EE0_H_INCLUDED
# define __WSI_UIKIT_UITABLEVIEWCONTROLLER_E656BAE2FB4D4EF18D1C311369954EE0_H_INCLUDED

# import "UITableView+WSI.h"
# import "UIViewController+WSI.h"
# import "UINavigationController+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface WSIUITableViewController : WSIUIViewController <UITableViewDataSource, UITableViewDelegate> {
    
    //! style.
    UITableViewStyle _tableViewStyle;
        
    //! datas.
    id _datas;
    
    //! row height.
    real _rowHeight;
}

@property (nonatomic, assign) UITableViewStyle tableViewStyle;
@property (nonatomic, assign) real rowHeight;
@property (nonatomic, assign) id<UITableViewDataSource> dataSource;
@property (nonatomic, assign) id<UITableViewDelegate> delegate;
@property (nonatomic, readonly) WSIUITableView *tableView;
@property (nonatomic, retain) id datas;

//! init.
- (id)init;
- (id)initWithStyle:(UITableViewStyle)style;

//! load.
- (void)reloadData;

@end

@interface UINavigationTableViewController : WSIUINavigationController {
    WSIUITableViewController* rootTable;
}

@property (nonatomic, readonly) WSIUITableViewController* rootTable;

- (id)init;
- (id)initWithRootTitle:(NSString*)title;

@end

WSI_EXTERN signal_t kSignalSelectChanged;
WSI_EXTERN signal_t kSignalItemRemoving;
WSI_EXTERN signal_t kSignalItemRemoved;
WSI_EXTERN signal_t kSignalItemInserted;
WSI_EXTERN signal_t kSignalItemMoved;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "UITableViewCell+WSI.h"
# include "../WTL/Variant+WSI.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class ITableViewController;

WSI_END_NS
WSI_END_NS

WSI_BEGIN_HEADER_OBJC

_CXXCONTROLLER_DECL_BEGIN(WSIUITableViewController)
_CXXCONTROLLER_DECL_END

WSI_END_HEADER_OBJC

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

# include "UISectionItems.h"

class ITableViewController
: public IViewController
{
public:
    
    virtual void reload() = 0;    
    virtual void clear() = 0;
    
};

class TableIndexPath
: public ns::IndexPath
{
public:
    
    TableIndexPath(NSIndexPath* r)
    : ns::IndexPath(r)
    {
        PASS;
    }
    
    uint row() const
    {
        return this->_self.row;
    }
    
    uint section() const
    {
        return this->_self.section;
    }
    
};

WSI_BEGIN_NS(tpl)

template <typename itemT = TableCellObject>
class TableSection
: public Section<itemT>
{
public:
    
    TableSection()
    {
        PASS;
    }
    
    ns::String header;
    ns::String footer;
    
};

template <
typename tableT,
typename sectionT = TableSection<>,
typename controllerT = _CXXCONTROLLER(WSIUITableViewController),
typename viewT = WSIUITableView,
typename cxxviewT = ui::TableView,
typename ctlrI = ITableViewController
>
class TableViewController
: public SimpleController<
tableT, 
controllerT,
viewT,
cxxviewT,
ctlrI
>
{
    typedef 
    SimpleController<
    tableT, 
    controllerT,
    viewT,
    cxxviewT,
    ctlrI
    >
    super;
    
public:
    
    typedef sectionT section_type;
    typedef typename section_type::item_type cellobj_type;
    typedef TableIndexPath IndexPath;
    typedef ::wsi::Object* cell_pointer;
    
    TableViewController()
    {
        PASS;
    }
    
    virtual ~TableViewController()
    {
        PASS;
    }
    
    virtual uint count_sections() const
    {
        return _sections.size();
    }
    
    virtual section_type& section_at(uint idx)
    {
        return *_sections[idx];
    }
    
    virtual void add(section_type* sec)
    {
        _sections.push_back(sec);
        sec->grab();
    }
    
    virtual cell_pointer makecell(IndexPath const& idx) const
    {
        return NULL;
    }
    
    virtual cell_pointer makecell(IndexPath const& idx, cellobj_type const& obj) const
    {
        return makecell(idx);
    }
    
    variant_t const& data_at(IndexPath const& idx) const
    {
        return _sections[idx.section()]->at(idx.row());
    }
    
    virtual void reload()
    {
        [this->_self.tableView performSelectorOnMainThread:@selector(reloadData) withObject:nil waitUntilDone:YES];
    }
    
    virtual void clear()
    {
        _sections.clear();
    }
    
protected:
    
    core::refpointer_vector<section_type> _sections;
    
};

template <typename viewT>
inline_impl core::vector<typename TableView<viewT>::cell_pointer> TableView<viewT>::visible_cells() const
{
    core::vector<cell_pointer> ret;
    NSArray* cells = [this->_self visibleCells];
    ret.reserve(cells.count);
    for (id each in cells)
    {
        cell_pointer obj = (cell_pointer)[each object];
        ret.push_back(obj);
    }
    return ret;
}

WSI_END_NS

typedef tpl::TableSection<> TableSection;

WSI_BEGIN_NS(impl)

class TableController
: public tpl::TableViewController<TableController>
{
public:
    
    virtual ::wsi::Object* makecell(IndexPath const& idx) const
    {
        return ui::impl::TableCell::New();
    }
    
    virtual ::wsi::Object* makecell(IndexPath const& idx, cellobj_type const& obj) const
    {
        return makecell(idx);
    }
    
};

WSI_END_NS

class PlainTableController
: public tpl::TableViewController<PlainTableController>
{
public:
    
    PlainTableController()
    {
        PASS;
    }
    
};

template <typename implT, typename cellT>
class PlainTable
: public PlainTableController
{
public:
    
    PlainTable()
    {
        PASS;
    }
    
    virtual ::wsi::Object* makecell(IndexPath const& idx) const
    {
        return new cellT;
    }
    
};

class GroupedTableController
: public tpl::TableViewController<GroupedTableController>
{
public:
    
    GroupedTableController()
    {
        PASS;
    }        
    
    void init()
    {
        this->_self = [[controller_type alloc] initWithStyle:UITableViewStyleGrouped];
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif