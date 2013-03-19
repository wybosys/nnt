
# ifndef __NNT_UIKIT_ANNUALRING_F1E77F2FE460475BA722093779950FBF_H_INCLUDED
# define __NNT_UIKIT_ANNUALRING_F1E77F2FE460475BA722093779950FBF_H_INCLUDED

# import "UIControl+NNT.h"
# import "UIItemView.h"

NNT_BEGIN_HEADER_OBJC

@interface UIAnnualRingSingle : NNTUIView <UIItemsDatasource> {
    real _length, _radius;
    UIColor* _ringColor;
    WCGFill* _ringFill;
    CGShadow* _ringShadow;
    UIItemsContainer* _items;
    real _startAngle, _offAngle, _sweepAngle;
    real _innerRadius, _outterRadius;
    CGPoint _point;
    bool _clockwise;
}

@property (nonatomic, assign) real length, radius;
@property (retain) UIColor* ringColor;
@property (retain) WCGFill* ringFill;
@property (retain) CGShadow* ringShadow;
@property (nonatomic, readonly) UIItemsContainer* items;
@property (nonatomic, assign) real startAngle, sweepAngle;
@property (nonatomic, assign) real innerRadius, outterRadius;
@property (nonatomic, assign) bool clockwise;

- (bool)hitTest:(CGPoint)pt;
- (void)relayout:(BOOL)animated;
- (UIItemView*)hitTestFromAngle:(real)from toAngle:(real)to;
- (real)currentAngle;

@end

_CXXVIEW_DECL_BEGIN(UIAnnualRingSingle)
_CXXVIEW_DECL_END

@interface UIAnnualRingControl : NNTUIControl {
    NSMutableArray* _rings;
}

//! add a ring with parameter.
- (UIAnnualRingSingle*)addRingWithLength:(real)length radius:(real)radius;

//! add a ring object.
- (void)addRing:(UIAnnualRingSingle*)ring;

//! remove a ring.
- (void)removeRing:(UIAnnualRingSingle*)ring;

//! remove a ring at index.
- (void)removeRingAtIndex:(NSUInteger)idx;

//! count.
- (NSUInteger)count;

//! ring at index.
- (UIAnnualRingSingle*)ringAtIndex:(NSUInteger)idx;

@end

_CXXVIEW_DECL(UIAnnualRingControl);

NNT_EXTERN signal_t kSignalRingRotated;
NNT_EXTERN signal_t kSignalContentClicked;
NNT_EXTERN signal_t kSignalItemLayoutted;
NNT_EXTERN signal_t kSignalItemsLayoutted;
NNT_EXTERN signal_t kSignalItemInserted;
NNT_EXTERN signal_t kSignalItemRemoving;
NNT_EXTERN signal_t kSignalItemRemoved;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class IAnnualRingSingle
: public IView
{
    
};

class IAnnualRing
: public IControl
{
    
};

class AnnualRingSingle
: public View<
AnnualRingSingle,
_CXXVIEW(UIAnnualRingSingle),
IAnnualRingSingle
>,
public tpl::ItemsDatasource<AnnualRingSingle>
{
    typedef View<
    AnnualRingSingle,
    _CXXVIEW(UIAnnualRingSingle),
    IAnnualRingSingle
    > super;
    
public:
    
    AnnualRingSingle()
    {
        PASS;
    }
    
    AnnualRingSingle(UIAnnualRingSingle* r)
    : super((objc_type*)r, false)
    {
        PASS;
    }
    
    void layout_subviews()
    {
        PASS;
    }
    
    void set_ring(Color const& cor)
    {
        this->_self.ringColor = cor;
    }
    
    operator UIItemsContainer* () const
    {
        return (UIItemsContainer*)this->_self.items;
    }
    
    void relayout(bool animated = ui::animate)
    {
        [this->_self relayout:animated];
    }
    
    void set_ring(cg::Shadow const& sd)
    {
        this->_self.ringShadow = sd;
    }
    
    void set_ring(cg::Fill const& fl)
    {
        this->_self.ringFill = fl;
    }
    
    void set_length(real val)
    {
        this->_self.length = val;
    }
    
    real length() const
    {
        return this->_self.length;
    }
    
    void set_radius(real val)
    {
        this->_self.radius = val;
    }
    
    real radius() const
    {
        return this->_self.radius;
    }
    
    void set_start(cg::Angle const& val)
    {
        this->_self.startAngle = val;
    }
    
    void set_sweep(cg::Angle const& val)
    {
        this->_self.sweepAngle = val;
    }
    
    cg::Angle start_angle() const
    {
        return cg::Angle::Rad(this->_self.startAngle);
    }
    
    void set_radius_inner(real val)
    {
        this->_self.innerRadius = val;
    }
    
    void set_radius_outter(real val)
    {
        this->_self.outterRadius = val;
    }
    
    void set_clockwise(bool val)
    {
        this->_self.clockwise = val;
    }
    
    template <typename uiT>
    uiT* find(cg::Angle const& from, cg::Angle const& to)
    {
        UIItemView* item = [this->_self hitTestFromAngle:from.rad() toAngle:to.rad()];
        return (uiT*)[item object];
    }
    
};

class AnnualRing
: public Control<AnnualRing, _CXXVIEW(UIAnnualRingControl), IAnnualRing>
{
public:
    
    AnnualRing()
    {
        PASS;
    }
    
    UIAnnualRingSingle* add(real length, real radius)
    {
        return [this->_self addRingWithLength:length radius:radius];
    }
    
    void add(AnnualRingSingle& ringbar)
    {
        [this->_self addRing:ringbar];
    }
    
    void remove(uint idx)
    {
        [this->_self removeRingAtIndex:idx];
    }
    
    void remove(AnnualRingSingle const& ringbar)
    {
        [this->_self removeRing:ringbar];
    }
    
    usize count() const
    {
        return [this->_self count];
    }
    
    UIAnnualRingSingle* at(uint idx) const
    {
        return [this->_self ringAtIndex:idx];
    }
    
    template <typename T>
    T& at(uint idx) const
    {
        UIAnnualRingSingle* rs = at(idx);
        return *(T*)[rs object];
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
