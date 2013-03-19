
# ifndef __NNT_UIKIT_TABLETREECONTROLLER_3350A2F3AF9D4AAF9654A0FA8A06F876_H_INCLUDED
# define __NNT_UIKIT_TABLETREECONTROLLER_3350A2F3AF9D4AAF9654A0FA8A06F876_H_INCLUDED

# import "UITableViewController+NNT.h"
# import "UITableTreeView.h"

NNT_BEGIN_HEADER_OBJC

@interface UITableTreeViewController : NNTUITableViewController < 
UITableTreeViewDataSource, 
UITableTreeViewDelegate 
> {
    
}

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class ITableTreeController;

NNT_END_NS
NNT_END_NS

NNT_BEGIN_HEADER_OBJC

_CXXCONTROLLER_DECL_BEGIN(UITableTreeViewController)

@property (nonatomic, assign) ::wsi::ui::ITableTreeController* _cxxtable;

_CXXCONTROLLER_DECL_END

NNT_END_HEADER_OBJC

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class TableTreeSection
: public tpl::TableSection<TableTreeCellObject>
{
    
    typedef TableSection super;
    
public:
    
    TableTreeSection()
    : _var(NULL), parent(NULL)
    {
        PASS;
    }
    
    virtual ~TableTreeSection()
    {
        safe_delete(_var);
    }
        
    //! instance.
    virtual TableTreeSection* instance() const
    {
        return new TableTreeSection;
    }
    
    //! override.    
    virtual usize count() const
    {
        return _children.count();
    }
    
    template <typename valT>
    item_type& add(valT const& val)
    {
        return super::add<valT>(val);
    }
    
    virtual item_type& add(item_type* var)
    {
        TableTreeSection* item = this->instance();
        item->_var = var;
        item->parent = this;
        
        _children.push_back(item);

        return *var;
    }
    
    virtual variant_t& at(uint idx)
    {
        return _children[idx]->_var->var;
    }
    
    virtual variant_t const& at(uint idx) const
    {
        return _children[idx]->_var->var;
    }
    
    TableTreeSection& item_at(uint idx)
    {
        return *_children[idx];
    }
    
    TableTreeSection const& item_at(uint idx) const
    {
        return *_children[idx];
    }
    
    virtual item_type& object_at(uint idx)
    {
        return *_children[idx]->_var;
    }
    
    virtual item_type const& object_at(uint idx) const
    {
        return *_children[idx]->_var;
    }
    
    virtual void remove(uint idx)
    {
        _children.erase_destroy(_children.begin() + idx);
    }
    
    item_type* var()
    {
        return _var;
    }
    
    item_type const* var() const
    {
        return _var;
    }
    
    //! parent section.
    TableTreeSection* parent;
    
protected:
    
    //! children.
    core::pointer_vector<TableTreeSection> _children;
    
    //! cell container.
    item_type* _var;
    
};

class ITableTreeController
: public ITableViewController
{
public:
    
    virtual ITableGroupCell const* owner() const = 0;
    
};

NNT_BEGIN_NS(tpl)

template <typename implT,
typename sectionT = TableTreeSection,
typename ctlrT = _CXXCONTROLLER(UITableTreeViewController),
typename viewT = UITableTreeView,
typename cxxviewT = ui::TableTreeView,
typename ctlrI = ITableTreeController
>
class TableTreeController
: public tpl::TableViewController <
implT,
sectionT,
ctlrT,
viewT,
cxxviewT,
ctlrI
>
{
    typedef 
    tpl::TableViewController <
    implT,
    sectionT,
    ctlrT,
    viewT,
    cxxviewT,
    ctlrI
    >
    super;
    
public:
    
    typedef typename super::IndexPath IndexPath;
    typedef typename super::cellobj_type cellobj_type;
    typedef ::wsi::Object* cell_type;
    
    TableTreeController()
    : owner_cell(NULL)
    {
        this->_self._cxxtable = this;
    }
    
    virtual ~TableTreeController()
    {
        this->_self._cxxtable = NULL;
    }
    
    //! make a normal cell.
    virtual cell_type makecell(IndexPath const& idx) const
    {
        return NULL;
    }
    
    virtual cell_type makecell(IndexPath const& idx, cellobj_type const& obj) const
    {
        return makecell(idx);
    }
    
    //! make a group cell.
    virtual cell_type makegroupcell(IndexPath const& idx) const
    {
        return NULL;
    }
    
    virtual cell_type makegroupcell(IndexPath const& idx, cellobj_type const& obj) const
    {
        return makegroupcell(idx, obj);
    }
    
    //! the cell create this table.
    ITableGroupCell* owner_cell;
    
    virtual ITableGroupCell const* owner() const
    {
        return owner_cell;
    }
    
};

template <typename implT, typename subtableT, typename cellT, typename cellI>
inline_impl ITableTreeController const* TableGroupCell<implT, subtableT, cellT, cellI>::root_tree() const
{
    ITableTreeController const* tree = dynamic_cast<ITableTreeController const*>(this->owner());
    while (tree->owner())
    {
        tree = dynamic_cast<ITableTreeController const*>(tree->owner()->owner());
    }
    
    return tree;
}

NNT_END_NS

NNT_BEGIN_NS(impl)

class TableTreeController
: public tpl::TableTreeController<TableTreeController>
{
public:
    
    virtual cell_type makecell(IndexPath const& idx) const;
    virtual cell_type makegroupcell(IndexPath const& idx) const;
    
    virtual cell_type makecell(IndexPath const& idx, cellobj_type const& obj) const
    {
        return makecell(idx);
    }
    
    virtual cell_type makegroupcell(IndexPath const& idx, cellobj_type const& obj) const
    {
        return makegroupcell(idx);
    }
    
};

class TableGroupCell
: public tpl::TableGroupCell<TableGroupCell, TableTreeController>
{
    
};

inline_impl TableTreeController::cell_type TableTreeController::makecell(IndexPath const& idx) const
{
    return ui::impl::TableCell::New();    
}

inline_impl TableTreeController::cell_type TableTreeController::makegroupcell(IndexPath const& idx) const
{
    return ui::impl::TableGroupCell::New();   
}

NNT_END_NS

using impl::TableTreeController;

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif