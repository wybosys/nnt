
# ifndef __WSI_UIKIT_UIEXPOSEHORCONTROL_1C88961625BB4D6E8E2494B79D30D722_H_INCLUDED
# define __WSI_UIKIT_UIEXPOSEHORCONTROL_1C88961625BB4D6E8E2494B79D30D722_H_INCLUDED

# import "UIScrollView+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(UIGridView);

@interface UIExposeControl : WSIUIScrollView <UIScrollViewDelegate> {
    
    //! grid view.
    UIGridView *_gridView;
    
    //! center. default is YES.
    BOOL _alignCenter;
    
    //! preferred count.
    real _prefferedCount;
    
    //! margin.
    CGPadding _itemPadding;
    
    //! current item.
    UIGridViewItem* _current;
    
}

@property (nonatomic, readonly)   UIGridView *gridView;
@property (nonatomic, assign)     NSUInteger count;
@property (nonatomic, assign)     real prefferedCount;
@property (nonatomic, assign)     BOOL alignCenter;
@property (nonatomic, assign)     CGPadding itemPadding;
@property (nonatomic, readonly, assign)   UIGridViewItem* current;

//! add item.
- (id)addItem:(UIView*)view;
- (id)addItem:(UIView*)view updateLayout:(bool)up;

//! find item.
- (UIGridViewItem*)itemAt:(NSUInteger)idx;
- (UIView*)contentAt:(NSUInteger)idx;

//! index of item.
- (NSUInteger)indexOfItem:(UIGridViewItem*)item;

//! clear.
- (void)clear;

//! best size.
- (CGSize)bestSizeForItem;

//! relayout items.
- (void)relayoutItems;

@end

@interface UIExposeHorControl : UIExposeControl

//! init with frame.
- (id)initWithFrame:(CGRect)frame;
- (id)initWithFrame:(CGRect)frame count:(NSUInteger)count;

//! scroll to item.
- (void)scrollToItem:(CGPoint*)pt;
- (void)scrollToItemByIndex:(NSUInteger)idx;

@end

@interface UIExposeVecControl : UIExposeControl 

//! init with frame.
- (id)initWithFrame:(CGRect)frame;
- (id)initWithFrame:(CGRect)frame count:(NSUInteger)count;

//! scroll to item.
- (void)scrollToItem:(CGPoint*)pt;
- (void)scrollToItemByIndex:(NSUInteger)idx;

@end

_CXXCONTROL_DECL(UIExposeHorControl);
_CXXCONTROL_DECL(UIExposeVecControl);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "UIScrollView+WSI.h"
# include "UIGridView.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

template <typename implT, typename exposeT>
class Expose
: public ScrollView<implT, exposeT>
{
public:
    
    typedef GridItem<> item_type;
    
    Expose()
    : grid(this->_self.gridView)
    {
        PASS;
    }
    
    void set_aligncenter(bool val)
    {
        this->_self.alignCenter = val; 
    }
    
    bool aligncenter() const
    {
        return this->_self.alignCenter;
    }
    
    template <typename conT>
    void add_items(conT const& items)
    {        
        this->_self.count = this->_self.count + items.size();
        
        for (typename conT::const_iterator each = items.begin();
             each != items.end();
             ++each)
        {
            wtl::const_pointer<typename conT::value_type> ptr(*each);
            
            UIView* item = *ptr;                  
            
            [this->_self addItem:item updateLayout:NO];
        }
        
        [this->_self updateLayout];
    }
    
    template <typename viewT>
    void add_item(viewT const& v)
    {
        wtl::const_pointer<viewT> ptr(v);
        [this->_self addItem:*ptr];
    }
    
    void set_count(uint cnt)
    {
        this->_self.count = cnt;
    }
    
    uint count() const
    {
        return this->_self.count;
    }
    
    void set_preffered_count(real cnt)
    {
        this->_self.prefferedCount = cnt;
    }
    
    real preffered_count() const
    {
        return this->_self.prefferedCount;
    }
    
    void scroll_to(CGPoint const& pt)
    {
        CGPoint tpt = pt;
        [this->_self scrollToItem:&tpt];
    }
    
    void scroll_to(CGPoint& pt)
    {
        [this->_self scrollToItem:&pt];
    }
    
    void scroll_to(uint idx)
    {
        [this->_self scrollToItemByIndex:idx];
    }
    
    item_type item_at(uint idx) const
    {
        item_type::objc_type* item = (item_type::objc_type*)[this->_self itemAt:idx];
        return item_type(item);
    }
    
    item_type current() const
    {
        item_type::objc_type* item = (item_type::objc_type*)this->_self.current;
        return item_type(item);
    }
    
    template <typename itemT>
    uint index_of(itemT const& item) const
    {
        wtl::const_pointer<itemT> ptr(item);
        return [this->_self indexOfItem:*ptr];
    }
    
    void clear()
    {
        [this->_self clear];
    }
    
    CGSize best_size() const
    {
        return [this->_self bestSizeForItem];
    }
    
    void relayout_items()
    {
        [this->_self relayoutItems];
    }
    
    Grid grid;
};

class HorExpose
: public Expose<HorExpose,
_CXXCONTROL(UIExposeHorControl)
>
{
    
};

class VecExpose
: public Expose<VecExpose,
_CXXCONTROL(UIExposeVecControl)
>
{
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif