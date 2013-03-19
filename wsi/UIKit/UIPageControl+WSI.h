
# ifndef __WSI_UIKIT_UIPAGECONTROL_E0A583288B5241AFBEF61F61DD81F690_H_INCLUDED
# define __WSI_UIKIT_UIPAGECONTROL_E0A583288B5241AFBEF61F61DD81F690_H_INCLUDED

//! thanks to DDPageControl, https://github.com/ddeville/DDPageControl
# import "UIControl+WSI.h"

WSI_BEGIN_HEADER_OBJC

extern signal_t kSignalSelectChanged;
extern signal_t kSignalViewClicked;

enum {
	UIPageControlTypeOnFullOffFull		= 0,
	UIPageControlTypeOnFullOffEmpty		= 1,
	UIPageControlTypeOnEmptyOffFull		= 2,
	UIPageControlTypeOnEmptyOffEmpty	= 3,
};
typedef uint UIPageControlType;

@interface WSIUIPageControl : WSIUIView {
    
    //! page number.
    NSInteger _numberOfPages;
    
    //! current page no.
	NSInteger _currentPage;
    
    //! select color.
    UIColor *_selectedColor;
    
    //! normal color.
    UIColor *_normalColor;
}

//! pages number control.
@property (assign) NSInteger numberOfPages, currentPage;

//! colors.
@property (nonatomic, retain) UIColor *selectedColor, *normalColor;

//! hide when number < 2, default is YES.
@property (nonatomic) BOOL hidesForSinglePage;

//! other.
@property (nonatomic) BOOL defersCurrentPageDisplay;

//! indicator.
@property (nonatomic) CGFloat indicatorDiameter;
@property (nonatomic) CGFloat indicatorSpace;

//! type.
@property (nonatomic) UIPageControlType type;

//! init.
- (id)initWithType:(UIPageControlType)theType;
- (id)initWithFrame:(CGRect)frame;

// refresh.
- (void)updateCurrentPageDisplay;
- (CGSize)sizeForNumberOfPages:(NSInteger)pageCount;

//! change current page, no signal.
- (void)changeCurrentPage:(NSInteger)idx;

//! get stage rect.
- (CGRect)stageRect;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "UIControl+WSI.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class PageControl
: public Control<PageControl, WSIUIPageControl>
{
    typedef Control<PageControl, WSIUIPageControl> super;
    
public:
    
    PageControl()
    {
        PASS;
    }
    
    void set_count(uint val)
    {
        this->_self.numberOfPages = val;
    }
    
    uint count() const
    {
        return this->_self.numberOfPages;
    }
    
    void set_current(uint val)
    {
        this->_self.currentPage = val;
    }
    
    uint current() const
    {
        return this->_self.currentPage;
    }
    
    void set_singlehide(bool val)
    {
        this->_self.hidesForSinglePage = val;
    }
    
    cg::Rect stage_region() const
    {
        return [this->_self stageRect];
    }
    
    void set_diameter(real val)
    {
        this->_self.indicatorDiameter = val;
    }
    
    real diameter() const
    {
        return this->_self.indicatorDiameter;
    }
    
    void set_space(real val)
    {
        this->_self.indicatorSpace = val;
    }
    
    real space() const
    {
        return this->_self.indicatorSpace;
    }
    
    void set_selected(ui::Color const& cor)
    {
        this->_self.selectedColor = cor;
    }
    
    void set_normal(ui::Color const& cor)
    {
        this->_self.normalColor = cor;
    }
        
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif