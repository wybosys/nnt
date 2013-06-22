
# ifndef __NNT_UIKIT_PICKERCONTROLLER_A89F40EDEACE4BABA717095A952FA605_H_INCLUDED
# define __NNT_UIKIT_PICKERCONTROLLER_A89F40EDEACE4BABA717095A952FA605_H_INCLUDED

# import "UIControl+NNT.h"
# import "UIPickerView+NNT.h"
# import "UIItemView.h"

NNT_BEGIN_HEADER_OBJC

@interface UIPickerControl : NNTUIControl
<UIPickerViewDataSource, UIPickerViewDelegate>
{
    NNTUIPickerView* _pickerView;
    NSArray* _componentItems;
}

@property (nonatomic, readonly) NNTUIPickerView* pickerView;
@property (nonatomic, retain) NSArray* componentItems;

// Reloading whole view or single component
- (void)reloadAllComponents;
- (void)reloadComponent:(NSInteger)component;

// selection. in this case, it means showing the appropriate row in the middle
// scrolls the specified row to center.
- (void)selectRow:(NSInteger)row inComponent:(NSInteger)component animated:(BOOL)animated;

// returns selected row. -1 if nothing selected
- (NSInteger)selectedRowInComponent:(NSInteger)component;

@end

NNT_EXTERN CGFloat kUIPickerControlHeight;
NNT_EXTERN CGFloat kUIPickerControlItemFontSize;

@interface UIDrumPickerControl : UIDrumPickerView {
    UIItemsContainer* _items;
}

@property (nonatomic, retain) UIItemsContainer *items;

@end

NNT_EXTERN signal_t kSignalSelectChanged;

/* ! open a picker on a desktop.
 * \param items, a 2-dim array indicate Compons-Values datas.
 * \param ok a selector be called while push ok button.
 * \param cancel a selector be called while push cancel button.
 * \param target own the ok and cancel selectors.
 * \code
   NSArray* items = [NSArray arrayWithObjects:[NSArray arrayWithObjects:@"1", @"2", nil], [NSArray arrayWithObjects:@"a", @"b", nil], nil];
   UIPickerControl* picker = NNTOpenPickerDesktop(items, @selector(ok), @selector(cancel), target);
   [picker selectRow:0 inComponent:0 animated:YES];
   [picker selectRow:1 inComponent:1 animated:YES];
   [picker connect:kSignalSelectChanged sel:@selector(changed:) object:target];
 * \endcode
 */
NNT_EXTERN UIPickerControl* NNTOpenPickerDesktop(NSArray* items, SEL ok, SEL cancel, id target);

_CXXCONTROL_DECL(UIPickerControl);
_CXXCONTROL_DECL(UIDrumPickerControl);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "UISectionItems.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class PickerItemObject
: public SectionItem
{
public:
    
    void *view;
    
};

class PickerSection
: public Section<PickerItemObject>
{
    
};

class PickerIndexPath
: public ns::IndexPath
{
public:
    
    PickerIndexPath(uint component, uint idx)
    {
        this->_self.section = component;
        this->_self.row = idx;
    }
    
    uint component() const
    {
        return this->_self.section;
    }
    
    uint index() const
    {
        return this->_self.row;
    }
    
};

class IPickerControl
: public IControl
{
public:
    
    virtual uint count_components() const = 0;
    
};

class PickerItem
: public View<PickerItem>
{
public:
    
    PickerItem()
    {
        PASS;
    }
    
    PickerItemObject& object() const
    {
        return *(PickerItemObject*)_obj;
    }
    
    void set_object(PickerItemObject* obj)
    {
        _obj = obj;
    }
    
    virtual void update()
    {
        PASS;
    }
    
    virtual void selected()
    {
        PASS;
    }
    
protected:
    
    PickerItemObject* _obj;
    
};

class Picker
: public Control<Picker, _CXXCONTROL(UIPickerControl), IPickerControl>
{
public:
    
    typedef PickerIndexPath IndexPath;
    
    Picker()
    {
        PASS;
    }
    
    void reload(uint idx = -1)
    {
        if (idx == -1)
            [this->_self reloadAllComponents];
        else
            [this->_self reloadComponent:idx];
    }
    
    virtual void clear()
    {
        _sections.clear();
    }
    
    virtual void add(PickerSection* sec)
    {
        _sections.push_back(sec);
        sec->grab();
    }
    
    virtual PickerSection& at(uint idx)
    {
        return *_sections[idx];
    }
    
    virtual PickerItem* makeitem(IndexPath const&) const
    {
        return nil;
    }
    
    void show_indicator(bool val)
    {
        this->_self.pickerView.showsSelectionIndicator = val;
    }
    
    virtual uint count_components() const
    {
        return _sections.size();
    }
    
protected:
    
    core::refpointer_vector<PickerSection> _sections;
    
};

template <typename itemT = PickerItem>
class PickerControl
: public Picker
{
public:
    
    PickerControl()
    {
        PASS;
    }
    
    ~PickerControl()
    {
        PASS;
    }
    
    virtual PickerItem* makeitem(IndexPath const&) const
    {
        return new itemT;
    }
    
};

class DrumPicker
: public Control<DrumPicker, _CXXCONTROL(UIDrumPickerControl)>
{
public:
    
    DrumPicker()
    {
        PASS;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
