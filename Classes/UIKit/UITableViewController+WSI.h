
# ifndef __NNT_UIKIT_UITABLEVIEWCONTROLLER_E656BAE2FB4D4EF18D1C311369954EE0_H_INCLUDED
# define __NNT_UIKIT_UITABLEVIEWCONTROLLER_E656BAE2FB4D4EF18D1C311369954EE0_H_INCLUDED

# import "UITableView+NNT.h"
# import "UIViewController+NNT.h"
# import "UINavigationController+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface NNTUITableViewController : NNTUIViewController <UITableViewDataSource, UITableViewDelegate> {
    
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
@property (nonatomic, readonly) NNTUITableView *tableView;
@property (nonatomic, retain) id datas;

//! init.
- (id)init;
- (id)initWithStyle:(UITableViewStyle)style;

//! load.
- (void)reloadData;

@end

@interface UINavigationTableViewController : NNTUINavigationController {
    NNTUITableViewController* rootTable;
}

@property (nonatomic, readonly) NNTUITableViewController* rootTable;

- (id)init;
- (id)initWithRootTitle:(NSString*)title;

@end

NNT_EXTERN signal_t kSignalSelectChanged;
NNT_EXTERN signal_t kSignalItemRemoving;
NNT_EXTERN signal_t kSignalItemRemoved;
NNT_EXTERN signal_t kSignalItemInserted;
NNT_EXTERN signal_t kSignalItemMoved;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "UITableViewCell+NNT.h"
# include "../WTL/Variant+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class ITableViewController;

NNT_END_NS
NNT_END_NS

NNT_BEGIN_HEADER_OBJC

_CXXCONTROLLER_DECL_BEGIN(NNTUITableViewController)
_CXXCONTROLLER_DECL_END

NNT_END_HEADER_OBJC

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

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

NNT_BEGIN_NS(tpl)

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
typename controllerT = _CXXCONTROLLER(NNTUITableViewController),
typename viewT = NNTUITableView,
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

NNT_END_NS

typedef tpl::TableSection<> TableSection;

NNT_BEGIN_NS(impl)

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

NNT_END_NS

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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif