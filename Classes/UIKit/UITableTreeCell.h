
# ifndef __NNT_UIKIT_TABLETREECELL_48E2F3C353EE4CA28553EC07FFB20DF0_H_INCLUDED
# define __NNT_UIKIT_TABLETREECELL_48E2F3C353EE4CA28553EC07FFB20DF0_H_INCLUDED

# import "UITableViewCell+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface UITableViewGroupCell : NNTUITableViewCell {
    
    //! if the cell is expanded.
    BOOL isExpanded;
    
}

@property (nonatomic, assign) BOOL isExpanded;

- (BOOL)expand;
- (BOOL)collapse;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_OBJC

_CXXVIEW_DECL_BEGIN(UITableViewGroupCell)
_CXXVIEW_DECL_END

NNT_END_HEADER_OBJC

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class TableTreeSection;

class TableTreeCellObject
: public TableCellObject
{
public:
    
    TableTreeCellObject()
    : is_expanded(false), section(NULL), need_expand(false)
    {
        PASS;
    }
    
    //! status.
    bool is_expanded;
    
    //! need expand.
    bool need_expand;
    
    //! section.
    TableTreeSection* section;
    
};

class ITableTreeController;

class ITableGroupCell
: public ITableCell
{
public:
    
    virtual bool expand() = 0;
    virtual bool collapse() = 0;
    virtual bool is_expanded() const = 0;
    
    virtual void did_expanded() = 0;    
    virtual void did_collapsed() = 0;
    
    virtual ITableTreeController const* root_tree() const = 0;
    
    virtual ::nnt::Object* makesimple() const = 0;
    
};

NNT_BEGIN_NS(tpl)

template <typename implT,
typename subtableT,
typename cellT = _CXXVIEW(UITableViewGroupCell),
typename cellI = ITableGroupCell
>
class TableGroupCell
: public tpl::TableCell<implT,
cellT,
cellI
>
{
    typedef tpl::TableCell<implT,
    cellT,
    cellI
    > super;
    
public:
    
    typedef subtableT subtable_type;
    
    TableGroupCell()
    : _subtable(NULL)
    {
        super::set_select(UITableViewCellSelectionStyleNone);
    }
    
    virtual ~TableGroupCell()
    {
        if (this->has_object())
        {
            TableTreeCellObject& obj = (TableTreeCellObject&)this->object();
            if (obj.is_expanded)
                obj.need_expand = true;
        }
        
        safe_delete(_subtable);
    }
    
    virtual void update()
    {
        TableTreeCellObject const& obj = (TableTreeCellObject const&)this->object();
        if (obj.is_expanded && !_subtable)
        {
            if (obj.need_expand)            
                _doexpand();
        }
        else if (!obj.is_expanded && _subtable)
        {
            _docollapse();
        }
    }
    
    virtual bool expand()
    {
        if (is_expanded())
            return false;
        
        // cb.
        will_expand();
        
        // expand.
        TableTreeCellObject& obj = (TableTreeCellObject&)this->object();
        obj.is_expanded = true;
        obj.need_expand = true;
        
        return true;
    }
    
    virtual bool collapse()
    {
        if (!is_expanded())
            return false;
        
        // cb.
        will_collapse();
        
        // collapse.
        TableTreeCellObject& obj = (TableTreeCellObject&)this->object();
        obj.is_expanded = false;
        
        // refresh.
        update();
        
        return true;
    }
    
    virtual bool is_expanded() const
    {
        TableTreeCellObject const& obj = (TableTreeCellObject const&)this->object();
        return obj.is_expanded;
    }
    
    virtual void layout_subviews()
    {
        if (_subtable == NULL)
            return;
        
        _subtable->view().set_frame(this->view_bounds());
        _subtable->view().bring_totop();
    }
    
    virtual void set_object(TableCellObject* obj)
    {
        super::set_object(obj);
        
        TableTreeCellObject* tobj = (TableTreeCellObject*)obj;
        if (tobj->is_expanded)
            did_expanded();
        else
            did_collapsed();
    }
    
    virtual ITableTreeController const* root_tree() const;
    
    //! make simple group cell.
    virtual ::nnt::Object* makesimple() const;
    
    // callback.
    
    virtual void will_expand()
    {
        PASS;
    }
    
    virtual void did_expanded()
    {
        PASS;
    }
    
    virtual void will_collapse()
    {
        PASS;
    }
    
    virtual void did_collapsed()
    {
        PASS;
    }
        
protected:
        
    void _doexpand()
    {
        TableTreeCellObject& obj = (TableTreeCellObject&)this->object();
        
        // set.
        obj.need_expand = false;
        
        // create sub table.
        _subtable = new subtable_type;
        _subtable->add(obj.section);
        _subtable->owner_cell = this;
        
        // add view.
        [this->_self addSubview:_subtable->view()];
                
        // cb.
        did_expanded();
    }
    
    void _docollapse()
    {
        _subtable->remove_fromsuper();
        safe_delete(_subtable);
        
        // db.
        did_collapsed();
    }
    
    subtable_type* _subtable;
    
};

NNT_BEGIN_NS(impl)

template <typename subtableT, typename cellT, typename cellI>
class TableGroupCell
: public tpl::TableGroupCell<TableGroupCell<subtableT, cellT, cellI>, subtableT, cellT, cellI>
{
public:
    
    TableGroupCell()
    {
        PASS;
    }
    
    ~TableGroupCell()
    {
        PASS;
    }
    
};

NNT_END_NS // impl

template <typename implT, typename subtableT, typename cellT, typename cellI>
inline_impl ::nnt::Object* TableGroupCell<implT, subtableT, cellT, cellI>::makesimple() const
{
    typedef tpl::impl::TableGroupCell<subtableT, cellT, cellI> simple_type;
    return new simple_type;
}

NNT_END_NS // tpl

using tpl::TableGroupCell;

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
