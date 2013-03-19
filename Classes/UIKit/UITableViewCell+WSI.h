
# ifndef __NNT_UIKIT_UITABLEVIEWCELL_E2C08A8EBCC54DB3B6A33B02725C65B3_H_INCLUDED
# define __NNT_UIKIT_UITABLEVIEWCELL_E2C08A8EBCC54DB3B6A33B02725C65B3_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NNTUITableViewCell : UITableViewCell {
    
    //! if is used.
    BOOL _isUsed;
    
    NNTOBJECT_DECL;
}

@property (nonatomic, assign) BOOL isUsed;
@property (nonatomic, retain) WCGFill* backgroundFill;

NNTOBJECT_PROP;

//! update layout.
- (void)updateLayout:(CGRect)rect;

//! cell.
+ (NNTUITableViewCell*)cell;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_OBJC

_CXXVIEW_DECL(NNTUITableViewCell);

NNT_END_HEADER_OBJC

# include "UILabel+NNT.h"
# include "UISectionItems.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class TableCellObject
: public SectionItem
{
public:
    
    TableCellObject()
    : editable(false),
    removable(true),
    selectable(true),
    height(0)
    {
        editing_style = UITableViewCellEditingStyleDelete;
        editing_text = _W(@"DELETE");
    }
    
    //! style for editing.
    UITableViewCellEditingStyle editing_style;
    
    //! text for editing button.
    ns::String editing_text;
    
    //! if cell is editable.
    bool editable;
    
    //! if cell is removable.
    bool removable;
    
    //! if cell is selectable;
    bool selectable;
    
    //! height. default is 0, use system's height.
    real height;
    
};

class ITableViewController;

class ITableCell
: public IView
{
public:
    
    virtual void set_object(TableCellObject* obj) = 0;
    virtual bool has_object() const = 0;
    virtual TableCellObject& object() = 0;
    virtual void update() = 0;
    virtual void set_owner(ITableViewController*) = 0;
    virtual ITableViewController* owner() const = 0;
    virtual void selected() = 0;
    virtual void deselected() = 0;
    
};

NNT_BEGIN_NS(tpl)

template <typename implT,
typename cellT = _CXXVIEW(NNTUITableViewCell),
typename cellI = ITableCell
>
class TableCell
: public View<
implT, 
cellT,
cellI
>
{
    typedef View<
    implT,
    cellT,
    cellI
    > super;
    
    typedef typename super::objc_type objc_type;
        
public:
    
    TableCell()
    : _table(NULL)
    {
        this->_init();        
        this->_self = [[objc_type alloc] initWithZero];
        this->_updateself();
    }
    
    explicit TableCell(UITableViewCellStyle style, ns::String const& reuseId = ns::null_string)
    : super(nil)
    {
        this->_init();
        this->_self = [[objc_type alloc] initWithStyle:style reuseIdentifier:reuseId];
        this->_updateself();
    }
    
    void init()
    {
        PASS;
    }
        
    virtual ~TableCell()
    {
        safe_delete(_text);
        safe_delete(_detail);
        safe_delete(_content);
    }
    
    void layout_subviews()
    {
        PASS;
    }
    
    ui::Label& text()
    {
        if (_text == NULL)
            _text = new ui::Label((NNTUILabel*)this->_self.textLabel);
        return *_text;
    }
    
    ui::Label& detail()
    {
        if (_detail == NULL)
            _detail = new ui::Label((NNTUILabel*)this->_self.detailTextLabel);
        return *_detail;
    }
    
    _NullView<UIView>& content()
    {
        if (_content == NULL)
            _content = new _NullView<UIView>(this->_self.contentView);
        return *_content;
    }
    
    CGRect bounds() const
    {
        return this->_self.contentView.frame;
    }
    
    CGRect view_bounds() const
    {
        return this->_self.bounds;
    }
    
    void set_background(cg::Fill const& fill)
    {
        this->_self.backgroundFill = fill;
    }
    
    virtual bool has_object() const
    {
        return _var != NULL;
    }
    
    virtual void set_object(TableCellObject* obj)
    {
        _var = obj;
    }
    
    virtual void update()
    {
        PASS;
    }
    
    virtual TableCellObject& object()
    {
        return *_var;
    }
        
    virtual TableCellObject const& object() const
    {
        return *_var;
    }
    
    void set_select(UITableViewCellSelectionStyle style)
    {
        this->_self.selectionStyle = style;
    }
    
    void set_accessory(UITableViewCellAccessoryType type)
    {
        this->_self.accessoryType = type;
    }
    
    bool selected() const
    {
        return this->_self.selected;
    }
    
    void set_selected(bool val, bool ani = true)
    {
        [this->_self setSelected:val animated:ani];
    }
    
    void add_sub(UIView* view, BOOL can = NO)
    {
        view.userInteractionEnabled = can;
        super::add_subview(view);
    }
    
    void add_subview(UIView* view, BOOL can = NO)
    {
        view.userInteractionEnabled = can;
        super::add_subview(view);
    }
    
    virtual void set_owner(ITableViewController* ptr)
    {
        _table = ptr;
    }
    
    virtual ITableViewController* owner() const
    {
        return _table;
    }
    
    virtual void selected()
    {
        PASS;
    }
    
    virtual void deselected()
    {
        PASS;
    }

protected:
    
    void _init()
    {
        _text = NULL;
        _detail = NULL;
        _content = NULL;
        _var = NULL;
    }
    
    ui::Label *_text, *_detail;
    _NullView<UIView> *_content;
    TableCellObject* _var;
    ITableViewController* _table;
    
};

NNT_END_NS

using tpl::TableCell;

NNT_BEGIN_NS(impl)

class TableCell
: public tpl::TableCell<TableCell>
{
    
};

NNT_END_NS

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif