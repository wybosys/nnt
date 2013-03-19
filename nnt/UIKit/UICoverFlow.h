
# ifndef __NNT_UIKIT_COVERFLOW_922B0AC7F4274193BF6E9E1B842FA5AB_H_INCLUDED
# define __NNT_UIKIT_COVERFLOW_922B0AC7F4274193BF6E9E1B842FA5AB_H_INCLUDED

# import "UIView+NNT.h"
# import "UIItemView.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(UICoverFlow);
NNTDECL_EXTERN_CLASS(UICoverFlowItem);

NNT_EXTERN signal_t kSignalSelectChanged;

@protocol UICoverFlowDelegate <NSObject>
@optional

- (void)coverFlow:(UICoverFlow*)flow selectionDidChange:(int)index;

@end

NNTDECL_PRIVATE_HEAD(UICoverFlow);

@interface UICoverFlow : NNTUIView {
    
    id <UICoverFlowDelegate> _delegate;
        
    //! cover spacing. default is 40.
    real _coverSpacing;
    
    //! center cover offset. default is 70.
    real _centerCoverOffset;
    
    //! side cover angle. default is .21 in rad.
    real _coverAngle;
    
    //! side cover angle step. default is .0f in rad.
    real _coverAngleStep;
    
    //! side cover zposition step. default is 1.
    real _coverZPositionStep;
    
    //! side cover zposition. default is -50.
    real _coverZPosition;
    
    //! cover buffer. default is 10.
    uint _maxCoversOnScreen;
    
    //! number of images.
    uint _numberOfCovers;
    
    //! padding. default is .1 .1 .1 .1 in percent.
    CGPadding _padding;
        
    //! real item slant value, default m34 = -0.005.
    real _coverSlant;
    
    //! preferred width & height. default is 0.
    real _preferredWidth, _preferredHeight;
    
    //! item scale. default is 1.
    real _coverScale;
    
    //! scale to fit. default is NO.
    BOOL _scaleToFit;
    
    //! center offset. default is 0.
    CGPoint _centerOffset;
        
    //! items.
    UIItemsContainer* _items;
    
    NNTDECL_PRIVATE(UICoverFlow);
}

@property (nonatomic, assign) id <UICoverFlowDelegate> delegate;
@property (nonatomic, assign) real coverSpacing, centerCoverOffset, coverAngle, coverAngleStep, coverZPositionStep, coverZPosition;
@property (nonatomic, assign) real preferredWidth, preferredHeight;
@property (nonatomic, assign) real coverScale;
@property (nonatomic, assign) uint maxCoversOnScreen, numberOfCovers;
@property (nonatomic, assign) CGPadding padding;
@property (nonatomic, assign) real coverSlant;
@property (nonatomic, readonly) BOOL isCoverDragging;
@property (nonatomic, assign) BOOL scaleToFit;
@property (nonatomic, assign) CGPoint centerOffset;
@property (nonatomic, retain) UIItemsContainer* items;

//! set selected cover by id.
- (void)setSelectedCoverById:(int)newSelectedCover;

//! center selected cover.
- (void)centerOnSelectedCover:(BOOL)animated;

//! reload data.
- (void)reloadData;

//! relayout data.
- (void)relayoutData:(BOOL)animated;

@end

//! item selected changed.
NNT_EXTERN signal_t kSignalSelectChanged;

_CXXVIEW_DECL(UICoverFlow);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

NNT_BEGIN_NS(tpl)

class ICoverflow
: public IView
{
public:
  
    
};

template <typename implT,
typename objcT = _CXXVIEW(UICoverFlow),
typename objcI = ICoverflow>
class Coverflow
: public View<implT, objcT, objcI>
{
public:
    
    void set_spacing(real val)
    {
        this->_self.coverSpacing = val;
    }
    
    void set_offset(real val)
    {
        this->_self.centerCoverOffset = val;
    }
    
    void set_angle(cg::Angle const& val)
    {
        this->_self.coverAngle = val.rad();
    }
    
    void set_anglestep(cg::Angle const& val)
    {
        this->_self.coverAngleStep = val.rad();
    }
    
    void set_zposition(real val)
    {
        this->_self.coverZPosition = val;
    }
    
    void set_zstep(real val)
    {
        this->_self.coverZPositionStep = val;
    }
    
    void set_preferred(cg::Size const& sz)
    {
        this->_self.preferredWidth = sz.width();
        this->_self.preferredHeight = sz.height();
    }
    
    void set_preferred_width(real val)
    {
        this->_self.preferredWidth = val;
    }
    
    void set_preferred_height(real val)
    {
        this->_self.preferredHeight = val;
    }
    
    void set_scale(real val)
    {
        this->_self.coverScale = val;
    }
    
    void set_maxonscreen(uint val)
    {
        this->_self.maxCoversOnScreen = val;
    }
    
    void set_padding(cg::Padding const& val)
    {
        this->_self.padding = val;
    }
    
    void set_slant(real val)
    {
        this->_self.coverSlant = val;
    }
    
    void enable_scaletofit(bool val)
    {
        this->_self.scaleToFit = val;
    }
    
    void set_offset(cg::Point const& pt)
    {
        this->_self.centerOffset = pt;
    }
    
};

NNT_END_NS

class Coverflow
: public tpl::Coverflow<Coverflow>
{
public:
    
    Coverflow()
    {
        PASS;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
